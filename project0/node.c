#include "node.h"

struct node_vtable {
	bool (*ask_question)(struct node * this);
	char * (*serialize)(struct node * this);
};
