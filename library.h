#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define CATEGORY "category.txt"
#define LIST "list.txt"

/* this is a comment */ 
//this is old debug code

typedef struct{
	char *title;
	char *author;
	int id;
	int category;
	int time;/* time of borrowing. =0 if book is not borrowed */
}book;

/* general_functions.c */
int flush_stdin();//cleans scanf memory
int clean_scanf(int choice, int min, int max);//scanf that doesn't allow you to input random stuff
int illegal_char_check(char *sentence);/* checks for unauthorized characters after a scanf */
int countlines(char *filename, char target);/* counts the occurence of a specific char in a file */
FILE *open(const char *name, const char *mode);/* opens a file and exit if there was an error */

/* book_functions.c */
int count_book();/* counts the number of books in list.txt */
int choose_category(int n);/* choose a category; if n=1, can also add a category */
void create_book();/* adds a book to list.txt */
book book_ini();/* initiates values for a book structure */
book book_fill(int book_choice);/* fills a book from list.txt to a structure */
book book_choice();/* choose a book */
void print_book();/* prints info about a book */
void book_rent();/* rent a book */
void book_return();/* return a book */
