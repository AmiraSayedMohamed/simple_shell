#include "main.h"

/**
 * add_node_start - adds a node to the start of the list
 * @head: pointer to pointer to the head node
 * @str: string to be stored in the new node
 * @num: index used by history
 *
 * Return: pointer to the new head of the list
 */
list_t *add_node_start(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: pointer to pointer to the head node
 * @str: string to be stored in the new node
 * @num: index used by history
 *
 * Return: pointer to the new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *last_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = NULL;

	if (!*head)
	{
		*head = new_node;
		return (new_node);
	}

	last_node = *head;
	while (last_node->next)
		last_node = last_node->next;

	last_node->next = new_node;
	return (new_node);
}

/**
 * print_str_list - prints only the str element of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: number of nodes in the list
 */
size_t print_str_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * delete_node_at_index - deletes node at a given index
 * @head: pointer to pointer to the first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *current, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		current = *head;
		*head = (*head)->next;
		free(current->str);
		free(current);
		return (1);
	}

	prev_node = NULL;
	current = *head;

	while (current && i < index)
	{
		prev_node = current;
		current = current->next;
		i++;
	}

	if (current)
	{
		prev_node->next = current->next;
		free(current->str);
		free(current);
		return (1);
	}

	return (0);
}

/**
 * free_str_list - frees all nodes of a list
 * @head_ptr: pointer to pointer to the head node
 *
 * Return: void
 */
void free_str_list(list_t **head_ptr)
{
	list_t *current, *next_node;

	if (!head_ptr || !*head_ptr)
		return;

	current = *head_ptr;

	while (current)
	{
		next_node = current->next;
		free(current->str);
		free(current);
		current = next_node;
	}

	*head_ptr = NULL;
}

