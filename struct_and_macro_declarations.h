#ifndef STRUCT_AND_MACRO_DECLARATIONS_H_INCLUDED
#define STRUCT_AND_MACRO_DECLARATIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define INFINITY -1

#define FALSE 0
#define TRUE 1

typedef struct _VERTEX VERTEX;
typedef struct _LIST_NODE LIST_NODE;
typedef struct _LIST_HEAD LIST_HEAD;
typedef struct _GRAPH GRAPH;

struct _VERTEX {
    int name;
    int color;
    int distance;
    int degree;
    VERTEX* father;
};

struct _LIST_NODE {
    VERTEX* vertex;
    LIST_NODE* previous_node;
    LIST_NODE* next_node;
};

struct _LIST_HEAD {
    int list_size;
    LIST_NODE* first_node;
    LIST_NODE* last_node;
};

struct _GRAPH {
    int number_vertices;
    int number_edges;
    LIST_HEAD* adjacency_list;
};

#endif
