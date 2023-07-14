/* 
 * Name: Nick Avalani
 * Course: CSC 352, Fall 2022, Benjamin Dicken
 * Description: This program implements the M-Questions
 * Game with the user and uses functions from the mq header
 * file to find the answer
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mq.h"

int main(int argc, char* argv[]){
	//printf("Argv[1]: %s\n", *argv+7);
	MQDecisionTree* root = MQ_build_tree(argv[1]);
	MQ_populate_tree(root, argv[1]);
	MQDecisionTreeNode* parent = root->root;
	char answer[2];
	while(parent != NULL){
		if((parent->yes)->yes == NULL){
			//printf("Just before leaf node\n");
			printf("%s (y/n)\n", (parent->text));
                	scanf("%s", answer);
			if(strcmp(answer, "y") == 0){
                 	       if((parent->yes)->num_answers == 0){
					printf("You got me :)");
					return 0;
				}
			       else{
				       	for(int i = 0; i < ((parent->yes)->num_answers); i++){
			       			printf("is it a %s? (y/n)\n", ((parent->yes)->answers)[i]);
						scanf("%s", answer);
						if(strcmp(answer, "y") == 0){
							printf("I guessed it!");
							break;
						}
						if(i == ((parent->yes)->num_answers) - 1 && strcmp(answer, "n") == 0){
							printf("You got me :)");
                                        		break;
						}	
					}
				}
                	}
                	else if(strcmp(answer, "n") == 0){
                        	if((parent->no)->num_answers == 0){
                                        printf("You got me :)");
					return 0;
                                }
                               else{
                                        for(int i = 0; i < ((parent->no)->num_answers); i++){
                                                printf("is it a %s? (y/n)\n", ((parent->no)->answers)[i]);
                                                scanf("%s", answer);
                                                if(strcmp(answer, "y") == 0){
                                                        printf("I guessed it!");
                                                        return 0;
                                                }
						if(i == ((parent->no)->num_answers) - 1 && strcmp(answer, "n") == 0){
                                                        printf("You got me :)");
                                                        return 0;
                                                }
                                        }
                                }
                	}
			break;
		}
		else{
			printf("%s (y/n)\n", (parent->text));
			scanf("%s", answer);
			if(strcmp(answer, "y") == 0){
				parent = parent->yes;	
			}
			else if(strcmp(answer, "n") == 0){
				parent = parent->no;
			}
		}
	}
	MQ_free_tree(root);
	exit(0);
}

