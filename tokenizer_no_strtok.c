#include "shell.h"

/**
 * _strchr - Locate character in string
 * @s: The string to search
 * @c: The character to locate
 *
 * Return: Pointer to the first occurrence of the character c in the string s,
 * or NULL if the character is not found
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

/**
 * count_tokens - Count the number of tokens in a string
 * @str: The input string
 * @delim: The delimiter character
 *
 * Return: The number of tokens
 */

int count_tokens(char *str, char *delim)
{
	int count = 0;
	char *token, *ptr;

	if (str == NULL || delim == NULL)
		return (0);
	ptr = str;
	while ((token = _strchr(ptr, *delim)) != NULL)
	{
		count++;
		ptr = token + 1;
	}
	return (count + 1);
}

/**
 * strtow_no_strtok - Split a string into an array of words without using strtok
 * @str: The input string
 * @delim: The delimiter character
 *
 * Return: A pointer to an array of strings (words)
 */

char **strtow_no_strtok(char *str, char *delim)
{
	char **tokens;
	int count, i;
	char *token, *ptr;

	if (str == NULL || delim == NULL)
		return (NULL);

	count = count_tokens(str, delim);
	if (count == 0)
		return (NULL);
	tokens = malloc((count + 1) * sizeof(char *));

	if (tokens == NULL)
		return (NULL);
	ptr = str;
	for (i = 0; i < count - 1; i++)
	{
		token = _strchr(ptr, *delim);
		tokens[i] = _strndup(ptr, token - ptr);
		if (tokens[i] == NULL)
		{
			free_tokens(tokens);
			return (NULL);
		}
		ptr = token + 1;
	}

	tokens[count - 1] = _strdup(ptr);
	tokens[count] = NULL;

	return (tokens);

}

/**
 * free_tokens - Free the memory allocated for an array of tokens
 * @tokens: The array of tokens
 */

void free_tokens(char **tokens)
{
	int i;

	if (tokens == NULL)
		return;
	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);
	free(tokens);

}
