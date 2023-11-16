#include "shell.h"

/**
 * get_builtin - Retrieve function pointer associated with built-in command.
 * @cmd: The name of the built-in command.
 *
 * This function searches for a built-in command by comparing the provided
 * name with the list of known built-in commands. If a match is found
 * it returns the function pointer associated with that built-in command.
 *
 * @return: Function pointer to the corresponding built-in
 * command if found, otherwise, NULL.
 */
int (*get_builtin(char *cmd))(simple_shell_d *)
{
    builtin_t builtin[] = {
        {"env", _env},
        {"exit", exit_shell},
        {"setenv", _setenv},
        {"unsetenv", _unsetenv},
        {"cd", cd_shell},
        {"help", get_help},
        {NULL, NULL}};
    int i;

    for (i = 0; builtin[i].name; i++)
    {
        if (_strcmp(builtin[i].name, cmd) == 0)
            break;
    }

    return (builtin[i].f);
}
