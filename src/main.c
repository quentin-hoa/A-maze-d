/*
** EPITECH PROJECT, 2026
** A-maze-d
** File description:
** main
*/

#include "../include/my.h"

int handle_paths(room_t *start, room_t *end, values_t *values)
{
    path_t *path_list = NULL;
    path_t *new_path = extract_single_path(start, end);;
    robot_t *robots = malloc(sizeof(robot_t) * values->number_of_robots);

    while (new_path != NULL) {
        new_path->next = path_list;
        path_list = new_path;
        new_path = extract_single_path(start, end);
    }
    if (!path_list)
        return 84;
    return 0;
}

int main(int argc, char **argv)
{
    //parsing fonction de Daniel
}