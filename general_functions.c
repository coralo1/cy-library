#include "library.h"

/* this is a comment */ 
//this is old debug code

/* cleans scanf memory */
int flush_stdin(){
    while(getchar()!=('\n'));
		return 1;
}

/* scanf that doesn't let you */
int clean_scanf(int choice, int min, int max){
		while (choice<min||choice>max){
				fflush(stdin);
				scanf("%d",&choice);
				//printf("choice : %d\n",choice);
		}
		return choice;
}

/* opens a file */
FILE* open(const char* name,const char* mode){
    FILE* fp;
    fp=fopen(name,mode);
    if(fp==NULL){
        printf("there was an error opening %s\n",name);
        exit(1);
    }
    return fp;
}

/* checks for unauthorized characters in inputs */
int illegal_char_check(char* sentence) {
    int i=0;
		/* read each line in the input char array. if the char is authorized, go to next char; otherwise print an error message and quit*/
    for (i=0;i<(strlen(sentence));i++) {
        /* lowercase letters */
        if (sentence[i]>=97&&sentence[i]<=122) {
            continue;
        }
        /* uppercase letters */
        if (sentence[i]>=65&&sentence[i]<=90) {
            continue;
        }
        /* space */
        if (sentence[i]==32) {
            continue;
        }
        /* numbers */
        if (sentence[i]>=48&&sentence[i]<=58) {
            continue;
        }
        /* ,-. */
        if (sentence[i]>=44&&sentence[i]<=46) {
            continue;
        }
        /* &'() */
        if (sentence[i]>=38&&sentence[i]<=41) {
            continue;
        }
        printf("illegal characters input : %c\n",sentence[i]);
        return 0;
    }
    return 1;
}

/* counts the occurence of a specific char in a file */
int countlines (char *filename, char target) {
    FILE *fp = NULL;
    int lines=0;
    char ch;
    int test;
		
    fp=open(filename,"r");
		/* read first char in the file */
    ch=fgetc(fp);
		/* loop that reads every char in the file and checks if it is equal to the input target char. if yes, append 1 to "lines"*/
    while (ch!=EOF) {
        if (ch==target) {
            lines=lines+1;
        }
        ch=fgetc(fp);
    }
    test=fclose(fp);
		if (test!=0){
				printf("there was an error closing list.txt\n");
				exit;
		}
    return lines;
}

