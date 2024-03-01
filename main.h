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
int get_string_length(const char *input_string);
int my_strcmp(const char *str1, const char *str2);
char *my_strcat(char *dest, const char *src);
char *start_with(const char *str1, const char *str2);

/* str2_functions.c */
char *my_strcpy(char *dest, char *src);
char *my_strdup(const char *original);
void print_string(const char *str);
int _putchar(char c);

/* str3_functions.c */
char *copy_n_chars(const char *src, char *dest, int amount);
void concatenateStringsLimited(char *dest, const char *src, int n);
const char *locateCharacter(const char *str, char target);


/* check_string_atoi.c */
int isDelimiter(char c, const char *delimiter);
int isInteractiveMode(info_m *info);
int isAlphabetical(char c);
int stringToInteger(const char *str);

/* split_string.c */
static int countWords(const char *input, const char *delimiter);
static char **allocateMemory(int numWords);
static void exWords(const char *input, const char *delimiter, char **result);
char **splitString(const char *input, const char *delimiter);

/* reallocateMemory.c*/
void *reallocateMemory(void *ptr, unsigned int prevSize, unsigned int newSize);
void freeStringArray(char **array);
void *fillMemory(void *ptr, unsigned char byte, unsigned int numBytes);
int freeAndNull(void **ptr);

/*string_list.c*/
list_t *add_node_start(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_str_list(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_str_list(list_t **head_ptr);

/* shell_util1.c  */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);

/* shell_util.c */
int _exit_shell(info_t *info);
int _change_directory(info_t *info);
int _display_help(info_t *info);

/* shell_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
static char *read_history_from_file(info_t *info, int fd);
int read_history(info_t *info);

/* shell_exec.c */
int run_shell(info_t *info, char **av);
int find_builtin(info_t *info);
void find_command(info_t *info);
void fork_command(info_t *info);

/* list_functions.c */
size_t list_length(const list_t *head);
char **list_to_strings(list_t *head);
size_t print_list_nodes(const list_t *head);
list_t *find_node_with_prefix(list_t *head, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* io_utils.c */
void _print_string_stderr(char *string);
int _put_char_stderr(char c);
int _put_char_fd(char c, int fd);
int _print_string_fd(char *string, int fd);

/* input_handling.c */
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/* info_manager.c */
void init_info(info_t *info);
void populate_info(info_t *info, char **arguments);
void clear_info(info_t *info, int clear_all);

/* info_management.c */
void initialize_info(info_t *info);
void populate_info(info_t *info, char **av);
void deallocate_info(info_t *info, int all);

/*error_utils.c*/
int _str_to_int(char *str);
void print_error_msg(info_t *info, char *error_msg);
int print_decimal(int number, int fd);
char *convert_to_string(long int num, int base, int flags);
void remove_comment(char *buf);

/* environment_utils.c */
int _myenv(info_t *info);
char *_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);

/* environment.c */
char **fetch_environment(info_t *info);
int _delete_env_var(info_t *info, char *var_name);
int _set_env_var(info_t *info, char *var_name, char *value);

/* command_search.c */
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);

/* command_processing.c */
int is_delimiter(info_t *info, char *buf, size_t *pos);
void checkConti(info_t *info, char *buf, size_t *pos, size_t start, size_t len);
int replace_aliases(info_t *info);
int replace_variables(info_t *info);
int replace_string(char **old, char *new);


#endif
