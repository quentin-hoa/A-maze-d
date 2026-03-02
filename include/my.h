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
    tunnel_t *tunnels;
    struct room_s *next;
} room_t;

typedef struct robot_s {
    int id;
    room_t *current_room;
    struct robot_s *next;
} robot_t;


typedef struct values_s {
    int number_of_rooms;
    int density_of_connections;
    int number_of_robots;
} values_t;

#endif
