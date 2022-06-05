# cy-library

library system that allows borrowing, returning books, as well as viewing information about them.
user system is not implemented at all, as well as the time limit system (book borrowing time is technically implemented but nothing is done with it).

the program will most likely not function properly/crash if any of the files is missing/corrupted. inputs longer than 200 characters when naming category,titles and authors will also cause unintendted behavior/crashes.

# to compile :
- open a command prompt in program folder
- type ```make```
- type ```./library```

# book handling and how to manually add one (through editing list.txt)
a book is composed of 6 lines in the file :
- the first line is the book ID and should always be incremented by 1 from the last book
- the second line is the book's category ID, and corresponds to the one in "category.txt"
- the third line is the time of borrowing, and is set to 10 zeroes (```0000000000```) when a book is not borrowed
- the fourth line is the book's title
- the fifth line is the book's author
- the sixth line is a ```#``` separator, to differentiate between each book
- there must always be an empty line after the last book

# category handling and how to manually add one
a category is composed of one line in the category.txt file. each line is divded in two parts :
- a number which represents the category ID and should always be incremented by 1 from the last category
- a name for the category
