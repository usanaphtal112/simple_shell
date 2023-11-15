#include "shell.h"

/**
 * _strndup - Duplicate a portion of a string.
 * @s: The string to duplicate.
 * @n: The number of characters to duplicate.
 *
 * Return: A pointer to the duplicated string.
 */

char *_strndup(const char *s, size_t n)
{
	char *copy = malloc(n + 1);
	if (copy != NULL)
	{
		strncpy(copy, s, n);
		copy[n] = '\0';
	}
	return copy;
}

/**
 * _strdup - Duplicate a string.
 * @s: The string to duplicate.
 *
 * Return: A pointer to the duplicated string.
 */

char *_strdup(const char *s)
{
	return _strndup(s, strlen(s));
}
