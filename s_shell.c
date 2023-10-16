#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 * Ramatu Abubakar & Richard Samo
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				put_string(av[0]);
				put_string(": 0: Can't open ");
				put_string(av[1]);
				put_character('\n');
				put_character(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	display_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
