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
 * @brief Removes comments from the input string.
 *
 * Removes comments from the input string 'in'. If a '#' character
 * is encountered, the function removes the comment and trims any
 * trailing whitespace before the comment.
 *
 * @param in Pointer to the input string.
 * @return Pointer to the modified string without comments.
 */
char *without_comment(char *in)
{
    int i = 0;
    int j;
    int commentIndex = -1;
    /* Allocate memory for the result string*/
    char *result = (char *)malloc((commentIndex + 1) * sizeof(char));

    if (in == NULL || *in == '\0')
        return in; /* Nothing to do if the input is empty*/

    for (i = 0; in[i]; i++)
    {
        if (in[i] == '#' && (i == 0 || in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';'))
        {
            /* Find the index of the first '#' character*/
            commentIndex = i;
            break;
        }
    }

    if (commentIndex != -1)
    {
        /* Trim trailing whitespace before the comment*/
        while (commentIndex > 0 && (in[commentIndex - 1] == ' ' || in[commentIndex - 1] == '\t'))
            commentIndex--;

        if (result == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        /* Copy the non-comment part to the result string*/
        for (j = 0; j < commentIndex; j++)
            result[j] = in[j];

        result[commentIndex] = '\0'; /* Null-terminate the result string*/
        free(in);                    /* Free the original string*/
        return result;
    }

    return in; /* No comment found, return the original string*/
}
