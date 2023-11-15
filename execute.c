#include "shell.h"

/**
 * @brief Excute to main function for the simple shell program.
 *
 * This function implements a basic interactive shell loop.
 * It continuously prompts the user
 * with a command prompt ('$ '), reads user input,
 * and executes the entered command using
 *
 * @return 0 on successful completion.
 */
void execute_shell_loop(void)
{
	char *cmd;
	char **args;

	while (1)
	{
		_puts("$ ");
		cmd = read_command();

		if (cmd == NULL)
		{
			_putchar('\n');
			break;
		}
		if (*cmd)
		{
			args = tokenize(cmd);
			if (args != NULL)
			{
				if (is_builtin(args[0]))
					execute_builtin(args[0]);
				else if (execute_command(args) == -1)
					print_error("Command not found");
				free_tokens(args);
			}
		}
		free(cmd);
	}
}

/**
 * @brief Print an error message to the standard error stream.
 *
 * This function takes an error message as input and prints it
 * to the standard error stream (stderr) in the format "Error: message".
 *
 * @param msg The error message to be printed.
 */

void print_error(char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
}

/**
 * tokenize - Tokenize a command string.
 * @cmd: The command string to tokenize.
 *
 * Return: An array of tokens (words).
 */

char **tokenize(char *cmd)
{
	char **tokens;

	if (cmd == NULL)
		return (NULL);
	tokens = strtow_no_strtok(cmd, " \t\n");
	return (tokens);
}

/**
 * @brief Executes a command.
 *
 * This function takes a command as input, searches for
 * its path using find_path function,
 * forks a child process, and executes the command
 * using execve in the child process.
 * The parent process waits for the child process to complete.
 *
 * @param args A null-terminated string
 * containing the command to be executed.
 *
 * @return 0 on successful execution, -1 on failure.
 */

int execute_command(char **args)
{
	pid_t child_pid;
	char *path = find_path(args[0]);

	if (path == NULL)
	{
		print_error("Command not found");
		return (-1);
	}
	
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (-1);
	}

	if (child_pid == 0)
	{
		if (execve(path, args, NULL) == -1)
		{
			perror("Error:");
			free(path);
			exit(127);
		}
	}
	
	else
	{
		wait(NULL);
		free(path);
	}
	return (0);
}
