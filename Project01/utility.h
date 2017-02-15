//
//  utility.h
//  Project01
//
//  Created by sin on 2017/02/11.
//  Copyright © 2017年 shinji. All rights reserved.
//

#ifndef utility_h
#define utility_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


int getArrayLength(char ** dataArray);
int getArrayLen(char ** dataArray);
int strlength(char * line);
unsigned GetDigit(unsigned num);
char * convertFirstCapital(char * word);
void trim(char * s);
void bubbleSort(float * allGPAArray, int arrayLen);
void delay(int x);

#endif /* utility_h */
