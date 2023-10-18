#include "shell.h"

/**
 * def_list - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/

int def_list(program_data *data)
{
	int iterator;
	def options[] = {
		{"exit", def_exit},
		{"help", def_help},
		{"cd", def_cd},
		{"alias", def_alias},
		{"env", def_env},
		{"setenv", def_set_env},
		{"unsetenv", def_unset_env},
		{NULL, NULL}
	};

	for (iterator = 0; options[iterator].def != NULL; iterator++)
	{
		if (str_comp(options[iterator].def, data->command_name, 0))
		{
			return (options[iterator].function(data));
		}
	}
	return (-1);
}
