//
//  load.c
//  Project01
//
//  Created by sin on 2017/02/04.
//  Copyright © 2017年 shinji. All rights reserved.
//

#include "load.h"

char ** dividedDataCourses(char * dataArray, int * courseNum) {
    int j = 0, index = 0, count = 0,
    check = 0, startIndex = 0;
    char ** array;
    char * dap;
    dap = dataArray;
    array = (char ** ) malloc(sizeof(char * ) * N);
    while (dap[j] != '\0') { // each line
        
        if (dap[j] == '\"' && check == 0) {
            check = 1;
            startIndex = j;
        } else if (dap[j] == '\"' && check == 1) {
            array[index] = (char * ) malloc(sizeof(char * ) * count);
            strncpy(array[index], dap + (startIndex + 1), count - 1);
            array[index][count - 1] = '\0';
            count = 0;
            check = 0;
            index++;
        }
        if (check == 1) {
            count++;
        }
        j++;
    } * courseNum = index;
    array = (char ** ) realloc(array, sizeof(char * ) * index);
    
    free(dataArray);
    return array;
    
}


char * substring(char * word, int raw) {
    
    char * result;
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
        if (word[i] == '\"') {
            checker = 1;
        }
        if (checker == 1) {
            counter++;
        }
    }
    
    if (checker == 1) {
        counter = counter - 2;
        count_start = count_start + 1;
    }
    if (raw == 1) {
        counter = counter + 2;
        count_start = count_start - 1;
    }
    result = (char * ) malloc(sizeof(char * ) * counter);
    strncpy(result, word + (count_start), counter);
    result[counter] = '\0';
    
    free(word);
    
    return result;
}


char ** loadFile(char file_name[], int * num) {
    
    FILE * fp;
    char s[N];
    char ** dataArray;
    int i = 0;
    
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("%s cannot be opened file!\n", file_name);
        exit(1);
    }
    
    dataArray = (char ** ) malloc(sizeof(char * ) * N);
    while (fgets(s, N, fp) != NULL) { // get a each line, loop until null
        if ( * s != '\n') { // no need space
            trim(s); //trim empty space
            int len = strlength(s);
            dataArray[i] = (char * ) malloc(sizeof(char * ) * len + 1);
            strcpy(dataArray[i], s); // assign to
            dataArray[i][len + 1] = '\0';
            i++;
        }
    }
    
    ( * num) = i;
    fclose(fp);
    dataArray = (char ** ) realloc(dataArray, sizeof(char * ) * (i * 2));
    return dataArray;
}
