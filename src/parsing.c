/*
** EPITECH PROJECT, 2026
** A-maze-d
** File description:
** parsing
*/

#include "../include/my.h"

//elle sert à rien ta fonction, car on lit pas les valeur comme ça, regarde le générateur de labyrinth et le fichier mazed, il faudra il un input dans le terminal qui ressemble à ce qu'i y a dans maze
int parsing(int argc, char **argv, values_t *values_s)
{
    if (argc != 4) {
        write(2, "Wrong number of arguments", 25);
        return 84;
    }
    values_s->number_of_rooms = my_atoi(argv[1]);
    values_s->density_of_connections = my_atoi(argv[2]);
    values_s->number_of_robots = my_atoi(argv[3]);
    my_printf("%d", "%d", "%d", values_s->number_of_rooms, values_s->density_of_connections, values_s->number_of_robots);
    return 0;
}
