#include "shell.h"

/**
 * get_error - Generate and display an error message
 * based on the evaluation code.
 * @datash: Pointer to the simple_shell_d structure.
 * @eval: Evaluation code indicating the type of error.
 *
 * This function generates an error message based
 *  on the provided evaluation code and displays it on the
 * standard error output. The evaluation code corresponds
 * to specific error scenarios, such as environment-related errors
 * permission denied, command not found, and exit shell errors.
 * The resulting error message is dynamically
 * allocated and should be freed by the caller.
 *
 * @return: The provided evaluation code.
 */
int get_error(simple_shell_d *datash, int eval)
{
    char *error;

    switch (eval)
    {
    case -1:
        error = error_env(datash);
        break;
    case 126:
        error = error_path_126(datash);
        break;
    case 127:
        error = error_not_found(datash);
        break;
    case 2:
        if (_strcmp("exit", datash->args[0]) == 0)
            error = error_exit_shell(datash);
        else if (_strcmp("cd", datash->args[0]) == 0)
            error = error_get_cd(datash);
        break;
    }

    if (error)
    {
        write(STDERR_FILENO, error, _strlen(error));
        free(error);
    }

    datash->status = eval;
    return (eval);
}
