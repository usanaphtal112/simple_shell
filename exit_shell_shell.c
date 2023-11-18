#include "shell.h"

/**
 * exit_shell - Terminate the shell program with a specified exit status.
 * @datash: Pointer to the simple_shell_d structure.
 *
 * This function handles the 'exit' shell command, allowing user to terminate
 * the shell program with an optional exit status. If an exit status provided
 * as an argument, it is converted to an unsigned integer
 * used as the exit status.
 * If the argument is not a valid digit or exceeds the limit,
 * and the exit status is set to 2. If no argument is provided
 *
 * @return: 0 on successful termination, 1 if an error occurred.
 */
int exit_shell(simple_shell_d *datash)
{
    unsigned int ustatus;
    int big_num;
    int is_dig;
    int str_len;

    if (datash->args[1] != NULL)
    {
        ustatus = _atoi(datash->args[1]);
        is_dig = _isdigit(datash->args[1]);
        str_len = _strlen(datash->args[1]);
        big_num = ustatus > (unsigned int)INT_MAX;
        if (!is_dig || str_len > 10 || big_num)
        {
            get_error(datash, 2);
            datash->status = 2;
            return (1);
        }
        datash->status = (ustatus % 256);
    }
    return (0);
}
