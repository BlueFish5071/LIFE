#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void freeMap(char** map){
    int rowLength = sizeof(map);
    for(int i = 0; i<rowLength; i++){
        free(map[i]);
    }
    free(map);
}

int countRows(char** map){
    int rowCount = 0;
    int i = 0;
    while(map[i][0] == '.' || map[i][0] == '#'){
        rowCount++;
        i++;
    }
    return rowCount;
}
int countCols(char** map){
    int colCount = 0;
    int j = 0;
    while(map[0][j] == '.' || map[0][j] == '#'){
        colCount++;
        j++;
        printf("[%d] %d", colCount, j);
    }
    return colCount;
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
        map[i] = (char*) malloc(col * sizeof(char));
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
    //printMap(newMap);
    //átmásolás

    for(int i = 0; i<rowLength; i++){
        int colLength = sizeof(map[i]);
        for(int j = 0; j<colLength; j++){
            map[i][j] = newMap[i][j];
        }
    }

    for(int i = 0; i<rowLength; i++){
        map[i] = newMap[i];
    }
    //freeMap(newMap);
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



    /*
    char eletter[2][3] = {
        {'#',' ',' '},
        {'#','#','#'}
    };
    for(int sor = 0; sor<2; sor++){
        for(int oszlop = 0; oszlop<3; oszlop++){
            printf("%c", eletter[sor][oszlop]);
        }
        printf("\n");
    }
    printf("%d", sizeof(eletter));
    */

    return 0;
}
