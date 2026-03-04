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

path_t *extract_single_path(room_t *start, room_t *end)
{
    room_t *curr = NULL;
    int len = 0;
    tunnel_t *t = start->tunnels;
    room_t *first_step = NULL;

    // 1. Trouver une salle adjacente au START qui n'est pas encore "bloquée"
    while (t) {
        if (t->room_ptr->type == END || (t->room_ptr->distance > 0 && t->room_ptr->distance != -2)) {
            first_step = t->room_ptr;
            break;
        }
        t = t->next;
    }
    if (!first_step) return NULL;

    path_t *path = malloc(sizeof(path_t));
    path->rooms = malloc(sizeof(room_t *) * 2000); // Taille sécurisée
    path->robots_count = 0;
    path->next = NULL;

    curr = first_step;
    while (curr != NULL) {
        path->rooms[len++] = curr;
        if (curr->type == END) break;

        // On sauvegarde la distance actuelle et on marque la salle comme "bloquée" (-2)
        int current_dist = curr->distance;
        curr->distance = -2; 

        tunnel_t *tmp = curr->tunnels;
        room_t *next_step = NULL;
        while (tmp) {
            // Priorité absolue à la sortie END
            if (tmp->room_ptr->type == END) {
                next_step = tmp->room_ptr;
                break;
            }
            // Sinon on suit la pente de distance (distance - 1)
            if (tmp->room_ptr->distance == (current_dist - 1) && tmp->room_ptr->distance != -2) {
                next_step = tmp->room_ptr;
                break;
            }
            tmp = tmp->next;
        }
        curr = next_step;
        
        // Sécurité anti-boucle : si on stagne ou si len explose
        if (len > 1990) {
            curr = NULL;
            break;
        }
    }

    // Validation : si le chemin ne mène pas à END, on libère tout
    if (len == 0 || path->rooms[len - 1]->type != END) {
        free(path->rooms);
        free(path);
        return NULL;
    }
    path->length = len;
    return path;
}

// Répartit les robots sur les chemins selon la formule (longueur + nb_robots)
void assign_robots(path_t *paths, robot_t *robots, int nb_robots)
{
    for (int i = 0; i < nb_robots; i++) {
        path_t *best = paths;
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

// Gère le mouvement tour par tour
void solve_lemin(path_t *paths, robot_t *robots, int nb_robots)
{
    int finished = 0;
    
    printf("#moves\n"); // INDISPENSABLE
    while (finished < nb_robots) {
        bool moves_in_this_round = false;
        bool first_print = true;

        for (int i = 0; i < nb_robots; i++) {
            if (robots[i].finished) continue;

            int next_idx = robots[i].pos_in_path + 1;
            room_t *target = robots[i].path->rooms[next_idx];

            if (target->type == END || !target->occupied) {
                if (robots[i].pos_in_path != -1)
                    robots[i].path->rooms[robots[i].pos_in_path]->occupied = false;

                robots[i].pos_in_path++;
                
                if (!first_print) printf(" ");
                printf("P%d-%s", robots[i].id, target->name);
                first_print = false;
                moves_in_this_round = true;

                if (target->type == END) {
                    robots[i].finished = true;
                    finished++;
                } else {
                    target->occupied = true;
                }
            }
        }
        if (!moves_in_this_round) break;
        printf("\n");
    }
}
