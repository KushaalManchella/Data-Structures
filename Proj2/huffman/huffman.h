#include<stdio.h>
#include<stdlib.h>

typedef struct _Tree_Node{
	char ASCII;
	int freq;
	struct _Tree_Node *left;
	struct _Tree_Node *right;
} TreeNode;

typedef struct _Node{
	TreeNode *ptr;
	struct _Node *next;
} Node;


/*
void _destroy_node(Node* head);

void _destroy_tree(TreeNode* tree);

int _cmp_fn(TreeNode* p1, TreeNode* p2);

int _cmp_fn2(TreeNode* p1, TreeNode* p2);

Node *pq_enqueue(Node **pq, TreeNode *new_object, int (*cmp_fn)(TreeNode *, TreeNode *);


Node *pq_dequeue(Node **pq);
*/

