#include "shell.h"

/**
 * cd_to_home - Change the current working directory.
 * @datash: Pointer to the simple_shell_d structure.
 *
 * This function changes the current working directory
 * It updates the environment variables PWD and OLDPWD accordingly.
 * If the home directory is not found, it sets the appropriate error code.
 */

void cd_to_home(simple_shell_d *datash)
{
    char *p_pwd, *home;
    char pwd[PATH_MAX];

    getcwd(pwd, sizeof(pwd));
    p_pwd = _strdup(pwd);

    home = _getenv("HOME", datash->_environ);

    if (home == NULL)
    {
        set_env("OLDPWD", p_pwd, datash);
        free(p_pwd);
        return;
    }

    if (chdir(home) == -1)
    {
        get_error(datash, 2);
        free(p_pwd);
        return;
    }

    set_env("OLDPWD", p_pwd, datash);
    set_env("PWD", home, datash);
    free(p_pwd);
    datash->status = 0;
}

/**
 * cd_to - Change the current working directory to the specified directory.
 * @datash: Pointer to the simple_shell_d structure.
 *
 * This function changes the current working directory
 * It updates the environment variables PWD and OLDPWD accordingly.
 * If the specified directory is invalid, it sets the appropriate error code.
 */
void cd_to(simple_shell_d *datash)
{
    char pwd[PATH_MAX];
    char *dir, *cp_pwd, *cp_dir;

    getcwd(pwd, sizeof(pwd));

    dir = datash->args[1];
    if (chdir(dir) == -1)
    {
        get_error(datash, 2);
        return;
    }

    cp_pwd = _strdup(pwd);
    set_env("OLDPWD", cp_pwd, datash);

    cp_dir = _strdup(dir);
    set_env("PWD", cp_dir, datash);

    free(cp_pwd);
    free(cp_dir);

    datash->status = 0;

    chdir(dir);
}

/**
 * cd_previous - Change the current working directory
 * @datash: Pointer to the simple_shell_d structure.
 *
 * This function changes the current working directory.
 * and updates the environment variables PWD and OLDPWD accordingly.
 * It also prints the new current directory to the standard output.
 */
void cd_previous(simple_shell_d *datash)
{
    char pwd[PATH_MAX];
    char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

    getcwd(pwd, sizeof(pwd));
    cp_pwd = _strdup(pwd);

    p_oldpwd = _getenv("OLDPWD", datash->_environ);

    if (p_oldpwd == NULL)
        cp_oldpwd = cp_pwd;
    else
        cp_oldpwd = _strdup(p_oldpwd);

    set_env("OLDPWD", cp_pwd, datash);

    if (chdir(cp_oldpwd) == -1)
        set_env("PWD", cp_pwd, datash);
    else
        set_env("PWD", cp_oldpwd, datash);

    p_pwd = _getenv("PWD", datash->_environ);

    write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
    write(STDOUT_FILENO, "\n", 1);

    free(cp_pwd);
    if (p_oldpwd)
        free(cp_oldpwd);

    datash->status = 0;

    chdir(p_pwd);
}

/**
 * cd_dot - Change the current working directory to
 * the specified directory or stay in the current directory.
 * @datash: Pointer to the simple_shell_d structure.
 *
 * This function changes the current working directory
 * or remains in the current directory if the specified directory is "." or "/"
 * It updates the environment variables PWD and OLDPWD accordingly.
 */
void cd_dot(simple_shell_d *datash)
{
    char pwd[PATH_MAX];
    char *dir, *cp_pwd, *cp_strtok_pwd;

    getcwd(pwd, sizeof(pwd));
    cp_pwd = _strdup(pwd);
    set_env("OLDPWD", cp_pwd, datash);
    dir = datash->args[1];
    if (_strcmp(".", dir) == 0)
    {
        set_env("PWD", cp_pwd, datash);
        free(cp_pwd);
        return;
    }
    if (_strcmp("/", cp_pwd) == 0)
    {
        free(cp_pwd);
        return;
    }
    cp_strtok_pwd = cp_pwd;
    reverse_string(cp_strtok_pwd);
    cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
    if (cp_strtok_pwd != NULL)
    {
        cp_strtok_pwd = _strtok(NULL, "\0");

        if (cp_strtok_pwd != NULL)
            reverse_string(cp_strtok_pwd);
    }
    if (cp_strtok_pwd != NULL)
    {
        chdir(cp_strtok_pwd);
        set_env("PWD", cp_strtok_pwd, datash);
    }
    else
    {
        chdir("/");
        set_env("PWD", "/", datash);
    }
    datash->status = 0;
    free(cp_pwd);
}
