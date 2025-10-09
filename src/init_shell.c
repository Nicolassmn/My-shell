/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** init_shell
*/

#include "my.h"

void reinit(minishell_t *shell)
{
    CMD = NULL;
    PATH = NULL;
    TRASH = NULL;
    TAB = NULL;
    shell->man_cmd = false;
    shell->my_pid = getpid();
    if (is_atty_or_not() != 0)
        design(shell);
}

int free_memorie(minishell_t *shell)
{
    free(CMD);
    if (PATH != NULL)
        free(PATH);
    if (TRASH != NULL)
        free(TRASH);
    if (ARGS != NULL) {
        for (int i = 0; ARGS[i] && ARGS[i + 1]; i++)
            free(ARGS[i]);
        free(ARGS);
    }
    if (TAB != NULL) {
        for (int i = 0; TAB[i]; i++)
            free(TAB[i]);
        free(TAB);
    }
    TRASH = NULL;
    CMD = NULL;
    PATH = NULL;
    return 0;
}

void reset_mem(minishell_t *shell)
{
    free_memorie(shell);
    reinit(shell);
}

static void init(minishell_t *shell, char **env, int argc, char **argv)
{
    if (env[0] == NULL || (env[0] != NULL && env[1] == NULL))
        shell->empty_env = true;
    else
        shell->empty_env = false;
    CMD = NULL;
    PATH = NULL;
    TRASH = NULL;
    TAB = NULL;
    shell->man.index = 0;
    shell->exit = 0;
    shell->man_cmd = false;
    shell->background = false;
    shell->my_pid = getpid();
    VALUE = 0;
    (void)argc;
    (void)argv;
}

void init_shell(minishell_t *shell, int argc, char **argv, char **env)
{
    int j = 0;
    int i = 0;

    init(shell, env, argc, argv);
    if (shell->empty_env == false) {
        for (j = 0; env[j]; j++);
        shell->ev = malloc(sizeof(char *) * (1024));
        for (; env[i]; i++) {
            shell->ev[i] = my_strdup(env[i]);
        }
        shell->ev[i] = NULL;
    } else
        shell->ev = NULL;
    shell->env = malloc(sizeof(env_t));
    shell->env = copy_env(env);
    if (is_atty_or_not() != 0)
        design(shell);
    catch_signaux();
}
