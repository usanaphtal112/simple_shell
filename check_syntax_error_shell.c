#include "shell.h"

/**
 * @brief Checks for syntax errors in the main_input string.
 *
 * Checks for syntax errors in the main_input string 'main_input'
 * and prints an error message if any errors are found.
 *
 * @param simpdata Pointer to the simple_shell_d struct.
 * @param main_input Pointer to the main_input string.
 * @return 0 if no syntax errors are found, 1 otherwise.
 */
int check_syntax_error(simple_shell_d *simpdata, char *main_input)
{
    int begin = 0;
    int f_char = 0;
    int i = 0;

    f_char = first_char(main_input, &begin);
    if (f_char == -1)
    {
        print_syntax_error(simpdata, main_input, begin, 0);
        return (1);
    }

    i = error_sep_op(main_input + begin, 0, *(main_input + begin));
    if (i != 0)
    {
        print_syntax_error(simpdata, main_input, begin + i, 1);
        return (1);
    }

    return (0);
}

/**
 * @brief Checks for syntax errors related to separators and operators.
 *
 * Checks for syntax errors in the string 'main_input' related to separators and operators.
 * Returns the position of the first syntax error encountered.
 *
 * @param main_input Pointer to the main_input string.
 * @param i Current position in the string.
 * @param last Last encountered separator or operator.
 * @return Position of the first syntax error, or 0 if no errors are found.
 */
int error_sep_op(char *main_input, int i, char last)
{
    int count;

    count = 0;
    if (*main_input == '\0')
        return (0);

    if (*main_input == ' ' || *main_input == '\t')
        return (error_sep_op(main_input + 1, i + 1, last));

    if (*main_input == ';')
        if (last == '|' || last == '&' || last == ';')
            return (i);

    if (*main_input == '|')
    {
        if (last == ';' || last == '&')
            return (i);

        if (last == '|')
        {
            count = repeated_char(main_input, 0);
            if (count == 0 || count > 1)
                return (i);
        }
    }

    if (*main_input == '&')
    {
        if (last == ';' || last == '|')
            return (i);

        if (last == '&')
        {
            count = repeated_char(main_input, 0);
            if (count == 0 || count > 1)
                return (i);
        }
    }

    return (error_sep_op(main_input + 1, i + 1, *main_input));
}

/**
 * @brief Finds the first non-whitespace character in a string.
 *
 * Finds the first non-whitespace character in the string 'main_input' and sets 'i' to its position.
 *
 * @param main_input Pointer to the main_input string.
 * @param i Pointer to the variable storing the position of the first non-whitespace character.
 * @return 0 if a non-whitespace character is found, -1 otherwise.
 */
int first_char(char *main_input, int *i)
{

    for (*i = 0; main_input[*i]; *i += 1)
    {
        if (main_input[*i] == ' ' || main_input[*i] == '\t')
            continue;

        if (main_input[*i] == ';' || main_input[*i] == '|' || main_input[*i] == '&')
            return (-1);

        break;
    }

    return (0);
}

/**
 * @brief Prints a syntax error message to standard error.
 *
 * Prints a syntax error message to standard
 * error based on the given 'main_input' string,
 * position 'i', and 'bool' flag indicating whether the error
 * is at the current position
 * or one position before.
 *
 * @param simpdata Pointer to the simple_shell_d struct.
 * @param main_input Pointer to the main_input string.
 * @param i Position in the string where the error occurred.
 * @param bool Flag indicating if the error is at the current
 * position (0) or one position before (1).
 */
void print_syntax_error(simple_shell_d *simpdata, char *main_input, int i, int bool)
{
    char *msg, *msg2, *msg3, *error, *counter;
    int length;

    if (main_input[i] == ';')
    {
        if (bool == 0)
            msg = (main_input[i + 1] == ';' ? ";;" : ";");
        else
            msg = (main_input[i - 1] == ';' ? ";;" : ";");
    }

    if (main_input[i] == '|')
        msg = (main_input[i + 1] == '|' ? "||" : "|");

    if (main_input[i] == '&')
        msg = (main_input[i + 1] == '&' ? "&&" : "&");

    msg2 = ": Syntax error: \"";
    msg3 = "\" unexpected\n";
    counter = aux_itoa(simpdata->counter);
    length = _strlen(simpdata->av[0]) + _strlen(counter);
    length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

    error = malloc(sizeof(char) * (length + 1));
    if (error == 0)
    {
        free(counter);
        return;
    }
    _strcpy(error, simpdata->av[0]);
    _strcat(error, ": ");
    _strcat(error, counter);
    _strcat(error, msg2);
    _strcat(error, msg);
    _strcat(error, msg3);
    _strcat(error, "\0");

    write(STDERR_FILENO, error, length);
    free(error);
    free(counter);
}

/**
 * @brief Recursively counts the number of consecutive repeated characters.
 *
 * Recursively counts the number of consecutive repeated characters in the string 'main_input'
 * starting from the character at position 'i'.
 *
 * @param main_input Pointer to the main_input string.
 * @param i Starting position in the string.
 * @return The number of consecutive repeated characters.
 */
int repeated_char(char *main_input, int i)
{
    if (*(main_input - 1) == *main_input)
        return (repeated_char(main_input - 1, i + 1));

    return (i);
}
