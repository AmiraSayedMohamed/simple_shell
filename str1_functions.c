#include "main.h"

/**
 * get_string_length - returns the length of he string
 * @input_string: the string whose length to check
 * Return: integer length of string
 */

int get_string_length(const char *input_string)
{
	int length = 0;

	while (input_string[length] != '\0')
		length++;
	return (length);
}

/**
 * my_strcmp - a functionto compare two string
 * @str1: the first string
 * @str2: the second string
 *  Return: negative if s1 < s2, positive of s1 > s2, zero if s1 == s2
 */

int my_strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			return ((*str1 < *str2) ? -1 : -1);
		str1++;
		str2++;
	}
	return (0);
}

/**
 * my_strcat - a function that concatenate two string
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */

char *my_strcat(char *dest, const char *src)
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
 * start_with - checks if str1 starts with str2
 * @str1: string to search
 * @str2: the substring to find
 *
 * Return: address of next char of haystack of NULL
 */

char *start_with(const char *str1, const char *str2)
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
