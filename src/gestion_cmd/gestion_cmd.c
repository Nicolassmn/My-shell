/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** gestion_cmd
*/

#include "my.h"

static int gestion_error_cmd(minishell_t *shell, char *cmd)
{
    if (access(cmd, F_OK) != 0) {
        my_putstr(CMD);
        return (print_error(": Command not found.\n", shell));
    } else if (verify_type(CMD) == true || access(cmd, X_OK) != 0) {
        my_putstr(CMD);
        return (print_error(": Permission denied.\n", shell));
    }
    #ifdef __linux__
        return 0;
    #endif
    my_putstr(CMD);
    return (print_error(": Exec format error. Wrong Architecture.\n", shell));
}

static void failed_exec(minishell_t *shell)
{
    free_memorie(shell);
    VALUE = 1;
    exit(VALUE);
}

int exec(minishell_t *shell)
{
    char *cmd = NULL;

    if (access(CMD, X_OK) == 0)
        if (execve(CMD, ARGS, shell->ev) == -1)
            failed_exec(shell);
    if (shell->man_cmd == true) {
        if (gestion_error_cmd(shell, cmd) != true)
            exit(VALUE);
        if (execve(cmd, ARGS, shell->ev) == -1)
            failed_exec(shell);
    }
    if (execve(shell->man.path_cmd, ARGS, shell->ev) == -1)
        failed_exec(shell);
    return 0;
}

static int not_found(minishell_t *shell)
{
    my_putstr(CMD);
    my_putstr(": Command not found.\n");
    VALUE = 1;
    return VALUE;
}

static char *get_path(minishell_t *shell)
{
    env_t *tmp = shell->env;

    while (tmp) {
        if (my_strcmp(tmp->name, "PATH") == 0)
            return (tmp->data);
        else
            tmp = tmp->next;
    }
    return NULL;
}

int find_dir(minishell_t *shell)
{
    char *data = get_path(shell);
    char *token;
    char *buffer = NULL;

    if (data == NULL)
        return not_found(shell);
    token = strtok(data, ":");
    while (token != NULL) {
        buffer = my_strdup(token);
        my_strcat(buffer, "/");
        my_strcat(buffer, CMD);
        if (access(buffer, X_OK) == 0) {
            shell->man.path_cmd = my_strdup(buffer);
            free(buffer);
            return 0;
        }
        token = strtok(NULL, ":");
        free(buffer);
    }
    return not_found(shell);
}

static void sort_path(minishell_t *shell, int i)
{
    if (ARGS[i] == NULL)
        return;
    if (PATH == NULL)
        PATH = my_strdup(ARGS[i]);
    else
        TRASH = my_strdup(ARGS[i]);
}

void sort_arg(minishell_t *shell, char *str)
{
    ARGS = my_str_to_word_array(str);
    CMD = my_strdup(ARGS[0]);
    for (int i = 0; CMD[i]; i++)
        if (CMD[i] == '/')
            shell->man_cmd = true;
    for (int i = 1; ARGS[i]; i++) {
        if (long_path(shell, &i) == 0)
            continue;
        sort_path(shell, i);
    }
}

int gestion_cmd(minishell_t *shell)
{
    if (testing_bultin(shell) == true)
        return VALUE;
    shell->my_pid = fork();
    if (shell->my_pid == 0) {
        if (shell->man_cmd == true)
            exec(shell);
        if (find_dir(shell) == 0)
            exec(shell);
        exit(VALUE);
    }
    return 0;
}

void main_architecture(minishell_t *shell)
{
    char **tmp = ARGS;
    int status = 0;

    for (int i = 0; tmp[i]; i++) {
        primary_architecture(shell, tmp[i]);
        waitpid(shell->my_pid, &status, 0);
        if (status - 128 == 4 || status - 128 == 8 || status - 128 == 6 ||
            status - 128 == 15 || status - 128 == 11)
            VALUE = status - 128;
        handler(status - 128);
        if (shell->exit == -1)
            bultin_exit(shell);
        TRASH = NULL;
        CMD = NULL;
        PATH = NULL;
        shell->man.index = 0;
    }
    for (int i = 0; tmp[i]; i++)
        free(tmp[i]);
}
