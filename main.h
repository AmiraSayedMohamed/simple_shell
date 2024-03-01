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

/* realloc_memory.c*/
void *reallocateMemory(void *ptr, unsigned int prevSize, unsigned int newSize);
void freeStringArray(char **array);
void *fillMemory(void *ptr, unsigned char byte, unsigned int numBytes);
int freeAndNull(void **ptr);



#endif
