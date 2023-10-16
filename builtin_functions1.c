#include "shell.h"

/**
 * list_history - displays the history list
 * @info: Structure containing potential arguments
 *  Return: 0
 */
int list_history(info_t *info)
{
	display_list(info->history);
	return (0);
}

/**
 * remove_alias - remove alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: 0 on success else 1
 */
int remove_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = remove_node(&(info->alias),
		node_index_value(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * create_alias - create alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int create_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (add_node_last(&(info->alias), str, 0) == NULL);
}

/**
 * display_alias - display an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int display_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * aliases - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain.
 *  Return: Always 0
 */
int aliases(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			create_alias(info, info->argv[i]);
		else
			display_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
