#include "shell.h"

/**
 * get_sigint - Signal handler for the SIGINT signal (Ctrl+C).
 * @sig: Signal number (unused, required by the signal handler signature).
 *
 * This function serves as a signal handler for the SIGINT signal (Ctrl+C).
 * When the SIGINT signal is received, it writes a newline and a custom prompt
 * to the standard output to indicate the interruption of the current process.
 *
 * Note: The `(void)sig;`statement is used to avoid "unused parameter" warning
 */

void get_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n^-^ ", 5);
}
