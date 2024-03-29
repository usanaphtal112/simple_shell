#include "shell.h"

/**
 * @brief Executes a command line in the shell.
 *
 * Checks if the command is a built-in function or an external command and
 * executes it accordingly.
 *
 * @param datash Pointer to the data structure containing shell information.
 * @return 0 if the command was executed successfully, 1 otherwise.
 */
int exec_line(simple_shell_d *datash)
{
    int (*builtin)(simple_shell_d *datash);
    if (datash->args[0] == NULL)
        return (1);

    builtin = get_builtin(datash->args[0]);

    if (builtin != NULL)
        return (builtin(datash));

    return (cmd_exec(datash));
}
