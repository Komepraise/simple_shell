#include "shell.h"
/**
 * tokenize - this function separate the string using a designed delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(program_data *data)
{
	char *delimiter = " \t";
	int y, x, counter = 2, length;

	length = str_len(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (y = 0; data->input_line[y]; y++)
	{
		for (x = 0; delimiter[x]; x++)
		{
			if (data->input_line[y] == delimiter[x])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	y = 0;
	data->tokens[y] = str_dup(_strtok(data->input_line, delimiter));
	data->command_name = str_dup(data->tokens[0]);
	while (data->tokens[y++])
	{
		data->tokens[y] = str_dup(_strtok(NULL, delimiter));
	}
}
