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
	execute_shell_loop();
	return 0;
}
