#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cells.h"
#include "debugmalloc.h"


void freeMap(char** map, int rowLength){
    for(int i = 0; i<rowLength; i++){
        free(map[i]);
    }
    free(map);
}

void nextState(char** map, int rowLength, int colLength){
    int count;
    char** newMap = (char**) malloc(rowLength * sizeof(char*));
    for(int i = 0; i<rowLength; i++){
        newMap[i] = (char*) malloc(colLength * sizeof(char));
        for(int j = 0; j<colLength; j++){
            count = countNeighbours(map, i, j, rowLength, colLength);
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
    //atmasolas
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
