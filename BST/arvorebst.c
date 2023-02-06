#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *left, *right;
};

typedef struct node Node; //nao eh necessario escrever duas vezes

Node *treeInitialize()
{
    return NULL;
}

Node* insertNode(Node *root, int v){
    if(root == NULL){
        Node* aux = (Node*)malloc(sizeof(Node)); //sizeof(struct)
        aux->value = v;
        aux->left = NULL;
        aux->right = NULL;
        return aux;
    } else {
        if (root->value < v) //se v for maior do que o value da raiz anterior, entao ele irá para a direita
        {
            root->right = insertNode(root->right,v);
        }
        else{
            root->left = insertNode(root->left,v);
        }
        return root;
    }
    
}

void preorderPrint(Node* root){
    if(root != NULL){
        printf("%d ", root->value);
        preorderPrint(root->left);
        preorderPrint(root->right);
    }
}

void inorderPrint(Node* root){
    if(root != NULL){
        inorderPrint(root->left);
        printf("%d ", root->value);
        inorderPrint(root->right);
    }
}

void postorderPrint(Node* root){
    if(root != NULL){
        postorderPrint(root->left);
        postorderPrint(root->right);
        printf("%d ", root->value);
    }
}

void treeFree(Node *root){
    if(root != NULL){
        treeFree(root->left);
        treeFree(root->right);
        free(root);
    }
}

Node *treeSearch(Node *root, int value)
{
    if (root != NULL)
    {
        if (root->value == value)
            return root;
        else
        {
            if (value > root->value)
                return treeSearch(root->right, value);
            else
                return treeSearch(root->left, value);
        }
    }
    return NULL;
}

Node *printTreeSearch(Node *root, int value)
{
    treeSearch(root, value);
    if (root == NULL)
        printf("Elemento %d não encontrado. \n", value);
    else
        printf("Elemento encontrado: %d \n", value);
}

Node *treeMin(Node *root)
{//esta deve ser usada no node a direita para que se encontre o menor valor da arvore a direita, para efetuar a remocao posteriormente
    if (root != NULL)
    {
        Node *aux = root;
        while (aux->left != NULL)
        {
            aux = aux->left;
        }
        return aux;
    }
    return NULL;
}

Node *treeMax(Node *root)
{//esta deve ser usada no node a esquerda para que se encontre o maior valor da arvore a esquerda, para efetuar a remocao posteriormente
    if (root != NULL)
    {
        Node *aux = root;
        while (aux->right != NULL)
        {
            aux = aux->right;
        }
        return aux;
    }
    return NULL;
}

Node *treeRemove(Node *root, int value)
{
    if (root != NULL)
    {
        // casos para nenhum filho.
        if (value > root->value)
        {
            root->right = treeRemove(root->right, value);
        }
        else if (value < root->value)
        {
            root->left = treeRemove(root->left, value);
        }
        else
        {
            if (root->left == NULL && root->right == NULL)
            {
                free(root);
                return NULL;
            }//caso para somente filho direito
            else if (root->left == NULL && root->right != NULL)
            {
                // salvo a referencia dos proximos nós do nó removido no *aux, para nao perder a cadeia, e então remove o desejado e continua normalmente.
                Node *aux = root->right;
                free(root);
                return aux;
            }//caso para somente filho esquerdo
            else if (root->left != NULL && root->right == NULL)
            {
                Node *aux = root->left;
                free(root);
                return aux;
            }//caso para dois filhos
            else
            {
                // pegando o maior valor da sub-árvore de menores elementos(da esquerda)
                // ou pegando o menor elemento da sub-árvore de maiores elementos(da direita)
                Node *aux_minimo_da_dir = treeMin(root->right);
                int val_aux = aux_minimo_da_dir->value;
                root = treeRemove(root, val_aux); // removi o menor elemento da arvore da direita, e vou retornar o proprio root, depois colocar o menor elemento da direita no lugar da raíz
                root->value = val_aux;
            }
        }
        return root;
    }
    else
        return NULL;
}

int main(){
/* BST
            10
          /	   \
         5	    15
        / \     / \
           7       20 
            \
             9
*/
    Node *root = NULL;

    root = insertNode(root, 10);
    insertNode(root, 15);
    insertNode(root, 20);
    insertNode(root, 5);
    insertNode(root, 7);
    insertNode(root, 9);

    preorderPrint(root);
    //treeRemove(root, 9);
    treeRemove(root, 15);
    //treeRemove(root, 10);
    printf("\n");
    preorderPrint(root);

    treeFree(root);
    return 0;
}