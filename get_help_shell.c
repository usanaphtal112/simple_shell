#include "shell.h"

/**
 * get_help - Display help information for shell commands.
 * @datash: Pointer to the simple_shell_d structure.
 *
 * This function displays help information for various shell commands based on
 * the provided command-line argument. If no argument is provided, general help
 * information for the shell is displayed. Otherwise, it checks for specific
 * command names and displays their respective help information. If the command
 * is not recognized, an error message is displayed
 *
 * @return: 1 to indicate successful execution.
 */
int get_help(simple_shell_d *datash)
{

    if (datash->args[1] == 0)
        aux_help_general();
    else if (_strcmp(datash->args[1], "setenv") == 0)
        aux_help_setenv();
    else if (_strcmp(datash->args[1], "env") == 0)
        aux_help_env();
    else if (_strcmp(datash->args[1], "unsetenv") == 0)
        aux_help_unsetenv();
    else if (_strcmp(datash->args[1], "help") == 0)
        aux_help();
    else if (_strcmp(datash->args[1], "exit") == 0)
        aux_help_exit();
    else if (_strcmp(datash->args[1], "cd") == 0)
        aux_help_cd();
    else if (_strcmp(datash->args[1], "alias") == 0)
        aux_help_alias();
    else
        write(STDERR_FILENO, datash->args[0],
              _strlen(datash->args[0]));

    datash->status = 0;
    return (1);
}
