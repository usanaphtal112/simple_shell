#include "shell.h"

/**
 * @brief Reads a command from the standard input.
 *
 * This function uses getline to read a line of input
 * from the standard input (stdin).
 * The input is read into a dynamically allocated
 * buffer, and the buffer is returned.
 *
 * @return A dynamically allocated buffer containing the read command.
 * The caller is responsible for freeing the memory using free().
 */
char *read_command(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;

	getline(&buffer, &bufsize, stdin);
	return (buffer);
}
