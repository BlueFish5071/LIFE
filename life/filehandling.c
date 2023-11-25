#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "filehandling.h"
#include "print.h"
#include "cells.h"
#include "debugmalloc.h"

char** loadSave(int* readRows, int* readCols){
    int row, col;
    //file beolvasasa
    char filename[30];
    printf("Fajlnev: ");
    scanf("%s", filename);
    FILE* save = fopen(filename, "r");
    //hibakezeles
    if(save == NULL){
        perror("nagy a gond");
        return NULL;
    }
    //file fejlecenek beolvasasa
    fscanf(save, "%d;%d\n", &row, &col);
    //parameterben visszaadja sorok es oszlopok hosszat
    *readRows = row;
    *readCols = col;
    //jatekter lefoglalasa
    char** map = (char**) malloc(row * sizeof(char*));
    //hibakezelés
    if(map == NULL){
        perror("nagy a gond");
        return NULL;
    }
    //sorok lefoglalasa és feltoltese
    int itemCount = 0;
    for(int i = 0; i<row; i++){
        map[i] = (char*) malloc(col*sizeof(char));
        for(int j = 0; j<col; j++){
            char c = fgetc(save);
            map[i][j] = c;
            itemCount++;
        }
        //uj sor karakter atugrasa
        fgetc(save);
    }

    fclose(save);
    return map;
}

void saveMap(char** map, int rowLength, int colLength){
    char* filename = createFilename(getTime());     //filenev generalasa
    printf("Mentes helye: %s\n", filename);
    FILE* save = fopen(filename, "w");              //file letrehozasa
    //file feltoltese karakterenkent
    fprintf(save, "%d;%d\n", rowLength, colLength);
    for(int i = 0; i<rowLength; i++){
        for(int j = 0; j<colLength; j++){
            fputc(map[i][j], save);
        }
        fputc('\n', save);
    }
    free(filename);
    fclose(save);
}

char* getTime(){
    //format: Wed Nov 22 13:29:49 2023
    //source: https://www.ibm.com/docs/en/i/7.2?topic=functions-ctime-convert-time-character-string
    time_t ltime;
    time(&ltime);
    return ctime(&ltime);
}

char* createFilename(char* time){
    //format: Saves/DD_MM_YYYY_HH_MN_SC.txt\0 (30 characters)
    //char destName[30];
    char* destName = malloc(30);
    int day, mon, yr, hr, min, sec;
    char monthStr[4];
    for(int i = 0; i<3; i++)
        monthStr[i] = time[i+4];    //honap beolvasasa szovegkent
    monthStr[3] = '\0';             //lezaro nulla hozzadasa
    time = time + 8;                //elso 8 karakter torlese
    sscanf(time, "%d %d:%d:%d %d", &day, &hr, &min, &sec, &yr);
                //Wed Nov 22 13:29:49 2023
    char monthsList[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char* ptrMonth = strstr(monthsList, monthStr);      //honap megkeresese a listaban
    mon = (ptrMonth-monthsList)/3 + 1;                 //honapot megkapjuk ha visszaszamolunk a megtalalt mutatobol
    //filenev osszerakasa
    sprintf(destName, "Saves/%.2d_%.2d_%.4d_%.2d_%.2d_%.2d.txt",
            day, mon, yr, hr, min, sec);
    destName[29] = '\0';
    //printf("%s\n", destName);
    return destName;
}
