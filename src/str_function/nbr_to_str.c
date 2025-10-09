/*
** EPITECH PROJECT, 2023
** myhunter
** File description:
** put_nbr_to_str
*/

#include <stdlib.h>

void number(int nb, char *str, int *count)
{
    if (nb > 9) {
        number(nb / 10, str, count);
    }
    str[*count] = '0' + nb % 10;
    (*count)++;
}

char *nbr_to_str(unsigned int nb)
{
    int count = 0;
    char *str = malloc(sizeof(char) * 6);

    if (nb == 0) {
        str[count] = '0';
        count++;
    } else
        number(nb, str, &count);
    str[count] = '\0';
    return str;
}
