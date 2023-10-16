#include "shell.h"

/**
 * exit_function - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * Return: (0) if info.argv[0] != "exit"
 */
int exit_function(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = str_to_int(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			display_error(info, "Illegal number: ");
			put_string(info->argv[1]);
			put_character('\n');
			return (1);
		}
		info->err_num = str_to_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * cd_function - changes the current directory
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: 0
 */
int cd_function(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		display_error(info, "can't cd to ");
		put_string(info->argv[1]), put_character('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_function - provides help for a command
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: 0
 */
int help_function(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
