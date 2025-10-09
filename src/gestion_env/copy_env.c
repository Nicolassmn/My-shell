/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** copy_env
*/

#include "my.h"

static env_t *add_node(char *str)
{
    env_t *new_node;
    char **data = get_env(str);

    new_node = malloc(sizeof(env_t));
    new_node->name = my_strdup(data[0]);
    if (data[1] != NULL)
        new_node->data = my_strdup(data[1]);
    else
        new_node->data = NULL;
    new_node->next = NULL;
    return new_node;
}

static env_t *set_up_oldpwd(env_t *env)
{
    env_t *tmp = env;
    env_t *oldpwd = malloc(sizeof(env_t));
    char buffer[1024];

    oldpwd->name = my_strdup("OLDPWD");
    oldpwd->data = my_strdup(getcwd(buffer, 1024));
    oldpwd->next = NULL;
    if (env == NULL)
        return oldpwd;
    while (tmp->next != NULL) {
        if (my_strcmp(tmp->name, "OLDPWD") == 0)
            return env;
        tmp = tmp->next;
    }
    tmp->next = oldpwd;
    return env;
}

env_t *copy_env(char **env)
{
    env_t *copy_env = NULL;
    env_t *tmp = NULL;
    env_t *new;

    for (int i = 0; env[i]; i++) {
        new = add_node(env[i]);
        if (copy_env == NULL) {
            copy_env = new;
            tmp = copy_env;
        } else {
            tmp->next = new;
            tmp = tmp->next;
        }
    }
    copy_env = set_up_oldpwd(copy_env);
    return copy_env;
}
