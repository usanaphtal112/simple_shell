#include "shell.h"

/*
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

*/

/**
 * free_rvar_list - Frees the memory allocated for the read_variable linked list.
 *
 * The free_rvar_list function takes a pointer to the head of the read_variable linked
 * list and frees the memory allocated for each node in the list.
 *
 * @head: A pointer to the head of the read_variable linked list.
 */
void free_rvar_list(read_variable **head)
{
    read_variable *temp;
    read_variable *curr;

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

/**
 * variable_addition - Adds a node to the read_variable linked list.
 *
 * The variable_addition function creates a new node with the specified values
 * and appends it to the end of the read_variable linked list. If the list is empty,
 * it initializes the list with the new node.
 *
 * @head: A pointer to the head of the read_variable linked list.
 * @lvar: The length of the variable name.
 * @val: The value associated with the variable.
 * @lval: The length of the value.
 *
 * Return: A pointer to the head of the modified read_variable linked list.
 */
read_variable *variable_addition(read_variable **head, int lvar, char *val, int lval)
{
    read_variable *new, *temp;

    new = malloc(sizeof(read_variable));
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

/*

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

*/
