#include "shell.h"

var_n *variable_node(var_n **head, int lvar, char *val, int lval)
{
    var_n *new, *temp;

    new = malloc(sizeof(var_n));
    if (new == NULL)
        return (NULL);

    new->len_var = lvar;
    new->val = val;
    new->len_val = lval;

    new->next = NULL;
    temp = *head;

    if (temp == NULL)
    {
        *head = new;
    }
    else
    {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }

    return (*head);
}

void free_variable_list(var_n **head)
{
    var_n *temp;
    var_n *curr;

    if (head != NULL)
    {
        curr = *head;
        while ((temp = curr) != NULL)
        {
            curr = curr->next;
            free(temp);
        }
        *head = NULL;
    }
}
