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
    int endOfFileCondition;
    char *main_input;
    int syntax_error;
    int loop;

    while (1)
    {
        /* Display prompt*/
        write(STDIN_FILENO, "^-^ ", 4);

        /* Read input*/
        main_input = r_LineNode(&endOfFileCondition);

        /* Check for EOF*/
        if (endOfFileCondition != -1)
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
            loop = shellSplitCmd(simpdata, main_input);

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
    size_t result_index = 0;
    size_t length = strlen(in);
    size_t result_length = 0;
    size_t iterations;

    if (in == NULL || in[0] == '\0')
    {
        return NULL; /* Input is NULL or empty*/
    }

    /* Pass 1: Calculate the length of the result string*/
    for (iterations = 0; iterations < length; iterations++)
    {
        if (in[iterations] == '#' && (iterations == 0 || in[iterations - 1] == ' ' || in[iterations - 1] == '\t' || in[iterations - 1] == ';'))
        {
            /* Found a comment, skip until the end of the line*/
            while (iterations < length && in[iterations] != '\n')
            {
                iterations++;
            }
        }
        else
        {
            result_length++;
        }
    }

    if (result_length == 0)
    {
        /* The entire string is a comment*/
        free(in);
        return NULL;
    }

    /* Pass 2: Copy non-comment characters to the beginning of the input string*/
    for (iterations = 0; iterations < length; iterations++)
    {
        if (in[iterations] == '#' && (iterations == 0 || in[iterations - 1] == ' ' || in[iterations - 1] == '\t' || in[iterations - 1] == ';'))
        {
            /* Found a comment, skip until the end of the line*/
            while (iterations < length && in[iterations] != '\n')
            {
                iterations++;
            }
        }
        else
        {
            in[result_index++] = in[iterations];
        }
    }

    /* Null-terminate the modified input string*/
    in[result_index] = '\0';

    /* Reallocate memory to fit the new length*/
    in = realloc(in, result_index + 1);

    return in;
}
