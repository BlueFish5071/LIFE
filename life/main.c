#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "debugmalloc.h"

void freeMap(char** _map, int rowLength){
    for(int i = 0; i<rowLength; i++){
        free(_map[i]);
    }
    free(_map);
}

char** loadSave(const char* filename, int* readRows, int* readCols){
    int row, col;
    //file beolvasása
    FILE* save = fopen(filename, "r");
    //hibakezelés
    if(save == NULL){
        perror("nagy a gond");
        return NULL;
    }
    //file fejlécének beolvasása
    fscanf(save, "%d;%d\n", &row, &col);
    //saves rows and cols for further use
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
    //printf("%d elem van",itemCount);

    fclose(save);
    return map;
}

void printMap(char** map, int rowLength, int colLength){
    for(int i = 0; i<rowLength; i++){
        for(int j = 0; j<colLength; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
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

void printMenu(){
    printf("[1] Mentes betoltese\n"
           "[2] Allapot mentese\n"
           "[3] Kovetkezo allapot\n"
           "[4] Kilepes\n");
}

char* getTime(){
    //format: Wed Nov 22 13:29:49 2023
    //source: https://www.ibm.com/docs/en/i/7.2?topic=functions-ctime-convert-time-character-string
    //char* currentTime;
    time_t ltime;
    time(&ltime);
    //currentTime = ctime(&ltime);
    //return currentTime;
    return ctime(&ltime);
}

char* createFilename(char* time){
    //format: Saves/DD_MM_YYYY_HH_MN_SC.txt\0 (30 characters)
    char destName[30];
    int day, mon, yr, hr, min, sec;
    char monthStr[4];
    for(int i = 0; i<3; i++)
        monthStr[i] = time[i+4];    //honap beolvasasa szovegkent
    monthStr[3] = '\0';
    time = time + 8;                //elso 8 karakter torlese
    sscanf(time, "%d %d:%d:%d %d", &day, &hr, &min, &sec, &yr);
                //Wed Nov 22 13:29:49 2023
    char monthsList[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char* ptrMonth = strstr(monthsList, monthStr);      //honap megkeresese a listaban
    mon = (ptrMonth-monthsList)/3 + 1;                 //honapot megkapjuk ha visszaszamolunk a megtalalt mutatobol
    //filenev osszerakasa
    sprintf(destName, "Saves/%.2d_%.2d_%.4d_%.2d_%.2d_%.2d.txt\0",
            day, mon, yr, hr, min, sec);
    printf("%s\n", destName);
    return destName;
}

void saveMap(char** map, int rowLength, int colLength){
    char* filename = createFilename(getTime());
    //FILE* newSave = fopen("Saves/",'w+');
    //fclose(newSave);
}

int chooseMenu(){
    printMenu();
    int choice;
    if(scanf("%d",&choice) != 1)
        return 0;
    if(choice < 1 || choice > 4)
        return 0;
    return choice;
}

int main(){
    int rowLength, colLength;
    //char** mapInstance = loadSave("Saves/mapInstance.txt", &rowLength, &colLength);
    char** mapInstance;
    int choice;
    do{
        choice = chooseMenu();
        if(choice == 0) continue;
        switch(choice){
        case 1:
            mapInstance = loadSave("Saves/save1.txt", &rowLength, &colLength);
            printMap(mapInstance, rowLength, colLength);
            break;
        case 2:
            saveMap(mapInstance, rowLength, colLength);
            freeMap(mapInstance, rowLength);
            exit(0);
            break;
        case 3:
            nextState(mapInstance, rowLength, colLength);
            printMap(mapInstance, rowLength, colLength);
            break;
        case 4:
            freeMap(mapInstance, rowLength);
            exit(0);
            break;
        default:
            break;
        }
    }
    while(choice != 0);

    /*
    printf("\n\n\n");
    printMap(mapInstance, rowLength, colLength);

    nextState(mapInstance, rowLength, colLength);
    printMap(mapInstance, rowLength, colLength);
    freeMap(mapInstance, rowLength);
    */

    return 0;
}
