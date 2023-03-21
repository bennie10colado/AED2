#ifndef TESTANDORB_RB_H
#define TESTANDORB_RB_H

enum color {RED, BLACK, DOUBLE_BLACK};

typedef struct index_rb{
    int enrollmentCode_student;
    int index;
}index_rb;

typedef index_rb *Data_type;

typedef struct node_rb{
    Data_type data;
    enum color color;
    struct node_rb *left, *right, *father;
}node_rb;

typedef struct node_rb *Node_rb;

void printTree(node_rb *node, int level);
void elementPrintRB(node_rb *root);
void preorderPrintRB(node_rb *root);
void inorderPrintRB(node_rb *root);
void printPreorderElementRB(node_rb *root);
void printInorderElementRB(node_rb *root);
node_rb *search(node_rb *root, int target);
void freeTree(node_rb *node);

enum color colorNode(node_rb *root);

int higher(int v1, int v2);
int height(node_rb *root);
int treeMaxValue(node_rb *root);

int is_root(node_rb *node);
int isLeftSon(node_rb *root);
int isRightSon(node_rb *root);

node_rb *brother(node_rb *node);
node_rb *grandFather(node_rb *node);
node_rb *uncle(node_rb *node);

void rotateLeft(node_rb **root, node_rb *p);
void rotateRight(node_rb **root, node_rb *p);
void doubleRotateLeft(node_rb **root, node_rb *p);
void doubleRotateRight(node_rb **root, node_rb *p);

void initializeNodeRBNull(node_rb **root);
void initializeNodeRBRoot(node_rb **root, Data_type data);
node_rb *initializeNode(Data_type data);

void fixInsertionNode(node_rb **root, node_rb *new_node);
void insertionNode(node_rb **root, Data_type data);
void removeDoubleBlack(node_rb **root, node_rb *doubleBlackNode);
void fixDeletionNode(node_rb **root, node_rb* doubleBlackNode);
void deletionNode(node_rb **root, Data_type dataTarget);

#endif //TESTANDORB_RB_H
