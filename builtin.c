#include "shell.h"

/**
 * is_builtin - Check if a command is a built-in.
 * @cmd: The command to check.
 *
 * Return: 1 if the command is a built-in, 0 otherwise.
 */

int is_builtin(char *cmd)
{
	if (_strcmp(cmd, "exit") == 0 || _strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

/**
 * execute_builtin - Execute a built-in command.
 * @cmd: The built-in command to execute.
 *
 * Return: 0 on success, -1 on failure.
 */

int execute_builtin(char *cmd)
{
	if (_strcmp(cmd, "exit") == 0)
		exit(0);
	else if (_strcmp(cmd, "env") == 0)
		print_environment();
	return (-1);
}
