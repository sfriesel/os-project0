#include "leaf.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/uio.h>

static const struct node_vtable leaf_funcs = { /*TODO*/ NULL, NULL, NULL, NULL };

struct leaf * leaf_ctor(char * name) {
	struct node * super = node_ctor();
	super->vtable = &leaf_funcs;
	
	struct leaf * this = realloc(super, sizeof(*this));
	this->name = malloc(strlen(name) + 1);
	strcpy(this->name, name);
	
	return this;
}

void leaf_dtor(struct leaf * this) {
	free(this->name);
	node_dtor(&this->node);
}

void leaf_ask_question(struct node * super) {
	struct leaf * this = (struct leaf*)super;
	printf("Is it a %s?\n", this->name);
}

struct iovec leaf_serialize(struct node * super) {
	struct leaf * this = (struct leaf*)super;
	size_t name_len = strlen(this->name);
	uint32_t len_network_order = htonl(name_len);
	
	struct iovec result;
	result.iov_len = sizeof(uint8_t) + sizeof(uint32_t) + name_len;
	result.iov_base = malloc(result.iov_len);
	
	char * pos = result.iov_base;
	memset(pos, 1, sizeof(uint8_t));
	pos += sizeof(uint8_t);
	memcpy(pos, &len_network_order, sizeof(len_network_order));
	pos += sizeof(len_network_order);
	memcpy(pos, this->name, name_len);
	
	return result;
}
