#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 60 //Maximum allowed number of characters in an address.
#define MAX_FILE 30 //Maximum allowed number of characters in the name of a file.

struct pageNode{
    char address[MAX_LENGTH];
    int requestCounter;
    struct pageNode* previousNode;
    struct pageNode* nextNode;
};

/*
@brief Prints the linked list.

@param *head Pointer to the head node of the linked list, function starts to print from it and moves on to the last node.

@return
*/
void printTheList(struct pageNode *head){
    if(head == NULL)
        return;
    struct pageNode *current = head; //assigning a variable to the head node to traverse freely. 
    while(current->nextNode != NULL){  //traverse the list until the last node.
        printf("%s:%d  ",current->address,current->requestCounter);
        current = current->nextNode;
    }
    printf("%s:%d\n",current->address,current->requestCounter);
}

/*
@brief Clears the cache by starting from the head node of the list, goes all the way to the last. Also resets the counter back to 0.

@param **head Pointer to the pointer of the head node. Function assigns a variable to the node, and frees the linked list starting from there. Also assigns NULL to it at the end.
@param **last Pointer to the pointer of the last node. Gets assigned NULL to it at the end.
@param *counter Pointer to the counter variable of the amount of nodes in the linked list. Function resets the counter, so the program knows the cache has no elements in it after the function.

@return
*/
void clearCache(struct pageNode** head, struct pageNode **last, unsigned int *counter){
    if(*head == NULL){
        printf("The cache is already clear.\n");
        return;
    }
    struct pageNode* current = *head; //assigning a variable to the head node to traverse freely. 
    struct pageNode* next; //going to be needed to assign the current variable to this when the node that's pointed by current variable gets freed.
    while(current->nextNode != NULL){ //traverse the list until the last node.
        next = current->nextNode;
        free(current);
        current = next;
    }
    free(current);
    *counter = 0;
    *head = NULL;
    *last = NULL;

    printf("The cache is clear.\n");
}

/*
@brief Inserts an independent node, whether it's getting replaced or a new created one, to the head of the list.

@param **head Pointer to the pointer to the head node. Function updates the head node, so it's double pointer.
@param *newHead Pointer to the node that is getting inserted to the head of the list. Some of the fields of the node are getting updated, so it's a pointer.

@return
*/
void insertNodeToHead(struct pageNode** head, struct pageNode* newHead){
    if(*head == newHead) return;
    (*head) -> previousNode = newHead;
    newHead -> nextNode = *head;
    *head = newHead;
}

/*
@brief Removes a node from the linked list. The removed node may get inserted to the head, or it may be gone forever. Function updates the previous and next node pointer fields of the node, and it's neighbouring nodes.

@param *node Pointer to the node that is getting removed from the list.

@return
*/
void removeNode(struct pageNode *node){
    if(node->previousNode != NULL) //checks if the node that's getting removed has a previous node to avoid problems.
        node->previousNode->nextNode = node->nextNode;
            
    if(node->nextNode != NULL) //checks if the node that's getting removed has a previous node to avoid problems.
        node->nextNode->previousNode = node->previousNode;
            
    node->nextNode = NULL;
    node->previousNode = NULL;
}
/*
@brief Creates a new node for the linked list.

@param *addresName The address of the page, a field of the node.

@return The created node.
*/
struct pageNode* createNode(char *addressName){
    struct pageNode* newNode;
    newNode = (struct pageNode*) malloc(sizeof(struct pageNode));  //allocates memory for the node that is pointed by the newNode variable.
    strcpy(newNode->address,addressName);
    newNode->requestCounter = 1;
    newNode->nextNode = NULL;
    newNode->previousNode = NULL;
    return newNode;
}

/*
@brief Searches for the address input taken from the user. Searches the linked list for the address. If a node that contains the address doesn't exist, the function creates one and inserts it to the head of the list, and if the number of nodes in the list are already at the capacity given by the user, then the function removes the last node. Else if it founds a node that has the address, it increases it's requestCounter field. If the new requestCounter field of the node gets above the threshold taken by the user in the main menu, then the function inserts the node to the head of the list.

@param *address Address of the page taken from the user. Function searches for this address in the nodes of the cache.
@param **head Pointer to the pointer to the head node. It is needed for replacing the head node and searching the list.
@param **last Pointer to the pointer to the last node. It is needed for replacing the last node of the list when the capacity is exceeded.
@param capacity Total capacity of the cache taken from the user. If the number of nodes exceed it, last node is to be removed.
@param *counter Pointer to the counter of the nodes in the cache. It gets updated, so a pointer is assigned.
@param threshold The threshold for the nodes in the cache. If a node's requestCounter gets above it, the respective node is to be inserted at the head of the linked list.

@return
*/
void searchForAddress(char* address, struct pageNode** head, struct pageNode** last, unsigned int capacity, unsigned int *counter,unsigned int threshold ){
    struct pageNode* current = *head;  //assigning a variable to the head node to traverse freely. 
    
    while( ( current -> nextNode != NULL ) && ( strcmp(current->address, address) != 0 ) ){ //traverses the cache to find the node that contains the address.
        current = current->nextNode;                                                        //the loop breaks when it reaches the last node, or it finds the node with the address.
    }
    if(!strcmp(current->address,address)){ // if we find the node, increase the requestCounter. if the requestCounter passes the threshold, insert the node to the head.
        current->requestCounter++;
        if( ( current->requestCounter > threshold ) && current != *head ){
            if(current == *last){
                *last = (*last)->previousNode;
            }
            removeNode(current);
            insertNodeToHead(head,current);
        }
    }
    else{  // if we can't find the node, create one and insert it to the head. if the counter is already equal to the capacity, remove the last node.
        struct pageNode *newNode = createNode(address);
        insertNodeToHead(head,newNode);
        if(*counter == capacity){  //if the cache has reached it's capacity
            struct pageNode *newLastNode = (*last)->previousNode;
            removeNode(*last);
            free(*last);
            *last = newLastNode;
        }
        else{
            *counter = *counter + 1;
        }
    }
}

/*
@brief This function gets executed when the user chooses to give the address inputs manually. If the user types in -1, the process ends. If the user types in 0, cache gets cleared. Any other inputs are considered as address inputs. If the counter is 0, so there are no nodes in the cache, a new node gets created and the head and the last nodes are assigned to this node. Else, searchForAddress function gets executed. printTheList function gets executed after every input to update the user about the state of the cache.

@param capacity Total capacity of the cache taken from the user. It's used in searchForAddress function, this function simply passes the variable to it.
@param threshold The threshold for the nodes in the cache. It's used in searchForAddress function, this function simply passes the variable to it.
@param **head Pointer to the pointer to the head node. It's needed for the case where the cache is empty, and also gets passed to several functions.
@param **last Pointer to the pointer to the last node. It's needed for the case where the cache is empty, and also gets passed to the searchForAddress function.
@param *counter Pointer to the counter of the nodes in the cache. It gets updated, so a pointer is assigned. It also gets passed to clearCache and searchForAddress functions.

@return
*/
void giveInputManually(unsigned int capacity, unsigned int threshold, struct pageNode** head, struct pageNode** last, unsigned int *counter){
    char input[MAX_LENGTH];  //input taken from the user.
    short processContinuing = 1; //the variable to check if the process is still continuing.
    printf("Give the requested pages' addresses as an input. Maximum length is %d. Type in '-1' to end the process. Type in 0 to clear the cache anytime.\n",MAX_LENGTH);
    while(processContinuing == 1){
        printf("\nLast node's address: %s\n",(*last)->address);
        printf("Address: ");
        scanf(" %s", input);
        if( !strcmp(input,"-1") ){  //if the user types in -1
            printf("Ending the process.\n");
            processContinuing = 0;
        }
        else if( !strcmp(input,"0") ){ //if the user types in 0
            clearCache(head,last, counter);
        }
        else{ //if the input is an address
            if(*counter == 0){ //cache is empty
                *head = createNode(input);
                *last = *head;
                *counter = (*counter + 1);
            }
            else{
                searchForAddress(input,head,last,capacity,counter,threshold);
            }

            printTheList(*head);
        }
    }
    printf("Would you like to clear the cache? 0: No, 1: Yes\n");
    scanf("%hd",&processContinuing);
    if(processContinuing == 1) clearCache(head,last,counter);
    printf("Proccess has ended. Returning to the main menu.\n\n");
}

/*
@brief This function gets executed when the user chooses to read the addresses line by line from a file, preferably a .txt file. The function takes the name of the file from the user, and reads the addresses line by line. If the cache is empty, a new node is created with the address in the first line and the head and the last nodes are assigned to it. Else, the function calls in the searchForAddress function.

@param capacity Total capacity of the cache taken from the user. It's used in searchForAddress function, this function simply passes the variable to it.
@param threshold The threshold for the nodes in the cache. It's used in searchForAddress function, this function simply passes the variable to it.
@param **head Pointer to the pointer to the head node. It's needed for the case where the cache is empty, and also gets passed to several functions.
@param **last Pointer to the pointer to the last node. It's needed for the case where the cache is empty, and also gets passed to the searchForAddress function.
@param *counter Pointer to the counter of the nodes in the cache. It gets updated, so a pointer is assigned. It also gets passed to clearCache and searchForAddress functions.

@return
*/
void readFromFile(unsigned int capacity, unsigned int threshold, struct pageNode **head, struct pageNode **last, unsigned int *counter){
    char address[MAX_LENGTH];
    char fileName[MAX_FILE];
    int decision;
    FILE *file;
    do{
    printf("File name: ");
    scanf(" %s", fileName);
    file = fopen(fileName,"r");
    if(file == NULL)
        printf("An error occured while opening the file. Please try again.\n\n");
    }while(file == NULL);
    while( fgets(address,MAX_LENGTH - 1,file) ){ //loop gets executed until we reach the end of the file. reading line by line.
        address[strcspn(address,"\n")] = '\0';
        if(*counter == 0){
            *head = createNode(address);
            *last = *head;
            *counter = (*counter + 1);
        }
        else{
            searchForAddress(address,head,last,capacity,counter,threshold);
        }
        printTheList(*head);
        printf("Last read: %s\n",address);
    }

    fclose(file);
    printf("Would you like to clear the cache? 0: No, 1: Yes\n");
    scanf("%d",&decision);
    if(decision == 1) clearCache(head,last,counter);
    printf("Proccess has ended. Returning to the main menu.\n\n");

}


int main(){
    short decision; //short variable to execute different functions according to the user's desire.
    unsigned int capacity, threshold, counter=0; //in order: max number of nodes allowed in the cache, threshold of every node before they get inserted to head, current number of nodes in the cache.
    struct pageNode *head = NULL, *last = NULL; //head and last nodes of the linked list.
    
    printf("Capacity of the cache: "); scanf("%u", &capacity);
    printf("Threshold: "); scanf("%u", &threshold);

    do{
        printf("Read from file: 0\nGive inputs manually: 1\nExit program: 2\nClear the cache: 3\nRequest Counter: 4\n");
        scanf("%hd",&decision);
        while(decision != 0 && decision != 1 && decision != 2 && decision != 3){
            printf("Please give a valid input.\n\n");
            printf("Read from file: 0\nGive inputs manually: 1\nExit program: 2\nClear the cache: 3\nRequest Counter: 4\n");
            scanf("%d",&decision);
        }
        switch (decision){
        case 0:
        readFromFile(capacity,threshold,&head,&last, &counter);
        printTheList(head);
        break;
        case 1:
        giveInputManually(capacity,threshold,&head,&last, &counter);
        printTheList(head);
        break;
        case 3:
        clearCache(&head,&last, &counter);
        break;
        case 4:
        printf("Counter: %u\n",counter);
        }
    }while(decision != 2); //the loop gets executed until the user decides to end the program by giving the input: 2


    clearCache(&head,&last, &counter); //clear the cache before closing the program to avoid memory leaks.
    printf("Exiting the program.\n");
    return 0;
}