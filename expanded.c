#include "shell.h"

/**
 * exp_variables - exp variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void exp_variables(program_data *data)
{
	int x, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	add_buf(line, data->input_line);
	for (x = 0; line[x]; x++)
		if (line[x] == '#')
			line[x--] = '\0';
		else if (line[x] == '$' && line[x + 1] == '?')
		{
			line[x] = '\0';
			long_to_string(errno, expansion, 10);
			add_buf(line, expansion);
			add_buf(line, data->input_line + x + 2);
		}
		else if (line[x] == '$' && line[x + 1] == '$')
		{
			line[x] = '\0';
			long_to_string(getpid(), expansion, 10);
			add_buf(line, expansion);
			add_buf(line, data->input_line + x + 2);
		}
		else if (line[x] == '$' && (line[x + 1] == ' ' || line[x + 1] == '\0'))
			continue;
		else if (line[x] == '$')
		{
			for (j = 1; line[x + j] && line[x + j] != ' '; j++)
				expansion[j - 1] = line[x + j];
			temp = get_env_key(expansion, data);
			line[x] = '\0', expansion[0] = '\0';
			add_buf(expansion, line + x + j);
			temp ? add_buf(line, temp) : 1;
			add_buf(line, expansion);
		}
	if (!str_comp(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_dup(line);
	}
}

/**
 * exp_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void exp_alias(program_data *data)
{
	int x, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	add_buf(line, data->input_line);

	for (x = 0; line[x]; x++)
	{
		for (j = 0; line[x + j] && line[x + j] != ' '; j++)
			expansion[j] = line[x + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			add_buf(expansion, line + x + j);
			line[x] = '\0';
			add_buf(line, temp);
			line[str_len(line)] = '\0';
			add_buf(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_dup(line);
	}
}

/**
 * add_buf - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int add_buf(char *buffer, char *str_to_add)
{
	int length, x;

	length = str_len(buffer);
	for (x = 0; str_to_add[x]; x++)
	{
		buffer[length + x] = str_to_add[x];
	}
	buffer[length + x] = '\0';
	return (length + x);
}
