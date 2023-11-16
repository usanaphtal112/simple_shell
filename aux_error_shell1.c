#include "shell.h"

/**
 * error_get_cd - Generate an error message for 'cd' command errors.
 * @simpdata: Pointer to the simple_shell_d structure.
 *
 * This function generates an error message for 'cd' command errors, including
 * information about the program name, error type, command
 * It handles both illegal options and cases where the specified directory
 * The resulting error message is dynamically allocated
 *
 * @return: A pointer to the dynamically allocated error message.
 *          Returns NULL if memory allocation fails.
 */

char *error_get_cd(simple_shell_d *simpdata)
{
    int length, len_id;
    char *error, *ver_str, *msg;

    ver_str = aux_itoa(simpdata->counter);
    if (simpdata->args[1][0] == '-')
    {
        msg = ": Illegal option ";
        len_id = 2;
    }
    else
    {
        msg = ": can't cd to ";
        len_id = _strlen(simpdata->args[1]);
    }

    length = _strlen(simpdata->av[0]) + _strlen(simpdata->args[0]);
    length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
    error = malloc(sizeof(char) * (length + 1));

    if (error == 0)
    {
        free(ver_str);
        return (NULL);
    }

    error = strcat_cd(simpdata, msg, error, ver_str);

    free(ver_str);

    return (error);
}

/**
 * strcat_cd - Concatenate error message components for 'cd'
 * @simpdata: Pointer to the simple_shell_d structure.
 * @msg: String message indicating the type of error.
 * @error: Buffer to store the resulting error message.
 * @ver_str: String representation of the shell's execution counter.
 *
 * This function constructs an error message for 'cd'
 * various components such as the program name, error type
 * information. It handles illegal options by including
 * The resulting error message is stored in the provided buffer.
 *
 * @return: A pointer to the constructed error message.
 */
char *strcat_cd(simple_shell_d *simpdata, char *msg, char *error, char *ver_str)
{
    char *illegal_flag;

    _strcpy(error, simpdata->av[0]);
    _strcat(error, ": ");
    _strcat(error, ver_str);
    _strcat(error, ": ");
    _strcat(error, simpdata->args[0]);
    _strcat(error, msg);
    if (simpdata->args[1][0] == '-')
    {
        illegal_flag = malloc(3);
        illegal_flag[0] = '-';
        illegal_flag[1] = simpdata->args[1][1];
        illegal_flag[2] = '\0';
        _strcat(error, illegal_flag);
        free(illegal_flag);
    }
    else
    {
        _strcat(error, simpdata->args[1]);
    }

    _strcat(error, "\n");
    _strcat(error, "\0");
    return (error);
}

/**
 * error_exit_shell - Generate an error message
 *  for 'exit' command errors.
 * @simpdata: Pointer to the simple_shell_d structure.
 *
 * This function generates an error message
 * for 'exit' command errors, including
 * and should be freed by the caller.
 *
 * @return: A pointer to the dynamically allocated error message.
 * Returns NULL if memory allocation fails.
 */
char *error_exit_shell(simple_shell_d *simpdata)
{
    int length;
    char *error;
    char *ver_str;

    ver_str = aux_itoa(simpdata->counter);
    length = _strlen(simpdata->av[0]) + _strlen(ver_str);
    length += _strlen(simpdata->args[0]) + _strlen(simpdata->args[1]) + 23;
    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(ver_str);
        return (NULL);
    }
    _strcpy(error, simpdata->av[0]);
    _strcat(error, ": ");
    _strcat(error, ver_str);
    _strcat(error, ": ");
    _strcat(error, simpdata->args[0]);
    _strcat(error, ": Illegal number: ");
    _strcat(error, simpdata->args[1]);
    _strcat(error, "\n\0");
    free(ver_str);

    return (error);
}

/**
 * error_not_found - Generate an error message for command not found errors.
 * @simpdata: Pointer to the simple_shell_d structure.
 *
 * The resulting error message is dynamically allocated
 *
 * @return: A pointer to the dynamically allocated error message.
 *          Returns NULL if memory allocation fails.
 */
char *error_not_found(simple_shell_d *simpdata)
{
    int length;
    char *error;
    char *ver_str;

    ver_str = aux_itoa(simpdata->counter);
    length = _strlen(simpdata->av[0]) + _strlen(ver_str);
    length += _strlen(simpdata->args[0]) + 16;
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
    _strcat(error, ": not found\n");
    _strcat(error, "\0");
    free(ver_str);
    return (error);
}
