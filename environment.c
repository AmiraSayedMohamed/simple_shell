#include "main.h"

/**
 * fetch_environment - returns a copy of the environment variables
 * @info: Structure containing relevant information.
 *
 * Return: Array of strings containing environment variables.
 */
char **fetch_environment(info_t *info)
{
	if (!info->environment || info->env_altered)
	{
		info->environment = list_to_strings(info->env);
		info->env_altered = 0;
	}

	return (info->environment);
}

/**
 * _delete_env_var - Remove an environment variable
 * @info: Structure containing relevant information.
 * @var_name: the name of the environment variable to delete
 *
 * Return: 1 on successful deletion, 0 otherwise
 */
int _delete_env_var(info_t *info, char *var_name)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !var_name)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var_name);
		if (p && *p == '=')
		{
			info->env_altered = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_altered);
}

/**
 * _set_env_var - Initialize new enviro variable or modify an existing one
 * @info: Structure containing relevant information.
 * @var_name: the name of the environment variable
 * @value: the value to set for the environment variable
 *
 * Return: 0 on success, 1 on failure
 */
int _set_env_var(info_t *info, char *var_name, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!var_name || !value)
		return (1);

	buffer = malloc(_strlen(var_name) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var_name);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var_name);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_altered = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_altered = 1;
	return (0);
}

