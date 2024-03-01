#include "main.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates or appends to a history file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history_from_file - reads history data from a file
 * @info: the parameter struct
 * @fd: file descriptor for the history file
 *
 * Return: buffer containing history data, or NULL on failure
 */
static char *read_history_from_file(info_t *info, int fd)
{
	ssize_t rdlen;
	struct stat st;
	char *buf = NULL;

	if (!fstat(fd, &st))
	{
		if (st.st_size < 2)
			return (NULL);

		buf = malloc(sizeof(char) * (st.st_size + 1));
		if (!buf)
			return (NULL);

		rdlen = read(fd, buf, st.st_size);
		buf[st.st_size] = '\0';

		if (rdlen <= 0)
		{
			free(buf);
			return (NULL);
		}
	}

	return (buf);
}

/**
 * read_history - reads history from file and updates history list
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int fd, i, last = 0, linecount = 0;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);

	if (fd == -1)
		return (0);

	buf = read_history_from_file(info, fd);
	close(fd);

	if (!buf)
		return (0);

	for (i = 0; i < _strlen(buf); i++)
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}

	if (last != i)
		build_history_list(info, buf + last, linecount++);

	free(buf);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);
	return (info->histcount);
}


