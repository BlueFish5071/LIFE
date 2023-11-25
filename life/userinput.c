#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"

char** inputMap(int* inputRows, int* inputCols){
    int row, col;
    printf("sor;oszlop: ");
    //palya meretenek beolvasasa
    scanf("%d;%d", &row, &col);
    //parameterben visszaadja sorok es oszlopok hosszat
    *inputRows = row;
    *inputCols = col;
    //jatekter lefoglalasa
    char** map = (char**) malloc(row * sizeof(char*));
    //hibakezelés
    if(map == NULL){
        perror("nagy a gond");
        return NULL;
    }
    //sorok lefoglalása és feltöltése
    for(int i = 0; i<row; i++){
        *(map+i) = (char*) malloc(col*sizeof(char));
        for(int j = 0; j<col; j++){
            printf("[%d][%d]: ", i, j);
            scanf(" %c", &map[i][j]);
            //whitespace before %c eliminates new line character
            //source: https://www.codesdope.com/discussion/why-are-you-using-a-space-before-c-in-scanf-c-ch/
        }
    }
    printf("\n\n\n");
    return map;
}

int chooseMenu(){
    printMenu();
    int choice;
    if(scanf("%d",&choice) != 1)
        return 4;
    if(choice < 1 || choice > 5)
        return 4;
    return choice;
}
