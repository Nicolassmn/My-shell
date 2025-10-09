/*
** EPITECH PROJECT, 2023
** mimi
** File description:
** mimi
*/

#include "my.h"

static bool digit(char c)
{
    if (c < 48 || c > 57)
        return false;
    return true;
}

int my_atoi(char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    while (str[i] != '\0') {
        if (digit(str[i]) == true)
            result = result * 10 + (str[i] - '0');
        else
            break;
        i++;
    }
    result = result * sign;
    return result;
}
