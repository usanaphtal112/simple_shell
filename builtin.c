#include "shell.h"

/**
 * @brief Main function for the shell program.
 *
 * This function implements a simple interactive shell loop.
 * It continuously prompts the user
 * with a command prompt ('$ '), reads user input
 * processes the input until the user
 *
 * @return 0 on successful completion.
 */

int main(void)
{
	char *cmd;

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
			if (_strcmp(cmd, "env\n") == 0)
				print_environment();
			else if (_strcmp(cmd, "exit\n") == 0)
				break;
			else if (execute_command(cmd) == -1)
				print_error("Command not found");
			}
		free(cmd);
	}
	return (0);
}
