/*
** EPITECH PROJECT, 2026
** my.h
** File description:
** my.h - Main header file
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdarg.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdbool.h>

// Include my_printf functions
    #include "../lib/my_printf/include/my_printf.h"

// Include other_functions
    #include "../lib/other_functions/other_functions.h"

typedef enum TYPE {
    START,
    MIDDLE,
    END
} TYPE;

struct room_s;
typedef struct tunnel_s {
    struct room_s *room_ptr;
    struct tunnel_s *next;
} tunnel_t;

typedef struct room_s {
    char *name;
    int x;
    int y;
    TYPE type;

    bool occupied;
    int distance;
    bool visited;
    tunnel_t *tunnels;
    struct room_s *next;
} room_t;

typedef struct values_s {
    int number_of_rooms;
    int density_of_connections;
    int number_of_robots;
    int nb_round;
} values_t;

typedef struct queue_node_s {
    room_t *room;
    struct queue_node_s *next;
} queue_node_t;

typedef struct queue_s {
    queue_node_t *front;
    queue_node_t *rear;
} queue_t;


typedef struct path_s {
    room_t **rooms;
    int length;
    int robots_count;
    struct path_s *next;
} path_t;

typedef struct robot_s {
    int id;
    path_t *path;
    int pos_in_path;
    bool finished;
} robot_t;

int calcul_distances(room_t *head, room_t *end);
path_t *extract_single_path(room_t *start, room_t *end);
void print_distance(room_t *head);
void assign_robots(path_t *paths, robot_t *robots, int nb_robots);
void solve_lemin(path_t *paths, robot_t *robots, int nb_robots);

#endif
