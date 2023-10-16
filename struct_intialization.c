#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 * Return: void
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * create_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void create_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_token(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * release_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all
 */
void release_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			release_list(&(info->env));
		if (info->history)
			release_list(&(info->history));
		if (info->alias)
			release_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		buf_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
