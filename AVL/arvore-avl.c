#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int valor;
    struct node *esquerdo, *direito;
    int fb;
}Node;

Node *treeInitialize()
{
    return NULL;
}

Node *newNode(int val)
{
    Node *novo = malloc(sizeof(Node));

    if (novo)
    {
        novo->valor = val;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->fb = 0;
    }
    else
        printf("\nERRO ao alocar nó em novoNo!\n");
    return novo;
}

Node *rotacao_direita(Node *p){
    //rotacao de p para a direita, retornando ponteiro para a nova raiz da subárvore trocada.
    Node *u;
    u = p->esquerdo; //sub-árvore a esquerda de p.
/*
          p                            u     
        /   \                         /  \
       u     t3        ==>          t1    p 
     /   \                               / \ 
    t1   t2                            t2   t3
    
*/

    p->esquerdo = u->direito; //p pega o filho direito de u (maior elemento da subarvore a esquerda)
    u->direito = p; //p se torna filho direito de u

    p->fb = 0;
    p = u;
    return p;
}

Node *rotacao_esquerda(Node *p){
    Node *u;
    u = p->direito;
/*
          p                           u     
        /   \                       /   \
       t1    u        ==>          p    t3 
           /   \                  /  \ 
          t2   t3               t1   t2
    
*/
    p->direito = u->esquerdo; //p pega o filho esquerdo de u (menor elemento da sub-árvore a esquerda)
    u->esquerdo = p;
    return p;
}

Node *rotacao_dupla_direita(Node *p){

    Node *u,*v;
    u = p->esquerdo;
    v = u->direito;

    u->direito = v->esquerdo;
    v->esquerdo = u;

    p->esquerdo = v->direito;
    v->direito = p;
    //ajeitar balanceamento




    return p;
}

Node *caso1 (Node *p)
{
    // Chave foi inserida à esquerda de p e causou fb = -2. Será rotacao para a direita
    Node *u;
    u = p->esquerdo;
    if(u->fb == -1){ //caso para sinais iguais negativos: rotacao simples a direita.
        printf("\nFazendo rotação para à direita em %d", p->valor);
        p = rotacao_direita(p);
    }else{
        printf("\nFazendo rotação para à direita em %d", p->valor);
        p = rotacao_dupla_direita(p);
    }
    p->fb = 0;
    return p;
}

Node *caso2 (Node *p)
{
    // Chave foi inserida à direita de p e causou fb = 2. Será rotacoes para a esquerda.
    Node *u;
    u = p->direito;
    if(u->fb == 1){
        p = rotacao_esquerda(p);
    }else{
        printf("\nRotação para à esquerda em %d", p->valor);
        //p = rotacao_dupla_esquerda(p);
    }
    return p;
}

Node *insertionNode(Node *raiz, int v, int *cresceu){
    if (raiz == NULL)
    {
        Node *aux = (Node *)malloc(sizeof(Node));
        aux->valor= v;
        aux->esquerdo = NULL;
        aux->direito = NULL;
        aux->fb = 0;
        *cresceu = 1;
        printf("\nInseriu %d\n",aux->valor);
        return aux;
    } else if(v > raiz->valor){
        raiz->direito = insertionNode(raiz->direito, v, cresceu);
        if(*cresceu){ //verificar balanceamento
            switch (raiz->fb)
            {
            case -1:
                raiz->fb = 0; //nao cresceu
                *cresceu = 0;
                break;
            case 0:
                raiz->fb = 1; //inseriu à direita, entao o fb aumenta em 1
                break;
            case 1: //caso o fb(raiz) = +2, entao precisa reajustar pois aumentou em +1
                raiz = caso2(raiz);
                *cresceu = 0; //nao cresceu
                break;
            }
        }
    }else if(v < raiz->valor){
        raiz->esquerdo = insertionNode(raiz->esquerdo, v, cresceu);
        if(*cresceu){
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
                raiz = caso1(raiz); //caso fb(raiz) = -2, entao precisa reajustar pois diminuiu -1
                *cresceu = 0; //após a troca, ela fica balanceada
                break;
            
            default:
                break;
            }
        }
    }

    return raiz;
}

void printPreorder(Node *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->valor);
        printPreorder(raiz->esquerdo);
        printPreorder(raiz->direito);
    }
}

void printInorder(Node *raiz)
{
        if (raiz != NULL)
    {
        printPreorder(raiz->esquerdo);
        printf("%d ", raiz->valor);
        printPreorder(raiz->direito);
    }
}

void printPostorder(Node *raiz)
{
    if (raiz == NULL)
        return;
    printInorder(raiz->esquerdo);
    printInorder(raiz->direito);
    printf("%d ", raiz->valor);
}

int maior(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else if (b > a)
    {
        return b;
    }
    else
    {
        printf("Error.\n");
        return;
    }
}

int alturaTotal(Node *raiz){
    if(raiz == 0){
        return -1; //deve ser -1, pois se houvesse a raiz NULL, ao chegar na chamada recursiva se somaria 1, e daria errado.
    }else{
        int esq = alturaTotal(raiz->esquerdo);
        int dir = alturaTotal(raiz->direito);
        if(esq > dir)
            return esq + 1;
        else
            return dir +1;
    }
}

int fb_do_No(Node *no){
    if(no == NULL)
        return -1;
    else
        return no->fb;
}

int fator_de_Balanceamento(Node *no){
    if(no!= NULL)
        return (fb_do_No(no->esquerdo) - fb_do_No(no->direito));
    else
        return 0;
}

Node* rotacaoSimplesEsquerda(Node *raiz_r){
    Node *d, *e;

    d = raiz_r->direito; // d aponta para a subárvore direita da raiz_r
    e = d->esquerdo; // e aponta para o filho esquerdo de d


    d->esquerdo = raiz_r; // o filho esquerdo de d passa a ser a raiz_r
    raiz_r->direito = e; // o filho direito de r passa a ser e

    // recalcula a altura dos nós que foram movimentados
    raiz_r->fb = maior(fb_do_No(raiz_r->esquerdo), fb_do_No(raiz_r->direito)) + 1;
    d->fb = maior(fb_do_No(d->esquerdo), fb_do_No(d->direito)) + 1;

    return d;
}

Node *treeMin(Node *root)
{//esta deve ser usada no node a direita para que se encontre o menor valor da arvore a direita, para efetuar a remocao posteriormente
    if (root != NULL)
    {
        Node *aux = root;
        while (aux->esquerdo != NULL)
        {
            aux = aux->esquerdo;
        }
        return aux;
    }
    return NULL;
}

int main()
{
    Node *no_teste;
    no_teste = NULL;
    int cresceu;
    no_teste = insertionNode(no_teste,10, &cresceu);
    
    insertionNode(no_teste,15,&cresceu);
    insertionNode(no_teste,30,&cresceu);
    insertionNode(no_teste,0,&cresceu);
    insertionNode(no_teste,50,&cresceu);

    printPreorder(no_teste);

    return 0;
}