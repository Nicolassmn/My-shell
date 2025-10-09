/*
** EPITECH PROJECT, 2023
** epnf
** File description:
** frn
*/

#include "my.h"

static int separators(char c)
{
    if (c == ';')
        return 0;
    else
        return 1;
}

static int taille(char const *str)
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

static int my_strlen_modify(char const *str, int k)
{
    int i = 0;

    while (str[k] != '\0' && (separators(str[k]) == 1)) {
        k++;
        i++;
    }
    return i;
}

static void delete_extra_space(int *j, int *size, char **tab)
{
    if (tab[*size][*j - 1] == ' ')
        tab[*size][*j - 1] = '\0';
    else
        tab[*size][*j] = '\0';
    if (*j > 0) {
        *j = 0;
        (*size)++;
    }
}

char **sort_by_virgule(char const *str)
{
    int j = 0;
    int size_c = 0;
    char **tab = malloc(sizeof(char *) * (taille(str) * 2));

    for (int k = 0; str[k] != '\0' && size_c < (taille(str) * 2); k++) {
        if (str[k] == ' ' || str[k] == '\t')
            continue;
        tab[size_c] = malloc(sizeof(char) * (my_strlen_modify(str, k) * 2));
        for (; str[k] != '\0' && separators(str[k]) == 1 &&
            str[k] != '\n'; j++) {
                tab[size_c][j] = str[k];
                k++;
        }
        delete_extra_space(&j, &size_c, tab);
    }
    tab[size_c] = NULL;
    return tab;
}
