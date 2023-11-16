#include "shell.h"

/**
 * _atoi - Convert a string to an integer.
 * @s: The string to convert.
 *
 * This function converts a string to an integer, considering the sign and numeric
 * characters in the string. It handles both positive and negative integers.
 *
 * @return: The converted integer.
 */
int _atoi(char *s)
{
    unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

    while (*(s + count) != '\0')
    {
        if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
            break;

        if (*(s + count) == '-')
            pn *= -1;

        if ((*(s + count) >= '0') && (*(s + count) <= '9'))
        {
            if (size > 0)
                m *= 10;
            size++;
        }
        count++;
    }

    for (i = count - size; i < count; i++)
    {
        oi = oi + ((*(s + i) - 48) * m);
        m /= 10;
    }
    return (oi * pn);
}

/**
 * get_len - Calculate the length of an integer when represented as a string.
 * @n: The integer to calculate the length for.
 *
 * This function calculates the length of integer when represented as string,
 * taking into account the sign of the integer.
 * It is used as a helper function for the aux_itoa function.
 *
 * @return: The length of the integer as a string.
 */
int get_len(int n)
{
    unsigned int n1;
    int lenght = 1;

    if (n < 0)
    {
        lenght++;
        n1 = n * -1;
    }
    else
    {
        n1 = n;
    }
    while (n1 > 9)
    {
        lenght++;
        n1 = n1 / 10;
    }

    return (lenght);
}

/**
 * aux_itoa - Convert an integer to a string.
 * @n: The integer to convert.
 *
 * This function converts an integer to a string.
 * It allocates memory for the string, taking into account
 * the sign of the integer, and returns the resulting string.
 * The caller is responsible for freeing the allocated memory.
 *
 * @return: A dynamically allocated string representing the integer.
 *          Returns NULL if memory allocation fails.
 */
char *aux_itoa(int n)
{
    unsigned int n1;
    int lenght = get_len(n);
    char *buffer;

    buffer = malloc(sizeof(char) * (lenght + 1));
    if (buffer == 0)
        return (NULL);

    *(buffer + lenght) = '\0';

    if (n < 0)
    {
        n1 = n * -1;
        buffer[0] = '-';
    }
    else
    {
        n1 = n;
    }

    lenght--;
    do
    {
        *(buffer + lenght) = (n1 % 10) + '0';
        n1 = n1 / 10;
        lenght--;
    } while (n1 > 0);
    return (buffer);
}
