/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** bultin_exit
*/

#include "my.h"

static void clear_nodes(minishell_t *shell)
{
    env_t *tmp = shell->env;
    env_t *clear_node = NULL;

    while (tmp) {
        free(tmp->name);
        if (tmp->data != NULL)
            free(tmp->data);
        clear_node = tmp;
        tmp = tmp->next;
        free(clear_node);
    }
    for (int i = 0; shell->ev[i]; i++)
        free(shell->ev[i]);
    free(shell->ev);
}

int bultin_exit(minishell_t *shell)
{
    int value = VALUE;

    if (PATH == NULL) {
        free_memorie(shell);
        clear_nodes(shell);
        my_putstr("exit\n");
        exit(VALUE);
    }
    for (int i = 0; PATH[i]; i++)
        if (PATH[i] > '9' || PATH[i] < '0') {
            my_putstr("exit: Expression Syntax.\n");
            return true;
        }
    value = my_atoi(PATH);
    free_memorie(shell);
    clear_nodes(shell);
    my_putstr("exit\n");
    exit(value * -1);
}

static bool other_bultin(minishell_t *shell)
{
    if (my_strcmp(CMD, "setenv") == 0) {
        if (PATH == NULL)
            print_env(shell);
        else
            set_env(shell);
        return true;
    } else if (my_strcmp(CMD, "unsetenv") == 0) {
        unset_env(shell, PATH);
        return true;
    }
    if (my_strcmp(CMD, "echo") == 0 && my_strcmp(PATH, "$?") == 0) {
        my_putstr(nbr_to_str(VALUE));
        write(1, "\n", 1);
        return true;
    }
    return false;
}

bool testing_bultin(minishell_t *shell)
{
    if (my_strcmp(CMD, "exit") == 0)
        return (bultin_exit(shell));
    if (my_strcmp(CMD, "cd") == 0) {
        my_cd(shell);
        return true;
    }
    if (my_strcmp(CMD, "env") == 0) {
        print_env(shell);
        return true;
    }
    return other_bultin(shell);
}
