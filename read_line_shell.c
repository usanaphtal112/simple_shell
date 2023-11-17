#include "shell.h"

/**
 * @brief Reads a line from standard main_input.
 *
 * Reads a line from the standard main_input using the getline function.
 * Allocates memory dynamically for the main_input -
 * string and updates the variable pointed to by 'endOfFileCondition'
 * with the return value of getline.
 *
 * @param endOfFileCondition Pointer to the variable where -
 * return value of getline will be stored.
 * @return Pointer to the dynamically allocated main_input string.
 */
char *r_LineNode(int *endOfFileCondition)
{
    char *main_input = NULL;
    size_t bufsize = 0;

    *endOfFileCondition = getline(&main_input, &bufsize, stdin);

    return (main_input);
}
