/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** architecture
*/

#include "my.h"

void gestion_error(char *name, minishell_t *shell)
{
    perror(name);
    VALUE = 1;
    exit(EXIT_FAILURE);
}

char *div_cmd(minishell_t *shell)
{
    char *tmp = NULL;
    int index = shell->man.index;
    int m = 0;

    tmp = malloc(sizeof(char) * (my_strlen(TAB[index]) + 1));
    for (int j = 0; TAB[index][j]; j++) {
        if (j == 0 && TAB[index][j] == ' ')
            continue;
        else {
            tmp[m] = TAB[index][j];
            m++;
        }
    }
    tmp[m] = '\0';
    return tmp;
}

int third_architecture(minishell_t *shell, char *str)
{
    char **tmp = second_sorting(str);
    int status = 1;

    for (int i = 0; tmp[i]; i++) {
        status = check_other_separator(shell, tmp[i]);
        if (my_strcmp(tmp[i], "&") == 0) {
            status = background_execution(shell, tmp[i - 1], tmp[i + 1]);
            i++;
        }
        if (my_strcmp(tmp[i], "&&") == 0) {
            status = if_previous_succeeded(shell, tmp[i - 1], tmp[i + 1]);
            i++;
        }
        if (status == 2)
            return 2;
    }
    for (int i = 0; tmp[i]; i++)
        free(tmp[i]);
    free(tmp);
    return status;
}

static void check_fd(int *pipefd, int *input)
{
    if (*input != STDIN_FILENO)
        close(*input);
    if (pipefd[1] != STDOUT_FILENO)
        close(pipefd[1]);
    *input = pipefd[0];
}

int secondary_architecture(minishell_t *shell, char *args)
{
    int *pipefd = malloc(sizeof(int) * 2);
    int input = STDIN_FILENO;
    int status = 0;

    TAB = first_sorting(args);
    for (shell->man.index = 0; TAB[shell->man.index]; shell->man.index++) {
        if (TAB[shell->man.index + 1] != NULL)
            pipe(pipefd);
        else
            pipefd[1] = STDOUT_FILENO;
        status = third_architecture(shell, TAB[shell->man.index]);
        if (status == 2)
            break;
        if (status == 3)
            continue;
        one_pipe(shell, input, pipefd[1]);
        check_fd(pipefd, &input);
    }
    return 0;
}

int primary_architecture(minishell_t *shell, char *args)
{
    char **testing = get_double_pipe(args);

    for (int i = 0; testing[i]; i++) {
        secondary_architecture(shell, testing[i]);
        if (VALUE == 0)
            break;
    }
    for (int i = 0; testing[i]; i++)
        free(testing[i]);
    free(testing);
    return 0;
}
