/*
* Name: Nick Avalani
* Course: CSC 352, Fall 2022, Benjamin Dicken 
* Description: This header file defines all the functions
* and structs used in the mq.c file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This struct defines the node in the tree
typedef struct MQDecisionTreeNode {
	char text[50];
	int num_answers;
	char** answers;
	struct MQDecisionTreeNode* yes;
	struct MQDecisionTreeNode* no;
}MQDecisionTreeNode;

// This node defines the pointer to the root of the tree
typedef struct MQDecisionTree {
	MQDecisionTreeNode* root;
}MQDecisionTree;

/*
 * This function calls the recursive function that prints
 * the content of the tree
 * Arguments: root = root of the tree
 */
void MQ_print_tree(MQDecisionTree* root);

/*
 * This function extracts the question from the input
 * file and passes the question into the recursive function
 * that adds the question as a node in the tree
 * Argument: file_name = name of the input file
 * Return: The pointer to the tree after all questions from
 *         the input file are inserted.
 */
MQDecisionTree* MQ_build_tree(char* file_name); //CHANGE RETURN TYPE TO MQDECISIONTREE*

/*
 * This functions adding the answers to the questions
 * as leaf nodes to the tree
 * Arguments: tree = pointer to root node of the tree
 *            file_name = name of the input file
 */
void MQ_populate_tree(MQDecisionTree* tree, char* file_name);

/*
 * This helper function frees the nodes in the tree
 * recursively, from the leaf to the root.
 * Arguments: root = root node of the tree
 */
void MQ_free_tree(MQDecisionTree* tree);
