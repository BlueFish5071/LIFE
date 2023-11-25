#include <stdio.h>
#include "print.h"
#include "debugmalloc.h"

void printMap(const char** map, int rowLength, int colLength){
    for(int i = 0; i<rowLength; i++){
        for(int j = 0; j<colLength; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void printMenu(){
    printf("[1] Mentes betoltese\n"
           "[2] Allapot mentese\n"
           "[3] Kovetkezo allapot\n"
           "[4] Kilepes\n"
           "[5] Allapot begepelese\n");
}
