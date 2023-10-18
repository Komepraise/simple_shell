#include "shell.h"

int check_file(char *full_path);

/**
 * find_prog - find a program in path
 * @data: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */
int find_prog(program_data *data)
{
	int x = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_coc(str_dup("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);/* search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (x = 0; directories[x]; x++)
	{/* appends the function_name to path */
		directories[x] = str_coc(directories[x], data->tokens[0]);
		ret_code = check_file(directories[x]);
		if (ret_code == 0 || ret_code == 126)
		{/* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_dup(directories[x]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - tokenize the path in directories
 * @data: a pointer to the program's data
 * Return: array of path directories
 */
char **tokenize_path(program_data *data)
{
	int x = 0;
	int counter_dir = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = get_env_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = str_dup(PATH);

	/* find the number of directories in the PATH */
	for (x = 0; PATH[x]; x++)
	{
		if (PATH[x] == ':')
			counter_dir++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_dir);

	/*tokenize and duplicate each token of path*/
	x = 0;
	tokens[x] = str_dup(_strtok(PATH, ":"));
	while (tokens[x++])
	{
		tokens[x] = str_dup(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */
int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exist the file*/
	errno = 127;
	return (127);
}
