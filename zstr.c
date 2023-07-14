/*
Name: Nick Avalani
Course: CSC 352, Fall 2022, Benjamin Dicken
Description: This program implements many methods and functions that
manipulate and process the zstr data type.
*/
#include "zstr.h"
#include <stdio.h>
#include <stdlib.h>

zstr_code zstr_status = ZSTR_OK;   //Global variable initialization

/*
This function takes the length of the string
and returns the minimum bytes needed to use to 
malloc the zstr data type.
*/
int allocation(int space){
 	if(space <= 16){
                space = 16;
        }
        else if(space > 16 && space <= 32){
                space = 32;
        }
        else if(space > 32 && space <= 256){
                space = 256;
        }
        else if(space > 256 && space <= 1024){
               space = 1024;
        }
        else if(space > 1024 && space <= 2048){
                space = 2048;
        }
	else if(space > 2048){              
		zstr_status = ZSTR_ERROR;
		return zstr_status;
        }
	return space;
}

/*
This function creates a zstr data structure with the
length, allocation of memory, and the actual string which
is passed as an argument.
*/
zstr zstr_create(char* initial_data){
	int data_size = 0;
	for(int i = 0; *(initial_data + i) != '\0'; i++){
		data_size += 1;
	}
	int space = data_size + 4 + 4 + 1;
	int totalSpace = allocation(space);
	int *ptr0 = malloc(totalSpace);
	if(ptr0 == NULL){
		zstr_status = ZSTR_ERROR;
	}
	int *ptr = ptr0;
	ptr[0] = data_size;
	ptr[1] = totalSpace;
	ptr = ptr + 2;
	char* ptr2 = (char*)(ptr);
	for(int i = 0; i < data_size; i++){
		ptr2[i] = initial_data[i];
	}
	ptr2[data_size] = '\0';
	ptr = ptr - 2;
	return (zstr)(ptr0 + 2);            
}

/*
This function frees up the zstr in memory
*/
void zstr_destroy(zstr to_destroy){ 
	int* ptr = (int*) to_destroy;
	free((ptr - 2));
}

/*
This function appends the second argument to the
end of the first one in argument and resizes the
zstr to be appended to in memory
*/
void zstr_append(zstr* base, zstr to_append){
	int data_size = *((zstr)*base - 8);
	int allocated = *((zstr)*base - 4);
	int append_size = *((zstr)to_append - 8);
	if(data_size + append_size > (allocated - data_size - 9)){ //Resizing is required
		char total[data_size + append_size + 1];   
		for(int i = 0; i < data_size; i++){
			total[i] = (*base)[i];
		}
		for(int j = 0; j <= append_size; j++){
			total[data_size + j] = to_append[j];
                }
		zstr_destroy(*base);                             
		zstr replace = zstr_create(total);
		(*base) = replace;
		return;
	}
	else{                                                   //No resizing is necessary
		char* word = *base;
		char* word2 = to_append;
		word += data_size;
		for(int i = 0; i <= append_size; i++){
			word[i]  = word2[i];		
		}
		word -= data_size;
	}
}

/*
This function searches for word2 in word1. Returns 0 if found
and -1 if isn't found
*/
int search(char* word1, char* word2, int index, int size){
	int j = 0;
	for(int i = index; i < index + size; i++){
		if(word1[i] != word2[j]){
			return -1;
		}
		if(j < size){
			j++;
		}
	}
	return 0;
}

/*
This function returns the index of first occurence of the second
argument in the first argument.
*/
int zstr_index(zstr base, zstr to_search){
	char* word1 = (char*)(base);
	char* word2 = (char*)(to_search);
	for(int i = 0; word1[i] != '\0'; i++){
		if(word1[i] == word2[0]){
			int index = search(word1, word2, i, *((zstr)to_search - 8));
			if(index == 0){
				return i;
			}
		}
	}
	return -1;
}

/*
This function returns the count(number of instances) of the second 
argument in the first argument
*/
int zstr_count(zstr base, zstr to_search){
	int count = 0;
        for(int i = 0; base[i] != '\0'; i++){
                if(base[i] == to_search[0]){
                        int index = search(base, to_search, i, *((zstr)to_search-8));
                        if(index == 0){
                                count++;
                        }
                }
        }
        return count;
}

/*
This function returns 0 if both argument are the same
1, if the first argument is higher than the second,
-1, if the first argument is less than the second. 
Values are compared based on ascii code
*/
int zstr_compare(zstr x, zstr y){
	int i = 0;
	while(x[i] != '\0' && y[i] != '\0'){
		if(x[i] > y[i]){
			return ZSTR_GREATER;
		}
		else if(x[i] < y[i]){
			return ZSTR_LESS;
		}
		else{
			i++;
		}
	}
	if(*(x - 8) > *(y - 8)){
		return ZSTR_GREATER;
	}
	else if(*(x-8) < *(y-8)){
		return 	ZSTR_LESS;
	}
	else{
		return ZSTR_EQUAL;
	}
}

/*
This function prints the details of the zstr argument, i.e
the length of the string, the size in memory, and the actual
string
*/
void zstr_print_detailed(zstr data){
	int* nums = (int*) (data - 8);
	printf("STRLENGTH: %d\n", *(nums));
	printf(" DATASIZE: %d\n", *(nums + 1));
        printf("   STRING: >%s<\n", data);
}

/*
This functions returns a zstr whose string is a substring
of the base with indices begin(inclusive) and end(exclusive)
*/
zstr zstr_substring(zstr base, int begin, int end){
	base = base + begin;
	char substr[end - begin];
	for(int i = 0; i < end - begin; i++){
		substr[i] = base[i];
	}
	substr[end - begin] = '\0';
	zstr substring = zstr_create(substr);
	return substring;
}

