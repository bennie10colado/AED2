#ifndef PROJETO_INDEX_1VA_FINAL_DATA_TABLE_H
#define PROJETO_INDEX_1VA_FINAL_DATA_TABLE_H
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct student{
    char *name; //bst
    char course[128];
    int enrollmentCode; //rb
    int age; //avl
    float finalGrade;
}Student;

typedef struct node_bst *Node_bst;

typedef struct table{
    FILE *arcData;
    Node_bst indexBST;
}Table;

int initializeTable(Table *tab);
void finishTable(Table *tab);

void addStudent(Table *tab, Student *student);
Student *searchStudent(Table *tab, char *name_searched);
Student *searchStudent2(Table *tab, char *name_searched);

Student *readData();
void saveFileAuxBST(Node_bst root, FILE *arq);
void saveFileBST(Node_bst root, char* nome);
void loadingFileBST(Node_bst root, char *nome) ;
Node_bst loadingFileBST2(Node_bst root, char *nome);


char *deleteNewline(char *string);
void printElement(Node_bst root, Table *tab);
void preorderPrintTable(Node_bst root, Table *tab);
void inorderPrintTable(Node_bst root, Table *tab);
void postorderPrintTable(Node_bst root, Table *tab);
void printStudents(Table *tab);




#endif //PROJETO_INDEX_1VA_FINAL_DATA_TABLE_H