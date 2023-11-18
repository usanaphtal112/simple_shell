#include "shell.h"

/**
 * @brief Duplicates a string.
 *
 * Allocates memory for a new string, copies the content of the input string 's'
 * (including the null terminator), and returns a pointer to the new string.
 *
 * @param s Pointer to the input string to be duplicated.
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
 * Calculates and returns the length of the input string 's',
 * excluding the null terminator.
 *
 * @param s Pointer to the input string.
 * @return Length of the input string.
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
 * Compares each character in the input string 'str' to
 * the characters in the delimiter string
 * 'delim'. Returns 1 if all characters in 'str'
 * are delimiters; otherwise, returns 0.
 *
 * @param str The input string to be checked.
 * @param delim The set of delimiter characters.
 * @return 1 if all characters in 'str' are delimiters, 0 otherwise.
 */
int cmp_chars(char str[], const char *delim)
{
    unsigned int i, j, k;

    for (i = 0, k = 0; str[i]; i++)
    {
        for (j = 0; delim[j]; j++)
        {
            if (str[i] == delim[j])
            {
                k++;
                break;
            }
        }
    }
    if (i == k)
        return (1);
    return (0);
}

/**
 * @brief Tokenizes a string.
 *
 * Breaks the input string 'str' into tokens
 * using the specified delimiter string 'delim'.
 * Maintains state between calls using static variables.
 * Returns a pointer to the next token,
 * or NULL when no more tokens are found.
 *
 * @param str The input string to be tokenized.
 * @param delim The delimiter string used for tokenization.
 * @return Pointer to the next token, or NULL if no more tokens are found.
 */
char *_strtok(char str[], const char *delim)
{
    static char *splitted, *str_end;
    char *str_start;
    unsigned int i, bool;

    if (str != NULL)
    {
        if (cmp_chars(str, delim))
            return (NULL);
        splitted = str;
        i = _strlen(str);
        str_end = &str[i];
    }
    str_start = splitted;
    if (str_start == str_end)
        return (NULL);

    for (bool = 0; *splitted; splitted++)
    {
        if (splitted != str_start)
            if (*splitted && *(splitted - 1) == '\0')
                break;

        for (i = 0; delim[i]; i++)
        {
            if (*splitted == delim[i])
            {
                *splitted = '\0';
                if (splitted == str_start)
                    str_start++;
                break;
            }
        }
        if (bool == 0 && *splitted)
            bool = 1;
    }
    if (bool == 0)
        return (NULL);
    return (str_start);
}

/**
 * @brief Checks if a string contains only digits.
 *
 * Checks if all characters in the input string 's'
 * are digits (0-9). Returns 1 if all characters
 * are digits; otherwise, returns 0.
 *
 * @param s Pointer to the input string to be checked.
 * @return 1 if all characters in 's' are digits, 0 otherwise.
 */
int _isdigit(const char *s)
{
    unsigned int i;

    for (i = 0; s[i]; i++)
    {
        if (s[i] < 48 || s[i] > 57)
            return (0);
    }
    return (1);
}
