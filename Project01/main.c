//
//  main.c
//  Project01
//
//  Created by sin on 2017/02/02.
//  Copyright © 2017年 shinji. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "load.h"

struct account{
    int user;
    char* pass;
};
struct course{
    char* courseID;
    char* name;
};
struct student{
    int studentID;
    char* name;
    char* gender;
    short grade;
    char* address;
    short admission_year;
    char** courses;
    int courses_num;
};
struct studentcourse{
    int studentID;
    char* courseID;
    short mark;
};
void enterLogin( void );
void showLoginView( void );
void makeAccountStructure( char file_name[] );
void makeCourseStructure( char file_name[] );
void makeStudentStructure( char file_name[] );
void makeStuCourseStructure( char file_name[] );
int getArrayLength( char** dataArray );
int getArrayLen( char** dataArray );
void showPrintMyCourse( int myStudentID );
void showPrintMyTranscript( void );
void showPrintAllStudents( void );
void showPrintAllCourses( void );
void stageRanking( void );
char** getCourseName( char** courseID, int courseTotalNum, int transcript );
void bubbleSort(float* allGPAArray, int arrayLen);

int compareIds( int studentID );
float calculateGPA( int myStudentID );
int calculateRank( int myStudentID );
void printCourses();
unsigned GetDigit( unsigned num );
void getGender(char* sex);
char* convertFirstCapital(char* word);

void mainMenu();
void delay();
float* calculateAllGPA();

#define MAXUSER 1000
#define MAXTEXT 50
#define N 256

#define FILE_ACCOUNT "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/Accounts.txt";;
#define FILE_COURSE "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/Courses.txt"
#define FILE_STUDENT "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/Students.txt"
#define FILE_STUCOURSE "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/StudentsCourses.txt"

struct account*       Account;
struct course*        Course;
struct student*       Student;
struct studentcourse* StudentCourse;

int myStudentID = 0;
int myStuStrNum = 0;
int myRank = 0;
int accountMaxNum = 0;
int courseMaxNum = 0;
int studentMaxNum = 0;
int stuCourseMaxNum = 0;
char* GenderTitle;
char* GenderFirstPerson;

float myGpa = 0.0;
int numCourses = 0;


int main( int argc, const char * argv[] ) {
    
    char file_account[] = FILE_ACCOUNT;
    char file_course[] = FILE_COURSE;
    char file_student[] = FILE_STUDENT;
    char file_studentscourses[] = FILE_STUCOURSE;
    
    Account       = (struct account*) malloc(sizeof(struct account) * MAXUSER);
    Course        = (struct course*) malloc(sizeof(struct course) * MAXUSER);
    Student       = (struct student*) malloc(sizeof(struct student) * MAXUSER);
    StudentCourse = (struct studentcourse*) malloc(sizeof(struct studentcourse) * MAXUSER);
    
    makeAccountStructure(file_account);
    makeCourseStructure(file_course);
    makeStudentStructure(file_student);
    makeStuCourseStructure(file_studentscourses);
    
    Account = (struct account*) realloc(Account, sizeof(struct account ) * accountMaxNum);
    Course  = (struct course*) realloc(Course, sizeof(struct course ) * courseMaxNum);
    Student = (struct student*) realloc(Student, sizeof(struct student ) * studentMaxNum);
    StudentCourse = (struct studentcourse*) realloc(StudentCourse, sizeof(struct studentcourse ) * stuCourseMaxNum);
    
    showLoginView();
    
    return 0;
    
}


// need divided
void showLoginView(void){
    
//just try ======================= delete later
//    myStudentID = 7813007;
//    myGpa = calculateGPA(myStudentID);
////    stageRanking();
//    myStuStrNum = 0;
//    showPrintMyTranscript();
    //    showPrintAllStudents();
    
// ======================= delete later
    
    printf("************************************************************\n");
    printf("Please enter your account to login:\n");
    printf("************************************************************\n");
    enterLogin();
}


void enterLogin( void ){
    int num = 0, inputUsername = 0;
    char* inputPassword = malloc(sizeof(char) * N);
    printf("Username:");
    scanf("%d", &inputUsername);
    printf("Password:");
    scanf("%s", inputPassword);
    
    //check login
    for (int i = 0; i < accountMaxNum; i++) {
        if(inputUsername == Account[i].user){
            myStudentID = inputUsername;
            num = i;
            myStuStrNum = compareIds(myStudentID);
            break;
        }
    }
    
    if(strcmp(inputPassword,Account[num].pass) == 0){
        // login saccess
        printf("************************************************************\n");
        printf("Welcome to Cornerstone International College of Canada.\n");
        printf("************************************************************\n");
        delay(3000);
        myGpa = calculateGPA(myStudentID);
        getGender(Student[myStuStrNum].gender);
        mainMenu();
    }else{
        printf("************************************************************\n");
        printf("Your account does not exist. Please try again!\n");
        printf("************************************************************\n");
        enterLogin();
    }
    
}



void mainMenu(){
    int repeater = 0;
    int opt;
    while(repeater == 0){
        printf("******************************************\n");
        printf("Select from the options:\n");
        printf("******************************************\n");
        printf("¬[1] Print my enrollment certificate\n");
        printf("¬[2] Print my courses\n");
        printf("¬[3] Print my transcript\n");
        printf("¬[4] Print my GPA\n");
        printf("¬[5] Print my ranking among all students in the college\n");
        printf("¬[6] List of all available courses\n");
        printf("¬[7] List of all students\n");
        printf("¬[8] Logout\n");
        printf("¬[9] Exit\n");
        printf("******************************************\n");
        printf("Enter the number corresponding to each item to proceed:\n");
        
        
        scanf("%d",&opt);
        
        switch(opt){
            case 1:
                printf("Dear Sir/Madam,\n\nThis is to certify that %s. %s with student id %d is a student at grade %d at CICCC. %s was admited to our college in %hd and has taken %d course(s). Currently %s resides at %s\n\n",
                       GenderTitle,
                       Student[myStuStrNum].name,
                       myStudentID,Student[myStuStrNum].grade,
                       convertFirstCapital(GenderFirstPerson),
                       Student[myStuStrNum].admission_year,
                       Student[myStuStrNum].courses_num,
                       GenderFirstPerson,
                       Student[myStuStrNum].address);
                printf("If you have any questions, please do not hesitate to contact us.\n");
                delay(3000);
                break;
            case 2:
                printf("Hi %s. %s has taken the following courses:\n", GenderTitle, Student[myStuStrNum].name);
                
                showPrintMyCourse(myStudentID);
                break;
            case 3:
                printf("Hi %s. %s,\n", GenderTitle, Student[myStuStrNum].name);
                printf("Here is your transcript:\n\n");
                showPrintMyTranscript();
                printf("Your GPA is: %f\n\n",myGpa);
                break;
            case 4:
                printf("Hi %s. %s,\n", GenderTitle, Student[myStuStrNum].name);
                printf("Your GPA is: %f\n\n",myGpa);
                delay(4000);
                break;
            case 5:
                printf("Hi %s. %s,\n", GenderTitle, Student[myStuStrNum].name);
                stageRanking();
                printf("Your GPA is:%.2f and therefore your rank is %d\n\n",myGpa ,myRank);
                break;
            case 6:
                printf("The following courses are offered in CICCC:\n");
                showPrintAllCourses();
                break;
            case 7:
                printf("There are %d students in CICCC as following:\n", studentMaxNum);
                showPrintAllStudents();
                
                break;
            case 8:
                printf("Logging out...");
                delay(4000);
                repeater=1;
                
                break;
            case 9:
                printf("Thank you for using our program!\n");
                delay(4000);
                exit(1);
                break;
            default:
                printf("Wrong Option, please try again!\n");
        }
    }
    
    if (repeater == 1){
        delay(3000);
        showLoginView();
    }
}

void stageRanking( void ){
    float* allGPAArray = calculateAllGPA();
    int num = 0;
    while (allGPAArray[num] != '\0') {
        num++;
    }
    bubbleSort(allGPAArray, num);
    
    for (int i = 0; i < num; i++) {
        if(allGPAArray[i] == myGpa){
            myRank = i + 1;
        }
    }
}

void bubbleSort(float* allGPAArray, int arrayLen){
    
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



float* calculateAllGPA(){
    float* markArray = (float *) malloc(sizeof(float *) * studentMaxNum);
    float temNum = 0;
    int temIndex = 0;
    
    // first, all students were calcurated
    for (int i = 0; i < studentMaxNum; i++) {

        for (int a = 0; a < stuCourseMaxNum; a++) {
            if ( Student[i].studentID == StudentCourse[a].studentID ) {
                temNum = temNum + StudentCourse[a].mark;
                temIndex++;
            }
        }
        temIndex = temIndex;
        markArray[i] = temNum / temIndex;
        temNum = 0;
        temIndex = 0;
    }
    return markArray;
}







void showPrintMyCourse(int myStudentID){
    char** courseName;
    courseName = getCourseName(Student[myStuStrNum].courses, Student[myStuStrNum].courses_num, 0);
    int nums = getArrayLength(courseName);
    for (int i = 0; i < nums; i++) {
        printf("%d) %s \n", i+1, courseName[i]);
    }
}

void showPrintAllCourses( void ){
    for (int i = 0; i < courseMaxNum; i++) {
        printf("%d) %s: %s \n", i+1, Course[i].courseID, Course[i].name);
    }
}

void showPrintAllStudents(void){
    for (int i = 0; i < studentMaxNum; i++) {
        printf("%d) %s: %d \n", i+1, Student[i].name,Student[i].studentID);
    }
}



void showPrintMyTranscript(void){
    char** courseName;
    courseName = getCourseName(Student[myStuStrNum].courses, Student[myStuStrNum].courses_num, 1);
    
    int nums = getArrayLength(courseName);
    for (int i = 0; i < nums; i++) {
        printf("%d) %s \n", i+1, courseName[i]);
    }
}


char** getCourseName( char** courseID, int courseTotalNum, int transcript ){
    char** courseNameID;
    char* courseName;
    int num = 0;
//    int transcript = 1;
    courseNameID = (char **) malloc(sizeof(char **) * courseTotalNum);
    
    //自分が受けているコースを参照し [courseTotalNum]:自分が受けているコース数
    int noname = 0, marklen = 0;
    for (int a = 0; a < courseTotalNum; a++) {
        int idlen = 0, namelen = 0;
        // get course name from all info of course
        for (int i = 0; i < courseMaxNum; i++) {
            
            if(strcmp(courseID[a], Course[i].courseID) == 0){
                idlen = strlength(courseID[a]);// courseID of text length
                namelen = strlength(Course[i].name); //course name of text length
                courseNameID[num] = (char *) malloc(sizeof(char *) * (idlen+namelen+3));// for [: \0]
                courseName = Course[i].name;
                
                noname = 0;
                break; // if exist, escape
            }else{
                noname = 1; // if no found, checked
            }
        
        }

        //If there is no name
        if(noname == 1){
            noname = 0;
            int idlen = strlength(courseID[a]);
            courseNameID[num] = (char *) malloc(sizeof(char *) * (idlen+14+1));// for [: \0]
            courseName = "NO COURSE NAME";
        }
        
        //assign. whether there is a name or not
        strcpy(courseNameID[num], courseID[a]);
        strcat(courseNameID[num], ": ");
        strcat(courseNameID[num], courseName);
        
        // if you want to show mark...
        if(transcript == 1){
            //点数を計算するため、studentcourseからmarkを算出
            for (int l = 0; l < stuCourseMaxNum; l++) {
                
                //自分だけなおかつコース情報の中にないのは除外
                if( (myStudentID == StudentCourse[l].studentID) &&
                   (strcmp(courseID[a], StudentCourse[l].courseID) == 0) ){
                    
                    marklen = GetDigit(StudentCourse[l].mark);// get digit of mark
                    
                    //courseNameID[num] = (char *) malloc(sizeof(char *) * (idlen+namelen+3+marklen+2));// for [: \0]
                    courseNameID[num] = (char *) realloc(courseNameID[num], sizeof(char *) * (idlen+namelen+3+marklen+2));
                    
                    strcat(courseNameID[num], ": ");
                    int markNum = StudentCourse[l].mark;
                    char markEn[marklen];
                    sprintf(markEn, "%d", markNum);
                    strcat(courseNameID[num], markEn);
                    
                }
            }
        }
        
        num++;
    
    }
    
    return courseNameID;
    
}




int getArrayLength(char** dataArray){
    int num = 0;
    while (dataArray[num] != NULL) {
        num++;
    }
    return num;
}

int getArrayLen(char** dataArray){
    int size = sizeof dataArray / sizeof dataArray[0];
    return size;
}


int compareIds(int studentID){
    int result=0;
    for(int i=0;i<studentMaxNum;i++){
        if(Student[i].studentID==studentID){
            result = i;
        }
    }
    return result;
}


float calculateGPA( int myStudentID ){
    
    for (int i = 0; i < stuCourseMaxNum; i++) {
        if ( myStudentID == StudentCourse[i].studentID ) {
            myGpa = myGpa + StudentCourse[i].mark;
            numCourses++;
        }
    }
    return myGpa / numCourses;
}

int calculateRank(int myStudentID){
    int result = 0;
    
    return result;
}

unsigned GetDigit(unsigned num){
    unsigned digit=0;
    while(num!=0){
        num /= 10;
        digit++;
    }
    return digit;
}


void getGender(char* sex){
    
    if(strcmp(sex, "male") == 0){
        GenderTitle = "Mr";
        GenderFirstPerson = "he";
    }else{
        GenderTitle = "Mrs";
        GenderFirstPerson = "she";
    }
    
}


char* convertFirstCapital(char* word){
    char* tmp;
    int num = (int)strlen(word);
    for( int i = 0; i <= num; i++){
        if(i == 0){
            tmp[i] = toupper( word[i] );
        }else{
            tmp[i] = word[i];
        }
    }
    return tmp;
}


void makeAccountStructure( char file_name[] ){
    
    char** dataArray = loadFile(file_name);
    char** arrayUser = getData(dataArray, "User");
    accountMaxNum = getArrayLength(arrayUser);
    char** arrayPass = getData(dataArray, "Pass");
    
    for (int i = 0; i < accountMaxNum; i++) {
        Account[i].user = atoi(arrayUser[i]);
        Account[i].pass = arrayPass[i];
    }
    
}

void makeCourseStructure( char file_name[] ){
    
    char** dataArray;
    int dataLen = 0;
    
    dataArray = loadFile(file_name);
    
    char** arrayCourseID = getData(dataArray, "courseID");
    dataLen = getArrayLength(arrayCourseID);
    
    char** arrayName = getData(dataArray, "name");
    courseMaxNum = dataLen;
    
    for (int i = 0; i < dataLen; i++) {
        Course[i].courseID = arrayCourseID[i];
        Course[i].name = arrayName[i];
    }
    
}

void makeStudentStructure( char file_name[] ){
    
    char** dataArray;
    int dataLen = 0;
    
    dataArray = loadFile(file_name);
    char** arrayStudentID = getData(dataArray, "studentID");
    dataLen = getArrayLength(arrayStudentID);
    
    char** arrayName = getData(dataArray, "name");
    char** arrayGender = getData(dataArray, "gender");
    char** arrayGrade = getData(dataArray, "grade");
    char** arrayAddress = getData(dataArray, "address");
    char** arrayAdmis = getData(dataArray, "admission_year");
    char** arrayCourses = getData( dataArray, "courses");
    
    studentMaxNum = dataLen;
    
    for (int i = 0; i < dataLen; i++) {
        Student[i].studentID = atoi(arrayStudentID[i]);
        Student[i].name = arrayName[i];
        Student[i].gender = arrayGender[i];
        Student[i].grade = (short)atoi(arrayGrade[i]);
        Student[i].address = arrayAddress[i];
        Student[i].admission_year = (short)atoi(arrayAdmis[i]);
    }
    
    for (int i = 0; i < getArrayLength(arrayCourses); i++) {
        Student[i].courses = dividedDataCourses(arrayCourses[i]);
        Student[i].courses_num = getArrayLength(Student[i].courses);
    }
    
    
}


void makeStuCourseStructure( char file_name[] ){
    
    char** dataArray;
    int dataLen = 0;
    
    dataArray = loadFile(file_name);
    
    char** arrayStudentID = getData(dataArray, "studentID");
    dataLen = getArrayLength(arrayStudentID);
    
    char** arrayCourseID = getData(dataArray, "courseID");
    
    char** arrayMark = getData(dataArray, "mark");
    stuCourseMaxNum = dataLen;
    
    for (int i = 0; i < dataLen; i++) {
        StudentCourse[i].studentID = atoi(arrayStudentID[i]);
        StudentCourse[i].courseID = arrayCourseID[i];
        StudentCourse[i].mark = (short)atoi(arrayMark[i]);
    }
    
}


void delay(int x){
   	int c = 1, d = 1;
    for ( c = 1 ; c <= x ; c++ )
        for ( d = 1 ; d <= 200000 ; d++ )
        {}
}
