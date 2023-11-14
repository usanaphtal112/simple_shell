#ifndef SHELL_H
#define SHELL_H

#define READ_BUF_SIZE 1024

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

char *read_command(void);
int execute_command(char *cmd);
void _puts(char *str);
void _putchar(char c);
void print_error(char *msg);
char *_getline(void);

int _strcmp(const char *s1, const char *s2);
void print_environment(void);

#endif
