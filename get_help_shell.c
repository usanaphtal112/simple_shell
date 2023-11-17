#include "shell.h"

/**
 * get_help - Display help information for shell commands.
 * @simpdata: Pointer to the simple_shell_d structure.
 *
 * This function displays help information for various shell commands based on
 * the provided command-line argument. If no argument is provided, general help
 * information for the shell is displayed. Otherwise, it checks for specific
 * command names and displays their respective help information. If the command
 * is not recognized, an error message is displayed
 *
 * @return: 1 to indicate successful execution.
 */
int get_help(simple_shell_d *simpdata)
{
    const char *command = simpdata->args[1];

    if (command == NULL)
    {
        aux_help_general();
    }
    else if (strcmp(command, "setenv") == 0)
    {
        aux_help_setenv();
    }
    else if (strcmp(command, "env") == 0)
    {
        aux_help_env();
    }
    else if (strcmp(command, "unsetenv") == 0)
    {
        aux_help_unsetenv();
    }
    else if (strcmp(command, "help") == 0)
    {
        aux_help();
    }
    else if (strcmp(command, "exit") == 0)
    {
        aux_help_exit();
    }
    else if (strcmp(command, "cd") == 0)
    {
        aux_help_cd();
    }
    else if (strcmp(command, "alias") == 0)
    {
        aux_help_alias();
    }
    else
    {
        write(STDERR_FILENO, simpdata->args[0], _strlen(simpdata->args[0]));
    }

    simpdata->status = 0;
    return 1;
}
