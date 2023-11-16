#include "shell.h"

/**
 * @brief Concatenates two strings.
 *
 * Concatenates the string pointed to by src to the
 * end of the string pointed to by destin.
 *
 * @param destin Pointer to the destination string.
 * @param src Pointer to the source string.
 * @return Pointer to the destination string after concatenation.
 */

char *_strcat(char *destin, const char *src)
{
    int i;
    int j;

    for (i = 0; destin[i] != '\0'; i++)
        ;

    for (j = 0; src[j] != '\0'; j++)
    {
        destin[i] = src[j];
        i++;
    }

    destin[i] = '\0';
    return (destin);
}
/**
 * @brief Copies a string.
 *
 * Copies the string pointed to by src
 * (including the null terminator) to the string
 * pointed to by destin. The strings may not overlap
 * and the destination string must
 * be large enough to hold the source string.
 *
 * @param destin Pointer to the destination string.
 * @param src Pointer to the source string.
 * @return Pointer to the destination string after copying.
 */
char *_strcpy(char *destin, char *src)
{

    size_t a;

    for (a = 0; src[a] != '\0'; a++)
    {
        destin[a] = src[a];
    }
    destin[a] = '\0';

    return (destin);
}

/**
 * @brief Compares two strings.
 *
 * Compares the two strings string_1 and string_2.
 * Returns an integer less than, equal to,
 * or greater than zero if string_1 is found
 * respectively, to be less than, to match,
 * or be greater than string_2.
 *
 * @param string_1 Pointer to the first string.
 * @param string_2 Pointer to the second string.
 * @return Integer value indicating the result of the comparison.
 */
int _strcmp(char *string_1, char *string_2)
{
    int i;

    for (i = 0; string_1[i] == string_2[i] && string_1[i]; i++)
        ;

    if (string_1[i] > string_2[i])
        return (1);
    if (string_1[i] < string_2[i])
        return (-1);
    return (0);
}

/**
 * @brief Locates the first occurrence of a character in a string.
 *
 * Searches the string s for the first occurrence of the character c.
 *
 * @param s Pointer to the string to be searched.
 * @param c Character to be located.
 * @return Pointer to the first occurrence of the character c
 */
char *_strchr(char *s, char c)
{
    unsigned int i = 0;

    for (; *(s + i) != '\0'; i++)
        if (*(s + i) == c)
            return (s + i);
    if (*(s + i) == c)
        return (s + i);
    return ('\0');
}

/**
 * @brief Calculates the length (in characters) of the initial segment of s
 *         consisting of only characters from accept.
 *
 * Returns the length of the initial segment of s containing only characters
 * that appear in the accept string.
 *
 * @param s Pointer to the string to be analyzed.
 * @param accept Pointer to the string containing characters to match.
 * @return The length of the initial segment of s
 * consisting of only characters from accept.
 */
int _strspn(char *s, char *accept)
{
    int i, j, bool;

    for (i = 0; *(s + i) != '\0'; i++)
    {
        bool = 1;
        for (j = 0; *(accept + j) != '\0'; j++)
        {
            if (*(s + i) == *(accept + j))
            {
                bool = 0;
                break;
            }
        }
        if (bool == 1)
            break;
    }
    return (i);
}
