/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** pipe
*/

#include "my.h"

int exec_multi_cmd(minishell_t *shell)
{
    if (verify_type(CMD) == true) {
        print_error(": Permission denied.\n", shell);
        exit(VALUE);
    }
    if (testing_bultin(shell) == true)
        exit(VALUE);
    if (shell->man_cmd == true)
        exec(shell);
    if (find_dir(shell) == 0)
        exec(shell);
    exit(VALUE);
    return 0;
}

int one_pipe(minishell_t *shell, int intput_fd, int output_fd)
{
    char *cmd = div_cmd(shell);

    sort_arg(shell, cmd);
    if (testing_bultin(shell) == true)
        return(VALUE);
    shell->my_pid = fork();
    if (shell->my_pid == -1)
        gestion_error("fork", shell);
    if (shell->my_pid == 0) {
        if (intput_fd != STDIN_FILENO) {
            dup2(intput_fd, STDIN_FILENO);
            close(intput_fd);
        }
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        exec_multi_cmd(shell);
    } else
        wait(&VALUE);
    return 1;
}

int background_execution(minishell_t *shell, char *cmd1, char *cmd2)
{
    shell->my_pid = fork();
    if (shell->my_pid == -1) {
        gestion_error("fork", shell);
        return VALUE;
    } else if (shell->my_pid == 0) {
        sort_arg(shell, cmd1);
        exec_multi_cmd(shell);
    } else {
        TAB[shell->man.index] = my_strdup(cmd2);
        return 0;
    }
    return 0;
}

int if_previous_succeeded(minishell_t *shell, char *cmd1, char *cmd2)
{
    shell->my_pid = fork();
    if (shell->my_pid == -1) {
        gestion_error("fork", shell);
        return VALUE;
    } else if (shell->my_pid == 0) {
        sort_arg(shell, cmd1);
        exec_multi_cmd(shell);
    } else {
        wait(&VALUE);
    }
    if (VALUE != 0) {
        TAB[shell->man.index] = NULL;
        return 2;
    } else {
        TAB[shell->man.index] = my_strdup(cmd2);
        return 0;
    }
    return 0;
}

int check_other_separator(minishell_t *shell, char *str)
{
    char **tmp = thrid_sorting(str);
    int status = 1;

    for (int i = 0; tmp[i]; i++) {
        if (my_strcmp(tmp[i], "<") == 0)
            status = redirection_left(shell, tmp[i + 1], tmp[i - 1]);
        if (my_strcmp(tmp[i], ">") == 0)
            status = redirection_right(shell, tmp[i + 1], tmp[i - 1]);
        if (my_strcmp(tmp[i], "<<") == 0)
            status = double_redirection_left(shell, tmp[i + 1], tmp[i - 1]);
        if (my_strcmp(tmp[i], ">>") == 0)
            status = double_redirection_right(shell, tmp[i + 1], tmp[i - 1]);
    }
    for (int i = 0; tmp[i]; i++)
        free(tmp[i]);
    free(tmp);
    return status;
}
