#include "shell.h"

/**
 * @brief Main function for the simple shell program.
 *
 * This function implements a basic interactive shell loop.
 * It continuously prompts the user
 * with a command prompt ('$ '), reads user input,
 * and executes the entered command using
 *
 * @return 0 on successful completion.
 */

int main(void)
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
			if (args !=NULL)
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
	
	return (0);
}
