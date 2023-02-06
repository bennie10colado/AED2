#include <stdio.h>
#include <stdlib.h>

struct item
{
    int value;
};

typedef struct item Item;

struct node
{
    Item item;
    struct node *left;
    struct node *right;
};

typedef struct node Node;

Node *treeInitialize()
{
    return NULL;
}

Item itemCreate(int value)
{
    Item item;
    item.value = value;
    return item;
}

Node *TreeInsert(Node *root, Item v)
{
    if (root == NULL)
    {
        Node *aux = (Node *)malloc(sizeof(Node));
        aux->item = v;
        aux->left = NULL;
        aux->right = NULL;

        return aux;
    }
    else
    {
        if (v.value > root->item.value)
        {
            root->right = TreeInsert(root->right, v);
        }
        else if (v.value < root->item.value)
        {
            root->left = TreeInsert(root->left, v);
        }
        return root;
    }
}

void printPreorder(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->item.value);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

void printInorder(struct node *root)
{
    if (root == NULL)
        return;

    printInorder(root->left);
    printf("%d ", root->item.value);
    printInorder(root->right);
}

void printPostorder(struct node *root)
{
    if (root == NULL)
        return;

    printInorder(root->left);
    printInorder(root->right);
    printf("%d ", root->item.value);
}

void treeFree(Node *root)
{
    if (root != NULL)
    {

        treeFree(root->left);
        treeFree(root->right);
        free(root);
    }
}

Node *treeSearch(Node *root, int value)
{
    if (root != NULL)
    {
        if (root->item.value == value)
            return root;
        else
        {
            if (value > root->item.value)
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
{
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

Node *treeRemove(Node *root, int value)
{
    if (root != NULL)
    {
        // casos para nenhum filho.
        if (value > root->item.value)
        {
            root->right = treeRemove(root->right, value);
        }
        else if (value < root->item.value)
        {
            root->left = treeRemove(root->left, value);
        }
        else
        {
            if (root->left == NULL && root->right == NULL)
            {
                free(root);
                return NULL;
            }
            else if (root->left == NULL && root->right != NULL)
            {
                // salvo a referencia dos proximos nós do nó removido no *aux, para nao perder a cadeia, e então remove o desejado e continua normalmente.
                Node *aux = root->right;
                free(root);
                return aux;
            }
            else if (root->left != NULL && root->right == NULL)
            {
                Node *aux = root->left;
                free(root);
                return aux;
            } 
            else
            {
                // pegando o maior valor da sub-árvore de menores elementos(da esquerda)
                // ou pegando o menor elemento da sub-árvore de maiores elementos(da direita)
                Node *aux_minimo_da_dir = treeMin(root->right);
                Item itemAux = aux_minimo_da_dir->item;
                root = treeRemove(root, itemAux.value); // removi o menor elemento da arvore da direita, e vou retornar o proprio root, depois colocar o menor elemento da direita no lugar da raíz
                root->item = itemAux;
            }
        }
        return root;
    }
    else
        return NULL;
}

int main()
{
    Node *root = treeInitialize();
    root = TreeInsert(root, itemCreate(10));
    root = TreeInsert(root, itemCreate(15));
    root = TreeInsert(root, itemCreate(20));
    // root = TreeInsert(root, itemCreate(30));
    root = TreeInsert(root, itemCreate(5));
    root = TreeInsert(root, itemCreate(12));

    printf("Preorder antes da remocao: \n");
    printPreorder(root);
    printf("\n");
    // Node *temp = printTreeSearch(root, 12);
    treeRemove(root, 10);
    printf("Preorder depois da remocao: \n");
    printPreorder(root);

    treeFree(root);

    return 0;
}