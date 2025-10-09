/*
** EPITECH PROJECT, 2024
** shell1
** File description:
** too_long_path
*/

#include "my.h"

static bool check_path(minishell_t *shell, int *j)
{
    bool a = false;

    for (int i = 0; ARGS[*j][i]; i++)
        if (ARGS[*j][i] == 34)
            a = true;
    if (a != true)
        return false;
    else
        return true;
}

static char *copy_new_path(char *buffer, char *dest)
{
    int m = 0;

    dest = malloc(sizeof(char) * my_strlen(buffer));
    for (int i = 0; buffer[i]; i++)
        if (buffer[i] != 34) {
            dest[m] = buffer[i];
            m++;
        }
    dest[m] = '\0';
    return dest;
}

static char **insert_args(minishell_t *shell, int *j, int old, char *dest)
{
    char **new;
    int count = 0;
    int m = 0;

    for (int i = 0; ARGS[i]; i++) {
        if (i != *j && i != old)
            count++;
    }
    new = malloc(sizeof(char *) * (count + 3));
    for (int i = 0; ARGS[i]; i++) {
        if (i != old) {
            new[m] = my_strdup(ARGS[i]);
            m++;
        } else {
            new[m] = my_strdup(dest);
            m++;
            i = *j;
        }
    }
    return new;
}

static bool check_cha(char c)
{
    if (c == 34)
        return (false);
    else
        return (true);
}

int long_path(minishell_t *shell, int *j)
{
    char buffer[1024];
    char *dest = NULL;
    int tmp = *j;
    bool a = true;

    if (check_path(shell, j) != true)
        return 1;
    my_strcpy(buffer, ARGS[*j]);
    for (*j = *j + 1; ARGS[*j] && a == true; (*j)++) {
        for (int i = 0; ARGS[*j][i]; i++)
            a = check_cha(ARGS[*j][i]);
        my_strcat(buffer, " ");
        my_strcat(buffer, ARGS[*j]);
    }
    (*j)--;
    dest = copy_new_path(buffer, dest);
    PATH = malloc(sizeof(char) * my_strlen(dest) + 1);
    my_strcpy(PATH, dest);
    ARGS = insert_args(shell, j, tmp, dest);
    return 0;
}
