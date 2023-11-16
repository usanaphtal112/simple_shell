#include "shell.h"

/**
 * set_data - Initialize the simple_shell_d structure with necessary information.
 * @simpdata: Pointer to the simple_shell_d structure.
 * @av: Array of strings containing the program arguments.
 *
 * This function initializes the simple_shell_d structure with information needed
 * for the shell's operation. It sets various fields such as av, main_input, args,
 * status, counter, _environ, and pid. The _environ array is populated with
 * environment variables, and the pid field is set to the current process ID.
 */
void set_data(simple_shell_d *simpdata, char **av)
{
    unsigned int i;
    unsigned int env_count = 0;

    simpdata->av = av;
    simpdata->main_input = NULL;
    simpdata->args = NULL;
    simpdata->status = 0;
    simpdata->counter = 1;

    /* Count the number of environment variables*/
    while (environ[env_count])
    {
        env_count++;
    }

    /* Allocate memory for _environ array */
    simpdata->_environ = (char **)malloc(sizeof(char *) * (env_count + 1));
    for (i = 0; i < env_count; i++)
    {
        simpdata->_environ[i] = _strdup(environ[i]);
    }

    simpdata->_environ[env_count] = NULL;
    simpdata->pid = aux_itoa(getpid());
}

/**
 * free_data - Free allocated memory in the simple_shell_d structure.
 * @simpdata: Pointer to the simple_shell_d structure.
 *
 * This function frees the dynamically allocated memory within the simple_shell_d
 * structure, including the _environ array and the pid string. It iterates
 * through the _environ array and frees each string element. After freeing the
 * memory, the pointers are set to NULL to avoid potential use-after-free.
 */
void free_data(simple_shell_d *simpdata)
{
    unsigned int i;

    for (i = 0; simpdata->_environ[i]; i++)
    {
        free(simpdata->_environ[i]);
    }

    free(simpdata->_environ);
    free(simpdata->pid);
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
    simple_shell_d simpdata;
    (void)ac;

    signal(SIGINT, get_sigint);
    set_data(&simpdata, av);
    shell_loop(&simpdata);
    free_data(&simpdata);
    if (simpdata.status < 0)
        return (255);
    return (simpdata.status);
}

