#include <stdio.h>
#include <string.h>
#include "bst.h"

void elementPrintBST(Node_bst root) {
    printf("[%s] ", root->data->name_student);
}

void preorderPrintBST(Node_bst root){
    if(root != NULL){
        elementPrintBST(root);
        preorderPrintBST(root->left);
        preorderPrintBST(root->right);
    }
}

void inorderPrintBST(Node_bst root){
    if(root != NULL) {
        inorderPrintBST(root->left);
        elementPrintBST(root);
        inorderPrintBST(root->right);
    }
}

void postorderPrintBST(Node_bst root){
    if(root != NULL)
    {
        postorderPrintBST(root->left);
        postorderPrintBST(root->right);
        elementPrintBST(root);
    }
}

Node_bst treeSearchBST(Node_bst root, char* nome){
    if(root != NULL){
        if (strcmp(nome, root->data->name_student) == 0)
            return root;
        else{
            if (strcmpi(nome, root->data->name_student) > 0)
                return treeSearchBST(root->right, nome);
            else
                return treeSearchBST(root->left, nome);
        }
    }
    return NULL;
}

Node_bst treeMaxBST(Node_bst root){
    if(root != NULL){
        Node_bst aux = root;
        while (aux->right != NULL){
            aux = aux->right;
        }
        return aux;
    }
    return NULL;
}

char *highestValueBST(Node_bst root){
    if(root == NULL)
        return NULL;
    if(root->right == NULL)
        return root->data->name_student;
    else
        return highestValueBST(root->right);
}

char *lowestValueBST(Node_bst root){
    if(root == NULL)
        return NULL;
    if(root->left == NULL)
        return root->data->name_student;
    else
        return lowestValueBST(root->left);
}

void initializeNodeBST(Node_bst *root){
    *root = NULL;
}

Node_bst newNodeBST(Data_type data){
    Node_bst node = (Node_bst) malloc(sizeof(struct node_bst));
    //node->data = (Data_type) malloc(sizeof(Data_type));

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}


Node_bst insertNodeBST(Node_bst root, Data_type data){
    if(root == NULL){
        return newNodeBST(data);
    }
    if(strcmp(data->name_student, root->data->name_student) >= 0) {
        root->right = insertNodeBST(root->right, data);
    }else{
        root->left = insertNodeBST(root->left, data);
    }
    return root;
}

Node_bst removeNodeBST(Node_bst root, char *name){
    if(root == NULL){
        //printf("Student not found");
        return NULL;}

    if(strcmp(name, root->data->name_student) > 0){
        root->right = removeNodeBST(root->right, name);
    }
    else if(strcmp(name, root->data->name_student) < 0){
        root->left = removeNodeBST(root->left, name);
    }else{
        if(root->left == NULL && root->right == NULL){
            free(root);
            //printf("Student deleted with success.\n");
            return NULL;
        }
        else if(root->left == NULL && root->right != NULL){
            Node_bst aux = root->right;
            free(root);
            //printf("Student deleted with success.\n");
            return aux;
        }
        else if (root->left != NULL && root->right == NULL){
            Node_bst aux = root->left;
            free(root);
            //printf("Student deleted with success.\n");
            return aux;
        }
        else{
            Node_bst aux = treeMaxBST(root->left);
            root->data->name_student = aux->data->name_student;
            root->left = removeNodeBST(root->left, aux->data->name_student);
            return root;
        }
    }
    return root;
}

void freeTreeBST(Node_bst root){
    if (root != NULL){
        freeTreeBST(root->left);
        freeTreeBST(root->right);
        free(root->data->name_student);
        free(root);
    }
}
