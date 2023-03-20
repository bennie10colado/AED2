#ifndef PROJETO_INDEX_1VA_FINAL_BST_H
#define PROJETO_INDEX_1VA_FINAL_BST_H
#include <stdlib.h>

typedef struct index_bst {
    char *name_student;
    int index;
} index_bst;

typedef index_bst *Data_type;

typedef struct node_bst{
    Data_type data;
    struct node_bst *left, *right;
}node_bst;

typedef struct node_bst *Node_bst;

void elementPrintBST(Node_bst root);
void preorderPrintBST(Node_bst root);
void inorderPrintBST(Node_bst root);
void postorderPrintBST(Node_bst root);

Node_bst treeSearchBST(Node_bst root, char* nome);
Node_bst treeMaxBST(Node_bst root);
char *highestValueBST(Node_bst root);
char *lowestValueBST(Node_bst root);

void freeTreeBST(Node_bst root);
void initializeNodeBST(Node_bst *root);
Node_bst newNodeBST(Data_type data);
Node_bst insertNodeBST(Node_bst root, Data_type data);
Node_bst removeNodeBST(Node_bst root, char *name);



#endif //PROJETO_INDEX_1VA_FINAL_BST_H