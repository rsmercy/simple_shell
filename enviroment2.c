#include "shell.h"

/**
 * _environ - returns the string array
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
char **_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = remove_node(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @v: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *v, char *val)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!v || !val)
		return (0);

	buf = malloc(_strlen(v) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, v);
	_strcat(buf, "=");
	_strcat(buf, val);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, v);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_last(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
