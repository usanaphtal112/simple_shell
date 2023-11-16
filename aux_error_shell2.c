#include "shell.h"

/**
 * error_path_126 - Generate an error message for
 * permission denied errors (exit code 126).
 * @simpdata: Pointer to the simple_shell_d structure.
 *
 * This function generates an error message for
 * permission denied errors (exit code 126), including information
 * about the program name, the shell's execution counter,
 * and the command. The resulting error message is dynamically allocated
 * and should be freed by the caller.
 *
 * @return: A pointer to the dynamically allocated error message.
 *          Returns NULL if memory allocation fails.
 */
char *error_path_126(simple_shell_d *simpdata)
{
    int length;
    char *ver_str;
    char *error;

    ver_str = aux_itoa(simpdata->counter);
    length = _strlen(simpdata->av[0]) + _strlen(ver_str);
    length += _strlen(simpdata->args[0]) + 24;
    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(error);
        free(ver_str);
        return (NULL);
    }
    _strcpy(error, simpdata->av[0]);
    _strcat(error, ": ");
    _strcat(error, ver_str);
    _strcat(error, ": ");
    _strcat(error, simpdata->args[0]);
    _strcat(error, ": Permission denied\n");
    _strcat(error, "\0");
    free(ver_str);
    return (error);
}

/**
 * error_env - Generate an error message for environment-related errors.
 * @simpdata: Pointer to the simple_shell_d structure.
 *
 * This function generates an error message for environment-related errors,
 * including information about the program name, the shell's execution counter
 * the command, and a generic message indicating the inability to add/remove
 * from the environment. The resulting error message
 * is dynamically allocated and should be freed by the caller.
 *
 * @return: A pointer to the dynamically allocated error message.
 *          Returns NULL if memory allocation fails.
 */
char *error_env(simple_shell_d *simpdata)
{
    int length;
    char *error;
    char *ver_str;
    char *msg;

    ver_str = aux_itoa(simpdata->counter);
    msg = ": Unable to add/remove from environment\n";
    length = _strlen(simpdata->av[0]) + _strlen(ver_str);
    length += _strlen(simpdata->args[0]) + _strlen(msg) + 4;
    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(error);
        free(ver_str);
        return (NULL);
    }

    _strcpy(error, simpdata->av[0]);
    _strcat(error, ": ");
    _strcat(error, ver_str);
    _strcat(error, ": ");
    _strcat(error, simpdata->args[0]);
    _strcat(error, msg);
    _strcat(error, "\0");
    free(ver_str);

    return (error);
}
