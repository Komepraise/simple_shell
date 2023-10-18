#include "shell.h"

/**
 * str_len - returns the length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */
int str_len(char *string)
{
	int len = 0;

	if (string == NULL)
		return (0);

	while (string[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * str_dup - duplicates an string
 * @string: String to be copied
 * Return: pointer to the array
 */
char *str_dup(char *string)
{
	char *result;
	int len, x;

	if (string == NULL)
		return (NULL);

	len = str_len(string) + 1;

	result = malloc(sizeof(char) * len);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (x = 0; x < len ; x++)
	{
		result[x] = string[x];
	}

	return (result);
}

/**
 * str_comp - Compare two strings
 * @string1: String one, or the shorter
 * @string2: String two, or the longer
 * @num: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equals,0 if the strings are different
 */
int str_comp(char *string1, char *string2, int num)
{
	int iterator;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (num == 0) /* infinite longitud */
	{
		if (str_len(string1) != str_len(string2))
			return (0);
		for (iterator = 0; string1[iterator]; iterator++)
		{
			if (string1[iterator] != string2[iterator])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (iterator = 0; iterator < num ; iterator++)
		{
			if (string1[iterator] != string2[iterator])
			return (0);
		}
		return (1);
	}
}

/**
 * str_coc - concatenates two strings.
 * @string1: String to be concatenated
 * @string2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *str_coc(char *string1, char *string2)
{
	char *result;
	int len1 = 0, len2 = 0;

	if (string1 == NULL)
		string1 = "";
	len1 = str_len(string1);

	if (string2 == NULL)
		string2 = "";
	len2 = str_len(string2);

	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of string1 */
	for (len1 = 0; string1[len1] != '\0'; len1++)
		result[len1] = string1[len1];
	free(string1);

	/* copy of string2 */
	for (len2 = 0; string2[len2] != '\0'; len2++)
	{
		result[len1] = string2[len2];
		len1++;
	}

	result[len1] = '\0';
	return (result);
}


/**
 * str_reverse - reverses a string.
 *
 * @string: pointer to string.
 * Return: void.
 */
void str_rev(char *string)
{

	int x = 0, len = str_len(string) - 1;
	char hold;

	while (x < len)
	{
		hold = string[x];
		string[x++] = string[len];
		string[len--] = hold;
	}
}
