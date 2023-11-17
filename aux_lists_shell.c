#include "shell.h"

/**
 * separation_list - Frees the memory allocated for sep_list.
 * @head: Pointer to the head of the sep_list.
 */
void separation_list(sep_list **head)
{
    sep_list *temp;
    sep_list *curr;

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
 * f_list - Frees the memory allocated for LineList_Var.
 * @head: Pointer to the head of the LineList_Var.
 */
void f_list(LineList_Var **head)
{
    LineList_Var *temp;
    LineList_Var *curr;

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
 * LineList_Var_node - Adds a new node with line at the end of LineList_Var.
 * @head: Pointer to the head of the LineList_Var.
 * @line: Pointer to the line string to be added to the new node.
 *
 * Return: Pointer to the modified LineList_Var.
 */
LineList_Var *LineList_Var_node(LineList_Var **head, char *line)
{
    LineList_Var *new, *temp;

    new = malloc(sizeof(LineList_Var));
    if (new == NULL)
        return (NULL);

    new->line = line;
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

/**
 * add_separation_end - Adds a new node with separator at the end of sep_list.
 * @head: Pointer to the head of the sep_list.
 * @sep: Separator character to be added to the new node.
 *
 * Return: Pointer to the modified sep_list.
 */
sep_list *add_separation_end(sep_list **head, char sep)
{
    sep_list *new, *temp;

    new = malloc(sizeof(sep_list));
    if (new == NULL)
        return (NULL);

    new->separator = sep;
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
