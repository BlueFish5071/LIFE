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

char** loadsave(const char* filename){
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
    //játéktér lefoglalása
    char** map = (char**) malloc(row * sizeof(char*));
    //hibakezelés
    if(map == NULL){
        perror("nagy a gond");
        return NULL;
    }
    //sorok lefoglalása és feltöltése
    for(int i = 0; i<row; i++){
        map[i] = (char*) malloc(col * sizeof(char));
        for(int j = 0; j<col; j++){
            char c = fgetc(save);
            map[i][j] = c;
        }
        //új sor karakter átugrása
        fgetc(save);
        //if(feof(save)) break;
    }
    /*
    for(int i = 0; i<row; i++){
        map[i] = (char*) malloc((col+2) * sizeof(char));
        //hibakezelés
        if(map[i] == NULL){
            perror("nagy a gond");
            return NULL;
        }
        char* temp = malloc((col+2)*sizeof(char));
        printf("%s\n",temp);
        fgets(temp, (col+2), save);
        for(int j = 0; j<col+1; j++){
            map[i][j] = temp[j];
        }
    }
    */

    fclose(save);
    return map;
}

void printMap(char** map){
    printf("\n\n\n");
    int rowLength = sizeof(map);
    for(int i = 0; i<rowLength; i++){
        int colLength = sizeof(map[i]);
        for(int j = 0; j<colLength; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void nextState(char** map){

    int rowLength = sizeof(map);
    char** newMap = (char**) malloc(rowLength * sizeof(char*));
    for(int i = 0; i<rowLength; i++){
        int colLength = sizeof(map[i]);
        newMap[i] = (char*) malloc(colLength * sizeof(char));
        for(int j = 0; j<colLength; j++){
            int count = countNeighbours(map, i, j);
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
    freeMap(newMap);
}

int countNeighbours(char** map,  int row, int col){
    int count = 0;
    int rowLength = sizeof(map);
    for(int i = row-1; i<=row+1; i++){
        int colLength = sizeof(map[i]);
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

    char** amongus = loadsave("Saves/amongus.txt");
    printMap(amongus);
    printf("\n\n\n");
    nextState(amongus);
    printMap(amongus);



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
