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
        printf("\n=-=-=-=-=-=-= College of Winterhold =-=-=-=-=-=-=\n");
        printf("1.  Adicionar Estudante.                           /\n");
        printf("2.  Inorder no indice da bst.                      /\n");                 
        printf("3.  Inorder no indice bst na tabela.               /\n");
        printf("4.  Procurar Estudante pelo nome.                  /\n");
        printf("10. Salvar arquivo BST: indexBST.dat               /\n");
        printf("99. Finalizar e salvar.                            /\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("digite sua opcao: \n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                addStudent(&tab, readData()); 
                break;

            case 2:
                inorderPrintBST(tab.indexBST); //funciona antes de fechar o terminal, ao reler novamente da erro apos salvar o arquivo
                printf("\n");            
                break;

            case 3:
                inorderPrintTable(tab.indexBST, &tab); //erro de segmentacao
                printf("\n");                
                break;

            case 4:
                char name_student[128];
                Student *target = NULL;
                printf("Digite o nome do estudante procurado: \n");
                scanf("%s", name_student);
                target = searchStudent(&tab, name_student); //nao esta lendo corretamente
                if(target != NULL)
                    printf("nome: %s, curso: %s, nota: %f\n", target->name, target->course, target->finalGrade);
                else
                    printf("target nao encontrado.\n");
                break;

            case 5:
                break;
            
            case 6:
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