#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "data_table.h"

int main() {
    Table tab;
    initializeTable(&tab);
    printf("tabela inicializada.\n");
    int opcao;

    while(1) {
        printf("\n=-=-=-=-=-=-= MENU =-=-=-=-=-=-=\n");
        printf("1.  Adicionar Estudante.\n");
        printf("2.  Inorder no indice da bst da tabela.\n");
        printf("3.  Inorder no indice bst na tabela.\n");
        printf("4.  Procurar Estudante pelo nome.\n");
        printf("5.  \n");
        printf("6.  \n");
        printf("7.  \n");
        printf("8.  \n");
        printf("9.  \n");
        printf("10.  Salvar arquivo BST: indexBST.dat\n");
        printf("99. Finalizar.\n");
        printf("digite sua opcao: \n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                addStudent(&tab, readData());
                break;
            case 2:
                inorderPrintBST(tab.indexBST);
                printf("\n");            
                break;
            case 3:
                inorderPrintTable(tab.indexBST, &tab);
                printf("\n");                
                break;
            case 4:
                char name_student[128];
                Student *target;
                printf("Digite o nome do estudante procurado: \n");
                scanf("%s", name_student);
                target = searchStudent(&tab, name_student);
                printf("nome: %s, curso: %s, nota: %f\n", target->name, target->course, target->finalGrade);
                break;

            case 10:
                saveFileBST(tab.indexBST, "indexBST.dat");
                break;

            case 99:
                finishTable(&tab);
                exit(0);
        }
    }
}


/*
joaozin gameplay|bcc|10.000000|21|111
carlinhos da silva peres|agro|9.000000|22|222
jaja|aaa|10.000000|21|21
joao|bcc|10.000000|10|111
jojo|bizarre|10.000000|222|1111

estava na dataBST.dat
*/