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

char** dividedDataCourses(char* dataArray);

#endif /* load_h */
