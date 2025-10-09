/*
** EPITECH PROJECT, 2023
** mimi
** File description:
** mimi
*/

#include "my.h"

int my_putstr(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++)
        my_putchar(str[i]);
    return i;
}
