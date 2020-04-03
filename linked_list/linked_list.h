#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include "../struct_and_macro_declarations.h"

LIST_NODE* create_node(VERTEX* vertex);
LIST_HEAD* create_head();
void append_node(LIST_HEAD* list_head, LIST_NODE* node);

#endif
