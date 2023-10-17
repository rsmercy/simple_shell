#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH 1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * Ramatu Abubakar & Richard Samo
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct information - contains pseudo-arguements
 * @arg: a string generated from getline
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct information
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin_list - contains builtin
 * @type: builtin command flag
 * @func: pointer to function
 */
typedef struct builtin_list
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int if_exec(info_t *, char *);
char *duplicate_char(char *, int, int);
char *path_find(info_t *, char *, char *);

int loophsh(char **);

void put_string(char *);
int put_character(char);
int put_to_filedes(char c, int fd);
int put_string_filedes(char *str, int fd);

int _strlen(char *string);
int _strcmp(char *string1, char *string2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *destination, char *source);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char c);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **str_token(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int buf_free(void **);

int interactive_mode(info_t *);
int if_delimeter(char, char *);
int if_alpha(int);
int _atoi(char *);

int str_to_int(char *);
void display_error(info_t *, char *);
int display_decimal(int, int);
char *conv_numb(long int, int, int);
void remove_comments(char *);

int exit_function(info_t *);
int cd_function(info_t *);
int help_function(info_t *);

int list_history(info_t *);
int aliases(info_t *);

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

void clear_info(info_t *);
void create_info(info_t *, char **);
void release_info(info_t *, int);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

char **_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *get_history(info_t *info);
int create_history(info_t *info);
int display_history(info_t *info);
int add_history(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

list_t *add_node_begining(list_t **, const char *, int);
list_t *add_node_last(list_t **, const char *, int);
size_t display_list_string(const list_t *);
int remove_node(list_t **, unsigned int);
void release_list(list_t **);

size_t list_length(const list_t *);
char **list_strings(list_t *);
size_t display_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t node_index_value(list_t *, list_t *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif /* SHELL_H */
