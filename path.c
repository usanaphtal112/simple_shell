#include "shell.h"

/**
 * @brief Executes a command.
 *
 * This function takes a command as input, searches for
 * its path using find_path function,
 * forks a child process, and executes the command 
 * using execve in the child process.
 * The parent process waits for the child process to complete.
 *
 * @param cmd A null-terminated string
 * containing the command to be executed.
 *
 * @return 0 on successful execution, -1 on failure.
 */
int execute_command(char *cmd)
{
	pid_t child_pid;
	char *path = find_path(cmd);

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
			if (execve(path, cmd, NULL) == -1)
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
