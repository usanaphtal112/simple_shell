#include "shell.h"

/**
 * @brief Sets or updates the value of an environment variable.
 *
 * If the environment variable exists, its value is updated; otherwise, a new
 * environment variable is added.
 *
 * @param name The name of the environment variable.
 * @param value The value to set for the environment variable.
 * @param datash Pointer to the data structure containing shell information.
 */
void set_env(char *name, char *value, simple_shell_d *datash)
{
    int i;
    char *var_env, *name_env;

    for (i = 0; datash->_environ[i]; i++)
    {
        var_env = _strdup(datash->_environ[i]);
        name_env = _strtok(var_env, "=");
        if (_strcmp(name_env, name) == 0)
        {
            free(datash->_environ[i]);
            datash->_environ[i] = copy_info(name_env, value);
            free(var_env);
            return;
        }
        free(var_env);
    }

    datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
    datash->_environ[i] = copy_info(name, value);
    datash->_environ[i + 1] = NULL;
}

/**
 * @brief Copies and concatenates the given name and value into a new string.
 *
 * @param name The name part of the environment variable.
 * @param value The value part of the environment variable.
 * @return A new string containing the formatted environment variable.
 */
char *copy_info(char *name, char *value)
{
    char *new;
    int len_name, len_value, len;

    len_name = _strlen(name);
    len_value = _strlen(value);
    len = len_name + len_value + 2;
    new = malloc(sizeof(char) * (len));
    _strcpy(new, name);
    _strcat(new, "=");
    _strcat(new, value);
    _strcat(new, "\0");

    return (new);
}

/**
 * @brief Implementation of the `unsetenv` command.
 *
 * Removes the specified environment variable.
 *
 * @param datash Pointer to the data structure containing shell information.
 * @return 1 indicating success.
 */
int _unsetenv(simple_shell_d *datash)
{
    char **realloc_environ;
    char *var_env, *name_env;
    int i, j, k;

    if (datash->args[1] == NULL)
    {
        get_error(datash, -1);
        return (1);
    }
    k = -1;
    for (i = 0; datash->_environ[i]; i++)
    {
        var_env = _strdup(datash->_environ[i]);
        name_env = _strtok(var_env, "=");
        if (_strcmp(name_env, datash->args[1]) == 0)
        {
            k = i;
        }
        free(var_env);
    }
    if (k == -1)
    {
        get_error(datash, -1);
        return (1);
    }
    realloc_environ = malloc(sizeof(char *) * (i));
    for (i = j = 0; datash->_environ[i]; i++)
    {
        if (i != k)
        {
            realloc_environ[j] = datash->_environ[i];
            j++;
        }
    }
    realloc_environ[j] = NULL;
    free(datash->_environ[k]);
    free(datash->_environ);
    datash->_environ = realloc_environ;
    return (1);
}

/**
 * @brief Implementation of the `setenv` command.
 *
 * Sets or updates the value of an environment variable.
 *
 * @param datash Pointer to the data structure containing shell information.
 * @return 1 indicating success.
 */
int _setenv(simple_shell_d *datash)
{

    if (datash->args[1] == NULL || datash->args[2] == NULL)
    {
        get_error(datash, -1);
        return (1);
    }

    set_env(datash->args[1], datash->args[2], datash);

    return (1);
}
