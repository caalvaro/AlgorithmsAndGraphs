#include "struct_and_macro_declarations.h"
#include "print_functions/print_functions.h"
#include "graph_structure/graph_structure.h"

int main(void) {
    int number_vertices, number_edges;
    GRAPH* graph;
    char input_test[11];

    printf("Insert Graph's number of vertices: ");
    while (TRUE) {
        fgets(input_test, sizeof(input_test), stdin);

        if (sscanf(input_test, "%d", &number_vertices) && number_vertices > 0) break;
        printf("\nSomething went wrong. Please enter a positive integer: ");
    }

    printf("Insert Graph's number of edges: ");
    while (TRUE) {
        fgets(input_test, sizeof(input_test), stdin);

        if (sscanf(input_test, "%d", &number_edges) && number_edges > 0) break;
        printf("\nSomething went wrong. Please enter a positive integer: ");
    }

    graph = create_graph(number_vertices, number_edges);

    print_adjacency_list(graph->adjacency_list, graph->number_vertices);

    return 0;
}
