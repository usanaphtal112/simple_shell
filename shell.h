#ifndef SHELL_H
#define SHELL_H

#define READ_BUF_SIZE 1024

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

char *_getline(void);
char *read_command(void);
int _getchar(void);
char *_strncat(char *dest, const char *src, size_t n);

char **tokenize(char *str);
int execute_command(char **args);
void _puts(char *str);

void execute_shell_loop(void);
void _putchar(char c);
void print_error(char *msg);
char *_getline(void);

int _strcmp(const char *s1, const char *s2);
void print_environment(void);
void free_tokens(char **tokens);

char *find_path(char *cmd);
int is_builtin(char *cmd);
int execute_builtin(char *cmd);

char *_strndup(const char *s, size_t n);
char *_strdup(const char *s);

char **strtow_no_strtok(char *str, char *delim);

#endif
