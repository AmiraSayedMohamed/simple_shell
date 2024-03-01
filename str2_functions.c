#include "main.h"

/**
 * my_strcpy - copies a string
 * @dest: the destination
 * @src: source
 * Return: pointer to destination
 */

char *my_strcpy(char *dest, char *src)
{
	char *original_dest = dest;

	while ((*dest++ = *src++) != '\0')
		;
	return (original_dest);
}

/**
 * my_strdup - duplicate a string
 * @original: the string ti duplicated string
 *
 * Return: pointer to duplicated string
 */

char *my_strdup(const char *original)
{
	if (original == NULL)
		return (NULL);

	int length = 0;

	while (original[length] != '\0')
		length++;
	char *duplicate = (char *)malloc((length + 1) * sizeof(char));

	if (duplicate == NULL)
		return (NULL);
	for (int i = 0; i <= length; i++)
	{
		duplicate[i] = original[i];
	}
	return (duplicate);
}


/**
 * print_string - prints an input string
 * @str: the string to be print
 *
 * Return: Nothing
 */

void print_string(const char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
}

/**
 * _putchar - a functions that writes the character to stdout
 * @c: the character to print
 *
 * Return: 1 on success, -1 on error
 */

int _putchar(char c)
{
	static int j;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buffer, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buffer[j++] = c;
	return (j);
}

