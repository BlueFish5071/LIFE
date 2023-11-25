#ifndef CELLS_H_INCLUDED
#define CELLS_H_INCLUDED

void freeMap(char** map, int rowLength);

void nextState(char** map, int rowLength, int colLength);

int countNeighbours(char** map,  int row, int col, int rowLength, int colLength);

#endif // CELLS_H_INCLUDED
