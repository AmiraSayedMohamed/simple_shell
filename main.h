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
#define BUF_FLUSH -1

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

/* memory.c*/
int freeAndNull(void **ptr);

/* realloc_memory.c*/
void *reallocateMemory(void *ptr, unsigned int prevSize, unsigned int newSize);
void freeStringArray(char **array);
void *fillMemory(void *ptr, unsigned char byte, unsigned int numBytes);

/* print_errors1.c */
void printError(info_m *info, char *estr);
int print_decimal(int input, int fd)
char *convert_num(long int num, int base, int flags);
void remove_comments(char *buf);


/* linked_list.c*/
list_m *addNode_ToStart(list_m **head, const char *str, int num);
list_m *add_node_end(list_m **head, const char *str, int num);
size_t print_list_str(const list_m *h);
int delete_node_at_index(list_m **head, unsigned int index);
void free_list(list_m **head_ptr);

/* list1.c */
size_t list_len(const list_m *h);
char **list_to_strings(list_m *head);
size_t print_list(const list_m *h);
list_m *node_starts_with(list_m *node, char *prefix, char c);
ssize_t get_node_index(list_m *head, list_m *node);

/* print_errors2 */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);


/* toem_shloop.c */
int hsh(info_t *, char**);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t*, char*, char*);

/* loophsh.c */
int loophsh(char **);
/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
