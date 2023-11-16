#include "shell.h"

/**
 * aux_help_cd - Displays information about the 'cd' builtin command.
 *
 * The aux_help_cd function prints information about the 'cd' command.
 * It provides details on changing the shell working directory.
 */
void aux_help_cd(void)
{
    char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

    write(STDOUT_FILENO, help, _strlen(help));
    help = "\tChange the shell working directory.\n ";
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help - Displays information about builtin commands.
 *
 * The aux_help function prints brief summaries of builtin commands.
 * It provides information about the 'help' command.
 */
void aux_help(void)
{
    char *help = "help: help [-dms] [pattern ...]\n";

    write(STDOUT_FILENO, help, _strlen(help));
    help = "\tDisplay information about builtin commands.\n ";
    write(STDOUT_FILENO, help, _strlen(help));
    help = "Displays brief summaries of builtin commands.\n";
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_alias - Displays information about the 'alias' builtin command.
 *
 * The aux_help_alias function prints information about the 'alias' command.
 * It provides details on how to define or display aliases.
 */
void aux_help_alias(void)
{
    char *help = "alias: alias [-p] [name[=value]...]\n";

    write(STDOUT_FILENO, help, _strlen(help));
    help = "\tDefine or display aliases.\n ";
    write(STDOUT_FILENO, help, _strlen(help));
}
