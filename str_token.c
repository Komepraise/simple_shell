#include "shell.h"
/**
 * _strtok - separates strings with delimiters
 * @line: It´s pointer to array we receive in getline.
 * @delim: It´s characters we mark off string in parts.
 * Return: A pointer to the created token
*/
char *_strtok(char *line, char *delim)
{
	int x;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (x = 0; delim[x] != '\0'; x++)
		{
			if (*str == delim[x])
			break;
		}
		if (delim[x] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (x = 0; delim[x] != '\0'; x++)
		{
			if (*str == delim[x])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
