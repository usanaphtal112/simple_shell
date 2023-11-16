#include "shell.h"

/**
 * cd_shell - Change the current working directory based on provided arguments.
 * @datash: Pointer to the simple_shell_d structure.
 *
 * This function interprets the arguments passed to the 'cd' shell command and
 * changes the current working directory accordingly. It supports various
 * directory specifications, such as absolute paths, relative paths, "$HOME",
 * "~" (home directory), and "--" (previous directory).
 * If no argument is provided or if the argument is "$HOME", "~", or "--",
 * it changes the directory to the user's home directory. If argument is "-",
 * it changes the directory to the previous working directory. If the argument
 * is ".", "..", or a valid path, it changes
 * the directory to the specified path.
 * Returns: 1 on success.
 */
int cd_shell(simple_shell_d *datash)
{
    char *dir;
    int ishome, ishome2, isddash;

    dir = datash->args[1];

    if (dir != NULL)
    {
        ishome = _strcmp("$HOME", dir);
        ishome2 = _strcmp("~", dir);
        isddash = _strcmp("--", dir);
    }

    if (dir == NULL || !ishome || !ishome2 || !isddash)
    {
        cd_to_home(datash);
        return (1);
    }

    if (_strcmp("-", dir) == 0)
    {
        cd_previous(datash);
        return (1);
    }

    if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
    {
        cd_dot(datash);
        return (1);
    }

    cd_to(datash);

    return (1);
}
