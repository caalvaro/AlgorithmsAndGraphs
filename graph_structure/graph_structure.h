#ifndef GRAPH_STRUCTURE_H_INCLUDED
#define GRAPH_STRUCTURE_H_INCLUDED

#include "../struct_and_macro_declarations.h"
#include "../linked_list/linked_list.h"

VERTEX* create_vertex(int name);
VERTEX* get_vertex_by_name(VERTEX* vertices_list, int vertex_name);
LIST_HEAD* get_adjacent_vertices(LIST_HEAD* adjacency_list, int vertex_name);
void add_vertex_neighbor(LIST_HEAD* adjacency_list, VERTEX* vertices_list, int first_vertex_name, int second_vertex_name);
BOOLEAN edge_already_exists(int* edges_list, int first_vertex_name, int second_vertex_name);
LIST_HEAD* create_adjacency_list(VERTEX* vertices_list, int number_vertices, int number_edges, int* edges_list);
int* create_edges_list(int number_vertices, int number_edges);
VERTEX* create_vertices_list(int number_vertices);
extern GRAPH* create_graph(int number_vertices, int number_edges);

#endif
