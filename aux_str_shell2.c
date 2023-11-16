#include "shell.h"

/**
 * @brief Duplicates a string.
 *
 * Allocates memory for a new string, copies the content of the main_input string 's'
 * (including the null terminator), and returns a pointer to the new string.
 *
 * @param s Pointer to the main_input string to be duplicated.
 * @return Pointer to the duplicated string, or NULL if memory allocation fails.
 */
char *_strdup(const char *s)
{
    char *new;
    size_t len;

    len = _strlen(s);
    new = malloc(sizeof(char) * (len + 1));
    if (new == NULL)
        return (NULL);
    _memcpy(new, s, len + 1);
    return (new);
}

/**
 * @brief Computes the length of a string.
 *
 * Calculates and returns the length of the main_input string 's',
 * excluding the null terminator.
 *
 * @param s Pointer to the main_input string.
 * @return Length of the main_input string.
 */
int _strlen(const char *s)
{
    int len;

    for (len = 0; s[len] != 0; len++)
    {
    }
    return (len);
}

/**
 * @brief Compares characters in a string to a set of characters.
 *
 * Compares each character in the main_input string 'str' to
 * the characters in the delimiter string
 * 'delim'. Returns 1 if all characters in 'str'
 * are delimiters; otherwise, returns 0.
 *
 * @param str The main_input string to be checked.
 * @param delim The set of delimiter characters.
 * @return 1 if all characters in 'str' are delimiters, 0 otherwise.
 */
int cmp_chars(char str[], const char *delim)
{
    while (*str)
    {
        if (strchr(delim, *str) == NULL)
        {
            return 0;
        }
        str++;
    }

    return 1;
}

/**
 * @brief Tokenizes a string.
 *
 * Breaks the main_input string 'str' into tokens
 * using the specified delimiter string 'delim'.
 * Maintains state between calls using static variables.
 * Returns a pointer to the next token,
 * or NULL when no more tokens are found.
 *
 * @param str The main_input string to be tokenized.
 * @param delim The delimiter string used for tokenization.
 * @return Pointer to the next token, or NULL if no more tokens are found.
 */
char *_strtok(char str[], const char *delim)
{
    static char *nextToken;
    char *tokenStart;

    if (str != NULL)
    {
        nextToken = str;
    }

    while (*nextToken && strchr(delim, *nextToken) != NULL)
    {
        nextToken++;
    }

    if (*nextToken == '\0')
    {
        return NULL;
    }

    tokenStart = nextToken;

    while (*nextToken && strchr(delim, *nextToken) == NULL)
    {
        nextToken++;
    }

    if (*nextToken != '\0')
    {
        *nextToken = '\0';
        nextToken++;
    }

    return tokenStart;
}

/**
 * @brief Checks if a string contains only digits.
 *
 * Checks if all characters in the main_input string 's'
 * are digits (0-9). Returns 1 if all characters
 * are digits; otherwise, returns 0.
 *
 * @param s Pointer to the input string to be checked.
 * @return 1 if all characters in 's' are digits, 0 otherwise.
 */
int _isdigit(const char *s)
{
    while (*s)
    {
        if (*s < '0' || *s > '9')
        {
            return 0;
        }
        s++;
    }

    return 1;
}
