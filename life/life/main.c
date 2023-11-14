#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debugmalloc.h"

void freeMap(char** _map, int rowLength){
    for(int i = 0; i<rowLength; i++){
        free(_map[i]);
    }
    free(_map);
}

//saves rwos and cols for further use
char** loadsave(const char* filename, int* readRows, int* readCols){
    int row;
    int col;
    //file beolvasása
    FILE* save = fopen(filename, "r");
    //hibakezelés
    if(save == NULL){
        perror("nagy a gond");
        return NULL;
    }
    //file fejlécének beolvasása
    fscanf(save, "%d;%d\n", &row, &col);
    *readRows = row;
    *readCols = col;
    //játéktér lefoglalása
    char** map = (char**) malloc(row * sizeof(char*));
    //hibakezelés
    if(map == NULL){
        perror("nagy a gond");
        return NULL;
    }
    //sorok lefoglalása és feltöltése
    int itemCount = 0;
    for(int i = 0; i<row; i++){
        map[i] = (char*) malloc(col*sizeof(char));
        for(int j = 0; j<col; j++){
            char c = fgetc(save);
            map[i][j] = c;
            itemCount++;
        }
        //új sor karakter átugrása
        fgetc(save);
        //if(feof(save)) break;
    }
    printf("%d elem van",itemCount);

    fclose(save);
    return map;
}

void printMap(char** map, int rowLength, int colLength){
    printf("\n\n\n");
    for(int i = 0; i<rowLength; i++){
        for(int j = 0; j<colLength; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void nextState(char** map, int rowLength, int colLength){

    char** newMap = (char**) malloc(rowLength * sizeof(char*));
    for(int i = 0; i<rowLength; i++){
        newMap[i] = (char*) malloc(colLength * sizeof(char));
        for(int j = 0; j<colLength; j++){
            int count = countNeighbours(map, i, j, rowLength, colLength);
            bool alive = false;
            if(map[i][j] == '#'){
                if(count < 2) alive = false;
                if(count == 2 || count == 3) alive = true;
                if(count > 3) alive = false;
            }
            else{
                if(count == 3) alive = true;
            }

            newMap[i][j] = (alive == true) ? '#' : '.' ;
        }
    }
    //átmásolás

    for(int i = 0; i<rowLength; i++){
        for(int j = 0; j<colLength; j++){
            map[i][j] = newMap[i][j];
        }
    }
    freeMap(newMap, rowLength);
}

int countNeighbours(char** map,  int row, int col, int rowLength, int colLength){
    int count = 0;
    for(int i = row-1; i<=row+1; i++){
        for(int j = col-1; j<=col+1; j++){
            if(i < 0 || i >= rowLength) continue;
            if(j < 0 || j >= colLength) continue;
            if(i == row && j == col) continue;
            if(map[i][j] == '#') count++;
        }
    }
    return count;
}


int main(){
    int rowLength, colLength;
    char** amongus = loadsave("Saves/amongus.txt", &rowLength, &colLength);
    printMap(amongus, rowLength, colLength);
    printf("\n\n\n");
    nextState(amongus, rowLength, colLength);
    printMap(amongus, rowLength, colLength);
    freeMap(amongus, rowLength);

    return 0;
}
