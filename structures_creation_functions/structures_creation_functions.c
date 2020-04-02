#include "structures_creation_functions.h"

VERTEX* create_vertex(int name) {
    VERTEX* vertex;

    vertex = (VERTEX*) malloc(sizeof(VERTEX));
    if (!vertex) {
        printf("Error allocating memory for graph vertex\n");
        return NULL;
    }

    vertex->name = name;
    vertex->color = WHITE;
    vertex->distance = INFINITY;
    vertex->father = NULL;
    vertex->degree = 0;

    return vertex;
}

LIST_NODE* create_node(VERTEX* vertex) {
    LIST_NODE* node;

    node = (LIST_NODE*) malloc(sizeof(LIST_NODE));
    if (!node) {
        printf("Error allocating memory for list node\n");
        return NULL;
    }

    node->vertex = vertex;
    node->next_node = NULL;

    return node;
}

LIST_HEAD* create_head() {
    LIST_HEAD* head;

    head = (LIST_HEAD*) malloc(sizeof(LIST_HEAD));
    if (!head) {
        printf("Error allocating memory for list head\n");
        return NULL;
    }

    head->first_node = NULL;

    return head;
}

void append_node(LIST_HEAD* list_head, LIST_NODE* node) {
    LIST_NODE* aux_node;

    node->vertex->degree += 1;

    if (!list_head->first_node) {
        list_head->first_node = node;
        return;
    }

    aux_node = list_head->first_node;

    while (aux_node->next_node) {
        aux_node = aux_node->next_node;
    }

    aux_node->next_node = node;

    return;
}

int edge_already_exists(int* edges_list, int first_vertex_name, int second_vertex_name) {
    int i = 0;

    while (*(edges_list + i)) {
        if ((*(edges_list + i) == first_vertex_name && *(edges_list + i + 1) == second_vertex_name)
            || (*(edges_list + i) == second_vertex_name && *(edges_list + i + 1) == first_vertex_name)) return TRUE;

        i += 2;
    }

    return FALSE;
}

LIST_HEAD* create_adjacency_list(int number_vertices, int number_edges, int* edges_list) {
    LIST_HEAD *adjacency_list, *current_list_head_index;
    int i;

    adjacency_list = (LIST_HEAD*) calloc(number_vertices, sizeof(LIST_HEAD));
    if (!adjacency_list) {
        printf("Error allocating memory for adjacency list\n");
        return NULL;
    }

    for (i = 0; i < number_edges; i++) {
        VERTEX* vertex;
        LIST_NODE* node;
        int first_vertex_name, second_vertex_name;

        first_vertex_name = *(edges_list + 2 * i);
        second_vertex_name = *(edges_list + 2 * i + 1);

        vertex = create_vertex(second_vertex_name);
        node = create_node(vertex);

        current_list_head_index = adjacency_list + first_vertex_name - 1;

        append_node(current_list_head_index, node);

        vertex = create_vertex(first_vertex_name);
        node = create_node(vertex);

        current_list_head_index = adjacency_list + second_vertex_name - 1;

        append_node(current_list_head_index, node);
    }

    return adjacency_list;
}

int* create_edges_list(int number_vertices, int number_edges) {
    int i;
    int* edges_list;
    int vertex1, vertex2;
    char input_test[22];

    edges_list = (int*) calloc(number_edges * 2, sizeof(int*));

    printf("\n\nFrom now on, insert each edge\nExample: An edge connecting vertice 1 to 3 will be entered \"1 3\"\n");

    for (i = 0; i < number_edges; i++) {
        printf("\nEdge %d: ", i + 1);
        while (TRUE) {
            fgets(input_test, sizeof(input_test), stdin);

            if (sscanf(input_test, "%d %d", &vertex1, &vertex2) == 2
                && vertex1 > 0
                && vertex2 > 0
                && vertex1 <= number_vertices
                && vertex2 <= number_vertices
                && vertex1 != vertex2
                && !edge_already_exists(edges_list, vertex1, vertex2)) break;
            printf("\nSomething went wrong. Please give a valid vertex name: ");
        }

        *(edges_list + 2 * i) = vertex1;
        *(edges_list + 2 * i + 1) = vertex2;
    }

    return edges_list;
}

extern GRAPH* create_graph(int number_vertices, int number_edges) {
    int* edges_list;
    LIST_HEAD* adjacency_list;
    GRAPH* graph;

    graph = (GRAPH*) malloc(sizeof(GRAPH));
    if (!graph) {
        printf("Error allocating memory for graph\n");
        return NULL;
    }

    edges_list = create_edges_list(number_vertices, number_edges);
    adjacency_list = create_adjacency_list(number_vertices, number_edges, edges_list);

    graph->number_vertices = number_vertices;
    graph->number_edges = number_edges;
    graph->adjacency_list = adjacency_list;

    return graph;
}
