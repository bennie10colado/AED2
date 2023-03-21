#ifndef TESTANDOAVL_AVL_H
#define TESTANDOAVL_AVL_H

typedef struct index_avl {
    int age_student;
    int index;
}index_avl;

typedef index_avl *Data_type;

typedef struct node_avl{
    Data_type data;
    struct node_avl *left, *right;
    int fb;
}node_avl;

typedef struct node_avl *Node_avl;

void elementPrintAVL(Node_avl root);
void preorderPrintAVL(Node_avl root);
void inorderPrintAVL(Node_avl root);
void postorderPrintAVL(Node_avl root);

int higher(int v1, int v2);
int height(Node_avl root);

Node_avl treeMaxAVL(Node_avl root);
int treeMaxValue(Node_avl root);
int lowerValue(Node_avl root);

void initializeNodeAVL(Node_avl *root);

Node_avl newNodeAVL(Data_type data);

Node_avl rotateRight(Node_avl p);
Node_avl doubleRotateRight(Node_avl p);
Node_avl rotateLeft(Node_avl p);
Node_avl doubleRotateLeft(Node_avl p);

Node_avl case1(Node_avl p);
Node_avl case2(Node_avl p);
Node_avl rotate(Node_avl root);

Node_avl insertionNodeAVL(Node_avl root, Data_type data, int *increased);
Node_avl removeNodeAVL(Node_avl root, int ageStudentTarget, int *decreased);


#endif //TESTANDOAVL_AVL_H
