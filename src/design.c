/*
** EPITECH PROJECT, 2024
** caca
** File description:
** design
*/

#include "my.h"

int design(minishell_t *shell)
{
    env_t *tmp = shell->env;

    shell->dir = malloc(sizeof(char) * 1024);
    my_strcpy(shell->dir, "\033[3;32m");
    shell->empty_env = true;
    while (tmp) {
        if (my_strcmp(tmp->name, "PWD") == 0 && tmp->data != NULL) {
            my_strcat(shell->dir, tmp->data);
            my_strcat(shell->dir, "%:");
            shell->empty_env = false;
            break;
        } else
            tmp = tmp->next;
    }
    if (shell->empty_env == true)
        my_strcat(shell->dir, ">");
    my_strcat(shell->dir, "\033[0m");
    my_putstr(shell->dir);
    return 0;
}
