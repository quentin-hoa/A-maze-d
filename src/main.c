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
    values_t values = {0};

    (void)argc;
    (void)argv;
    if (parsing(&values) == 84)
        return 84;
    if (!values.start || !values.end) {
        write(2, "No start or end room\n", 21);
        return 84;
    }
    calcul_distances(values.rooms, values.end);
    return handle_paths(values.start, values.end, &values);
}