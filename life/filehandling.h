#ifndef FILEHANDLING_H_INCLUDED
#define FILEHANDLING_H_INCLUDED

char** loadSave(int* readRows, int* readCols);
void saveMap(char** map, int rowLength, int colLength);
static char* getTime();
static char* createFilename(char* time);


#endif // FILEHANDLING_H_INCLUDED
