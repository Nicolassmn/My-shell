/*
** EPITECH PROJECT, 2023
** epnf
** File description:
** frn
*/

#include "my.h"

static int separators(char c)
{
    if (c == '&')
        return 0;
    else
        return 1;
}

static int size(char const *str)
{
    int i = 0;
    int size = 1;

    while (str[i] != '\0') {
        if ((separators(str[i]) == 1) && (separators(str[i + 1]) == 0))
            size += 1;
        i++;
    }
    return size;
}

static void increase(int *j, int *size)
{
    (*size)++;
    *j = 0;
}

static void add_separator(char const *str, int *k, int *size, char **tab)
{
    char *tmp = malloc(sizeof(char) * 1024);
    int i = *k;
    int j = 0;

    (*size)++;
    for (; str[i] && separators(str[i]) == 0 && j < 2; i++) {
        tmp[j] = str[i];
        j++;
    }
    tab[*size] = my_strdup(tmp);
    *k = i;
}

char **second_sorting(char const *str)
{
    int j = 0;
    int size_c = 0;
    char **tab = malloc(sizeof(char *) * (size(str) * 2 + 1));

    for (int k = 0; str[k] != '\0' && size_c < (size(str) * 2 + 1);) {
        tab[size_c] = malloc(sizeof(char) * 1024);
        for (; separators(str[k]) == 1 && str[k] != '\0'; j++) {
            tab[size_c][j] = str[k];
            k++;
        }
        tab[size_c][j] = '\0';
        add_separator(str, &k, &size_c, tab);
        increase(&j, &size_c);
    }
    tab[size_c - 1] = NULL;
    return tab;
}
