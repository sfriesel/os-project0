#pragma once

#include <stdio.h>
#include <stdbool.h>

struct node;

struct node_vtable {
	void (*ask_question)(struct node * this);
	struct node * (*process_answer)(struct node * this, char answer, struct node ** root);
	struct iovec (*serialize)(struct node * this);
	void (*node_dtor)(struct node * this);
};

struct inner_node;

struct node {
	const struct node_vtable * vtable;
	struct inner_node * parent;
};

struct node * node_factory(FILE * file);

struct node * node_ctor(struct inner_node * parent);
void node_dtor(struct node * this);
void node_ask_question(struct node * this);
struct node * node_process_answer(struct node * this, char answer, struct node ** root);
struct iovec node_serialize(struct node * this);

