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
    line_t *temp = *head;

    new_node->content = my_strdup(content);
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
}

static room_t *find_room(room_t *head, char *name)
{
    while (head) {
        if (strcmp(head->name, name) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

static void add_tunnel(room_t *a, room_t *b)
{
    tunnel_t *ta = malloc(sizeof(tunnel_t));
    tunnel_t *tb = malloc(sizeof(tunnel_t));

    ta->room_ptr = b;
    ta->next = a->tunnels;
    a->tunnels = ta;
    tb->room_ptr = a;
    tb->next = b->tunnels;
    b->tunnels = tb;
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

static void parse_room(char *line, type_t next_type, room_t **head,
    room_t **tail, values_t *values)
{
    char *sp1 = strchr(line, ' ');
    char *sp2;
    room_t *room;

    if (!sp1)
        return;
    *sp1 = '\0';
    sp2 = strchr(sp1 + 1, ' ');
    if (!sp2)
        return;
    *sp2 = '\0';
    room = create_room(line, my_atoi(sp1 + 1), my_atoi(sp2 + 1), next_type);
    add_room(head, tail, room);
    if (next_type == START)
        values->start = room;
    if (next_type == END)
        values->end = room;
}

int parsing(values_t *values)
{
    char *line = NULL;
    size_t len = 0;
    type_t next_type = MIDDLE;
    room_t *head = NULL;
    room_t *tail = NULL;
    char *dash;

    if (getline(&line, &len, stdin) == -1)
        return 84;
    add_line(&values->lines, line);
    values->number_of_robots = my_atoi(line);
    while (getline(&line, &len, stdin) != -1) {
        add_line(&values->lines, line);
        int l = strlen(line);
        if (l > 0 && line[l - 1] == '\n')
            line[l - 1] = '\0';
        if (strcmp(line, "##start") == 0) {
            next_type = START;
        } else if (strcmp(line, "##end") == 0) {
            next_type = END;
        } else if ((dash = strchr(line, '-')) && !strchr(line, ' ')) {
            *dash = '\0';
            room_t *a = find_room(head, line);
            room_t *b = find_room(head, dash + 1);
            if (a && b)
                add_tunnel(a, b);
        } else if (strchr(line, ' ')) {
            parse_room(line, next_type, &head, &tail, values);
            next_type = MIDDLE;
        }
    }
    free(line);
    values->rooms = head;
    return 0;
}
