/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** unsetenv
*/

#include "my.h"

static int gestion_error_unsetenv(minishell_t *shell, char *str)
{
    if (shell->env == NULL) {
        VALUE = 1;
        return 1;
    }
    if (str == NULL) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        VALUE = 1;
        return VALUE;
    }
    if (my_strcmp(str, "*") == 0) {
        VALUE = 1;
        return VALUE;
    }
    return 0;
}

static void free_data(env_t *tmp)
{
    free(tmp->name);
    free(tmp->data);
    free(tmp);
}

static void clear_node(env_t *tmp, env_t *prev, minishell_t *shell)
{
    if (tmp->next == NULL) {
        if (prev == NULL)
            shell->env = NULL;
        else
            prev->next = NULL;
        free_data(tmp);
    } else if (my_strcmp(tmp->name, shell->env->name) == 0) {
        shell->env = tmp->next;
        free_data(tmp);
    } else {
        prev->next = tmp->next;
        free_data(tmp);
    }
}

int unset_env(minishell_t *shell, char *str)
{
    env_t *tmp = shell->env;
    env_t *prev = NULL;

    if (gestion_error_unsetenv(shell, str) != 0)
        return VALUE;
    while (tmp) {
        if (my_strcmp(tmp->name, str) == 0) {
            clear_node(tmp, prev, shell);
            return VALUE;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return 0;
}
