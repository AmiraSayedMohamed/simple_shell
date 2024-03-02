#include "main.h"

/**
 * interactive - checks if the shell is in interactive mode
 * @info: Pointer to a struct address
 *
 * Return: (1) if in interactive mode, (0) otherwise
 */
int interactive(info_t *info)
{
	if (isatty(STDIN_FILENO))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * is_delim - function to check if a character is a delimiter
 * @c: the character we want to check
 * @delimiter: string of delimiters to compare with
 *
 * Return: (1) if character is a delimiter, (0) otherwise
 */
int is_delim(char c, const char *delimiter)
{
	while (*delimiter != '\0')
	{
		if (*delimiter == c)
		{
			return (1); /* character is a delimiter */
		}
		delimiter++;
	}
	return (0); /* character is not a delimeter */
}

/**
 * _isalpha - Checks if a character is alphabetical
 * @c: The character to check
 *
 * Return: (1) if c is alphabetical, (0) otherwise
 */
int _isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1); /* Return 1 for alphabetical character */
	}
	else
	{
		return (0); /* Return 0 for non-alphabetical character */
	}
}

/**
 * _atoi - Converts a string to an integer
 * @str: The string to be converted
 *
 * Return: The converted integer, or 0 if no number in the string
 */
int atoi(const char *str)
{
	int result = 0;
	int sign = 1; /* sign of the number 1 for positive, -1 for negative */

	/* Check for empty string */
	if (str == NULL || *str == '\0')
	{
		return (0);
	}

	/* Handle optional sign */
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}

	/* Convert the string to an integer */
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}

	return (result * sign);
}

