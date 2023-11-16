#include "shell.h"

/**
 * @brief Swaps special characters in the input string representation.
 *
 * Swaps '|' and '&' characters in the input -
 * string 'input' with their internal
 * representations (ASCII 16 and 12, respectively).
 * If 'bool' is 0, swaps the characters;
 * if 'bool' is 1, swaps them back to their original form.
 *
 * @param input Pointer to the input string.
 * @param bool Flag indicating whether to swap or revert the characters.
 * @return Pointer to the modified input string.
 */
char *swap_char(char *input, int bool)
{
    int i;

    if (bool == 0)
    {
        for (i = 0; input[i]; i++)
        {
            if (input[i] == '|')
            {
                if (input[i + 1] != '|')
                    input[i] = 16;
                else
                    i++;
            }

            if (input[i] == '&')
            {
                if (input[i + 1] != '&')
                    input[i] = 12;
                else
                    i++;
            }
        }
    }
    else
    {
        for (i = 0; input[i]; i++)
        {
            input[i] = (input[i] == 16 ? '|' : input[i]);
            input[i] = (input[i] == 12 ? '&' : input[i]);
        }
    }
    return (input);
}

/**
 * @brief Splits a string into tokens based on a delimiter.
 *
 * Splits the input string 'input' into tokens
 * using the delimiter defined by 'TOK_DELIM'.
 * Allocates memory dynamically for the tokens
 * returns a pointer to the resulting array.
 *
 * @param input Pointer to the input string.
 * @return Pointer to the array of tokens.
 */
char **split_line(char *input)
{
    size_t bsize;
    size_t i;
    char **tokens;
    char *token;

    bsize = TOK_BUFSIZE;
    tokens = malloc(sizeof(char *) * (bsize));
    if (tokens == NULL)
    {
        write(STDERR_FILENO, ": allocation error\n", 18);
        exit(EXIT_FAILURE);
    }

    token = _strtok(input, TOK_DELIM);
    tokens[0] = token;

    for (i = 1; token != NULL; i++)
    {
        if (i == bsize)
        {
            bsize += TOK_BUFSIZE;
            tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
            if (tokens == NULL)
            {
                write(STDERR_FILENO, ": allocation error\n", 18);
                exit(EXIT_FAILURE);
            }
        }
        token = _strtok(NULL, TOK_DELIM);
        tokens[i] = token;
    }

    return (tokens);
}

/**
 * @brief Moves to the next nodes in the separator and line linked lists.
 *
 * Moves to the next nodes in the separator linked
 * list ('list_s') and line linked list ('list_l')
 * based on the current state of the shell represented by 'datash'.
 *
 * @param list_s Pointer to the separator linked list.
 * @param list_l Pointer to the line linked list.
 * @param datash Pointer to the simple_shell_d struct.
 * @return No return value.
 */
void go_next(sep_list **list_s, line_list **list_l, simple_shell_d *datash)
{
    int loop_sep;
    sep_list *ls_s;
    line_list *ls_l;

    loop_sep = 1;
    ls_s = *list_s;
    ls_l = *list_l;

    while (ls_s != NULL && loop_sep)
    {
        if (datash->status == 0)
        {
            if (ls_s->separator == '&' || ls_s->separator == ';')
                loop_sep = 0;
            if (ls_s->separator == '|')
                ls_l = ls_l->next, ls_s = ls_s->next;
        }
        else
        {
            if (ls_s->separator == '|' || ls_s->separator == ';')
                loop_sep = 0;
            if (ls_s->separator == '&')
                ls_l = ls_l->next, ls_s = ls_s->next;
        }
        if (ls_s != NULL && !loop_sep)
            ls_s = ls_s->next;
    }

    *list_s = ls_s;
    *list_l = ls_l;
}

/**
 * @brief Splits and executes commands based on separators and operators.
 *
 * Splits the input string into lines and executes
 * commands based on separators and operators.
 * Uses linked lists for separators and lines to manage the command structure.
 *
 * @param datash Pointer to the simple_shell_d struct.
 * @param input Pointer to the input string.
 * @return 0 if the loop should terminate, 1 otherwise.
 */
int split_commands(simple_shell_d *datash, char *input)
{

    sep_list *head_s, *list_s;
    line_list *head_l, *list_l;
    int loop;

    head_s = NULL;
    head_l = NULL;

    add_nodes(&head_s, &head_l, input);

    list_s = head_s;
    list_l = head_l;

    while (list_l != NULL)
    {
        datash->input = list_l->line;
        datash->args = split_line(datash->input);
        loop = exec_line(datash);
        free(datash->args);

        if (loop == 0)
            break;

        go_next(&list_s, &list_l, datash);

        if (list_l != NULL)
            list_l = list_l->next;
    }

    free_sep_list(&head_s);
    free_line_list(&head_l);

    if (loop == 0)
        return (0);
    return (1);
}

/**
 * @brief Adds separator and line nodes to their respective linked lists.
 *
 * Modifies the input string 'input' by swapping
 * special characters and adds separator
 * nodes to the 'head_s' linked list and line
 * nodes to the 'head_l' linked list.
 *
 * @param head_s Pointer to the head of the separator linked list.
 * @param head_l Pointer to the head of the line linked list.
 * @param input Pointer to the input string.
 * @return No return value.
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
    int i;
    char *line;

    input = swap_char(input, 0);

    for (i = 0; input[i]; i++)
    {
        if (input[i] == ';')
            add_sep_node_end(head_s, input[i]);

        if (input[i] == '|' || input[i] == '&')
        {
            add_sep_node_end(head_s, input[i]);
            i++;
        }
    }

    line = _strtok(input, ";|&");
    do
    {
        line = swap_char(line, 1);
        add_line_node_end(head_l, line);
        line = _strtok(NULL, ";|&");
    } while (line != NULL);
}
