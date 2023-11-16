#include "shell.h"

/**
 * @brief Reads a line from standard input.
 *
 * Reads a line from the standard input using the getline function.
 * Allocates memory dynamically for the input -
 * string and updates the variable pointed to by 'i_eof'
 * with the return value of getline.
 *
 * @param i_eof Pointer to the variable where -
 * return value of getline will be stored.
 * @return Pointer to the dynamically allocated input string.
 */
char *read_line(int *i_eof)
{
    char *input = NULL;
    size_t bufsize = 0;

    *i_eof = getline(&input, &bufsize, stdin);

    return (input);
}
