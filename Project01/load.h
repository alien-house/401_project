//
//  load.h
//  Project01
//
//  Created by sin on 2017/02/04.
//  Copyright © 2017年 shinji. All rights reserved.
//

#ifndef load_h
#define load_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

#define MAXUSER 256
#define N 256

char ** readFile(char file_name[], char target[]);
char * substring(char * word, int raw);
char ** loadFile(char file_name[], int * num);
char ** getData(char ** dataArray, char target[]);
char ** dividedDataCourses(char * dataArray, int * courseNum);


#endif /* load_h */
