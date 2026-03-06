/*
** EPITECH PROJECT, 2026
** A-maze-d
** File description:
** parsing
*/

#include "../include/my.h"

static void add_line(line_t **head, char *content)
{
    line_t *new_node = malloc(sizeof(line_t));
    line_t *last = *head;

    new_node->content = my_strdup(content);
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    while (last->next)
        last = last->next;
    last->next = new_node;
}

static room_t *find_room(room_t *room, char *name)
{
    while (room) {
        if (strcmp(room->name, name) == 0)
            return room;
        room = room->next;
    }
    return NULL;
}

static void add_tunnel(room_t *a, room_t *b)
{
    tunnel_t *to_b = malloc(sizeof(tunnel_t));
    tunnel_t *to_a = malloc(sizeof(tunnel_t));

    to_b->room_ptr = b;
    to_b->next = a->tunnels;
    a->tunnels = to_b;
    to_a->room_ptr = a;
    to_a->next = b->tunnels;
    b->tunnels = to_a;
}

static room_t *create_room(char *name, int x, int y, type_t type)
{
    room_t *room = malloc(sizeof(room_t));

    room->name = my_strdup(name);
    room->x = x;
    room->y = y;
    room->type = type;
    room->occupied = false;
    room->distance = -1;
    room->visited = false;
    room->tunnels = NULL;
    room->next = NULL;
    return room;
}

static void add_room(room_t **head, room_t **tail, room_t *room)
{
    if (!*head) {
        *head = room;
        *tail = room;
    } else {
        (*tail)->next = room;
        *tail = room;
    }
}

static room_t *parse_room(char *line, type_t next_type,
    room_t **head, room_t **tail)
{
    char *name_end = strchr(line, ' ');
    char *x_end;
    room_t *room;

    if (!name_end)
        return NULL;
    *name_end = '\0';
    x_end = strchr(name_end + 1, ' ');
    if (!x_end)
        return NULL;
    *x_end = '\0';
    room = create_room(line, my_atoi(name_end + 1), my_atoi(x_end + 1),
        next_type);
    add_room(head, tail, room);
    return room;
}

static void parse_tunnel(char *line, room_t *head)
{
    char *dash;
    room_t *a;
    room_t *b;

    dash = strchr(line, '-');
    if (!dash)
        return;
    *dash = '\0';
    a = find_room(head, line);
    b = find_room(head, dash + 1);
    if (a && b)
        add_tunnel(a, b);
}

static void process_line(char *line, type_t *next_type,
    room_t **tail, values_t *values)
{
    room_t *room;

    if (strcmp(line, "##start") == 0 || strcmp(line, "##end") == 0) {
        *next_type = (strcmp(line, "##start") == 0) ? START : END;
        return;
    }
    if (strchr(line, '-') && !strchr(line, ' ')) {
        parse_tunnel(line, values->rooms);
        return;
    }
    if (!strchr(line, ' '))
        return;
    room = parse_room(line, *next_type, &values->rooms, tail);
    if (*next_type == START)
        values->start = room;
    if (*next_type == END)
        values->end = room;
    *next_type = MIDDLE;
}

int parsing(values_t *values)
{
    char *line = NULL;
    size_t len = 0;
    type_t next_type = MIDDLE;
    room_t *tail = NULL;
    int line_len;

    values->rooms = NULL;
    if (getline(&line, &len, stdin) == -1)
        return 84;
    add_line(&values->lines, line);
    values->number_of_robots = my_atoi(line);
    while (getline(&line, &len, stdin) != -1) {
        add_line(&values->lines, line);
        line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n')
            line[line_len - 1] = '\0';
        process_line(line, &next_type, &tail, values);
    }
    free(line);
    return 0;
}
