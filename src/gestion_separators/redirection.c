/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** redirection
*/

#include "my.h"

static int gestion_closing(char *name, minishell_t *shell,
    int file, int *pipefd)
{
    if (name != NULL) {
        perror(name);
        VALUE = 1;
    }
    if (my_strcmp(name, "pipe") == 0) {
        close(file);
        VALUE = 1;
    }
    if (my_strcmp(name, "pipefd") == 0) {
        if (file != -1)
            close(file);
        close(pipefd[0]);
        close(pipefd[1]);
        VALUE = 1;
    }
    return VALUE;
}

static int init(minishell_t *shell, int file, int *pipefd)
{
    if (file == -1)
        return (gestion_closing("open", shell, file, pipefd));
    if (pipe(pipefd) == -1)
        return (gestion_closing("pipe", shell, file, pipefd));
    shell->my_pid = fork();
    if (shell->my_pid == -1)
        return (gestion_closing("fork", shell, file, pipefd));
    return 0;
}

static void achitecture_rigth(minishell_t *shell, int file,
    int *pipefd, char *cmd)
{
    if (shell->my_pid == 0) {
        if (dup2(file, STDOUT_FILENO) == -1)
            exit(gestion_closing("dup2", shell, file, pipefd));
        close(file);
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            close(pipefd[0]);
            exit(gestion_closing("dup2", shell, file, pipefd));
        }
        close(pipefd[0]);
        sort_arg(shell, cmd);
        exec_multi_cmd(shell);
        exit(VALUE);
    } else {
        close(file);
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(shell->my_pid, NULL, 0);
    }
}

int double_redirection_right(minishell_t *shell, char *filename, char *cmd)
{
    int file =
        open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    int pipefd[2];

    if (init(shell, file, pipefd) != 0)
        return 1;
    achitecture_rigth(shell, file, pipefd, cmd);
    return 3;
}

int double_redirection_left(minishell_t *shell, char *eof, char *cmd)
{
    char *str = NULL;
    size_t size = 0;

    while (getline(&str, &size, stdin) != -1) {
        if (str[0] != '\0' && str[my_strlen(str) -1] == '\n')
            str[my_strlen(str) -1] = '\0';
        if (my_strcmp(str, eof) == 0)
            break;
        my_strcat(str, " ");
        my_strcat(cmd, str);
    }
    TAB[shell->man.indexs] = my_strdup(cmd);
    free(str);
    return 0;
}

int redirection_right(minishell_t *shell, char *filename, char *cmd)
{
    int file =
        open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    int pipefd[2];

    if (init(shell, file, pipefd) != 0)
        return 1;
    achitecture_rigth(shell, file, pipefd, cmd);
    return 3;
}

static int init_left(minishell_t *shell, int file)
{
    if (file == -1)
        return (gestion_closing("open", shell, file, NULL));
    if (dup2(file, STDIN_FILENO) == -1) {
        perror("dup2");
        close(file);
        return 1;
    }
    return 0;
}

int redirection_left(minishell_t *shell, char *filename, char *cmd)
{
    int file = open(filename, O_RDONLY);
    char *str = NULL;
    size_t size = 0;

    if (init_left(shell, file) != 0)
        return 1;
    close(file);
    while (getline(&str, &size, stdin) != -1) {
        if (str[0] != '\0' && str[my_strlen(str) -1] == '\n')
            str[my_strlen(str) -1] = '\0';
        my_strcat(str, " ");
        my_strcat(cmd, str);
    }
    TAB[shell->man.indexs] = my_strdup(cmd);
    free(str);
    return 0;
}
