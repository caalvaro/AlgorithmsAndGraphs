#include "graph_algorithms.h"

void breadth_first_search(GRAPH* graph, int start_vertex_name) {
    LIST_HEAD *queue, *adjacent_vertices_of_exploring_vertex;
    VERTEX *start_vertex;
    LIST_NODE *exploring_vertex_node, *adjacent_vertex_node;

    start_vertex = get_vertex_by_name(graph->vertices_list, start_vertex_name);
    start_vertex->color = GRAY;
    start_vertex->distance = 0;
    start_vertex->father = NULL;

    queue = create_head();
    append_node(queue, create_node(start_vertex));

    while (queue->list_size != 0) {
        exploring_vertex_node = dequeue(queue);

        adjacent_vertices_of_exploring_vertex = get_adjacent_vertices(graph->adjacency_list, exploring_vertex_node->vertex->name);

        if (adjacent_vertices_of_exploring_vertex->first_node == NULL) continue;
        adjacent_vertex_node = adjacent_vertices_of_exploring_vertex->first_node;

        while (adjacent_vertex_node != NULL) {
            if (adjacent_vertex_node->vertex->color == WHITE) {
                adjacent_vertex_node->vertex->color = GRAY;
                adjacent_vertex_node->vertex->distance = exploring_vertex_node->vertex->distance + 1;
                adjacent_vertex_node->vertex->father = exploring_vertex_node->vertex;

                append_node(queue, create_node(adjacent_vertex_node->vertex));
            }

            adjacent_vertex_node = adjacent_vertex_node->next_node;
        }

        exploring_vertex_node->vertex->color = BLACK;
    }

    graph->was_explored = TRUE;
    return;
}

BOOLEAN is_connected(GRAPH* graph) {
    int i, start_vertex_name = 1;

    if (graph->was_explored == FALSE) {
        breadth_first_search(graph, start_vertex_name);
    }

    for (i = 0; i < graph->number_vertices; i++) {
        VERTEX* vertex;
        vertex = graph->vertices_list + i;

        if (vertex->color == WHITE) return FALSE;
    }

    return TRUE;
}
