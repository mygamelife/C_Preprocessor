#ifndef Node_H
#define Node_H

typedef struct Node Node;

struct Node {
	Node *left;
	Node *right;
	char color;		// 'b' or 'r' (black or red)
	int data;
	void *dataPtr;
};

#endif // Node_H

