#include "data_table.h"
#include "bst.h"
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdio_ext.h>

char *deleteNewline(char *string){
    string[strlen(string)-1] = '\0';
    //string[strlen(string)] = '\n';
    return string;
}

Student *readData(){
    Student *newStudent = (Student *) malloc(sizeof(Student));
    char *buffer = (char *) malloc(256 * sizeof(char));
    getchar();

    printf("Student's Name:");
    fgets(buffer, 255,  stdin);
    deleteNewline(buffer);
    newStudent->name = strdup(buffer);

    printf("Course name:");
    fgets(buffer, 128,  stdin);
    deleteNewline(buffer);
    strncpy(newStudent->course, buffer, sizeof(newStudent->course) - 1);

    printf("Final grade of the student:");
    scanf("%f", &newStudent->finalGrade);

    printf("Age:");
    scanf("%d", &newStudent->age); //eh int entao pode ser scanf

    printf("Enrollment code student:");
    scanf("%d", &newStudent->enrollmentCode);

    printf("=-=-=-= [%s][%s][%f][%d][%d] =-=-=-=",
           newStudent->name, newStudent->course, newStudent->finalGrade, newStudent->age, newStudent->enrollmentCode);
    free(buffer);
    return newStudent;
}

void saveFileAuxBST(Node_bst root, FILE *arq){
    if(root != NULL) {
        fprintf(arq, "%d|%s", root->data->index, root->data->name_student);
        //fwrite(root->data->name_student, sizeof(Student), 1, arq);
        saveFileAuxBST(root->left, arq);
        saveFileAuxBST(root->right, arq);
    }
}

void saveFileBST(Node_bst root, char *nome){
    FILE *arq;
    arq = fopen(nome, "w+");

    if(arq != NULL) {
        saveFileAuxBST(root, arq);
        fclose(arq);
    }
}

Node_bst loadingFileBST(Node_bst root, char *nome){
    FILE *arq;
    arq = fopen(nome, "rb");
    index_bst *temp;

    if(arq != NULL){
        temp = (index_bst *) malloc(sizeof(index_bst));
        printf("%d", sizeof(index_bst));

        while(fread(temp, sizeof(index_bst), 1, arq)){

            root = insertNodeBST(root, temp);
            temp = (index_bst *) malloc(sizeof(index_bst));
        }
        fclose(arq);
    }else{
        printf("\n\t--> ERRO ao abrir arquivo!\n");
    }
    return root;
}

/*
int getline(char **lineptr, size_t *n, FILE *stream){
    static char line[256];
    char *ptr;
    unsigned int len;

    if (lineptr == NULL || n == NULL){
        errno = EINVAL;
        return -1;
    }

    if(ferror (stream))
        return -1;

    if (feof(stream))
        return -1;

    fgets(line,256,stream);
    ptr = strchr(line,'\n');
    if(ptr)
        *ptr = '\0';

    len = strlen(line);
    if ((len+1) < 256){
        ptr = realloc(*lineptr, 256);
        if (ptr == NULL)
            return(-1);
        *lineptr = ptr;
        *n = 256;
    }
    strcpy(*lineptr,line);
    return(len);
}*/

Node_bst loadingFileBST2(Node_bst root, char *nome) {
    FILE *arq;
    arq = fopen(nome, "r+");
    size_t len = 50;
    char *linha = malloc(len);
    char delim[] = "|";
    Data_type temp;

    if(arq != NULL){
        temp = (Data_type) malloc(sizeof(Data_type));
        while(getline(&linha, &len, arq) > 0){ //se nao encontra retorna -1
            char *var = malloc(len);
            var = linha;
            char *ptr = strtok(var, delim);

            temp->index = atoi(ptr);
            ptr = strtok(NULL, delim);
            temp->name_student = (char *) malloc(sizeof(ptr));
            deleteNewline(ptr);
            strcpy(temp->name_student, ptr);

            root = insertNodeBST(root, temp);
            temp = (Data_type) malloc(sizeof(Data_type));
        }
        fclose(arq);
        free(temp);
    }
    free(linha);
    return root;
}

int initializeTable(Table *tab){
    initializeNodeBST(&tab->indexBST);
    tab->arcData = fopen("dataBST.dat", "a+b");
    tab->indexBST = loadingFileBST2(tab->indexBST, "indexBST.dat");

    if(tab->arcData != NULL)
        return 1;
    else
        return 0;
}

void finishTable(Table *tab){
    fclose(tab->arcData);
    saveFileBST(tab->indexBST, "indexBST.dat");//bst
    //avl
    //rb
}

void printElement(Node_bst root, Table *tab){
    Student *temp = (Student *) malloc(sizeof(Student));
    fseek(tab->arcData, root->data->index, SEEK_SET);
    fread(temp, sizeof(Student), 1, tab->arcData);

    printf("%s|%s|%f|%d|%d\n", temp->name, temp->course, temp->finalGrade, temp->age, temp->enrollmentCode);

    free(temp);
}

void preorderPrintTable(Node_bst root, Table *tab){
    if(root != NULL){
        printElement(root, tab);
        preorderPrintTable(root->left, tab);
        preorderPrintTable(root->right, tab);
    }
}

void inorderPrintTable(Node_bst root, Table *tab){
    if(root != NULL) {
        inorderPrintTable(root->left, tab);
        printElement(root, tab);
        inorderPrintTable(root->right, tab);
    }
}

void postorderPrintTable(Node_bst root, Table *tab){
    if(root != NULL){
        postorderPrintTable(root->left, tab);
        postorderPrintTable(root->right, tab);
        printElement(root, tab);
    }
}

void addStudent(Table *tab, Student *student){
    int positionNewReg;
    if(tab->arcData != NULL){
        fseek(tab->arcData, 0L, SEEK_END);
        positionNewReg = ftell(tab->arcData);

        Data_type newDataBST = (Data_type) malloc(sizeof(Data_type));
        newDataBST->name_student = student->name;
        newDataBST->index = positionNewReg;

        tab->indexBST = insertNodeBST(tab->indexBST, newDataBST);

        fwrite(student, sizeof(Student), 1, tab->arcData);

        //fprintf(tab->arcData, "%s|%s|%f|%d|%d\n", student->name,student->course, student->finalGrade, student->age, student->enrollmentCode);
    }
}


Student *searchStudent(Table *tab, char *name_searched){
    if(tab->arcData != NULL){
        node_bst *temp;
        temp = tab->indexBST;
        while (temp != NULL){
            if(temp->data->name_student == name_searched){
                fseek(tab->arcData, temp->data->index, SEEK_SET);

                Student *wanted = (Student*) malloc(sizeof(Student));
                fread(wanted, sizeof(Student), 1, tab->arcData);
                return wanted;
            }else{
                if(strcmp(name_searched, temp->data->name_student) >= 0){
                    temp = temp->right;
                }else{
                    temp = temp->left;
                }
            }
        }
    }
    return NULL;
}
