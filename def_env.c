#include "shell.h"

/**
 * def_env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int def_env(program_data *data)
{
	int y;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		_print_env(data);
	else
	{
		for (y = 0; data->tokens[1][y]; y++)
		{/* checks if exists a char = */
			if (data->tokens[1][y] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				var_copy = str_dup(get_env_key(cpname, data));
				if (var_copy != NULL)
					ste_env_key(cpname, data->tokens[1] + y + 1, data);

				/* print the environ */
				_print_env(data);
				if (get_env_key(cpname, data) == NULL)
				{/* print the variable if it does not exist in the environ */
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{/* returns the old value of the var*/
					ste_env_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[y] = data->tokens[1][y];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * def_set_env - ..
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int def_set_env(program_data *data)
{
	/* validate args */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	ste_env_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * def_unset_env - ..
 * @data: struct for the program's data'
 * Return: ..
 */
int def_unset_env(program_data *data)
{
	/* validate args */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	rmv_env_key(data->tokens[1], data);

	return (0);
}
