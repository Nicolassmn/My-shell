/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** function_cd
*/

#include "my.h"

int verify_type(char *newdir)
{
    struct stat info_fd;

    if (lstat(newdir, &info_fd) == -1)
        return false;
    return S_ISDIR(info_fd.st_mode) ? true : false;
}

static int verify_perm(char *newdir)
{
    if (access(newdir, R_OK | X_OK) == 0)
        return (true);
    else
        return false;
}

int gestion_error_cd(char *newdir, minishell_t *shell)
{
    if (TRASH != NULL) {
        my_putstr("cd: Too many arguments.\n");
        VALUE = 1;
        return VALUE;
    }
    if (my_strlen(newdir) >= 4090) {
        my_putstr(newdir);
        return (print_error(": File name too long.\n", shell));
    } else if (verify_type(newdir) == false) {
        my_putstr(newdir);
        return (print_error(": Not a directory.\n", shell));
    }
    if (verify_perm(newdir) == false) {
        my_putstr(newdir);
        return (print_error(": Permission denied.\n", shell));
    }
    return VALUE;
}

static char *back_old_dir(minishell_t *shell)
{
    env_t *tmp = shell->env;

    while (tmp) {
        if (my_strcmp(tmp->name, "OLDPWD") == 0) {
            return (tmp->data);
        } else
            tmp = tmp->next;
    }
    return NULL;
}

static char *back_to_home(minishell_t *shell)
{
    env_t *tmp = shell->env;

    while (tmp) {
        if (my_strcmp(tmp->name, "HOME") == 0) {
            return (tmp->data);
        } else
            tmp = tmp->next;
    }
    my_putstr("cd: No home directory.\n");
    VALUE = 1;
    return NULL;
}

char *new_dir(minishell_t *shell)
{
    char *dir = NULL;

    if (shell->env == NULL)
        return (NULL);
    if (PATH == NULL || my_strcmp(PATH, "~") == 0)
        return (back_to_home(shell));
    if (PATH[0] == '~' && PATH[1] == '/') {
        dir = back_to_home(shell);
        if (dir == NULL)
            return NULL;
        my_strcat(dir, PATH + 1);
        return dir;
    }
    if (my_strcmp(PATH, "-") == 0)
        return (back_old_dir(shell));
    return (PATH);
}

int my_cd(minishell_t *shell)
{
    char buffer[1024];
    char *newdir = new_dir(shell);
    char *olddir = my_strdup(getcwd(buffer, 1024));
    env_t *tmp = shell->env;

    if (gestion_error_cd(newdir, shell) != 0 || newdir == NULL) {
        return VALUE;
    } else if (chdir(newdir) < 0) {
        my_putstr(newdir);
        return (print_error(": No such file or directory.\n", shell));
    }
    while (tmp) {
        if (strcmp(tmp->name, "PWD") == 0)
            tmp->data = my_strdup(getcwd(buffer, 1024));
        if (my_strcmp(tmp->name, "OLDPWD") == 0)
            tmp->data = my_strdup(olddir);
        tmp = tmp->next;
    }
    VALUE = 0;
    return VALUE;
}
