#include "shell.h"

/**
 * @brief Reverses a string in-place.
 *
 * Reverses the characters in the input string 's' in-place.
 *
 * @param sptr Pointer to the string to be reversed.
 */
void reverse_string(char *sptr)
{
    int count = 0, i, j;
    char *str, temp;

    while (count >= 0)
    {
        if (sptr[count] == '\0')
            break;
        count++;
    }
    str = sptr;

    for (i = 0; i < (count - 1); i++)
    {
        for (j = i + 1; j > 0; j--)
        {
            temp = *(str + j);
            *(str + j) = *(str + (j - 1));
            *(str + (j - 1)) = temp;
        }
    }
}
