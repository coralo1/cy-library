#include "library.h"

/* this is a comment */ 
//this is old debug code

/* initialize a book with empty/default values */
book book_ini(){
    book book1;
    book1.title=malloc(201);
    strcpy(book1.title,"");
    book1.author=malloc(201);
    strcpy(book1.author,"");
    book1.id=0;
    book1.category=0;
		book1.time=0;

    return book1;
}

/* count books */
int count_book(int choice){
    FILE *fp=NULL;
    int amount,test,i,lines;
    char target;
    char *line=malloc(201);
    
    /* count the amount of times the char # appears. it's used to separate chars*/
    target='#';
    amount=countlines(LIST,target);

    fp=open(LIST,"r");
    printf("\n");
		/* print the title of each book if choice=1*/
    if (choice==1){
			/* repeat for every book */
				for (i=0;i<amount;i++){
        		lines=0;
						/* read until end of file */
        		while (fgets(line,200,fp)!=NULL){
								/* if the line is equal to a title line, print it */
            		if (lines==(2+(6*i))){
                		fgets(line,200,fp);
                		printf("%d : %s",i+1,line);
            		}
            		lines=lines+1;
        		}
        		rewind(fp);
    		}
		}
		
    free(line);
		test=fclose(fp);
		if (test!=0){
				printf("there was an error closing list.txt\n");
				exit;
		}
    return amount;
}

/* category selection. n defines wether you can add a category or not */
int choose_category (int n){
    FILE *fp = NULL;
    int i,lines,choice;
		char c;
    char *line=malloc(201);
    char target;
    int test;
    

    fp=open(CATEGORY,"r");
		/* counts the amount of line breaks in category.txt (= count the amount of categories in category.txt) */
    target='\n';
    lines = countlines(CATEGORY,target)+1;
		//printf("there are %d lines\n",lines);

    printf("please choose a category :\n");
		/* print every category */
    for (i=0;i<lines;i++){
        fgets(line,200,fp);
        printf("%s",line);
    }
		/* option to add a category, is used when adding a book */
    if (n==0){
        printf("\n%d add a category\n",lines+1);
    }
    else {
        printf("\n");
    }
		/* asks for input until a number between 1 and the number of categories(+1 if we're adding a category) is entered */
		choice=clean_scanf(choice,1,(lines+1-n));
    /* adding a category */
		//printf("choice : %d | lines+1 = %d\n",ch!oice,(lines+1));
    if (choice==(lines+1)){
        printf("enter a new category name :\n");
        flush_stdin();
        scanf("%[^\n\r]",line);
				//printf("we are after scanf\n");
				/* check for unauthorized char in category name*/
        if (illegal_char_check(line)==0){
            fclose(fp);
						free(line);
            exit;
        }
				/* close category.txt and open it in append mode to be at the end of file instantly, then add the new category numder & name*/
        test=fclose(fp);
        fp=open(CATEGORY,"a+");
        fprintf(fp,"\n%d %s",(lines+1),line);
				//getchar();
				//printf("added something to category.txt\n");
				//getchar();
    }
    test=fclose(fp);
		if (test!=0){
				printf("there was an error closing category.txt\n");
				free(line);
				exit;
		}
    free(line);
    return (choice);
}

//creates and fills a book
void create_book(){
    /* A FAIRE : vérifier si l'utilisateur qui veut créer le livre est un professeur */
    FILE *fp = NULL;
    int lines=0;
    int category;
    char *title=malloc(201);
    char *author=malloc(201);
    char target;
    int test;
    
		/* counts the aomunt of books in list.txt*/
    target='#';
    lines=countlines(LIST,target);

    fp=open(LIST,"a+");
    flush_stdin();
    printf("please enter the title, without unusual characters\n");
    scanf("%[^\n\r\b]",title);    /*if you ctrl+c here, the program doesn't stop instantly and writes random characters. it looks like it takes ctrl+c as an input. in the rare case that the random chars are authorized, it may add a book*/
    printf("\n");
		/* check for unauthorized characters in input */
    if (illegal_char_check(title)==0){
        free(title);
        free(author);
        return;
    }
    
    /* id */
    fprintf(fp, "%d\n",(lines+1));
    /* category */
    category=choose_category(0);
    fprintf(fp, "%d\n",category);
		/* time */
		fprintf(fp, "0000000000\n");
    /* title */
    fputs(title,fp);
    fprintf(fp, "\n");
    /* author */
    printf("please enter the author\n");
    flush_stdin();
    scanf("%[^\n\r]",author);
		/* check for unauthorized characters in input */
    if (illegal_char_check(author)==0){
        free(title);
        free(author);
        fclose(fp);
        exit;
    }
    fputs(author,fp);
		/* # separator */
    fprintf(fp, "\n#\n");
		test=fclose(fp);
		if (test!=0){
				printf("there was an error closing category.txt\n");
				exit;
		}
    free(title);
    free(author);
}

/* fills a book struct from file */
book book_fill(int book_choice){
    FILE *fp;
    book book1;
    int i,test;
    char *line=malloc(201);

		/* initializes book struct with empty/default values */
		book1=book_ini();
    fp=open(LIST,"r");
    /* moves cursor to start of desired book */
    for (i=0;i<(6*(book_choice-1));i++){
        fgets(line,200,fp);
    }
    //printf("we got to the start of desired book\n");
		
    /* assign values from file to struct */
    for (i=0;i<5;i++){
        //printf("book.title before fgets, i = %d : %s",i,book1.title);
        fgets(line,200,fp);
        //printf("book.title after fgets, i = %d : %s",i,book1.title);
        //if (i==2){
            //printf("you've selected : %s",line);
        //} else if (i>2){
            //printf("book.title during for loop, i = %d : %s",i,book1.title);
        //}
        switch (i){
						/* assign id */
            case 0 :
                book1.id=atoi(line);
                continue;
						/* assign category */
            case 1 :
                book1.category=atoi(line);
                continue;
						/* assign time */
            case 2 :
								book1.time=strtoul(line,(char**)(line+10),10);
								book1.time=atoi(line);
						/* assign title */
            case 3 :
								//printf("entering case 2\n");
                strcpy(book1.title,line);
                //printf("book.title after assignation = %s",book1.titl!e);
                continue;
						/* assign author */
						case 4 :
								//printf("entering case 3\n");
                strcpy(book1.author,line);
                //printf("book.title after author assigation : %s",book1.author);
                continue;

						/* default case in case something goes wrong */
            default :
                printf("there was an error during book assignment\n");
                break;
        }
    }
    free(line);
    test=fclose(fp);
		if (test!=0){
				printf("there was an error closing list.txt\n");
				exit;
		}
    return book1;
}

/* choose a book */
book book_choice(){
    FILE *fp;
    book book1=book_ini();
    int choice=0;
    int book_choice=0;
    int category,i,amount,count,test;
    int lines=0;
		char c;
    char *line=malloc(201);

    //printf("\ttitle : %s\tauthor : %s\tcategory : %d\n\tid : %d\n",book1.title,book1.author,book1.category,book1.id);
    fp=open(LIST,"r");
		/* asks for input until entered value is betweeen 1 and 3 */
		printf("\nhow to view books :\n1 : view all books\n2 : view by category\n3 : cancel\n");
		choice=clean_scanf(choice,1,3);
		switch(choice){
    		/* view all books */
        case 1 :
            /* select a book */
						amount=count_book(1);
						printf("\nenter the number of the book you want : ");
						/* asks for input until entered value is betweeen 1 and amount of existing books */
						book_choice=clean_scanf(book_choice,1,amount);
            /* fills book struct from list.txt */
						book1=book_fill(book_choice);
            //printf("book.title after for loop = %s",book1.title);
            free(line);
            test=fclose(fp);
						if (test!=0){
								printf("there was an error closing list.txt\n");
								exit;
						}
            return book1;
            break;

        /* view by category */
				case 2 :
            printf("\n");
						/* choose a category */
            category=choose_category(1);
            count=1;
            printf("\n");
						/* gets the amount of books in list.txt */
						amount=count_book(0);
						//printf("amount = %d\n",amount);
						/* this code reads list.txt and prints books that have a category matching the selected category */
            /* repeat for every book */
						for (i=0;i<amount;i++){
            		lines=1;
								/* reads each line in the file*/
                while(fgets(line,200,fp)!=NULL){
                    //printf("ch : %c, category : %d, lines : %d, 6*i : %d\n",line[0],(char)category,lines,(2+(6*i)));
                    /* if the line read is equal to the selected category AND the line corresponds to a category line (to avoid considering a title starting by selected category, or a book having its ID being selected category)*/
										if ((line[0]==(category+48))&&(lines==2+(6*i))){
                        //printf("entering if\n");
												/* go to title line*/
                        fgets(line,200,fp);
												fgets(line,200,fp);
                        printf("%d : %s",i+1,line); 
                        count=count+1;/* could be used to fix weird book numbers but if we select them by id it somewhat makes sense so whatever */
                    }
                    lines=lines+1;
                }
                /* go back to the start of the file */
                rewind(fp);
            }

						printf("\nenter the number of the book you want : ");
						/* asks for input until the user selects a book. you can still select book that are not displayed though */
						book_choice=clean_scanf(book_choice,1,amount);
						/* fills book struct frome list.txt */
            book1=book_fill(book_choice);
            free(line);
            test=fclose(fp);
						if (test!=0){
								printf("there was an error closing list.txt\n");
								exit;
						}
            return book1;
            break;

        /* cancel */
				case 3 :
            break;

        /* default case in case something goes wrong */
        default :
            printf("there was an error during book view selection\n");
            break;
    }
    //printf("now on free and fclose\n");
    free(line);
    test=fclose(fp);
		if (test!=0){
				printf("there was an error closing list.txt\n");
				exit;
		}
}

/* print a book */
void print_book(){
    book book1;
    book* pbook;
    
    /* select book */
    pbook=&book1;
    book1=book_choice(pbook);
    /* print book */
    printf("\ttitle : %s\tauthor : %s\ttime of borrowing : %d\n\tcategory : %d\n\tid : %d\n",book1.title,book1.author,book1.time,book1.category,book1.id);
}

/* rent a book */
void book_rent(){
		FILE *fp;
		time_t sec;
		book book1;
		book *pbook;
		int i,test;
		char *line=malloc(201);

		/* select book */
		printf("select a book to rent :\n");
		pbook=&book1;
    book1=book_choice(pbook);
		/* check if book was selected (in case user cancels in book selection) */
		if (book1.id==0){
				printf("\nthere was no book selected\n");
				return;
		}
		/* check if book is available */
		if (book1.time!=0){
				printf("\nthis book is already borrowed\n");
				return;
		}


		fp=open(LIST,"r+");
		/* moves cursor to "time" line of desired book
		6 lines per book,-1 because file starts at 0 and not 6, +2 because time is the 3rd line */
		for (i=0;i<(6*((book1.id)-1)+2);i++){
				
				fgets(line,200,fp);
				//printf("%s",line);
		}
		/* change from read to write */
		fseek(fp,0,SEEK_CUR);
		/* gets current time and writes it in "time" line of desired book */
		sec=time(NULL);
		//printf("\nreplacing time now, time = %ld\n",sec);
		fprintf(fp,"%ld\n",sec);
		test=fclose(fp);
		if (test!=0){
				printf("there was an error closing list.txt\n");
				exit;
		}
		free(line);
}

/* return a book
A FAIRE : verifier que la personne qui rend un livre est la même qui a emprunté le livre */
void book_return(){
		FILE *fp;
		char *line=malloc(201);
		int test,i;
		book book1;
		book* pbook;

		/* select book */
		printf("select a book to return :\n");
		pbook=&book1;
    book1=book_choice(pbook);
		/* check if book was selected (in case user cancels) */
		if (book1.id==0){
			printf("\nthere was no book selected\n");
			return;
		}

		fp=open(LIST,"r+");
		/* moves cursor to "time" line of desired book */
		for (i=0;i<(6*((book1.id)-1)+2);i++){
				fgets(line,200,fp);
				//printf("%s",line);
		}
		fgets(line,200,fp);
		/* check if book is borrowed */
		if (line[0]=='0'){
			printf("\nthat book wasn't borrowed\n");
			return;
		}
		/* change from read to write, and go back to start of line, then reset time value of book*/
		fseek(fp,-12,SEEK_CUR);
		fprintf(fp,"0000000000\n");
		printf("\nbook returned succesfuly!\n");

		test=fclose(fp);
		if (test!=0){
				printf("\nthere was an error closing list.txt\n");
				exit;
		}
		free(line);

}