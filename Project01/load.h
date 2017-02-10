//
//  load.h
//  Project01
//
//  Created by sin on 2017/02/04.
//  Copyright © 2017年 shinji. All rights reserved.
//

#ifndef load_h
#define load_h

char** readFile( char file_name[], char target[]);
void trim( char *s );

char* substring(char* word, int raw);
char** loadFile( char file_name[] );
char** getData(char** dataArray, char target[]);

int strlength(char* line);
unsigned GetDigit( unsigned num );

int getArrayLength( char** dataArray );
int getArrayLen( char** dataArray );
void bubbleSort(float* allGPAArray, int arrayLen);
char** dividedDataCourses(char* dataArray);

char* convertFirstCapital(char* word);
void delay();
#endif /* load_h */
