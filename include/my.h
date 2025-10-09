/*
** EPITECH PROJECT, 2024
** src
** File description:
** my
*/

#pragma once

#include "signal.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "mystruct.h"

#define ARGS shell->man.args
#define CMD shell->man.cmd
#define PATH shell->man.path
#define TRASH shell->man.trash
#define TAB shell->man.tab
#define VALUE shell->return_value

//str function
void my_putchar(char c);
int my_putlong(long nb);
int my_putshort(short nb);
int my_putstr(char const *str);
char *nbr_to_str(unsigned int nb);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
int my_strlen(char const *str);
int my_atoi(char *str);

//env
int print_env(minishell_t *shell);
env_t *copy_env(char **env);
int unset_env(minishell_t *shell, char *str);
int set_env(minishell_t *shell);
char **get_env(char const *str);

//function gestion minishell
int design(minishell_t *shell);
void init_shell(minishell_t *shell, int argc, char **argv, char **env);
void reinit(minishell_t *shell);
int is_atty_or_not(void);
void catch_signaux(void);
void handler(int signum);
void reset_mem(minishell_t *shell);
int free_memorie(minishell_t *shell);
int print_error(char *name, minishell_t *shell);

//gestion errors and addon
int gestion_error_execve(minishell_t *shell, char *cmd);
int long_path(minishell_t *shell, int *j);

//architecture separators
int primary_architecture(minishell_t *shell, char *args);
char *div_cmd(minishell_t *shell);
void gestion_error(char *name, minishell_t *shell);
int one_pipe(minishell_t *shell, int intput_fd, int output_fd);
int background_execution(minishell_t *shell, char *cmd1, char *cmd2);
int if_previous_succeeded(minishell_t *shell, char *cmd1, char *cmd2);
int check_other_separator(minishell_t *shell, char *str);
int double_redirection_right(minishell_t *shell, char *filename, char *cmd);
int double_redirection_left(minishell_t *shell, char *filename, char *cmd);
int redirection_right(minishell_t *shell, char *filename, char *cmd);
int redirection_left(minishell_t *shell, char *filename, char *cmd);
int exec_multi_cmd(minishell_t *shell);

//str to word array
char **my_str_to_word_array(char const *str);
char **sort_by_virgule(char const *str);
char **first_sorting(char const *str);
char **second_sorting(char const *str);
char **get_double_pipe(char const *str);
char **thrid_sorting(char const *str);


//gestion cmd and exec
void main_architecture(minishell_t *shell);
void sort_arg(minishell_t *shell, char *str);
int find_dir(minishell_t *shell);
int exec(minishell_t *shell);
int verify_type(char *newdir);

//bultin
int bultin_exit(minishell_t *shell);
bool testing_bultin(minishell_t *shell);
int my_cd(minishell_t *shell);
