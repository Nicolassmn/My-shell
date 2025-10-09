/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** mystruct
*/

#pragma once

#include <signal.h>

typedef struct env_s {
    char *name;
    char *data;
    struct env_s *next;
} env_t;

typedef struct gestion_cmd_s {
    char **args;
    char **tab;
    char *path;
    char *cmd;
    char *trash;
    char *path_cmd;
    int separator;
    int index;
    int *pids;
    int indexs;
} gestion_cmd_t;

typedef struct minishell_s {
    int exit;
    gestion_cmd_t man;
    int return_value;
    __pid_t my_pid;
    char *dir;
    char **ev;
    env_t *env;
    bool man_cmd;
    bool background;
    bool empty_env;
} minishell_t;
