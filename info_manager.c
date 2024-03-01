#include "main.h"

/**
 * init_info - Initializes the info_t struct
 * @info: Pointer to the info_t struct
 */
void init_info(info_t *info)
{
	info->argument = NULL;
	info->argument_vector = NULL;
	info->path = NULL;
	info->argument_count = 0;
}

/**
 * populate_info - Populates the info_t struct with provided arguments
 * @info: Pointer to the info_t struct
 * @arguments: Argument vector
 */
void populate_info(info_t *info, char **arguments)
{
	int i = 0;

	info->program_name = arguments[0];
	if (info->argument)
	{
		info->argument_vector = strtow(info->argument, " \t");
		if (!info->argument_vector)
		{
			info->argument_vector = malloc(sizeof(char *) * 2);
			if (info->argument_vector)
			{
				info->argument_vector[0] = _strdup(info->argument);
				info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; info->argument_vector && info->argument_vector[i]; i++)
			;
		info->argument_count = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * clear_info - Clears the info_t struct fields
 * @info: Pointer to the info_t struct
 * @clear_all: Boolean flag to indicate whether to clear all fields
 */
void clear_info(info_t *info, int clear_all)
{
	ffree(info->argument_vector);
	info->argument_vector = NULL;
	info->path = NULL;
	if (clear_all)
	{
		if (!info->command_buffer)
			free(info->argument);
		if (info->environment)
			free_list(&(info->environment));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environment_variables);
		info->environment_variables = NULL;
		bfree((void **)info->command_buffer);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}

