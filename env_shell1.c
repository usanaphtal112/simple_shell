#include "shell.h"

/**
 * @brief Displays the environment variables.
 *
 * @param simpdata Pointer to the data structure containing shell information.
 * @return 1 indicating success.
 */
int _env(simple_shell_d *simpdata)
{
    int i, j;

    for (i = 0; simpdata->_environ[i]; i++)
    {

        for (j = 0; simpdata->_environ[i][j]; j++)
            ;

        write(STDOUT_FILENO, simpdata->_environ[i], j);
        write(STDOUT_FILENO, "\n", 1);
    }
    simpdata->status = 0;

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
    size_t itr = 0;

    /* Compare characters until the end of either string or until '=' is encountered*/
    while (nenv[itr] && nenv[itr] != '=' && nenv[itr] == name[itr])
    {
        itr++;
    }

    /* Check if the comparison stopped because of '=' or if both strings match*/
    if (nenv[itr] == '=' && name[itr] == '\0')
    {
        /* Entire name matches, return the length of the common prefix*/
        return itr + 1;
    }
    else
    {
        /* Names do not match*/
        return 0;
    }
}

/**
 * @brief Compares the first 'n' characters of two strings in a case-sensitive manner.
 *
 * This function compares the first 'n' characters of the strings 'str1' and 'str2'
 * in a case-sensitive manner. The comparison stops when 'n' characters are
 * compared, or when the end of either string is reached. It returns 0 if the
 * compared portions are equal, a positive value if 'str1' is greater, and a
 * negative value if 'str2' is greater.
 *
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @param n The maximum number of characters to compare.
 * @return 0 if the compared portions are equal, a positive value if 'str1' is greater,
 *         and a negative value if 'str2' is greater.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
    while (n > 0 && *str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
        n--;
    }
    if (n == 0)
    {
        return 0;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
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
    int i;
    int name_len = _strlen(name);

    for (i = 0; _environ[i]; i++)
    {
        if (_strncmp(_environ[i], name, name_len) == 0 && _environ[i][name_len] == '=')
        {
            return _environ[i] + name_len + 1;
        }
    }

    return NULL;
}
