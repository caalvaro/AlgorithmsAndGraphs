#include "struct_and_macro_declarations.h"
#include "print_functions.h"
#include "structures_creation_functions.h"

int main(void) {
    int number_vertices, number_edges;
    int is_digraph;
    GRAPH* graph;

    printf("Insert Graph's number of vertices: ");
    scanf("%d", &number_vertices);

    printf("Insert Graph's number of edges: ");
    scanf("%d", &number_edges);

    printf("Is it a Directional Graph(Digraph)? (0-no / 1-yes): ");
    scanf("%d", &is_digraph);

    graph = create_graph(number_vertices, number_edges, is_digraph);

    print_adjacency_list(graph->adjacency_list, graph->number_vertices);

    return 0;
}
