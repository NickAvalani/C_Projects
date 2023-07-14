/*
Name: Nick Avalani
Course: CSC 352
Description: This program determines the number of possible
locations a chess piece (king, pawn or brigadier) can be on
when it has a specified number of moves. 
*/

#include <stdlib.h>
#include <stdio.h>


void pawn(int moves){
        int loc = moves + 1;
        printf("possible locations: %d\n", loc);
}

void king(int moves){
        int loc = (2 * moves + 1) * (2 * moves + 1);
        printf("possible locations: %d\n", loc);
}

void brigadier(int moves){
        int loc = 0;
        int sum = 0;
        for( int i = 1; i <= moves; i++){
                sum += i;
        }
        loc = 4 * sum + 1;
        printf("possible locations: %d\n", loc);
}

int main(void){
	char type;
	int moves;
	printf("Enter piece type (k, b, p):\n");
	scanf("%c", &type);
	printf("Enter number of moves:\n");
	scanf("%d", &moves);

	if(moves == 0){
		printf("possible locations: 1");
	}
	else{
		if(type == 'p'){
			pawn(moves);
		}
		else if (type ==  'k'){
			king(moves);
		}
		else if(type == 'b'){
			brigadier(moves);
		}
	}
}



