#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * @struct data_shell
 * @brief Struct representing the data structure for a shell program.
 *
 * The data_shell struct holds various fields needed for
 *  the functionality of a shell program.
 *
 * @var av An array of strings representing the
 * arguments passed to the shell.
 * @var input A string representing the input to the shell.
 * @var args An array of strings representing the parsed arguments.
 * @var status An integer representing the status of the shell.
 * @var counter An integer counter used for tracking.
 * @var _environ An array of strings
 * representing the environment variables.
 * @var pid A string representing the process.
 */

typedef struct data
{
    char **av;
    char *input;
    char **args;
    int status;
    int counter;
    char **_environ;
    char *pid;
} data_shell;

/**
 * @struct sep_list
 * @brief Struct representing a list of separators.
 *
 * The sep_list struct is used to create a linked list of separators.
 *
 * @var separator A character representing the separator.
 * @var next A pointer to the next element in the list.
 */
typedef struct sep_list_s
{
    char separator;
    struct sep_list_s *next;
} sep_list;

/**
 * @struct line_list
 * @brief Struct representing a list of lines.
 *
 * The line_list struct is used to create a linked list of lines.
 *
 * @var line A string representing a line.
 * @var next A pointer to the next element in the list.
 */
typedef struct line_list_s
{
    char *line;
    struct line_list_s *next;
} line_list;

/**
 * @struct r_var_list
 * @brief Struct representing a list of variables.
 *
 * The r_var_list struct is used to create a linked list of variables.
 *
 * @var len_var An integer representing the length of the variable.
 * @var val A string representing the value of the variable.
 * @var len_val An integer representing the length of the value.
 * @var next A pointer to the next element in the list.
 */
typedef struct r_var_list
{
    int len_var;
    char *val;
    int len_val;
    struct r_var_list *next;
} r_var;

/**
 * @struct builtin_t
 * @brief Struct representing a built-in shell command.
 *
 * The builtin_t struct holds information about
 * built-in command, including its name
 * and a function pointer to the corresponding
 * function that implements the command.
 *
 * @var name A string representing the name of the built-in command.
 * @var f A function pointer to the function implementing the built-in command.
 */
typedef struct builtin_s
{
    char *name;
    int (*f)(data_shell *datash);
} builtin_t;

/*
sep_list *add_separation_end(sep_list **head, char sep);
void separation_list(sep_list **head);
line_list *line_list_node(line_list **head, char *line);
void line_list(line_list **head);
*/

r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
char *_strchr(char *s, char c);
char *_strcat(char *destin, const char *src);
int _strspn(char *s, char *accept);
char *_strcpy(char *destin, char *src);
int _strcmp(char *string_1, char *string_2);

char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int _strlen(const char *s);
char *_strdup(const char *s);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);
int cmp_chars(char str[], const char *delim);

void reverse_string(char *sptr);

int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *datash, char *input, int i, int bool);
int check_syntax_error(data_shell *datash, char *input);

char *error_not_found(data_shell *datash);
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_exit_shell(data_shell *datash);
char *error_get_cd(data_shell *datash);

char *without_comment(char *in);
void shell_loop(data_shell *datash);

char *read_line(int *i_eof);

/*
void check_env(var_n **h, char *in, data_shell *data);
int check_vars(var_n **h, char *in, char *st, data_shell *data);
char *replaced_input(var_n **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *datash);
*/

char *rep_var(char *input, data_shell *datash);
void check_env(r_var **h, char *in, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
int check_vars(r_var **h, char *in, char *st, data_shell *data);

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

int exec_line(data_shell *datash);

int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);
int cmd_exec(data_shell *datash);

char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);

char *copy_info(char *name, char *value);
int _setenv(data_shell *datash);
void set_env(char *name, char *value, data_shell *datash);
int _unsetenv(data_shell *datash);

void aux_help_cd(void);
void aux_help_alias(void);
void aux_help(void);

void cd_previous(data_shell *datash);
void cd_dot(data_shell *datash);
void cd_to_home(data_shell *datash);
void cd_to(data_shell *datash);

int cd_shell(data_shell *datash);

char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);

int (*get_builtin(char *cmd))(data_shell *datash);

int get_help(data_shell *datash);

int exit_shell(data_shell *datash);

int _atoi(char *s);
char *aux_itoa(int n);
int get_len(int n);

int get_error(data_shell *datash, int eval);

void get_sigint(int sig);

void aux_help_unsetenv(void);
void aux_help_env(void);
void aux_help_exit(void);
void aux_help_setenv(void);
void free_rvar_list(r_var **head);
void aux_help_general(void);

char *error_path_126(data_shell *datash);
char *error_env(data_shell *datash);
char *error_get_alias(char **args);
char *error_syntax(char **args);
char *error_permission(char **args);

sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

#endif
