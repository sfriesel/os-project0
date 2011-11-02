CFLAGS ?= -std=c99 -Wall -Wextra -Wno-unused-parameter -Werror -Wfatal-errors

agg: main.c node.c node.h leaf.c leaf.h inner_node.c inner_node.h
	$(CC) $(CFLAGS) -o $@ $(filter %.c,$^)

clean:
	git clean -Xfd
