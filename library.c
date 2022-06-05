#include "library.h"

/* this is a comment */ 
//this is old debug code

void main(){
    int loop=0;
		int test;
    int choice=0;

    while (loop==0){
        printf("\n|*****************************************************|\nwhat would you like to do :\n1 : add a book to the library\n2 : print info about an existing book\n3 : rent a book\n4 : return a book\n5 : add a category\n6 : exit the program\n|*****************************************************|\n");
				/* keeps asking for input until a number between 1 and 6 is entered */
				//scanf("%d",&choice);
				choice=clean_scanf(choice,1,6);
				switch (choice){
            case 1 :
                create_book();
                break;
            case 2 :
                print_book();
                break;
            case 3 :
								book_rent();
                break;
            case 4 :
                book_return();
                break;
						case 5 :
								test=choose_category(0);
								printf("test=%d\n",test);
								getchar();
								break;		
						case 6 :
								loop=1;
								break;

        }
        choice=0;
    }
}