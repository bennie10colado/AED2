#include "avl.h"
#include <stdio.h>

int main(){

    Node_avl root;
    initializeNodeAVL(&root);
    int increased, decreased;

    index_avl idade, idade1, idade2, idade3, idade4, idade5;
    idade.age_student = 10;
    idade1.age_student = 20;
    idade2.age_student = 25;
    idade3.age_student = 30;
    idade4.age_student = 35;
    idade5.age_student = 40;

    printf("inseriu: %d\n", idade.age_student); //10
    root = insertionNodeAVL(root, &idade, &increased);
    preorderPrintAVL(root);
    printf("\n\n");
    printf("inseriu: %d\n", idade1.age_student); //20
    root = insertionNodeAVL(root, &idade1, &increased);
    preorderPrintAVL(root);
    printf("\n\n");
    printf("inseriu: %d\n", idade2.age_student); //25
    root = insertionNodeAVL(root, &idade2, &increased);
    preorderPrintAVL(root);
    printf("\n\n");
    printf("inseriu: %d\n", idade3.age_student); //30
    root = insertionNodeAVL(root, &idade3, &increased);
    preorderPrintAVL(root);
    printf("\n\n");
    printf("inseriu: %d\n", idade4.age_student); //35
    root = insertionNodeAVL(root, &idade4, &increased);
    preorderPrintAVL(root);
    printf("\n\n");
    printf("inseriu: %d\n", idade5.age_student); //40
    root = insertionNodeAVL(root, &idade5, &increased);
    preorderPrintAVL(root);
    printf("\n\n");
    //printf("inseriu: %d\n", idade6.age_student);
    //root = insertionNodeAVL(root, &idade6, &increased);
    preorderPrintAVL(root);
    printf("\n\n");


    printf("removeu: %d\n", idade1.age_student);
    root = removeNodeAVL(root,idade1.age_student, &decreased);
    preorderPrintAVL(root);
    printf("\n\n");
    printf("removeu: %d\n", idade1.age_student);
    root = removeNodeAVL(root,idade2.age_student, &decreased);
    preorderPrintAVL(root);
    printf("\n\n");
    printf("removeu: %d\n", idade1.age_student);
    root = removeNodeAVL(root,idade3.age_student, &decreased);
    preorderPrintAVL(root);
    printf("\n\n");
    printf("removeu: %d\n", idade1.age_student);
    root = removeNodeAVL(root,idade4.age_student, &decreased);
    preorderPrintAVL(root);
    printf("\n\n");
    printf("removeu: %d\n", idade1.age_student);
    root = removeNodeAVL(root,idade5.age_student, &decreased);
    preorderPrintAVL(root);
    printf("\n\n");
    printf("removeu: %d\n", idade1.age_student);
    root = removeNodeAVL(root,idade.age_student, &decreased);
    preorderPrintAVL(root);
    printf("\n\n");

    printf("tudo removido!\n");


    return 0;
}