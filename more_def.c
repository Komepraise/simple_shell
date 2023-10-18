#include "shell.h"

/**
 * def_exit - exit of the program with the status
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int def_exit(program_data *data)
{
	int x;

	if (data->tokens[1] != NULL)
	{/*if exists arg for exit, check if is a number*/
		for (x = 0; data->tokens[1][x]; x++)
			if ((data->tokens[1][x] < '0' || data->tokens[1][x] > '9')
				&& data->tokens[1][x] != '+')
			{/*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * def_cd - change the current directory
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int def_cd(program_data *data)
{
	char *dir_home =  get_env_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_comp(data->tokens[1], "-", 0))
		{
			dir_old =  get_env_key("OLDPWD", data);
			if (dir_old)
				error_code = set__act_dir(data, dir_old);
			_print( get_env_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set__act_dir(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set__act_dir(data, dir_home));
	}
	return (0);
}

/**
 * set_act_dir - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set__act_dir(program_data *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_comp(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		ste_env_key("PWD", new_dir, data);
	}
	ste_env_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * def_help - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int def_help(program_data *data)
{
	int x, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (x = 0; mensajes[x]; x++)
	{
		/*print the length of string */
		length = str_len(data->tokens[1]);
		if (str_comp(data->tokens[1], mensajes[x], length))
		{
			_print(mensajes[x] + length + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * def_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int def_alias(program_data *data)
{
	int x = 0;

	/* if there are no arguments, print all environment */
	if (data->tokens[1] == NULL)
		return (pnt_alias(data, NULL));

	while (data->tokens[++x])
	{/* if there are arguments, set or print each env variable*/
		if (cnt_char(data->tokens[x], "="))
			set_alias(data->tokens[x], data);
		else
			pnt_alias(data, data->tokens[x]);
	}

	return (0);
}
