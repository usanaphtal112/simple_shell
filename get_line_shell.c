#include "shell.h"

/**
 * @brief Reads a line from the provided stream and stores it in lineptr.
 *
 * Reads characters from the standard input (STDIN_FILENO)
 * until a newline character '\n' is encountered.
 * The resulting line is stored in the lineptr buffer.
 * The function reallocates memory for lineptr
 * as needed. The size of the allocated memory is stored in n.
 *
 * @param lineptr Pointer to the line buffer.
 * @param n Pointer to the size variable.
 * @param stream File stream (not used in this implementation).
 * @return The number of characters read (including newline)
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
    int i;
    static ssize_t input;
    ssize_t retval;
    char *buffer;
    char t = 'z';

    if (input == 0)
        fflush(stream);
    else
        return (-1);
    input = 0;

    buffer = malloc(sizeof(char) * READ_BUF_SIZE);
    if (buffer == 0)
        return (-1);
    while (t != '\n')
    {
        i = read(STDIN_FILENO, &t, 1);
        if (i == -1 || (i == 0 && input == 0))
        {
            free(buffer);
            return (-1);
        }
        if (i == 0 && input != 0)
        {
            input++;
            break;
        }
        if (input >= READ_BUF_SIZE)
            buffer = _realloc(buffer, input, input + 1);
        buffer[input] = t;
        input++;
    }
    buffer[input] = '\0';
    bring_line(lineptr, n, buffer, input);
    retval = input;
    if (i != 0)
        input = 0;
    return (retval);
}
/**
 * @brief Updates the lineptr and n variables based
 * on the provided buffer and its size.
 *
 * If lineptr is NULL or n is less than the size of the buffer
 * it allocates memory for lineptr and assigns the buffer to lineptr.
 *  If n is less than the size of the buffer, it updates n.
 * Otherwise, it copies the buffer content to lineptr and frees the buffer.
 *
 * @param lineptr Pointer to the line buffer.
 * @param n Pointer to the size variable.
 * @param buffer Pointer to the buffer.
 * @param j Size of the buffer.
 * @return No return value.
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

    if (*lineptr == NULL)
    {
        if (j > READ_BUF_SIZE)
            *n = j;

        else
            *n = READ_BUF_SIZE;
        *lineptr = buffer;
    }
    else if (*n < j)
    {
        if (j > READ_BUF_SIZE)
            *n = j;
        else
            *n = READ_BUF_SIZE;
        *lineptr = buffer;
    }
    else
    {
        _strcpy(*lineptr, buffer);
        free(buffer);
    }
}
