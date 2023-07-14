/*
Name: Nick Avalani
Course: CSC 352, Fall 2022, Benjamin Dicken
Description: This program implements a simplified version
of the cut command that takes infinite number of lines.
Two command line arguments can be taken. The first being
a flag (-l, -w, -c) and the second being the columns that
need to be "cut".
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
This function returns 0 if the parameter passed is a digit
and returns 1 if otherwise.
*/
int isDigit(char elem){
        if(elem >= '0' && elem <= '9'){
                return 0;
        }
        return 1;
}

/*
This function checks if there are 2 command line arguments,
the first command line argument is either -l, -w, -c and
makes sure first and last selection argument is a digit.
*/
int check_input(int argc, char * argv[]){
	if(argc != 3){
                printf("expected 2 command line arguments.\n");
                return 1;
        }
        else if(strcmp(argv[1], "-l") != 0 && strcmp(argv[1], "-w") != 0 && strcmp(argv[1], "-c") != 0){
                printf("Invalid delimiter type.\n");
                return 1;
        }
	else{
		if(isDigit(argv[2][0]) || isDigit(argv[2][strlen(argv[2]) - 1])){
			printf("Invalid selection.\n");
			return 1;
		}
        	for(int i = 0; i < strlen(argv[2]); i++){
                	if( isDigit(argv[2][i]) == 1 && argv[2][i] != ',' && argv[2][i] != '-'){
				printf("Invalid selection.\n");
                                return 1;
        		}
        	}
		return 0;
	}
	return 0;
}

/*
This function implement the -l flag of
scut. buffer is the string of input, nums is
an array of integer with number of columns to
be extracted and open is the size of the array
of integers.
*/
void scut_l(char buffer[], int nums[], int open){
	for(int i = 0; i < open; i++){
		printf("%c ", buffer[nums[i] - 1]);
	}
}

/*
This function tell the program if the line we are
iterating over needs to be printed to the console.
It returns 0 if true and 1 if otherwise.
*/
int isPresent(int elem, int nums[],int open){
	for(int i = 0; i < open; i++){
		if(elem == nums[i]){
			return 0;
		}
	}
	return 1;
}

/*
This function implements the -c flag of scut
where the nth string in buffer is printed out,
while splitting the string by the commas,
buffer is the string of input, nums is
an array of integer with number of columns to
be extracted and open is the size of the array
of integers.
*/
void scut_c(char buffer[], int nums[], int open){
	int elem = 1;
	for(int i = 0; i < strlen(buffer); i++){
		if(isPresent(elem, nums, open) == 0 && buffer[i] != ','){
			printf("%c", buffer[i]);
		}
		else if(buffer[i] == ',' && isPresent(elem, nums , open) == 0){
			printf(" ");
			elem++;
		}
		else if(buffer[i] == ','){
			elem++;
		}
	}
}

/*
This function implements the -w flag of scut
where the nth string in buffer is printed out,
while splitting the string by the whitespaces,
buffer is the string of input, nums is
an array of integer with number of columns to
be extracted and open is the size of the array
of integers.
*/
void scut_w(char buffer[], int nums[], int open){
	int elem = 1;
	if(buffer[strlen(buffer) - 1] == '\n'){
		buffer[strlen(buffer) - 1] = '\0';
	}
        for(int i = 0; i < strlen(buffer); i++){
		if(isPresent(elem, nums, open) == 0 && buffer[i] != ' '){
        		printf("%c", buffer[i]);
		}
		else if(buffer[i] == ' ' && isPresent(elem, nums, open) == 0){
			printf(" ");
			elem++;
		}
		else if(buffer[i] == ' '){
			elem++;
		}
	}
}

/*
This function helps the program specifically when
dashes are being dealt with. This function
finds what is in the other side of the
hyphen, i.e the second bound. argv is the
command line argument and i is the index of
the hyphen.
*/
int find_end(char * argv[], int i){
	int sum = argv[2][i + 1] - '0';
	for(int j = 1; (i + j + 1) < strlen(argv[2]); j++){
		if(isDigit(argv[2][i + j]) == 0 && isDigit(argv[2][i + j + 1]) == 0){
			int num1 = argv[2][i + j] - '0';
			int num2 = argv[2][i + j + 1] - '0';
			sum = (num1 * 10) + num2;
		}
		else{
			return sum;
		}
	}
	return sum;
}

int main(int argc, char * argv[]){
	int retval = check_input(argc, argv);
	int nums[128];                                         // all the columns to be extracted from are put in an array
	int open = 0;
	int sum = 0;
	if(retval == 0){
		for(int i = 0; i < strlen(argv[2]);i++){       // the column numbers are being transferred to an array
			if(i + 1 < strlen(argv[2]) && isDigit(argv[2][i]) == 0 && isDigit(argv[2][i + 1]) == 0){
				int num1 = argv[2][i] - '0';
				int num2 = argv[2][i + 1] - '0';
				sum = (num1 * 10) + num2;
				if((9 < sum) && (sum < 100)){
					i += 1;
				}
				else if (sum >= 100){
					i += 2;
				}
			}
			else if(argv[2][i] == '-'){
				int start = sum;
				int end = find_end(argv, i);
				for(int j = start; j <= end; j++){
					nums[open] = j;
					open++;
				}
			}
			else if(i >= 0 && isDigit(argv[2][i]) == 0 && argv[2][i + 1] != '-' && argv[2][i - 1] != '-'){
				nums[open] = argv[2][i] - '0';
				open++;
			}
			else if(isDigit(argv[2][i]) == 0 && argv[2][i + 1] == '-'){
				sum = argv[2][i] - '0';
			}
		}
		char buffer[102];
		if(strcmp(argv[1], "-l") == 0){
                	while(scanf("%101s", buffer) != EOF){
			        scut_l(buffer, nums, open);
			        printf("\n");
                        }
		}
		else if(strcmp(argv[1], "-c") == 0){
                        while(scanf("%101s", buffer) != EOF){
				scut_c(buffer, nums, open);
				printf("\n");
			}
                }
		else if(strcmp(argv[1], "-w") == 0){
                        while(fgets(buffer, 101, stdin) != NULL){
				scut_w(buffer, nums, open);
				printf("\n");
			}
		}
	}
	else{
		return 1;
	}
	return 0;
}

