#include "print_functions.h"

extern void print_adjacency_list(LIST_HEAD* adjacency_list, int number_vertices) {
    int i;
    LIST_NODE* aux_node;

    printf("\n");

    for (i = 0; i < number_vertices; i++) {
        printf("VERTEX %d: ", i + 1);

        aux_node = (adjacency_list + i)->first_node;

        if (!aux_node) {
            printf("*");
        }

        while (aux_node) {
            printf("%d ", aux_node->vertex->name);
            aux_node = aux_node->next_node;
        }

        printf("\n");
    }

    printf("\n");
}
