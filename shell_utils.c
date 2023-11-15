#include "shell.h"

/**
 * _getchar - Custom getchar function.
 *
 * This function reads a character from the standard input.
 *
 * Return: The character read or EOF on error.
 */
int _getchar(void)
{
	return getchar();
}

/**
 * _strncat - Custom strncat function.
 *
 * This function appends the first `n` characters of the string `src`
 * to the end of the string `dest`. The resulting string in `dest`
 * is null-terminated.
 *
 * @param dest: The destination string.
 * @param src: The source string.
 * @param n: The maximum number of characters to append.
 *
 * Return: A pointer to the resulting string `dest`.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	return strncat(dest, src, n);
}

/**
 * _getline - Read a line from the standard input.
 *
 * Return: A dynamically allocated buffer containing the read line.
 * The caller is responsible for freeing the memory using free().
 */
char *_getline(void)
{
	static char buffer[READ_BUF_SIZE];
	static int bytes_read = 0;
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
