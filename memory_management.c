#include "shell.h"

/**
 * buf_free - frees a pointer and NULL
 * @ptr: address of the pointer
 *
 * Return: 0.
 */
int buf_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
