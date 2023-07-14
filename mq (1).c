/*
 * Programmer: Nick Avalani
 * Course: CSc 352, Fall 2022, Benjamin Dicken
 * Description: This code defines the functions that for the
 * M-Questions Game. The functions build the tree, add the questions
 * and answers in the nodes, frees the tree, and prints out its 
 * contents.
 */
#include <stdio.h>
#include <stdlib.h>
#include "mq.h"

/*
 * This helper function recursively traverses the tree and prints the
 * content of the tree.
 * Arguments: curr = node in the tree
 *            height = height of the node in the tree, starting at zero
 *            flag = if it is one, that indicates a yes, and no if its 0
 */
void print_helper(MQDecisionTreeNode* curr, int height, int flag){
	if(curr == NULL){
		//printf("Its Null\n");
		return;
	}
	
	if(height != 1){
		for(int i = 0; i < height - 1; i++){
			printf("    ");
		}
	}
	if(height >= 0){
		if(flag == 0){
			printf("-n-> ");
		}
		else if(flag == 1){
			printf("-y-> ");
		}
	}
	if(curr->yes == NULL){
		if(curr->num_answers > 0){
			printf("| ");
			for(int i = 0; i < curr->num_answers; i++){
				printf("%s", (curr->answers)[i]);
				printf(" | ");
			}
		}
		printf("\n");
		return;
	}
	else{
		printf("[%s]\n", curr->text);
		print_helper(curr->yes, height+1, 1);
		print_helper(curr->no, height+1, 0);

	}
}

/*
 * This function calls the recursive function that prints
 * the content of the tree
 * Arguments: root = root of the tree
 */
void MQ_print_tree(MQDecisionTree* root){
	//printf("Print Tree\n");
	print_helper(root->root, 0, -1);
}

/*
 * This helper function recursively inserts nodes to the
 * tree.
 * Arguments: root = root node of the tree
 *            node = question that needs to be inserted in the tree
 *            flag = flag is an int that is 1 if its a leaf node and 
 *            0 if otherwise
 * Returns: the root node of the tree after insertion
 */
MQDecisionTreeNode* insert_recur(MQDecisionTreeNode* root, char* node, int flag){
	//if(root == NULL && flag == 1){

	//}
	if(root == NULL){
		//printf("Created a node\n");
		MQDecisionTreeNode* question = malloc(sizeof(MQDecisionTreeNode));
		for(int i = 0; node[i] != '\0'; i++){
			(question->text)[i] = node[i];
		}
		(question->text)[strlen(node)] = '\0'; 
		question->num_answers = 0;
		question->answers = 0;
		question->yes = NULL;
		question->no = NULL;
		return question;
	}
	//printf("Created a child\n");
	root->yes = insert_recur(root->yes, node, 0);
	root->no = insert_recur(root->no, node, 0);
	return root;
}

/*
 * This function extracts the question from the input
 * file and passes the question into the recursive function
 * that adds the question as a node in the tree
 * Argument: file_name = name of the input file
 * Return: The pointer to the tree after all questions from
 * 	   the input file are inserted.
 */
MQDecisionTree* MQ_build_tree(char* file_name){ 
	FILE* input = fopen(file_name, "r");
	char buffer[128];
        int i = 0;
	MQDecisionTree* tree = malloc(sizeof(MQDecisionTree));
	tree->root = NULL;

	if(input != NULL){
        	while(fgets(buffer, 127, (FILE*)input) != NULL){       
                	if(i == 1){
				buffer[strlen(buffer) - 1] = '\0';
				//printf("buffer: %s\n", buffer);
                        	char* ptr = strtok(buffer, ",");
                        	while(ptr != NULL){
                                	//printf("Questions: %s\n", ptr);
					tree->root = insert_recur(tree->root, ptr, 0);
                                	ptr = strtok(NULL, ",");
                        	}
				//adding a leaf node
				tree->root = insert_recur(tree->root, "", 1);
                     
                	}
			i++;
       		}
	}
	fclose(input);
	return tree;
}

/*
 * This functions adding the answers to the questions
 * as leaf nodes to the tree
 * Arguments: tree = pointer to root node of the tree
 * 	      file_name = name of the input file
 */
void MQ_populate_tree(MQDecisionTree* tree, char* file_name){
	FILE* file = fopen(file_name, "r");
	int i = 0;
	char buffer[128];	
	if(file != NULL){
		//printf("in if stmt\n");
		while(fgets(buffer, 127, file) != NULL){
			//printf("in while loop\n");
			if(i > 1){
				char answer[128] = "";
				int len = 0;
				for(int j = 0; buffer[j] != ','; j++){
					answer[j] = buffer[j];
					len++;
				}	
				answer[len++] = '\0';
				MQDecisionTreeNode* curr = tree->root;

				while(buffer[len] != '\0'){
					if(buffer[len] == '0'){
						curr = curr->no;
					}
					else if(buffer[len] == '1'){
						curr = curr->yes;
					}
					len++;
				}
				if(curr -> answers == NULL){
					curr->answers = malloc(sizeof(char*)); 
					for(int i = 0; i < curr->num_answers; i++){
						(curr->answers)[i] = malloc(20 * sizeof(char));
					}
					//printf("Here in null");
				}
				(curr->answers)[curr->num_answers] = malloc(sizeof(answer) + 1);
				//printf("Here outside null");
				for(int j = 0; j < strlen(answer); j++){
					(curr->answers)[(curr->num_answers)][j] = answer[j];
				}
				(curr->answers)[curr->num_answers][strlen(answer)] = '\0';
				curr->num_answers++;
			}
			i++;
		}
	}
	fclose(file);
	return;
}

/*
 * This helper function frees the nodes in the tree
 * recursively, from the leaf to the root.
 * Arguments: root = root node of the tree
 */
void free_helper(MQDecisionTreeNode* root){
	if(root->yes == NULL && root->no == NULL){
		if((root->num_answers) != 0){
			//printf("leaf with answers: %d\n", (root->num_answers));
			for(int i = 0; i < (root->num_answers); i++){
				free((root->answers)[i]);
			}
			//free(*(root->answers));
			free(root->answers);
			free(root);
		}
		else{
			//printf("empty\n");
		}
	return;
	}
	else{
		free_helper(root->yes);
		free_helper(root->no);
		//printf("root is %s\n", (root->text));
		free(root);
		return;
	}
}

/*
 * This function passes the root node of the tree that can
 * free it from memory.
 * Arguments: tree = pointer to root node of the tree
 */
void MQ_free_tree(MQDecisionTree* tree){
	MQDecisionTreeNode* root = tree -> root;
	free_helper(root);
	free(tree);
}
