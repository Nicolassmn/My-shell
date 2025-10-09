/*
** EPITECH PROJECT, 2024
** shell2
** File description:
** main
*/

#include "my.h"

int is_atty_or_not(void)
{
    return (isatty(STDIN_FILENO));
}

int print_error(char *name, minishell_t *shell)
{
    my_putstr(name);
    VALUE = 1;
    return VALUE;
}

static bool skip_invisible_char(char c, char *str)
{
    if (c == 10 && is_atty_or_not() == 0)
        exit(0);
    if (c == '\n') {
        my_putstr(str);
        return true;
    } else
        return false;
}

int main(int argc, char **argv, char **env)
{
    minishell_t *shell = malloc(sizeof(minishell_t));
    char *str = NULL;
    size_t size = 0;

    init_shell(shell, argc, argv, env);
    while (getline(&str, &size, stdin) != -1) {
        if (skip_invisible_char(str[0], shell->dir) == true)
            continue;
        ARGS = sort_by_virgule(str);
        main_architecture(shell);
        free_memorie(shell);
        reinit(shell);
    }
    if (is_atty_or_not() != 0)
        my_putstr("\nexit\n");
    return VALUE;
}
