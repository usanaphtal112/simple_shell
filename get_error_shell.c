#include "shell.h"

/**
 * @brief Generate and display an error message based on the evaluation code.
 *
 * This function generates an error message based on the provided evaluation code
 * and displays it on the standard error output. The evaluation code corresponds
 * to specific error scenarios, such as environment-related errors,
 * permission denied, command not found, and exit shell errors.
 * The resulting error message is dynamically allocated and should be freed by the caller.
 *
 * @param simpdata Pointer to the simple_shell_d structure.
 * @param eval Evaluation code indicating the type of error.
 * @return The provided evaluation code.
 */
int get_error(simple_shell_d *simpdata, int eval)
{
    char *error = NULL;

    if (eval == -1)
        error = error_env(simpdata);
    else if (eval == 126)
        error = error_path_126(simpdata);
    else if (eval == 127)
        error = error_not_found(simpdata);
    else if (eval == 2)
    {
        if (_strcmp("exit", simpdata->args[0]) == 0)
            error = error_exit_shell(simpdata);
        else if (_strcmp("cd", simpdata->args[0]) == 0)
            error = error_get_cd(simpdata);
    }

    if (error)
    {
        write(STDERR_FILENO, error, _strlen(error));
        free(error);
    }

    simpdata->status = eval;
    return eval;
}
