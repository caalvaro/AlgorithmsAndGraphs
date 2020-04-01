#include "struct_and_macro_declarations.h"
#include "print_functions/print_functions.h"
#include "structures_creation_functions/structures_creation_functions.h"

int main(void) {
    int number_vertices, number_edges;
    int is_digraph;
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

    printf("Is it a Directional Graph(Digraph)? (0-no / 1-yes): ");
    while (TRUE) {
        fgets(input_test, sizeof(input_test), stdin);

        if (sscanf(input_test, "%d", &is_digraph) && (is_digraph == 0 || is_digraph == 1)) break;
        printf("\nSomething went wrong. Please enter a 0 if it isn't a Digraph or a 1 if it is: ");
    }

    graph = create_graph(number_vertices, number_edges, is_digraph);

    print_adjacency_list(graph->adjacency_list, graph->number_vertices);

    return 0;
}
