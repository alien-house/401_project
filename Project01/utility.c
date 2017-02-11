//
//  utility.c
//  Project01
//
//  Created by sin on 2017/02/11.
//  Copyright © 2017年 shinji. All rights reserved.
//

#include "utility.h"


void bubbleSort(float * allGPAArray, int arrayLen) {
    
    float tmp;
    for (int i = 0; i < arrayLen; i++) {
        for (int j = arrayLen; j > i; j--) {
            if (allGPAArray[j - 1] < allGPAArray[j]) {
                tmp = allGPAArray[j];
                allGPAArray[j] = allGPAArray[j - 1];
                allGPAArray[j - 1] = tmp;
            }
        }
    }
    
}

int strlength(char * line) {
    int len = (int) strlen(line);
    return len;
}

int getArrayLength(char ** dataArray) {
    int num = 0;
    while (dataArray[num] != NULL) {
        num++;
    }
    return num;
}

int getArrayLen(char ** dataArray) {
    int size = sizeof dataArray / sizeof dataArray[0];
    return size;
}


char * convertFirstCapital(char * word) {
    char * tmp = NULL;
    int num = (int) strlen(word);
    tmp = malloc(num + 1);
    for (int i = 0; i <= num; i++) {
        if (i == 0) {
            tmp[i] = toupper(word[i]);
        } else {
            tmp[i] = word[i];
        }
    }
    return tmp;
}

unsigned GetDigit(unsigned num) {
    unsigned digit = 0;
    while (num != 0) {
        num /= 10;
        digit++;
    }
    return digit;
}

void trim(char * s) {
    int i, j;
    for (i = (int) strlen(s) - 1; i >= 0 && isspace(s[i]); i--);
    s[i + 1] = '\0';
    for (i = 0; isspace(s[i]); i++);
    if (i > 0) {
        j = 0;
        while (s[i]) s[j++] = s[i++];
        s[j] = '\0';
    }
}

//void delay(int x) {
//    int c = 1, d = 1;
//    for (c = 1; c <= x; c++)
//        for (d = 1; d <= 200000; d++) {}
//}

int delay(unsigned long x) {
    clock_t  s = clock();
    clock_t  c;
    
    do {
        if ((c = clock()) == (clock_t)-1)       /* エラー */
            return (0);
    } while (1000UL * (c - s) / CLOCKS_PER_SEC <= x);
    return (1);
}
