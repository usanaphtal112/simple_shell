#include "shell.h"

/**
 * @brief Checks for and adds special variables
 *
 * Checks the main_input string 'in' for special
 * variables such as "$?", "$$", "\n", " ", "\t", and ";".
 * Adds these variables to the replacement variable
 * linked list ('h') with their corresponding values.
 *
 * @param h Pointer to the head of the replacement variable linked list.
 * @param in Pointer to the main_input string.
 * @param st Pointer to the status string.
 * @param data Pointer to the simple_shell_d struct.
 * @return The length of the checked string.
 */
int check_vars(read_variable **h, char *in, char *st, simple_shell_d *data)
{
    int i, lst, lpd;

    lst = _strlen(st);
    lpd = _strlen(data->pid);

    for (i = 0; in[i]; i++)
    {
        if (in[i] == '$')
        {
            if (in[i + 1] == '?')
                variable_addition(h, 2, st, lst), i++;
            else if (in[i + 1] == '$')
                variable_addition(h, 2, data->pid, lpd), i++;
            else if (in[i + 1] == '\n')
                variable_addition(h, 0, NULL, 0);
            else if (in[i + 1] == '\0')
                variable_addition(h, 0, NULL, 0);
            else if (in[i + 1] == ' ')
                variable_addition(h, 0, NULL, 0);
            else if (in[i + 1] == '\t')
                variable_addition(h, 0, NULL, 0);
            else if (in[i + 1] == ';')
                variable_addition(h, 0, NULL, 0);
            else
                check_env(h, in + i, data);
        }
    }

    return (i);
}
/**
 * @brief Checks and adds environment variables
 *
 * Checks the main_input string 'in' for environment variables
 * adds them to the replacement variable linked list ('h').
 * Environment variables are compared against the current environment
 * in the simple_shell_d struct ('data') to find their values.
 *
 * @param h Pointer to the head of the replacement variable linked list.
 * @param in Pointer to the main_input string.
 * @param data Pointer to the simple_shell_d struct.
 * @return No return value.
 */
void check_env(read_variable **h, char *in, simple_shell_d *data)
{
    int row, chr, j, lval;
    char **_envr;

    _envr = data->_environ;
    for (row = 0; _envr[row]; row++)
    {
        for (j = 1, chr = 0; _envr[row][chr]; chr++)
        {
            if (_envr[row][chr] == '=')
            {
                lval = _strlen(_envr[row] + chr + 1);
                variable_addition(h, j, _envr[row] + chr + 1, lval);
                return;
            }

            if (in[j] == _envr[row][chr])
                j++;
            else
                break;
        }
    }

    for (j = 0; in[j]; j++)
    {
        if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
            break;
    }

    variable_addition(h, j, NULL, 0);
}

/**
 * @brief Replaces variables in the main_input string with their corresponding values.
 *
 * Replaces variables in the main_input string 'main_input' with their corresponding values
 * using the replacement variable linked list. The function also frees
 * and the replacement variable linked list.
 *
 * @param main_input Pointer to the main_input string.
 * @param simpdata Pointer to the simple_shell_d struct.
 * @return Pointer to the new string with variables replaced.
 */
char *rep_var(char *main_input, simple_shell_d *simpdata)
{
    read_variable *head, *indx;
    char *status, *new_input;
    int olen, nlen;

    status = aux_itoa(simpdata->status);
    head = NULL;

    olen = check_vars(&head, main_input, status, simpdata);

    if (head == NULL)
    {
        free(status);
        return (main_input);
    }

    indx = head;
    nlen = 0;

    while (indx != NULL)
    {
        nlen += (indx->len_val - indx->len_var);
        indx = indx->next;
    }

    nlen += olen;

    new_input = malloc(sizeof(char) * (nlen + 1));
    new_input[nlen] = '\0';

    new_input = replaced_input(&head, main_input, new_input, nlen);

    free(main_input);
    free(status);
    free_rvar_list(&head);

    return (new_input);
}
/**
 * @brief Replaces variables in the main_input string with their values.
 *
 * Replaces variables in the main_input string 'main_input' with their corresponding values
 * using the replacement variable linked list ('head').
 * The result is stored in a new string.
 *
 * @param head Pointer to the head of the replacement variable linked list.
 * @param main_input Pointer to the main_input string.
 * @param new_input Pointer to the new string where the result will be stored.
 * @param nlen The length of the new string.
 * @return Pointer to the new string with variables replaced.
 */
char *replaced_input(read_variable **head, char *main_input, char *new_input, int nlen)
{
    read_variable *indx;
    int i, j, k;

    indx = *head;
    for (j = i = 0; i < nlen; i++)
    {
        if (main_input[j] == '$')
        {
            if (!(indx->len_var) && !(indx->len_val))
            {
                new_input[i] = main_input[j];
                j++;
            }
            else if (indx->len_var && !(indx->len_val))
            {
                for (k = 0; k < indx->len_var; k++)
                    j++;
                i--;
            }
            else
            {
                for (k = 0; k < indx->len_val; k++)
                {
                    new_input[i] = indx->val[k];
                    i++;
                }
                j += (indx->len_var);
                i--;
            }
            indx = indx->next;
        }
        else
        {
            new_input[i] = main_input[j];
            j++;
        }
    }

    return (new_input);
}
