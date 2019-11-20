#ifndef PI_FILE_H
#define PI_FILE_H


int reading_file(char *path, float *matrix, int dim1, int dim2);


int reading_file2(char *path, float *matrix, int dim1, int dim2, int identifier);


int recording_file(char *path, float *matrix, int dim1, int dim2);


int createFileName(char *fileName, int size, int number);


int recording_fileAppend(char *path, float *matrix, int dim1, int dim2);


#endif
