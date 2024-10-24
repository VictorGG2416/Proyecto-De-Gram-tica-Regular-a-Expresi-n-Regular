#include "main.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//Funtion to create a new node
Node* createNode(const  char *ruleIdentifier, const char *production)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->ruleIdentifier = strdup(ruleIdentifier); //store rule identifier
    newNode->productions = strdup(production);        //store production
    newNode->next = NULL;
    return newNode;
}

//Funtion to find a node by rule identifier
Node* findNode(Node *head, const char *ruleIdentifier)
{
    Node *current=head;
    while(current != NULL)
    {
        if(strcmp(current->ruleIdentifier, ruleIdentifier) == 0)
        {
            return current; //Return the node if found
        }
        current = current->next;
    }
    return NULL; //Return NULL if not  foundby
}

//Funcion to append a production to an existing node
void appendProduction(Node *node, const char *production)
{
    //Allocate new space to hold the existing productions + new production + separator " | "
    size_t newSize = strlen(node->productions) + strlen(production) + 4;
    node->productions = (char *)realloc(node->productions, newSize);

    // Append the newproduction whit " | " separator
    strcat(node->productions, " | ");
    strcat(node->productions, production);
}

//Funcion to aooend a new node or update an existing one
void appendOrUpdateNode(Node **head, const char *ruleIdentifier, const char *production)
{
    Node *existingNode = findNode(*head,ruleIdentifier);
    if(existingNode != NULL)
    {
        appendProduction(existingNode, production); //If found, append the production 
    }
    else
    {
        Node *newNode = createNode(ruleIdentifier, production); //Create a new node
        if(*head == NULL)
        {
            *head= newNode; //If the list is empty, set the head
        }
        else
        {
            Node *temp= *head;
            while(temp->next != NULL)
            {
                temp= temp->next;
            }
            temp->next= newNode; //Add the new node to the end of the list
        }
    }
}

//Function to free the  linked list
void freeLinkedList(Node *head)
{
    Node *current = head;
    Node *nextNode;
    while(current != NULL)
    {
        nextNode = current->next;
        free(current->ruleIdentifier); //Free the rule identifier string
        free(current->productions);    //Free the production string
        free(current);                 //Free the node
        current = nextNode;
    }
}

//Funtion to split a line into rule identifier and oridyction
void splitLine(const char *line, char *ruleIdentifier, char *production)
{
    //Find the position of "->"in the line
    const char *delimiter= strstr(line, "->");
    if(delimiter != NULL)
    {
        //copy the part before "->" into ruleIdentifire
        strncpy(ruleIdentifier, line, delimiter - line);
        ruleIdentifier[delimiter - line] = '\0'; //NULL-terminate the identifier

        //copy the part after "->" into production
        strcpy(production, delimiter + 2); //Skip the "->"
    }
}

//Function to create a linked list from the file
Node* createLinkedList(FILE *file)
{
    Node *head= NULL; //Head of the linked list
    char line[MAX_LINE_LENGTH];
    char ruleIdentifier[MAX_LINE_LENGTH];
    char production[MAX_LINE_LENGTH];

    //Read the file line by line and store each line in a new node or update an existing one
    while(fgets(line, sizeof(line), file))
    {
        //Remove the newline character if present
        line[strcspn(line, "\n")]= '\0';

        //Split the line into rule ifentifier and production 
        splitLine(line, ruleIdentifier, production);

        //Append or update the node in the linked list
        appendOrUpdateNode(&head, ruleIdentifier, production);
    }

    return head;
}

//Funtion to print the linked list
void printList(Node *head)
{
    Node *current = head;
    while(current != NULL)
    {
        printf("%s -> %s\n", current->ruleIdentifier, current->productions);
        current = current->next;
    }
}

int main()
{
    FILE *file= fopen("gramatica1.txt","r");
    if(file == NULL)
    {
        perror("Error openinh file");
        return 1;
    }

    Node *head= createLinkedList(file);

    fclose(file);

    //Ouput the contents of the linked list
    printList(head);

    //Free the linked list
    freeLinkedList(head);
    return 0;
}