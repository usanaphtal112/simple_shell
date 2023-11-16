#include "shell.h"

/**
 * @brief Shell loop for continuous input and command execution.
 *
 * The main loop for the shell, continuously prompts
 * the user for input, reads the input,
 * removes comments, checks for syntax errors
 * replaces variables, and executes commands.
 *
 * @param datash Pointer to the data_shell struct.
 * @return No return value.
 */
void shell_loop(data_shell *datash)
{
    int loop, i_eof;
    char *input;

    loop = 1;
    while (loop == 1)
    {
        write(STDIN_FILENO, "^-^ ", 4);
        input = read_line(&i_eof);
        if (i_eof != -1)
        {
            input = without_comment(input);
            if (input == NULL)
                continue;

            if (check_syntax_error(datash, input) == 1)
            {
                datash->status = 2;
                free(input);
                continue;
            }
            input = rep_var(input, datash);
            loop = split_commands(datash, input);
            datash->counter += 1;
            free(input);
        }
        else
        {
            loop = 0;
            free(input);
        }
    }
}

/**
 * @brief Removes comments from the input string.
 *
 * Removes comments from the input string 'in'. If a '#'
 * character is encountered,
 * the function truncates the string up to the '#' character
 * If the '#' is the first character, the entire
 * string is freed, and NULL is returned.
 *
 * @param in Pointer to the input string.
 * @return Pointer to the modified string without comments
 * NULL if the entire string is a comment.
 */
char *without_comment(char *in)
{
    int i, up_to;

    up_to = 0;
    for (i = 0; in[i]; i++)
    {
        if (in[i] == '#')
        {
            if (i == 0)
            {
                free(in);
                return (NULL);
            }

            if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
                up_to = i;
        }
    }

    if (up_to != 0)
    {
        in = _realloc(in, i, up_to + 1);
        in[up_to] = '\0';
    }

    return (in);
}
