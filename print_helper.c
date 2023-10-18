#include "shell.h"

/**
 * _print - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the numb of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_len(string)));
}
/**
 *  _prints - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the numb of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int  _prints(char *string)
{
	return (write(STDERR_FILENO, string, str_len(string)));
}

/**
 * _print_err - writes a array of chars in the standart error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the numb of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print_err(int errorcode, program_data *data)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		 _prints(data->program_name);
		 _prints(": ");
		 _prints(n_as_string);
		 _prints(": ");
		 _prints(data->tokens[0]);
		if (errorcode == 2)
			 _prints(": Illegal numb: ");
		else
			 _prints(": can't cd to ");
		 _prints(data->tokens[1]);
		 _prints("\n");
	}
	else if (errorcode == 127)
	{
		 _prints(data->program_name);
		 _prints(": ");
		 _prints(n_as_string);
		 _prints(": ");
		 _prints(data->command_name);
		 _prints(": not found\n");
	}
	else if (errorcode == 126)
	{
		 _prints(data->program_name);
		 _prints(": ");
		 _prints(n_as_string);
		 _prints(": ");
		 _prints(data->command_name);
		 _prints(": Permission denied\n");
	}
	return (0);
}
