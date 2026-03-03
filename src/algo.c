/*
** EPITECH PROJECT, 2026
** A-maze-d
** File description:
** algo
*/

#include "../include/my.h"
#include <math.h>
#include <stdlib.h>

queue_t *init_queue(void)
{
    queue_t *q = malloc(sizeof(queue_t));

    if (!q)
        return NULL;
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void add_to_queue(queue_t *queue, room_t *to_add)
{
    queue_node_t *new_node = malloc(sizeof(queue_node_t));

    if (!new_node || !to_add)
        return;
    new_node->room = to_add;
    new_node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
        return;
    }
    queue->rear->next = new_node;
    queue->rear = new_node;
}

room_t *remove_from_queue(queue_t *queue)
{
    queue_node_t *temp;
    room_t *room;

    if (queue->front == NULL)
        return NULL;
    temp = queue->front;
    room = temp->room;
    queue->front = queue->front->next;
    if (queue->front == NULL)
        queue->rear = NULL;
    free(temp);
    return room;
}

int calcul_distances(room_t *head, room_t *end)
{
    room_t *current = head;
    queue_t *queue = malloc(sizeof(queue_t));

    if (!head)
        return 84;
    while (current) {
        current->distance = -1;
        current = current->next;
    }
    end->distance = 0;

    return 0;
}
