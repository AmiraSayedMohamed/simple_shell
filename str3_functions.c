#include "main.h"

/**
 * _strncpy - a functin that copy a string but using limited character
 * @src: the source string
 * @dest: the destination string to be copies
 * @amount: the amount of bytes that maximally used
 * Return: the string
 */

char *_strncpy(const char *src, char *dest, int amount)
{
	int i;

	for (i = 0; i < amount && src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strncat - concatenate two string with limited character
 * @dest: the first string
 * @src: the second string
 * @n: the amount of byted that maximally used
 * Return: the concatenated string
 */

void _strncat(char *dest, const char *src, int n)
{
	int dest_len = 0;

	while (dest[dest_len] != '\0')
		dest_len++;
	int i = 0;

	while (src[i] != '\0' && i < n - dest_len - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
}

/**
 * _strchr - a function that locates a character in a string
 * @str: string to parsed
 * @target: the character to look for
 *
 * Return: (s) a pointer to the memory area s
 */

const char *_strchr(const char *str, char target)
{
	while (*str != '\0')
	{
		if (*str == target)
			return (str);
		str++;
	}
	return (NULL);
}
