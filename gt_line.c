#include "shell.h"

/**
* gt_line - read one line from the prompt.
* @data: structure of the program's data
*
* Return: reading counting bytes.
*/
int gt_line(program_data *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *comm_arr[10] = {NULL};
	static char opp_arr[10] = {'\0'};
	ssize_t bytes_read, y = 0;

	if (!comm_arr[0] || (opp_arr[0] == '&' && errno != 0) ||
		(opp_arr[0] == '|' && errno == 0))
	{
		for (y = 0; comm_arr[y]; y++)
		{
			free(comm_arr[y]);
			comm_arr[y] = NULL;
		}

		
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		y = 0;
		do {
			comm_arr[y] = str_dup(_strtok(y ? NULL : buff, "\n;"));
			y = logic_check(comm_arr, y, opp_arr);
		} while (comm_arr[y++]);
	}

	data->input_line = comm_arr[0];
	for (y = 0; comm_arr[y]; y++)
	{
		comm_arr[y] = comm_arr[y + 1];
		opp_arr[y] = opp_arr[y + 1];
	}

	return (str_len(data->input_line));
}


/**
* logic_check - checks and split for && and || operators
* @comm_arr: array of the commands.
* @y: index in the comm_arr to be checked
* @opp_arr: array of the logical operators for each previous command
*
* Return: index of the last command in the comm_arr.
*/
int logic_check(char *comm_arr[], int y, char opp_arr[])
{
	char *temp = NULL;
	int x;

	for (x = 0; comm_arr[y] != NULL  && comm_arr[y][x]; x++)
	{
		if (comm_arr[y][x] == '&' && comm_arr[y][x + 1] == '&')
		{
			temp = comm_arr[y];
			comm_arr[y][x] = '\0';
			comm_arr[y] = str_dup(comm_arr[y]);
			comm_arr[y + 1] = str_dup(temp + x + 2);
			y++;
			opp_arr[y] = '&';
			free(temp);
			x = 0;
		}
		if (comm_arr[y][x] == '|' && comm_arr[y][x + 1] == '|')
		{
			temp = comm_arr[y];
			comm_arr[y][x] = '\0';
			comm_arr[y] = str_dup(comm_arr[y]);
			comm_arr[y + 1] = str_dup(temp + x + 2);
			y++;
			opp_arr[y] = '|';
			free(temp);
			x = 0;
		}
	}
	return (y);
}
