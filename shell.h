#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define READ_BUF_SIZE 1024
#define TOKEN_READ_BUF_SIZE 128
#define TOKEN_DELIM " \t\r\n\a"

extern char **environ;

/**
 * @struct simple_shell_d
 * @brief Struct representing the data structure for a shell program.
 *
 * The simple_shell_d struct holds various fields needed for
 *  the functionality of a shell program.
 *
 * @var av An array of strings representing the
 * arguments passed to the shell.
 * @var main_input A string representing the main_input to the shell.
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
    char *main_input;
    char **args;
    int status;
    int counter;
    char **_environ;
    char *pid;
} simple_shell_d;

typedef int BuiltinFunction(simple_shell_d *simpdata);
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
 * @struct LineList_Var
 * @brief Struct representing a list of lines.
 *
 * The LineList_Var struct is used to create a linked list of lines.
 *
 * @var line A string representing a line.
 * @var next A pointer to the next element in the list.
 */
typedef struct LineNode
{
    char *line;
    struct LineNode *next;
} LineList_Var;

/**
 * @struct df_variableNode
 * @brief Struct representing a list of variables.
 *
 * The df_variableNode struct is used to create a linked list of variables.
 *
 * @var len_var An integer representing the length of the variable.
 * @var val A string representing the value of the variable.
 * @var len_val An integer representing the length of the value.
 * @var next A pointer to the next element in the list.
 */
typedef struct df_variableNode
{
    int len_var;
    char *val;
    int len_val;
    struct df_variableNode *next;
} read_variable;

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
    BuiltinFunction *function;
} builtin_t;

/*
sep_list *add_separation_end(sep_list **head, char sep);
void separation_list(sep_list **head);
LineList_Var *LineList_Var_node(LineList_Var **head, char *line);
void LineList_Var(LineList_Var **head);
*/

read_variable *variable_addition(read_variable **head, int lvar, char *var, int lval);
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

int repeated_char(char *main_input, int i);
int error_sep_op(char *main_input, int i, char last);
int first_char(char *main_input, int *i);
void print_syntax_error(simple_shell_d *simpdata, char *main_input, int i, int bool);
int check_syntax_error(simple_shell_d *simpdata, char *main_input);

char *error_not_found(simple_shell_d *simpdata);
char *strcat_cd(simple_shell_d *, char *, char *, char *);
char *error_exit_shell(simple_shell_d *simpdata);
char *error_get_cd(simple_shell_d *simpdata);

char *without_comment(char *in);
void shell_loop(simple_shell_d *simpdata);

char *r_LineNode(int *endOfFileCondition);

/*
void check_env(var_n **h, char *in, simple_shell_d *data);
int check_vars(var_n **h, char *in, char *st, simple_shell_d *data);
char *replaced_input(var_n **head, char *main_input, char *new_input, int nlen);
char *rep_var(char *main_input, simple_shell_d *simpdata);
*/

char *rep_var(char *main_input, simple_shell_d *simpdata);
void check_env(read_variable **h, char *in, simple_shell_d *data);
char *replaced_input(read_variable **head, char *main_input, char *new_input, int nlen);
int check_vars(read_variable **h, char *in, char *st, simple_shell_d *data);

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
int exec_line(simple_shell_d *simpdata);
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(simple_shell_d *simpdata);
int check_error_cmd(char *dir, simple_shell_d *simpdata);
int cmd_exec(simple_shell_d *simpdata);
char *_getenv(const char *name, char **_environ);
int _env(simple_shell_d *simpdata);
char *copy_info(char *name, char *value);
int _setenv(simple_shell_d *simpdata);
void set_env(char *name, char *value, simple_shell_d *simpdata);
int _unsetenv(simple_shell_d *simpdata);
void aux_help_cd(void);
void aux_help_alias(void);
void aux_help(void);
void cd_previous(simple_shell_d *simpdata);
void cd_dot(simple_shell_d *simpdata);
void cd_to_home(simple_shell_d *simpdata);
void cd_to(simple_shell_d *simpdata);
int cd_shell(simple_shell_d *simpdata);
char *swap_char(char *main_input, int bool);
void add_nodes(sep_list **head_s, LineList_Var **head_l, char *main_input);
char **split_line(char *main_input);
int (*get_builtin(char *cmd))(simple_shell_d *simpdata);
int get_help(simple_shell_d *simpdata);
int exit_shell(simple_shell_d *simpdata);
int _atoi(char *s);
char *aux_itoa(int n);
int get_len(int n);
int get_error(simple_shell_d *simpdata, int eval);
void get_sigint(int sig);
void aux_help_unsetenv(void);
void aux_help_env(void);
void aux_help_exit(void);
void go_next(sep_list **list_s, LineList_Var **list_l, simple_shell_d *simpdata);
int shellSplitCmd(simple_shell_d *simpdata, char *main_input);
void aux_help_setenv(void);
void free_rvar_list(read_variable **head);
void aux_help_general(void);
char *error_path_126(simple_shell_d *simpdata);
char *error_env(simple_shell_d *simpdata);
sep_list *add_separation_end(sep_list **head, char sep);
void separation_list(sep_list **head);
LineList_Var *LineList_Var_node(LineList_Var **head, char *line);
void f_list(LineList_Var **head);

#endif
