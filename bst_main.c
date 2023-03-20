#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


int mama() {
    Node_bst root;
    initializeNodeBST(&root);


    char* vector_ins[10] = {"jose", "maria", "joana", "Joana", "jucicreia marababa",
                        "jose aquino rego", "art","an", "aaaaAAA", "B"};
    char* vector_del[10] = {"jose","Joana","jucicreia marababa","jose aquino rego","maria",
                 "joana","art", "an", "aaaaAAA", "B"};
    int i;

    for(i=0; i<10; i++){
        root = insertNodeBST(root, vector_ins[i]);
    }

    for(i=0; root != NULL; i++){
        preorderPrintBST(root);
        root = removeNodeBST(root, vector_del[i]);
        printf ("\n");
    }

    /*
    char* vector_ins[7] = {"joao", "sara", "antonia", "pajucara", "marquinhos katiau", "superman", "josias"};

    int i;
    for(i = 0; i<7; i++){
        root = insertNodeBST(root, vector_ins[i], 1);
    }

    char* vector_del[] = {"joao","antonia","pajucara","marquinhos katiau","josias","sara","superman"};

    for(i=0; root != NULL; i++){

        preorderPrintBST(root);
        printf ("\n");
        printf ("Removendo: %s", vector_del[i]);
        root = removeNodeBST(root, vector_del[i]);
        printf ("\n");
    }*/

    return 0;
}
