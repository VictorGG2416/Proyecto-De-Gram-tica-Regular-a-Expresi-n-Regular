#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE_LENGTH 100

//Node structure for the linked list
typedef struct Node
{
	char *ruleIdentifier;
	char *productions;
	struct Node *next;
}Node;

Node * createNode(const char *ruleIdentifier, const char *production);
void appendNode(Node **head, const char *ruleIdentifier, const char *prouction);
void freelinkedlist(Node *head);
Node * createLinkedList(FILE *file);
void printList(Node *head);

void splitLine(const char *line, char *ruleIdentifier, char *production);

Node* findNode(Node *head, const char *ruleIdentifier);
void appendProduction(Node *node, const char *production);
void appendOrUpdateNode(Node **head, const char *ruleIdentifier, const char *production);