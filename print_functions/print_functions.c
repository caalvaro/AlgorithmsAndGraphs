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

extern void print_vertices_list(VERTEX* vertices_list, int number_vertices) {
    VERTEX* vertex;
    int i;

    printf("\n***VERTICES LIST***\n");

    for (i = 0; i < number_vertices; i++) {
        int father_name;
        char* color;

        vertex = vertices_list + i;
        if (vertex->father) father_name = vertex->father->name;
        else father_name = 0;

        if (vertex->color == 0) color = "WHITE";
        else if (vertex->color == 1) color = "GRAY";
        else if (vertex->color == 2) color = "BLACK";

        printf("VERTEX %d:\n\tColor: %s\n\tDistance: %d\n\tFather: %d\n",
            vertex->name,
            color,
            vertex->distance,
            father_name);
    }

    printf("\n*******************\n");
}
