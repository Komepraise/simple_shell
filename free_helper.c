#include "shell.h"

/**
 * free_recurrent_data - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void rel_rec_dat(program_data *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * rel_dat - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_all_data(program_data *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	rel_rec_dat(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void free_array_of_pointers(char **array)
{
	int x;
	
	if (array != NULL)
	{
		for (x = 0; array[x]; x++)
			free(array[x]);

		free(array);
		array = NULL;
	}
}
