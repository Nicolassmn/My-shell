/*
** EPITECH PROJECT, 2023
** epnf
** File description:
** frn
*/

#include "my.h"

static int separators(char c)
{
    if (c == '|')
        return 0;
    else
        return 1;
}

static int size(char const *str)
{
    int i = 0;
    int size = 1;

    while (str[i] != '\0') {
        if ((separators(str[i]) == 1) && (separators(str[i + 1]) == 1))
            size += 1;
        i++;
    }
    return size;
}

static void add_separator(char const *str, int *k, int *j, char *tab)
{
    int i = *k;

    if (str[*k] == '|' && str[*k + 1] == '|') {
        tab[*j] = '\0';
        return;
    }
    for (; str[i] != '\0'; i++) {
        if (str[i] == '|' && str[i + 1] == '|')
            break;
        tab[*j] = str[i];
        (*j)++;
    }
    tab[*j] = '\0';
    *k = i + 2;
}

char **get_double_pipe(char const *str)
{
    int j = 0;
    int size_c = 0;
    char **tab = malloc(sizeof(char *) * (size(str) * 2));

    for (int k = 0; str[k] != '\0' && size_c < (size(str) * 2);) {
        if (separators(str[k]) == 0)
            k++;
        tab[size_c] = malloc(sizeof(char) * (1024));
        for (; separators(str[k]) == 1 &&
            str[k] != '\0' && str[k] != '\n'; j++) {
            tab[size_c][j] = str[k];
            k++;
        }
        add_separator(str, &k, &j, tab[size_c]);
        size_c++;
        j = 0;
    }
    tab[size_c] = NULL;
    return tab;
}
