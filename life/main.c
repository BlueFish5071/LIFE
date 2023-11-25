#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "print.h"
#include "filehandling.h"
#include "userinput.h"
#include "cells.h"


int main(){
    int rowLength, colLength;
    static char** mapInstance;
    int choice;
    do{
        choice = chooseMenu();
        if(choice == 0) continue;
        switch(choice){
        case 1:
            mapInstance = loadSave(&rowLength, &colLength);
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
        case 5:
            mapInstance = inputMap(&rowLength, &colLength);
            printMap(mapInstance, rowLength, colLength);
            break;
        default:
            break;
        }
    }
    while(choice != 0);

    return 0;
}
