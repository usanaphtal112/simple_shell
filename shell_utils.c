#include "shell.h"

#define READ_BUF_SIZE 1024

/**
 * @brief Reads a command from the standard input using buffered input.
 *
 * This function reads a line of input
 * From the standard input (stdin) using buffered input.
 * It reads characters until encountering
 * EOF or a newline character ('\n').
 *
 * @return A dynamically allocated buffer containing the read command.
 * The caller is responsible for freeing the memory using free().
 */
char *read_command(void)
{
	char buffer[READ_BUF_SIZE];
	int bytes_read = 0;
	char *result = NULL;

	while (1)
	{
		int c = _getchar();

		if (c == EOF || c == '\n')
			break;

		buffer[bytes_read++] = c;

		if (bytes_read == READ_BUF_SIZE)
		{
			result = _strncat(result, buffer, READ_BUF_SIZE);
			if (result == NULL)
				return (NULL);
			bytes_read = 0;
		}
	}

	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		result = _strncat(result, buffer, bytes_read + 1);
	}

	return (result);
}
