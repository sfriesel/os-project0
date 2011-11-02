#pragma once

#include "node.h"

struct inner_node {
	struct node node;
	char * question;
	struct node * yes;
	struct node * no;
};

struct inner_node * inner_node_ctor(char * question, struct node * yes, struct node * no);
void inner_node_dtor(struct inner_node * this);
