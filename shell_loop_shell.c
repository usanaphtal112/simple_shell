#include "shell.h"

/**
 * @brief Shell loop for continuous input and command execution.
 *
 * The main loop for the shell, continuously prompts
 * the user for input, reads the input,
 * removes comments, checks for syntax errors
 * replaces variables, and executes commands.
 *
 * @param simpdata Pointer to the simple_shell_d struct.
 * @return No return value.
 */
void shell_loop(simple_shell_d *simpdata)
{
    int i_eof;
    char *main_input;
    int syntax_error;
    int loop;

    while (1)
    {
        /* Display prompt*/
        write(STDIN_FILENO, "^-^ ", 4);

        /* Read input*/
        main_input = read_line(&i_eof);

        /* Check for EOF*/
        if (i_eof != -1)
        {
            /* Process input*/
            main_input = without_comment(main_input);
            if (main_input == NULL)
                continue;

            /* Check syntax errors*/
            syntax_error = check_syntax_error(simpdata, main_input);
            if (syntax_error == 1)
            {
                simpdata->status = 2;
                free(main_input);
                continue;
            }

            /* Replace variables*/
            main_input = rep_var(main_input, simpdata);

            /* Execute commands*/
            loop = split_commands(simpdata, main_input);

            /* Update counter*/
            simpdata->counter += 1;

            /* Free allocated memory*/
            free(main_input);
        }
        else
        {
            /* Handle EOF*/
            free(main_input);
            break;
        }

        /* Check loop condition*/
        if (loop == 0)
            break;
    }
}

/**
 * @brief Removes comments from the main_input string.
 *
 * Removes comments from the main_input string 'in'. If a '#'
 * character is encountered,
 * the function truncates the string up to the '#' character
 * If the '#' is the first character, the entire
 * string is freed, and NULL is returned.
 *
 * @param in Pointer to the main_input string.
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
