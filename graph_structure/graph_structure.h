#include "../struct_and_macro_declarations.h"
#include "../linked_list/linked_list.h"

VERTEX* create_vertex(int name);
void add_vertex_neighbor(LIST_HEAD* adjacency_list, int first_vertex_name, int second_vertex_name);
int edge_already_exists(int* edges_list, int first_vertex_name, int second_vertex_name);
LIST_HEAD* create_adjacency_list(int number_vertices, int number_edges, int* edges_list);
int* create_edges_list(int number_vertices, int number_edges);
extern GRAPH* create_graph(int number_vertices, int number_edges);
