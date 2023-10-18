#include "shell.h"

/**
 *  get_env_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char * get_env_key(char *key, program_data *data)
{
	int x, key_len = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	key_len = str_len(key);

	for (x = 0; data->env[x]; x++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_comp(key, data->env[x], key_len) &&
		 data->env[x][key_len] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->env[x] + key_len + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);
}

/**
 * ste_env_key - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int ste_env_key(char *key, char *value, program_data *data)
{
	int x, key_len = 0, is_new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the leng of the variable requested */
	key_len = str_len(key);

	for (x = 0; data->env[x]; x++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_comp(key, data->env[x], key_len) &&
		 data->env[x][key_len] == '=')
		{/* If key already exists */
			is_new_key = 0;
			/* free the entire variable, it is new created below */
			free(data->env[x]);
			break;
		}
	}
	/* make an string of the form key=value */
	data->env[x] = str_coc(str_dup(key), "=");
	data->env[x] = str_coc(data->env[x], value);

	if (is_new_key)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		data->env[x + 1] = NULL;
	}
	return (0);
}

/**
 * rmv_env_key - remove a key from the environment
 * @key: the key to remove
 * @data: the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int rmv_env_key(char *key, program_data *data)
{
	int x, key_len = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains the leng of the variable requested */
	key_len = str_len(key);

	for (x = 0; data->env[x]; x++)
	{/* iterates through the environ and checks for coincidences */
		if (str_comp(key, data->env[x], key_len) &&
		 data->env[x][key_len] == '=')
		{/* if key already exists, remove them */
			free(data->env[x]);

			/* move the others keys one position down */
			x++;
			for (; data->env[x]; x++)
			{
				data->env[x - 1] = data->env[x];
			}
			/* put the NULL value at the new end of the list */
			data->env[x - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 *_print_env - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void _print_env(program_data *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
