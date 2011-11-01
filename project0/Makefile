CFLAGS ?= -std=c99 -Wall -Wextra -Werror -Wfatal-errors

agg: main.c node.c node.h
	$(CC) $(CFLAGS) -o $@ $(filter %.c,$^)

clean:
	git clean -Xfd
