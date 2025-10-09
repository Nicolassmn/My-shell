/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** setenv
*/

#include "my.h"

static int split_error(char *data, minishell_t *shell)
{
    for (int i = 1; data[i]; i++) {
        if ((data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' &&
            data[i] <= 'Z') || (data[i] <= '9' && data[i] >= '0'))
            VALUE = 0;
        else {
            VALUE = 1;
            my_putstr(
            "setenv: Variable name must contain alphanumeric characters.\n");
            return VALUE;
        }
    }
    return 0;
}

int gestion_error_setenv(char *data, minishell_t *shell)
{
    if (ARGS[3] == NULL);
    else {
        VALUE = 1;
        my_putstr("setenv: Too many arguments.\n");
        return VALUE;
    }
    if ((data[0] < 'a' || data[0] > 'z') &&
        (data[0] < 'A' || data[0] > 'Z')) {
        VALUE = 1;
        write(1, "setenv: Variable name must begin with a letter.\n", 48);
        return VALUE;
    }
    return (split_error(data, shell));
}

static env_t *add_node(minishell_t *shell)
{
    env_t *new_node;

    new_node = malloc(sizeof(env_t));
    new_node->name = my_strdup(PATH);
    if (TRASH != NULL)
        new_node->data = my_strdup(TRASH);
    else
        new_node->data = NULL;
    new_node->next = NULL;
    return new_node;
}

static int gestion_setenv(minishell_t *shell, env_t *tmp)
{
    if (my_strcmp(PATH, tmp->name) == 0) {
        if (TRASH != NULL) {
            tmp->data = my_strdup(TRASH);
        } else
            free(tmp->data);
        VALUE = 0;
        return VALUE;
    }
    return 1;
}

int print_env(minishell_t *shell)
{
    env_t *tmp = shell->env;

    while (tmp) {
        my_putstr(tmp->name);
        write(1, "=", 1);
        if (tmp->data != NULL)
            my_putstr(tmp->data);
        write(1, "\n", 1);
        tmp = tmp->next;
    }
    VALUE = 0;
    return 0;
}

int set_env(minishell_t *shell)
{
    env_t *tmp = shell->env;

    if (PATH == NULL)
        return print_env(shell);
    else if (gestion_error_setenv(ARGS[1], shell) != 0)
        return VALUE;
    while (tmp->next != NULL) {
        if (gestion_setenv(shell, tmp) == 0)
            return VALUE;
        else
            tmp = tmp->next;
    }
    if (shell->env == NULL)
        shell->env = add_node(shell);
    else
        tmp->next = add_node(shell);
    return VALUE;
}
