#include "graph_structure.h"

VERTEX* create_vertex(int name) {
    VERTEX* vertex;

    vertex = (VERTEX*) malloc(sizeof(VERTEX));
    if (vertex == NULL) {
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

VERTEX* get_vertex_by_name(VERTEX* vertices_list, int vertex_name) {
    return vertices_list + vertex_name - 1;
}

LIST_HEAD* get_adjacent_vertices(LIST_HEAD* adjacency_list, int vertex_name) {
    return adjacency_list + vertex_name - 1;
}

void add_vertex_neighbor(LIST_HEAD* adjacency_list, VERTEX* vertices_list, int first_vertex_name, int second_vertex_name) {
    LIST_HEAD* first_vertex_index_in_adjacency_list;
    VERTEX* vertex;
    LIST_NODE* node;

    vertex = get_vertex_by_name(vertices_list, second_vertex_name);
    vertex->degree += 1;
    node = create_node(vertex);

    first_vertex_index_in_adjacency_list = adjacency_list + first_vertex_name - 1;
    append_node(first_vertex_index_in_adjacency_list, node);

    return;
}

BOOLEAN edge_already_exists(int* edges_list, int first_vertex_name, int second_vertex_name) {
    int i = 0;
    int vertex1_name_from_edges_list = 1, vertex2_name_from_edges_list;

    while (vertex1_name_from_edges_list != 0) {
        vertex1_name_from_edges_list = *(edges_list + i);
        vertex2_name_from_edges_list = *(edges_list + i + 1);

        if ((vertex1_name_from_edges_list == first_vertex_name && vertex2_name_from_edges_list == second_vertex_name)
            || (vertex1_name_from_edges_list == second_vertex_name && vertex2_name_from_edges_list == first_vertex_name)) return TRUE;

        i += 2;
    }

    return FALSE;
}

LIST_HEAD* create_adjacency_list(VERTEX* vertices_list, int number_vertices, int number_edges, int* edges_list) {
    LIST_HEAD *adjacency_list;
    int i;

    adjacency_list = (LIST_HEAD*) calloc(number_vertices, sizeof(LIST_HEAD));
    if (adjacency_list == NULL) {
        printf("Error allocating memory for adjacency list\n");
        return NULL;
    }

    for (i = 0; i < number_edges; i++) {
        int first_vertex_name, second_vertex_name;

        first_vertex_name = *(edges_list + 2 * i);
        second_vertex_name = *(edges_list + 2 * i + 1);

        add_vertex_neighbor(adjacency_list, vertices_list, first_vertex_name, second_vertex_name);
        add_vertex_neighbor(adjacency_list, vertices_list, second_vertex_name, first_vertex_name);
    }

    return adjacency_list;
}

int* create_edges_list(int number_vertices, int number_edges) {
    int i;
    int* edges_list;
    int vertex1, vertex2;
    char input_test[22];

    edges_list = (int*) calloc(number_edges * 2, sizeof(int*));
    if (edges_list == NULL) {
        printf("Error allocating memory for edges list\n");
        return NULL;
    }

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

VERTEX* create_vertices_list(int number_vertices) {
    VERTEX* vertices_list;
    int vertex_name;

    vertices_list = (VERTEX*) calloc(number_vertices, sizeof(VERTEX));
    if (vertices_list == NULL) {
        printf("Error allocating memory for vertices list\n");
        return NULL;
    }

    for (vertex_name = 1; vertex_name <= number_vertices; vertex_name++) {
        VERTEX* vertex;

        vertex = vertices_list + vertex_name - 1;
        vertex->name = vertex_name;
        vertex->distance = INFINITY;
    }

    return vertices_list;
}

extern GRAPH* create_graph(int number_vertices, int number_edges) {
    int* edges_list;
    VERTEX* vertices_list;
    LIST_HEAD* adjacency_list;
    GRAPH* graph;

    graph = (GRAPH*) malloc(sizeof(GRAPH));
    if (graph == NULL) {
        printf("Error allocating memory for graph\n");
        return NULL;
    }

    vertices_list = create_vertices_list(number_vertices);
    edges_list = create_edges_list(number_vertices, number_edges);
    adjacency_list = create_adjacency_list(vertices_list, number_vertices, number_edges, edges_list);

    graph->number_vertices = number_vertices;
    graph->number_edges = number_edges;
    graph->vertices_list = vertices_list;
    graph->adjacency_list = adjacency_list;
    graph->was_explored = FALSE;

    return graph;
}
