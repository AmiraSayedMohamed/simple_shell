#include "main.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments.
 * Return: -2 if exit is requested, 1 for illegal exit number, else -2
 */
int _myexit(info_t *info)
{
	int exit_status;

	if (info->args[1])
	{
		exit_status = _erratoi(info->args[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_err_puts(info->args[1]);
			_err_putchar('\n');
			return (1);
		}
		info->err_num = exit_status;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *new_dir, buffer[1024];
	int chdir_result;

	if (!info->args[1])
		new_dir = _getenv(info, "HOME=");
	else if (_strcmp(info->args[1], "-") == 0)
		new_dir = _getenv(info, "OLDPWD=");
	else
		new_dir = info->args[1];

	if (!new_dir)
		chdir_result = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
	else
		chdir_result = chdir(new_dir);

	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_err_puts(new_dir), _err_putchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - displays a help message
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	(void)info;
	_puts("help call works. Function not yet implemented \n");
	return (0);
}

