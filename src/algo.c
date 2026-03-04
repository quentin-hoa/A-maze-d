/*
** EPITECH PROJECT, 2026
** A-maze-d
** File description:
** algo
*/

#include "../include/my.h"
#include <stdlib.h>

void print_distance(room_t *head)
{
    room_t *current = head;

    while (current) {
        printf("room %s distance to end: %d\n", current->name, current->distance);
        current = current->next;
    }
}
