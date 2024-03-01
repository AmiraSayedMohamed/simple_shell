#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/* for read and write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -i

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* str1_funcitons.c */
int _strlen(char *input_string);
int _strcmp(char *str1,char *str2);
char *_strcat(char *dest,char *src);
char *starts_with(char *str1, char *str2);

/* str2_functions.c */
char *_strcpy(char *dest, char *src);
char *_strdup(const char *original);
void _puts(const char *str);
int _putchar(char c);

/* str3_functions.c */
char *_strncpy(const char *src, char *dest, int amount);
void _strncat(char *dest, const char *src, int n);
const char *_strchr(const char *str, char target);


/* check_string_atoi.c */
int is_delim(char c, const char *delimiter);
int interactive(info_m *info);
int _isalpha(char c);
int _atoi(const char *str);

/* split_string.c */
static int countWords(const char *input, const char *delimiter);
static char **allocateMemory(int numWords);
static void exWords(const char *input, const char *delimiter, char **result);
char **splitString(const char *input, const char *delimiter);

/* reallocateMemory.c*/
void *_realloc(void *ptr, unsigned int prevSize, unsigned int newSize);
void ffree(char **array);
void *_memset(void *ptr, unsigned char byte, unsigned int numBytes);
int bfree(void **ptr);

/*string_list.c*/
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

/* shell_util1.c  */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);

/* shell_util.c */
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

/* shell_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* shell_exec.c */
int hsh(info_t *info, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* list_functions.c */
size_t list_len(const list_t *head);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *head);
list_t *node_starts_with(list_t *head, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* io_utils.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* input_handling.c */
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/* info_manager.c */
void clear_info(info_t *info);
void set_info(info_t *info, char **arguments);
void free_info(info_t *info, int clear_all);

/* info_management.c */
void initialize_info(info_t *info);
void populate_info(info_t *info, char **av);
void deallocate_info(info_t *info, int all);

/*error_utils.c*/
int _erratoi(char *str);
void print_error(info_t *info, char *error_msg);
int print_d(int number, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

/* environment_utils.c */
int _myenv(info_t *info);
char *_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);

/* environment.c */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var_name);
int _setenv(info_t *info, char *var_name, char *value);

/* command_search.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *info, char *, char *);

/* command_processing.c */
int is_chain(info_t *info, char *buf, size_t *pos);
void check_chain(info_t *info, char *buf, size_t *pos, size_t start, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);

/* loopsh.c */
int loophsh(char **);



#endif
