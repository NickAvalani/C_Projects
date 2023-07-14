/*
Name: Nick Avalani
Course: CSC 352, Fall 2022, Benjamin Dicken
Description: This program implements a library of functions
for the zstr data type. It also defines the zstr, zstr_code and 
the exit codes for zstr
*/

#include <stdio.h>
#include <stdlib.h>

//Global variables
typedef char* zstr;
typedef int zstr_code;
static const int ZSTR_OK = 0;
static const int ZSTR_ERROR = 100;
static const int ZSTR_GREATER = 1;
static const int ZSTR_LESS = -1;
static const int ZSTR_EQUAL = 0;
extern zstr_code zstr_status;

/*
This function creates a zstr data structure with the
length, allocation of memory, and the actual string which
is passed as an argument, and returns a pointer which points
to the start of the char array
*/
zstr zstr_create(char* initial_data); 

/*
This function frees up the zstr in memory
*/
void zstr_destroy(zstr to_destroy);

/*
This function appends the second argument to the
end of the first one in argument and resizes the
zstr to be appended to in memory
*/
void zstr_append(zstr* base, zstr to_append);

/*
This function returns the index of first occurence of the second
argument in the first argument.
*/
int zstr_index(zstr base, zstr to_search);

/*
This function returns the count(number of instances) of the second
argument in the first argument
*/
int zstr_count(zstr base, zstr to_search);

/*
This function returns 0 if both argument are the same
1, if the first argument is higher than the second,
-1, if the first argument is less than the second.
Values are compared based on ascii code
*/
int zstr_compare(zstr x, zstr y);

/*
This function prints the details of the zstr argument, i.e
the length of the string, the size in memory, and the actual
string
*/
void zstr_print_detailed(zstr data);

/*
This functions returns a zstr whose string is a substring
of the base with indices begin(inclusive) and end(exclusive)
*/
zstr zstr_substring(zstr base, int begin, int end);


