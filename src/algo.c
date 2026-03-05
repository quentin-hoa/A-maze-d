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

static void get_first_step(room_t *start, room_t **first_step)
{
    tunnel_t *t = start->tunnels;

    while (t) {
        if (t->room_ptr->distance != -1) {
            *first_step = t->room_ptr;
            return;
        }
        t = t->next;
    }
}

// trouve la pochaine salle la plus proche de end qui n'est pas occupée par un autre chemin qui existe déjà (-2 de dsitance)
room_t *find_next_step(room_t *current, int current_dist)
{
    tunnel_t *tmp = current->tunnels;
    room_t *next_step = NULL;

    while (tmp) {
        if (tmp->room_ptr->type == END)
            return tmp->room_ptr;
        // cherche la salle avec une distance = à la distance actuelle -1 (prochaine salle la plus proche de la sortie)
        if (tmp->room_ptr->distance == (current_dist - 1) && tmp->room_ptr->distance != -2) {
            next_step = tmp->room_ptr;
            break;
        }
        tmp = tmp->next;
    }
    return next_step;
}
//si le chemin ne mène pas à END, on libère tout
path_t *no_end_path(int len, path_t *path)
{
    if (len == 0 || path->rooms[len - 1]->type != END) {
        free(path->rooms);
        free(path);
        return NULL;
    }
    return path;
}

static void go_trough_all_rooms(room_t *curr, path_t *path, int *len, int current_dist)
{
    while (curr != NULL) {
        path->rooms[(*len)++] = curr;
        if (curr->type == END)
            break;
        //sauvegarde la distance actuelle et on marque la salle comme "bloquée" (-2)
        current_dist = curr->distance;
        curr->distance = -2; 
        curr = find_next_step(curr, current_dist);
        if (*len > 1990) {
            curr = NULL;
            break;
        }
    }
}

path_t *extract_single_path(room_t *start, room_t *end)
{
    room_t *curr = NULL;
    int len = 0;
    tunnel_t *t = start->tunnels;
    room_t *first_step = NULL;
    path_t *path = malloc(sizeof(path_t));
    path->rooms = malloc(sizeof(room_t *) * 2000);
    int current_dist;

    get_first_step(start, &first_step);
    if (!first_step)
        return NULL;
    path->robots_count = 0;
    path->next = NULL;
    curr = first_step;
    go_trough_all_rooms(curr, path, &len, current_dist);
    if (!no_end_path(len, path))
        return NULL;
    path->length = len;
    return path;
}

void assign_robots(path_t *paths, robot_t *robots, int nb_robots)
{
    path_t *best = paths;

    for (int i = 0; i < nb_robots; i++) {
        for (path_t *curr = paths; curr; curr = curr->next) {
            if ((curr->length + curr->robots_count) < (best->length + best->robots_count))
                best = curr;
        }
        robots[i].id = i + 1;
        robots[i].path = best;
        robots[i].pos_in_path = -1;
        robots[i].finished = false;
        best->robots_count++;
    }
}
