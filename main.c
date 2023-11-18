#include "shell.h"

/**
 * set_data - Initialize the simple_shell_d structure with necessary information.
 * @datash: Pointer to the simple_shell_d structure.
 * @av: Array of strings containing the program arguments.
 *
 * This function initializes the simple_shell_d structure with information needed
 * for the shell's operation. It sets various fields such as av, input, args,
 * status, counter, _environ, and pid. The _environ array is populated with
 * environment variables, and the pid field is set to the current process ID.
 */
void set_data(simple_shell_d *datash, char **av)
{
    unsigned int i;

    datash->av = av;
    datash->input = NULL;
    datash->args = NULL;
    datash->status = 0;
    datash->counter = 1;

    for (i = 0; environ[i]; i++)
        ;

    datash->_environ = malloc(sizeof(char *) * (i + 1));

    for (i = 0; environ[i]; i++)
    {
        datash->_environ[i] = _strdup(environ[i]);
    }

    datash->_environ[i] = NULL;
    datash->pid = aux_itoa(getpid());
}

/**
 * free_data - Free allocated memory in the simple_shell_d structure.
 * @datash: Pointer to the simple_shell_d structure.
 *
 * This function frees the dynamically allocated memory within the simple_shell_d
 * structure, including the _environ array and the pid string. It iterates
 * through the _environ array and frees each string element. After freeing the
 * memory, the pointers are set to NULL to avoid potential use-after-free.
 */
void free_data(simple_shell_d *datash)
{
    unsigned int i;

    for (i = 0; datash->_environ[i]; i++)
    {
        free(datash->_environ[i]);
    }

    free(datash->_environ);
    free(datash->pid);
}

/**
 * main - Entry point for the custom shell program.
 * @ac: Number of command-line arguments.
 * @av: Array of strings containing command-line arguments.
 *
 * This function serves as the entry point for the custom shell program.
 * It initializes the simple_shell_d structure, sets up a signal handler for
 * SIGINT (Ctrl+C), enters the shell loop, and frees allocated memory
 * before returning the exit status.
 *
 * @return: The exit status of the shell program.
 */

int main(int ac, char **av)
{
    simple_shell_d datash;
    (void)ac;

    signal(SIGINT, get_sigint);
    set_data(&datash, av);
    shell_loop(&datash);
    free_data(&datash);
    if (datash.status < 0)
        return (255);
    return (datash.status);
}
