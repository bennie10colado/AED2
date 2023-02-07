#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int valor;
    struct node *esquerdo, *direito;
    int fb;
} Node;

Node *treeInitialize()
{
    return NULL;
}

Node *rotacao_direita(Node *p)
{
    // rotacao de p para a direita, retornando ponteiro para a nova raiz da subárvore trocada.
    Node *u;
    u = p->esquerdo; // sub-árvore a esquerda de p.
    /*
              p                            u
            /   \                         /  \
           u     t3        ==>          t1    p
         /   \                               / \
        t1   t2                            t2   t3

    */

    p->esquerdo = u->direito; // p pega o filho direito de u (maior elemento da subarvore a esquerda)
    u->direito = p;           // p se torna filho direito de u

    p->fb = 0;
    p = u;
    return p;
}

Node *rotacao_esquerda(Node *p)
{
    Node *u;
    u = p->direito;
    /*
              p                           u
            /   \                       /   \
           t1    u        ==>          p    t3
               /   \                  /  \
              t2   t3               t1   t2

    */
    p->direito = u->esquerdo; // p pega o filho esquerdo de u (menor elemento da sub-árvore a esquerda)
    u->esquerdo = p;
    return p;
}

Node *rotacao_dupla_direita(Node *p)
{

    Node *u, *v;
    u = p->esquerdo;
    v = u->direito;

    p->esquerdo = u->direito;
    u->direito = v->esquerdo;
    v->esquerdo = u;

    return p;
}

Node *caso1(Node *p)
{
    // Valor foi inserida à esquerda de p e causou fb = -2. Será rotacao para a direita
    Node *u;
    u = p->esquerdo;
    if (u->fb == -1)
    { // caso para sinais iguais negativos: rotacao simples a direita.
        printf("\nFazendo rotacao para a direita em %d", p->valor);
        p = rotacao_direita(p);
    }
    else
    {
        printf("\nFazendo rotacao para a direita em %d", p->valor);
        p = rotacao_dupla_direita(p);
    }
    p->fb = 0;
    return p;
}

Node *caso2(Node *p)
{
    // Valor foi inserida à direita de p e causou fb = 2. Será rotacao para a esquerda.
    Node *u;
    u = p->direito;
    if (u->fb == 1)
    {
        printf("\nRotacao para a esquerda em %d", p->valor);
        p = rotacao_esquerda(p);
    }
    else
    {
        printf("\nRotacao dupla para a esquerda em %d", p->valor);
        // p = rotacao_dupla_esquerda(p);
    }
    return p;
}

Node *insertionNode(Node *raiz, int v, int *cresceu)
{
    if (raiz == NULL)
    {
        Node *aux = (Node *)malloc(sizeof(Node));
        aux->valor = v;
        aux->esquerdo = NULL;
        aux->direito = NULL;
        aux->fb = 0;
        *cresceu = 1;
        printf("\nInseriu %d\n", aux->valor);
        return aux;
    }
    else if (v > raiz->valor)
    {
        raiz->direito = insertionNode(raiz->direito, v, cresceu);
        if (*cresceu)
        { // verificar balanceamento
            switch (raiz->fb)
            {
            case -1:
                raiz->fb = 0; // nao cresceu
                *cresceu = 0;
                break;
            case 0:
                raiz->fb = 1; // inseriu à direita, entao o fb aumenta em 1
                break;
            case 1: // caso o fb(raiz) = +2, entao precisa reajustar pois aumentou em +1
                raiz = caso2(raiz);
                *cresceu = 0; // nao cresceu
                break;
            }
        }
    }
    else if (v < raiz->valor)
    {
        raiz->esquerdo = insertionNode(raiz->esquerdo, v, cresceu);
        if (*cresceu)
        {
            switch (raiz->fb)
            {
            case 1:
                raiz->fb = 0;
                *cresceu = 0;
                break;
            case 0:
                raiz->fb = -1;
                *cresceu = 1;
                break;
            case -1:
                raiz = caso1(raiz); // caso fb(raiz) = -2, entao precisa reajustar pois diminuiu -1
                *cresceu = 0;       // após a troca, ela fica balanceada
                break;

            default:
                break;
            }
        }
    }

    return raiz;
}
/*
Node removeNode(Node *raiz, int val, int *diminuiu){
    return raiz;
}*/

void printPreorder(Node *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->valor);
        printPreorder(raiz->esquerdo);
        printPreorder(raiz->direito);
    }
}

int main()
{
    Node *no_teste;
    no_teste = treeInitialize();
    int cresceu;
    no_teste = insertionNode(no_teste, 10, &cresceu);
    
    insertionNode(no_teste,15,&cresceu);
    insertionNode(no_teste,30,&cresceu);
    insertionNode(no_teste,0,&cresceu);
    insertionNode(no_teste,50,&cresceu);

    printPreorder(no_teste);

    return 0;
}