#include "struct_and_macro_declarations.h"

VERTEX* create_vertex(int name);
LIST_NODE* create_node(VERTEX* vertex);
LIST_HEAD* create_head();
void append_node(LIST_HEAD* list_head, LIST_NODE* node);
LIST_HEAD* create_adjacency_list(int number_vertices, int number_edges, int* edges_list, int is_digraph);
int* create_edges_list(int number_edges);
extern GRAPH* create_graph(int number_vertices, int number_edges, int is_digraph);
