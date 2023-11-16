#include "shell.h"

/**
 * @brief Displays the environment variables.
 *
 * @param datash Pointer to the data structure containing shell information.
 * @return 1 indicating success.
 */
int _env(simple_shell_d *datash)
{
    int i, j;

    for (i = 0; datash->_environ[i]; i++)
    {

        for (j = 0; datash->_environ[i][j]; j++)
            ;

        write(STDOUT_FILENO, datash->_environ[i], j);
        write(STDOUT_FILENO, "\n", 1);
    }
    datash->status = 0;

    return (1);
}

/**
 * @brief Compares an environment variable name with a given name.
 *
 * @param nenv The environment variable string.
 * @param name The name to compare.
 * @return The length of the common prefix if the names match, 0 otherwise.
 */
int cmp_env_name(const char *nenv, const char *name)
{
    int i;

    for (i = 0; nenv[i] != '='; i++)
    {
        if (nenv[i] != name[i])
        {
            return (0);
        }
    }

    return (i + 1);
}

/**
 * @brief Gets the value of an environment variable by name.
 *
 * @param name The name of the environment variable to retrieve.
 * @param _environ The array of environment variables.
 * @return The value of the environment variable if found, NULL otherwise.
 */
char *_getenv(const char *name, char **_environ)
{
    char *ptr_env;
    int i, mov;

    ptr_env = NULL;
    mov = 0;

    for (i = 0; _environ[i]; i++)
    {
        mov = cmp_env_name(_environ[i], name);
        if (mov)
        {
            ptr_env = _environ[i];
            break;
        }
    }

    return (ptr_env + mov);
}
