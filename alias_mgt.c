#include "shell.h"

/**
 * pnt_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int pnt_alias(program_data *data, char *alias)
{
	int y, x, alias_len;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_len = str_len(alias);
		for (y = 0; data->alias_list[y]; y++)
		{
			if (!alias || (str_comp(data->alias_list[y], alias, alias_len)
				&&	data->alias_list[y][alias_len] == '='))
			{
				for (x = 0; data->alias_list[y][x]; x++)
				{
					buffer[x] = data->alias_list[y][x];
					if (data->alias_list[y][x] == '=')
						break;
				}
				buffer[x + 1] = '\0';
				add_buf(buffer, "'");
				add_buf(buffer, data->alias_list[y] + x + 1);
				add_buf(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_alias(program_data *data, char *name)
{
	int y, alias_len;

	/* validate the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_len = str_len(name);

	for (y = 0; data->alias_list[y]; y++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_comp(name, data->alias_list[y], alias_len) &&
			data->alias_list[y][alias_len] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[y] + alias_len + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, program_data *data)
{

	int y, x;
	char buf[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (y = 0; alias_string[y]; y++)
		if (alias_string[y] != '=')
			buf[y] = alias_string[y];
		else
		{/* search if the value of the alias is another alias */
			temp = get_alias(data, alias_string + y + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (x = 0; data->alias_list[x]; x++)
		if (str_comp(buf, data->alias_list[x], y) &&
			data->alias_list[x][y] == '=')
		{/* if the alias alredy exist */
			free(data->alias_list[x]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		add_buf(buf, "=");
		add_buf(buf, temp);
		data->alias_list[x] = str_dup(buf);
	}
	else /* if the alias does not exist */
		data->alias_list[x] = str_dup(alias_string);
	return (0);
}
