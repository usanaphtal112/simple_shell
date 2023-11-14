#include "shell.h"

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
