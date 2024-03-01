#include "main.h"

/**
 * _str_to_int - Converts a string to an integer
 * @str: The string to be converted
 *
 * Return: Converted number if successful, otherwise -1
 */
int _str_to_int(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error_msg - Prints an error message
 * @info: Structure containing parameter and return info
 * @error_msg: String containing specified error type
 */
void print_error_msg(info_t *info, char *error_msg)
{
	_eputs(info->fname);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_msg);
}

/**
 * print_decimal - Prints a decimal (integer) number (base 10)
 * @number: The number to print
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters printed
 */
int print_decimal(int number, int fd)
{
	int (*print_char)(char) = _put_char;
	int i, count = 0;
	unsigned int absolute_value, current_digit;

	if (fd == STDERR_FILENO)
		print_char = _put_char_stderr;
	if (number < 0)
	{
		absolute_value = -number;
		print_char('-');
		count++;
	}
	else
		absolute_value = number;
	current_digit = absolute_value;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			print_char('0' + current_digit / i);
			count++;
		}
		current_digit %= i;
	}

	print_char('0' + current_digit);
	count++;

	return (count);
}

/**
 * convert_to_string - Converts a number to a string
 * @num: Number to convert
 * @base: Base for conversion
 * @flags: Argument flags
 *
 * Return: Pointer to the converted string
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long value = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		value = -num;
		sign = '-';
	}

	digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = digits[value % base];
		value /= base;
	} while (value != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comment - Replaces the first instance of '#' with '\0'
 * @buf: Address of the string to modify
 */
void remove_comment(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
}

