#include "main.h"

/**
 * _eputs - prints an input string to stderr
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *string)
{
	int index = 0;

	if (!string)
		return;
	while (string[index] != '\0')
	{
		_put_char_stderr(string[index]);
		index++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int buffer_index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || buffer_index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, buffer_index);
		buffer_index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[buffer_index++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int buffer_index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || buffer_index >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, buffer_index);
		buffer_index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[buffer_index++] = c;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @string: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int _putsfd(char *string, int fd)
{
	int count = 0;

	if (!string)
		return (0);
	while (*string)
	{
		count += _put_char_fd(*string++, fd);
	}
	return (count);
}

