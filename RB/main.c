#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int main() {
    index_rb data;
    data.enrollmentCode_student = 0;
    data.index = 0;
    node_rb *node_Test;
    initializeNodeRBRoot(&node_Test, &data);

    index_rb codigo0, codigo1, codigo2, codigo3, codigo4, codigo5; //por algum motivo está havendo alguma troca que está mudando os valores nos codigos em si
    codigo0.enrollmentCode_student = 10;
    codigo1.enrollmentCode_student = 20;
    codigo2.enrollmentCode_student = 30;
    codigo3.enrollmentCode_student = 40;
    codigo4.enrollmentCode_student = 50;
    codigo5.enrollmentCode_student = 60;

    insertionNode(&node_Test, &codigo0);
    preorderPrintRB(node_Test);
    printf("\n");
    insertionNode(&node_Test, &codigo1);
    preorderPrintRB(node_Test);
    printf("\n");
    insertionNode(&node_Test, &codigo2);
    preorderPrintRB(node_Test);
    printf("\n");
    insertionNode(&node_Test, &codigo3);
    preorderPrintRB(node_Test);
    printf("\n");
    insertionNode(&node_Test, &codigo4);
    preorderPrintRB(node_Test);
    printf("\n");
    insertionNode(&node_Test, &codigo5);
    preorderPrintRB(node_Test);
    printf("\n");


    deletionNode(&node_Test, &codigo0);//
    preorderPrintRB(node_Test);
    printf("\n");
    deletionNode(&node_Test, &codigo1);//
    preorderPrintRB(node_Test);
    printf("\n");
    deletionNode(&node_Test, &codigo2);//
    preorderPrintRB(node_Test);
    printf("\n");
    deletionNode(&node_Test, &codigo3);//
    preorderPrintRB(node_Test);
    printf("\n");
    deletionNode(&node_Test, &codigo4);//
    preorderPrintRB(node_Test);
    printf("\n");
    deletionNode(&node_Test, &codigo5);//
    preorderPrintRB(node_Test);
    printf("\n");


    printf("removeu tudo!\n");

    //freeTree(node_Test);
    return 0;
}