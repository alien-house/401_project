//
//  load.c
//  Project01
//
//  Created by sin on 2017/02/04.
//  Copyright © 2017年 shinji. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "load.h"

#define MAXUSER 1000
#define MAXTEXT 50
#define N 256




char** dividedDataCourses(char* dataArray){
    
    int j = 0, index = 0, count = 0,
    check = 0, startIndex = 0;
    char** array;
    char* dap;
    dap = dataArray;
    array = (char **) malloc(sizeof(char **) * N);
    
    while (dap[j] != '\0') { // each line
        
        if(dap[j] == '\"' && check == 0){
            check = 1;
            startIndex = j;
        }else if(dap[j] == '\"' && check == 1){
            array[index] = (char *) malloc(sizeof(char *) * (count));
            strncpy( array[index], dap+(startIndex+1), count-1 );
            array[index][count] = '\0';
            
            count = 0;
            check = 0;
            index++;
        }
        if(check == 1){
            count++;
        }
        j++;
    }
    array = (char **) realloc(array, sizeof(char **) * index);
    return array;
    
}






char** getData(char** dataArray, char target[]){
    
    int j = 0, i = 0;
    char** array;
    
    array = (char **) malloc(sizeof(char **) * N);
    while (dataArray[j] != NULL) {
        if((strstr(dataArray[j], target)) != NULL ){
            
            if( strcmp(target, "courses") == 0){
                array[i] = substring(dataArray[j], 1);
            }else{
                array[i] = substring(dataArray[j], 0);
            }
            i++;
        }
        j++;
    }
    array = (char **) realloc(array, sizeof(char **) * i);
    return array;
    
}



char* substring(char* word, int raw){
    
    char* result;
    int counter = 0;
    int count_start = 0;
    size_t len = 0;
    int checker = 0;
    len = strlen(word);
    
    // get start point
    while (word[count_start] != '\"') {
        count_start++;
    }
    
    for (int i = 0; i < len; i++) {
        if(word[i] == '\"'){
            checker = 1;
        }
        if(checker == 1){
            counter++;
        }
    }
    
    if(checker == 1){
        counter = counter - 2;
        count_start = count_start + 1;
    }
    if(raw == 1){
        counter = counter + 2;
        count_start = count_start - 1;
    }
    
    result = (char*) malloc(sizeof(char) * counter+1);
    strncpy( result, word+(count_start), counter );
    result[counter+1] = '\0';
    
    return result;
}



char** loadFile(char file_name[]){
    
    FILE *fp;
    char s[N];
    char **dataArray;
    int i = 0;
    
    fp = fopen( file_name, "r" );
    if( fp == NULL ){
        printf( "%s cannot be opened file!\n", file_name );
        exit(1);
    }
    
    dataArray = (char **) malloc(sizeof(char **) * N);
    while( fgets( s, N, fp ) != NULL ){ // get a each line, loop until null
        if(*s != '\n'){ // no need space
            trim(s); //trim empty space
            dataArray[i] = (char *) malloc(sizeof(char *) * N);
            strcpy(dataArray[i], s); // assign to
            int len = strlength(dataArray[i]);
            dataArray[i] = (char *) realloc(dataArray[i], sizeof(char *) * len+1);
            dataArray[i][len+1] = '\0';
            i++;
        }
    }
    
    fclose( fp );
    return dataArray;
}



void trim(char *s) {
    int i, j;
    for( i = (int)strlen(s)-1; i >= 0 && isspace( s[i] ); i-- ) ;
    s[i+1] = '\0';
    for( i = 0; isspace( s[i] ); i++ ) ;
    if( i > 0 ) {
        j = 0;
        while( s[i] ) s[j++] = s[i++];
        s[j] = '\0';
    }
}

int strlength(char* line){
    int len = (int)strlen(line);
    return len;
}

