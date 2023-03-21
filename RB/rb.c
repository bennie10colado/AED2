#include <stdio.h>
#include <stdlib.h>
#include "rb.h"
node_rb *null_node;

//PRINTS DE ORDENAÇÃO
void printTree(node_rb *node, int level) {
    if (node == NULL) {
        return;
    }
    printTree(node->right, level+1);
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%d(%c)\n", node->data->enrollmentCode_student, node->color == RED ? 'R' : 'B');
    printTree(node->left, level+1);
}

void elementPrintRB(node_rb *root) {
    printf("[%d] ", root->data->enrollmentCode_student); //&r?
}

void preorderPrintRB(node_rb *root){
    if(root != NULL){
        elementPrintRB(root);
        preorderPrintRB(root->left);
        preorderPrintRB(root->right);
    }
}

void inorderPrintRB(node_rb *root){
    if(root != NULL) {
        inorderPrintRB(root->left);
        elementPrintRB(root);
        inorderPrintRB(root->right);
    }
}

void printPreorderElementRB(node_rb *root){
    if (root != NULL){
        printf("%d ", root->data->enrollmentCode_student);
        printPreorderElementRB(root->left);
        printPreorderElementRB(root->right);
    }
}

void printInorderElementRB(node_rb *root){
    if (root != NULL){
        printInorderElementRB(root->left);
        printf("%d ", root->data->enrollmentCode_student);
        printInorderElementRB(root->right);
    }
}

node_rb *search(node_rb *root, int target){
    if (root == NULL || target == root->data->enrollmentCode_student)
        return root;
    if (target < root->data->enrollmentCode_student)
        return search(root->left, target);
    else
        return search(root->right, target);
}

void freeTree(node_rb *node){
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

enum color colorNode(node_rb *root){
    enum color c;
    if(root == NULL)
        c = BLACK;
    else
        c = root->color;

    return c;
}

int higher(int v1, int v2){
    if (v1 > v2)
        return v1;
    else
        return v2;
}

int height(node_rb *root){
    if (root == NULL)
    {
        return 0;
    }
    return 1 + higher(height(root->right), height(root->left));
}

int treeMaxValue(node_rb *root)
{
    if (root == NULL)
        return 0;
    if (root->right == NULL)
        return root->data->enrollmentCode_student;
    else
        return treeMaxValue(root->right);
}

//RELACOES DE PARENTES SE SAO VERDADEIRAS
int is_root(node_rb *node){
    return (node->father == NULL);
}

int isLeftSon(node_rb *root){
    return(root->father != NULL && root == root->father->left);
}

int isRightSon(node_rb *root){
    return(root->father != NULL && root == root->father->right);
}

//PARENTES
node_rb *brother(node_rb *node){
    if(node != NULL){
        if(isLeftSon(node))
            return node->father->right;
        else
            return node->father->left;
    } else{
        return NULL;
    }
}

node_rb *grandFather(node_rb *node){
    if(node != NULL) {
        return node->father->father;
    }else
        return NULL;
}

node_rb *uncle(node_rb *node){
    if(node != NULL){
        return brother(node->father);
    }else
        return NULL;
}

//FUNCOES ROTACOES
void rotateLeft(node_rb **root, node_rb *p){
    node_rb *u, *t2;
    //inicializacao
    u = p->right;
    t2 = u->left;
    int positionPivot = isRightSon(p);
    //troca
    p->right = t2;
    u->left = p; //p se torna filho esquerdo de u

    //atualizar os pais
    if(t2 != NULL){
        t2->father = p; //p se torna pai de t2 se este for diferente de nulo
    }
    u->father = p->father; //pai de u recebe o pai de p, pois trocarão de posições
    p->father = u; //u se torna pai de p

    if(is_root(u)){ //double black nao eh raiz pois 15 eh seu pai
        *root = u;//
    } else {
        if(positionPivot){
            u->father->right = u;
        }else{
            u->father->left = u;
        }
    }
    //printf("rotacao para a esquerda efetuada!\n");
}

/*
          p                            u
        /   \                         /  \
       u    t3        ==>          t1     p
     /   \                               / \
    t1   t2                            t2   t3
*/
void rotateRight(node_rb **root, node_rb *p) {
    node_rb *u, *t2;

    u = p->left;
    t2 = u->right;
    int positionPivot = isLeftSon(p);

    p->left = t2; //filho esquerdo de p recebe o filho direito de u

    if (t2 != NULL) {
        t2->father = p;
    }

    u->right = p;
    u->father = p->father; // pai de u recebe o pai de p, conservar arvores
    p->father = u;

    if (is_root(u)) {
        *root = u;
    } else {
        if (positionPivot) {
            u->father->left = u;
        }
        else{
            u->father->right = u;
        }
    }
    //printf("rotacao para a direita efetuada!\n");
}

void doubleRotateLeft(node_rb **root, node_rb *p){
    rotateRight(root, p->right);
    rotateLeft(root, p);
    //printf("rotacao dupla para a esquerda efetuada!\n");
}

void doubleRotateRight(node_rb **root, node_rb *p){
    rotateLeft(root, p->left);
    rotateRight(root, p);
    //printf("rotacao dupla para a direita efetuada!\n");
}

//FUNCOES NOS
void initializeNodeRBNull(node_rb **root){
    *root = NULL;
}

void initializeNodeRBRoot(node_rb **root, Data_type data){
    *root = NULL;

    null_node = (node_rb *)malloc(sizeof(node_rb));
    null_node->data = data;
    null_node->left = NULL;
    null_node->right = NULL;
    null_node->color = DOUBLE_BLACK;
}

node_rb *initializeNode(Data_type data){
    node_rb *aux = (node_rb*)malloc(sizeof(node_rb));
    aux->data = data;
    aux->father = NULL;
    aux->left = NULL;
    aux->right = NULL;
    aux->color = RED;

    return aux;
}

void fixInsertionNode(node_rb **root, node_rb *new_node) {
    while (colorNode(new_node) == RED && colorNode(new_node->father) == RED){
        //caso 1: recolorizacao
        if(colorNode(uncle(new_node)) == RED){
            uncle(new_node)->color = BLACK;
            new_node->father->color = BLACK;
            grandFather(new_node)->color = RED;
            new_node = grandFather(new_node);
            continue;
        }
        //caso 2.a
        if(isLeftSon(new_node) && isLeftSon(new_node->father)){
            rotateRight(root, grandFather(new_node)); // o avo eh o pivo
            new_node->father->color = BLACK;
            brother(new_node)->color = RED;
            continue;
        }
        //caso 2.b
        if(isRightSon(new_node) && isRightSon(new_node->father)){
            rotateLeft(root, grandFather(new_node));
            new_node->father->color = BLACK;
            brother(new_node)->color = RED;
            continue;
        }
        //caso 3.a
        if(isRightSon(new_node) && isLeftSon(new_node->father)){
            doubleRotateRight(root, grandFather(new_node));
            new_node->right->color = RED;
            new_node->left->color = RED;
            new_node->color = BLACK;
            continue;
        }
        //caso 3.b
        if(isLeftSon(new_node) && isRightSon(new_node->father)){
            doubleRotateLeft(root, grandFather(new_node));
            new_node->right->color = RED;
            new_node->left->color = RED;
            new_node->color = BLACK;
            continue;
        }
    }
    (*root)->color = BLACK;
}

/*
void fixInsertionNode2(Node **root, Node *new_node) { //codigo com erro, finalizar depois
    //printf("\na cor eh %d \n",new_node->color);
    while (colorNode(new_node) == RED && colorNode(new_node->father) == RED) { //se o pai é vermelho, temos uma violação

        if (isLeftSon(new_node->father)) { //se o pai for um filho esquerdo
            Node *aux = new_node->father->father->right; //tio: irmao direito do pai

            if (aux != NULL && aux->color == RED) { //correção caso 1: tio vermelho, filho vermelho e pai vermelho
                new_node->father->color = BLACK;
                aux->color = BLACK; //cor do tio
                new_node->father->father->color = RED;
                new_node = new_node->father->father; //recursivamente recebe o avo para analisar se existem mais violações ao decorrer da arvore
            } else{
                if(isRightSon(new_node)){ //se pai esquerdo e filho direito
                    new_node = new_node->father;
                    rotateLeft(root, new_node);
                }
                new_node->father->color = BLACK;
                new_node->father->father->color = RED;
                rotateRight(root, new_node->father->father);
            }
        } else{ //se o pai for um filho direito
            Node *aux = new_node->father->father->left; //tio: irmao esquerdo do pai

            if(aux != NULL && aux->color == RED){ //se o tio for vermelho,
                new_node->father->color = BLACK;
                aux->color = BLACK;
                new_node->father->father->color = RED;
                new_node = new_node->father->father;
            } else {
                if(isLeftSon(new_node)){// pai eh filho direito, no é filho esquerdo, seria 2 rotacoes
                    new_node = new_node->father;
                    rotateRight(root, new_node);
                }
                rotateLeft(root, new_node->father->father);
                new_node->father->color = BLACK;
                new_node->father->left->color = RED;
            }
        }
    }
    (*root)->color = BLACK;
}*/

void insertionNode(node_rb **root, Data_type data) {
    node_rb *temp, *parent, *root_aux;
    parent = NULL;
    root_aux = *root;

    while (root_aux != NULL) {
        parent = root_aux;
        if (data->enrollmentCode_student >= root_aux->data->enrollmentCode_student)
            root_aux = root_aux->right;
        else
            root_aux = root_aux->left;
    }

    temp = initializeNode(data);
    temp->father = parent;

    if (is_root(temp)) { //se o pai da raiz temp for NULL, se torna a nova raiz
        *root = temp;
    } else {
        if (data->enrollmentCode_student >= parent->data->enrollmentCode_student)
            parent->right = temp;
        else
            parent->left = temp;
    }
    fixInsertionNode(root, temp);
    //pode dar um free em temp, rootaux, e parent
}

void removeDoubleBlack(node_rb **root, node_rb *doubleBlackNode){
    if (doubleBlackNode == null_node) {
        if (isLeftSon(doubleBlackNode)) {
            doubleBlackNode->father->left = NULL;
        } else {
            doubleBlackNode->father->right = NULL;
        }
    } else {
        doubleBlackNode->color = BLACK;
    }
}

void fixDeletionNode(node_rb **root, node_rb* doubleBlackNode) {

    if (is_root(doubleBlackNode)) { //caso 1: retira DB por B
        removeDoubleBlack(root, doubleBlackNode);
        return;
    } else if (colorNode(doubleBlackNode->father) == BLACK
               && colorNode(brother(doubleBlackNode)) == RED
               && colorNode(brother(doubleBlackNode)->left) == BLACK
               && colorNode(brother(doubleBlackNode)->right) == BLACK) { //caso 2: rotacoes simples e recolorir

        brother(doubleBlackNode)->color = BLACK;
        doubleBlackNode->father->color = RED;
        if (isLeftSon(doubleBlackNode)) {
            rotateLeft(root, doubleBlackNode->father);
        } else {
            rotateRight(root, doubleBlackNode->father);
        }
        //grandFather(doubleBlackNode)->color = BLACK;
        //doubleBlackNode->father->color = RED;

        fixDeletionNode(root, doubleBlackNode);
        return;
    } else if (colorNode(doubleBlackNode->father) == BLACK
               && colorNode(brother(doubleBlackNode)) == BLACK
               && colorNode(brother(doubleBlackNode)->left) == BLACK
               && colorNode(brother(doubleBlackNode)->right) == BLACK) { //caso 3: recolorizacao
        doubleBlackNode->father->color = DOUBLE_BLACK;
        brother(doubleBlackNode)->color = RED;

        removeDoubleBlack(root, doubleBlackNode);
        fixDeletionNode(root, doubleBlackNode->father);
        return;
    } else if (colorNode(doubleBlackNode->father) == RED
               && colorNode(brother(doubleBlackNode)) == BLACK
               && colorNode(brother(doubleBlackNode)->left) == BLACK
               && colorNode(brother(doubleBlackNode)->right) == BLACK) { //caso 4: recolorizacao

        doubleBlackNode->father->color = BLACK;
        brother(doubleBlackNode)->color = RED;
        removeDoubleBlack(root, doubleBlackNode);
        return;
    } else if (isRightSon((brother(doubleBlackNode)))
               && colorNode(brother(doubleBlackNode)) == BLACK
               && colorNode(brother(doubleBlackNode)->left) == BLACK
               && colorNode(brother(doubleBlackNode)->right) == RED) { //caso 5a: rotacao e recolorizacao

        rotateLeft(root, brother(doubleBlackNode)); //pivo da SL eh o s
        brother(doubleBlackNode)->color = BLACK;
        brother(doubleBlackNode)->left->color = RED;

        fixDeletionNode(root, doubleBlackNode);
        return;
    } else if (isLeftSon((brother(doubleBlackNode)))
               && colorNode(brother(doubleBlackNode)) == BLACK
               && colorNode(brother(doubleBlackNode)->left) == RED
               && colorNode(brother(doubleBlackNode)->right) == BLACK) { //caso 5b: rotacao e recolorizacao

        rotateRight(root, brother(doubleBlackNode)); //pivo da SR eh o s
        brother(doubleBlackNode)->color = BLACK;
        brother(doubleBlackNode)->right->color = RED;

        fixDeletionNode(root, doubleBlackNode);
        return;
    } else if (isLeftSon(doubleBlackNode)) {//caso 6a: rotacao e recolorizacao do avo
        if (colorNode(brother(doubleBlackNode)) == BLACK && colorNode(brother(doubleBlackNode)->right) == RED) {

            brother(doubleBlackNode)->color = doubleBlackNode->father->color;
            rotateLeft(root, doubleBlackNode->father); //pivo da SL eh o p(pai do DB nulo)
            doubleBlackNode->father->color = BLACK;
            uncle(doubleBlackNode)->color = BLACK; //y fica preto
            removeDoubleBlack(root, doubleBlackNode);
            return;
        }
    } else if (isRightSon(doubleBlackNode)) {//caso 6b: rotacao e recolorizacao do avo
        if (colorNode(brother(doubleBlackNode)) == BLACK &&
            colorNode(brother(doubleBlackNode)->left) == RED) {//caso 6b: rotacao e recolorizacao

            brother(doubleBlackNode)->color = doubleBlackNode->father->color;
            rotateRight(root, doubleBlackNode->father);
            doubleBlackNode->father->color = BLACK;
            uncle(doubleBlackNode)->color = BLACK; //y fica preto
            removeDoubleBlack(root, doubleBlackNode);
            return;
        }
    }
}

void deletionNode(node_rb **root, Data_type dataTarget) {
    node_rb *remove_node;
    remove_node = *root;

    while (remove_node != NULL) {
        if (dataTarget->enrollmentCode_student == remove_node->data->enrollmentCode_student) {
            //caso o nó tiver 2 filhos
            if (remove_node->right != NULL && remove_node->left != NULL) {
                remove_node->data->enrollmentCode_student = treeMaxValue(remove_node->left);
                //printf("o valor eh remove node eh %d\n\n", remove_node->value);
                deletionNode(&(remove_node->left),dataTarget); //maior valor da arvore esquerda assume a posicao do no a ser removido, após isso inicia a busca a remover o nó "duplicado da raiz esquerda

                break;
            }
                //caso somente filho esquerdo
            else if (remove_node->right == NULL && remove_node->left != NULL) {
                node_rb *leftNode = remove_node->left;
                remove_node->data->enrollmentCode_student = leftNode->data->enrollmentCode_student;
                remove_node->left = NULL;

                free(leftNode);
            }
                //caso somente filho direito
            else if (remove_node->right != NULL && remove_node->left == NULL) {
                node_rb *rightNode = remove_node->right;
                remove_node->data->enrollmentCode_student = rightNode->data->enrollmentCode_student;
                remove_node->right = NULL;

                free(rightNode);
            }
            else if (remove_node->right == NULL && remove_node->left == NULL) {
                //se eh raiz
                if (is_root(remove_node)) {
                    *root = NULL;
                    break;
                }
                //se for vermelho
                if (colorNode(remove_node) == RED) {
                    if (isLeftSon(remove_node))
                        remove_node->father->left = NULL;
                    else
                        remove_node->father->right = NULL;

                    break;

                } else { //se for preto
                    null_node->father = remove_node->father;

                    if (isLeftSon(remove_node)) {
                        remove_node->father->left = null_node; //troca o nó que subiu por DB
                    } else {
                        remove_node->father->right = null_node;

                    }
                    free(remove_node);
                    fixDeletionNode(root, null_node);

                    break;
                }
            }
        } else {
            //percorre a arvore em busca do node a ser removido
            if (dataTarget->enrollmentCode_student >= remove_node->data->enrollmentCode_student){
                remove_node = remove_node->right;
            } else {
                remove_node = remove_node->left;
            }
        }
    }
}
