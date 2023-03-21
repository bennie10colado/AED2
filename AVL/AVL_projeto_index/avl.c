#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void elementPrintAVL(Node_avl root) {
    printf("[%d] ", root->data->age_student);
}

void preorderPrintAVL(Node_avl root){
    if(root != NULL){
        elementPrintAVL(root);
        preorderPrintAVL(root->left);
        preorderPrintAVL(root->right);
    }
}

void inorderPrintAVL(Node_avl root){
    if(root != NULL) {
        inorderPrintAVL(root->left);
        elementPrintAVL(root);
        inorderPrintAVL(root->right);
    }
}

void postorderPrintAVL(Node_avl root){
    if(root != NULL)
    {
        postorderPrintAVL(root->left);
        postorderPrintAVL(root->right);
        elementPrintAVL(root);
    }
}

int higher(int v1, int v2)
{
    if (v1 > v2)
        return v1;
    else
        return v2;
}

int height(Node_avl root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + higher(height(root->right), height(root->left));
}

Node_avl treeMaxAVL(Node_avl root){
    if(root != NULL){
        Node_avl aux = root;
        while (aux->right != NULL){
            aux = aux->right;
        }
        return aux;
    }
    return NULL;
}

int treeMaxValue(Node_avl root){
    if (root == NULL)
        return 0;
    if (root->right == NULL)
        return root->data->age_student;
    else
        return treeMaxValue(root->right);
}

int lowerValue(Node_avl root){
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        return root->data->age_student;
    else
        return lowerValue(root->left);
}

void initializeNodeAVL(Node_avl *root){
    *root = NULL;
}

Node_avl newNodeAVL(Data_type data){
    Node_avl aux = (Node_avl) malloc(sizeof(struct node_avl));
    aux->data = data;
    aux->left = NULL;
    aux->right = NULL;
    aux->fb = 0;

    return aux;
}

/*
          p(-2)                         u(0)
        /   \                         /  \
    (-1)u    t3        ==>          t1    p(0)
     /   \                               / \
    t1   t2                            t2   t3

*/
Node_avl rotateRight(Node_avl p){
    // rotacao de p(fb = -2) para a direita, retornando ponteiro para a nova raiz da subárvore trocada.
    Node_avl u, t2;
    u = p->left; // sub-árvore a esquerda de p.
    t2 = u->right;

    p->left = t2; // p pega o filho direito de u (maior elemento da subarvore a esquerda)
    u->right = p; // p se torna filho direito de u

    switch (u->fb)
    {
        case -1:
            p->fb = 0;
            u->fb = 0;
            break;

        case 0:
            p->fb = -1;
            u->fb = 1;
            break;

            // caso -1: é rotacao dupla direita(sinais diferentes)
    }
    return u;
}

/*
      p(-2)                         p                     v
    /   \                         /  \                  /   \
(1)u    t4        ==>            u    t4     ==>       u      p
 /   \                          /  \                  / \    / \
t1    v(?)                     v    t3               t1  t2 t3  t4
     / \                     /  \
    t2  t3                  t1   t2
*/
Node_avl doubleRotateRight(Node_avl p)
{
    Node_avl u, v, t2, t3;

    u = p->left;
    v = u->right;
    t2 = v->left;
    t3 = v->right;
    // primeira rotacao (S.E.)
    p->left = v;
    v->left = u;
    u->right = t2;
    // segunda rotacao (S.D.)
    p->left = t3;
    v->right = p;

    switch (v->fb)
    {
        case -1:
            u->fb = 0;
            p->fb = 1;
            v->fb = 0;
            break;
        case 0:
            u->fb = 0;
            p->fb = 0;
            v->fb = 0;
            break;
        case 1:
            u->fb = -1;
            p->fb = 0;
            v->fb = 0;
            break;
    }

    return v;
}

/*
          p(+2)                       u(0)
        /   \                       /   \
       t1    u(1)        ==>      p(0)    t3
           /   \                  /  \
          t2    t3               t1   t2

*/
Node_avl rotateLeft(Node_avl p)
{
    Node_avl u, t2;
    u = p->right;
    t2 = u->left;

    u->left = p;
    p->right = t2; // p pega o t2(filho left de u: menor elemento da sub-árvore a esquerda)

    switch (u->fb)
    {
        case 1:
            p->fb = 0;
            u->fb = 0;
            break;

        case 0:        // em caso de exclusao
            p->fb = 1; // poderia retirar essa linha
            u->fb = -1;
            break;

            // caso -1: é rotacao dupla esquerda(sinais diferentes)
    }
    return u;
}

Node_avl doubleRotateLeft(Node_avl p){
    Node_avl u, v, t2, t3;

    u = p->right;
    v = u->left;
    t2 = v->left;
    t3 = v->right;
    // primeira rotacao (S.E.)
    p->right = v;
    v->right = u;
    u->left = t3;
    // segunda rotacao (S.E.)

    v->left = p;
    p->right = t2;

    switch (v->fb)
    {
        case -1:
            u->fb = 1;
            p->fb = 0;
            v->fb = 0;
            break;
        case 0:
            u->fb = 0;
            p->fb = 0;
            v->fb = 0;
            break;
        case 1:
            u->fb = 0;
            p->fb = -1;
            v->fb = 0;
            break;
    }
    return v;
}

Node_avl case1(Node_avl p)
{
    // valor novo foi inserida à esquerda de p e causou fb = -2. Será rotacao para a direita
    Node_avl u;
    u = p->left;
    if (u->fb == -1)
    { // caso para sinais iguais negativos: rotacao simples a direita.
        printf("Rotacao simples direita em %d\n", p->data->age_student);
        p = rotateRight(p);
    }
    else
    {
        printf("Rotacao dupla direita em %d\n", p->data->age_student);
        p = doubleRotateRight(p);
    }
    p->fb = 0;
    return p;
}

Node_avl case2(Node_avl p)
{
    // Chave foi inserida à direita de p e causou fb = +2. Efetuará rotacoes para a esquerda.
    Node_avl u;
    u = p->right;
    // printPreorder(p);
    // printf("\n");
    if (u->fb == 1)
    { // caso para sinais iguais positivos: rotacao simples a esquerda
        printf("Rotacao simples esquerda em %d [%d]\n", p->data->age_student, p->fb);
        p = rotateLeft(p);
    }
    else
    {
        printf("Rotacao dupla esquerda em %d\n", p->data->age_student);
        p = doubleRotateLeft(p);
    }
    // printPreorder(p);
    // printf("\n");
    return p;
}

Node_avl rotate(Node_avl root)
{
    if (root->fb > 0)
    { // caso p(+2)
        return case2(root);
    }
    else
    { // caso p(-2)
        return case1(root);
    }
}

Node_avl insertionNodeAVL(Node_avl root, Data_type data, int *increased){
    if (root == NULL){
        Node_avl aux = (Node_avl) malloc(sizeof(struct node_avl));
        aux->data = data;
        aux->left = NULL;
        aux->right = NULL;
        aux->fb = 0;
        *increased = 1;
        // printf("Inseriu %d\n",aux->value);
        return aux;
    }
    else{
        if (data->age_student >= root->data->age_student){
            root->right = insertionNodeAVL(root->right, data, increased);
            if (*increased){ // verificar balanceamento
                switch (root->fb){
                    case -1:
                        *increased = 0;
                        root->fb = 0; //+1, nao cresceu
                        break;

                    case 0:
                        root->fb = 1; // inseriu à direita, fb + 1
                        *increased = 1;
                        break;

                    case 1:             // caso: o fb(root) = +2, entao precisa reajustar pois aumentou em + 1
                        *increased = 0; // nao cresceu, pois efetuará a correção
                        return rotate(root);
                }
            }
        }
        else{ // inserir valor a esquerda
            root->left = insertionNodeAVL(root->left, data, increased);
            if (*increased){
                switch (root->fb){
                    case 1:
                        root->fb = 0;
                        *increased = 0;
                        break;

                    case 0:
                        root->fb = -1;
                        *increased = 1;
                        break;

                    case -1:
                        *increased = 0;      // após a troca, ela fica balanceada
                        return rotate(root); // caso fb(root) = -2, entao precisa reajustar pois diminuiu -1
                }
            }
        }
        return root;
    }
}

Node_avl removeNodeAVL(Node_avl root, int ageStudentTarget, int *decreased){
    if (root == NULL)
        return NULL;

    if (root->data->age_student == ageStudentTarget){
        *decreased = 1;
        if (root->left == NULL && root->right == NULL)
        { // sem nós filhos
            free(root);
            return NULL;
        }
        else if (root->left != NULL && root->right == NULL)
        { // com filho esquerdo
            Node_avl aux_left = root->left;
            free(root);
            return aux_left;
        }
        else if (root->left == NULL && root->right != NULL)
        { // com filho direito
            Node_avl aux_right = root->right;
            free(root);
            return aux_right;
        }
        else if (root->left != NULL && root->right != NULL)
        { // com os dois filhos
            Node_avl aux = treeMaxAVL(root->left);
            root->data->age_student = aux->data->age_student;
            root->left = removeNodeAVL(root->left, aux->data->age_student, decreased);

            if (*decreased){
                switch (root->fb){// removendo da esquerda, entao soma o fb em 1
                    case -1:
                        *decreased = true;
                        root->fb = 0;
                        break;

                    case 0:
                        *decreased = false;
                        root->fb = 1;
                        break;

                    case 1: // fb(+2)
                        *decreased = true;
                        return rotate(root);
                }
            }
            return root;
        }
    }
    else{ // se nao encontrar o valor desejado para remoção
        if (ageStudentTarget >= root->data->age_student){
            root->right = removeNodeAVL(root->right, ageStudentTarget, decreased);
            if (*decreased){
                switch (root->fb) // removendo da direita, entao subtrai o fb em 1
                {
                    case -1: // fb(-2)
                        *decreased = true;
                        root->fb = 0;
                        return rotate(root);

                    case 0:
                        *decreased = false;
                        root->fb = -1;
                        break;

                    case 1:
                        *decreased = true;
                        root->fb = 0;
                        break;
                }
            }
        }
        else{
            root->left = removeNodeAVL(root->left, ageStudentTarget, decreased);
            if (*decreased){
                switch (root->fb) // removendo da esquerda, entao soma o fb em 1
                {
                    case -1:
                        *decreased = true;
                        root->fb = 0;
                        break;

                    case 0:
                        *decreased = false;
                        root->fb = 1;
                        break;

                    case 1: // fb(+2)
                        *decreased = true;
                        return rotate(root);
                }
            }
        }
        return root;
    }
}
