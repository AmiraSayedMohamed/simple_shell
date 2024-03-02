#include "main.h"

/**
 * _strlen - returns the length of he string
 * @input_string: the string whose length to check
 * Return: integer length of string
 */

int _strlen(const char *input_string)
{
	int length = 0;

	while (input_string[length] != '\0')
		length++;
	return (length);
}

/**
 * _strcmp - a functionto compare two string
 * @str1: the first string
 * @str2: the second string
 *  Return: negative if s1 < s2, positive of s1 > s2, zero if s1 == s2
 */


int _strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			return ((*str1 < *str2) ? -1 : 1);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

/**
 * *_strcat - a function that concatenate two string
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */

char *_strcat(char *dest, const char *src)
{
	char *original_dest = dest;

	while (*dest != '\0')
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return (original_dest);
}

/**
 * starts_with - checks if str1 starts with str2
 * @str1: string to search
 * @str2: the substring to find
 *
 * Return: address of next char of haystack of NULL
 */

char *starts_with(const char *str1, const char *str2)
{
	while (*str2 != '\0')
	{
		if (*str2 != *str1)
			return (NULL);
		str2++;
		str1++;
	}
	return ((char *)str1);
}
