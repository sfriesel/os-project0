Overview
========
struct node is the abstract base class that represents any part of the tree. It provides interfaces for serialization and interactive traversal of the tree in the form of a vtable that needs to be populated by sub classes. It also provides a static factory function for deserialization of a tree from a file.

struct inner_node and struct leaf are derived classes that implement these interfaces.

main() reads the input file given as parameter (empty file is possible for a clean start) and then loops, allowing the current node to interact with the user and transition to another node. It also intercepts the general commands for resetting, saving and terminating the game.
