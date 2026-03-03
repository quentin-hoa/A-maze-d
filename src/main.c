/*
** EPITECH PROJECT, 2026
** project_name
** File description:
** main
*/

#include "../include/my.h"
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    values_t *values = malloc(sizeof(values_t));
    if (!values)
        return 84;
    parsing(argc, argv, values);
    return 0;
}
