#include <stdio.h>
#include <stdlib.h>
#include "data_table.h"

int main() {
    Table tab;
    initializeTable(&tab);
    int opcao;

    while(1) {
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                addStudent(&tab, readData());
                break;
            case 2:
                inorderPrintTable(tab.indexBST, &tab);
                printf("\n");
                break;

            case 99:
                finishTable(&tab);
                exit(0);
        }
    }
}
