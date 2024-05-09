#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 60
#define LIMIT 10000

typedef struct stackNode{
    char data[MAX_WORD_LENGTH];
    struct stackNode *next;
}StackNode;

typedef struct stack{
    int elementNumber;
    StackNode *topNode;
}Stack;

typedef struct queueNode{
    Stack *stackStored;
    struct queueNode *next;
}QueueNode;

typedef struct queue{
    QueueNode *front;
    QueueNode *rear;
    int elementNumber;
}Queue;

/*
@brief Pushes a new node to an existing stack.

@param *pushedNode The node that is to be pushed.
@param *stack The stack that the node is getting pushed into.

@return
*/
void pushToStack(StackNode *pushedNode, Stack *stack){
    if(stack->elementNumber == 0){
        stack->topNode = pushedNode;
    }
    else{
        pushedNode->next = stack->topNode;
        stack->topNode = pushedNode;
    }
    stack->elementNumber = ( stack->elementNumber + 1 );
}

/*
@brief Pops the top element from the given stack and returns it.

@param *stack Pointer to the stack.

@return The top node.
*/
StackNode* popFromStack(Stack *stack){
    if(stack->elementNumber == 0){
        printf("Cannot pop from the stack, it's already empty!\n");
        return NULL;
    }
    StackNode *poppedNode = stack->topNode;
    stack->topNode = stack->topNode->next;
    stack->elementNumber = (stack->elementNumber - 1);
    return poppedNode;
}

/*
@brief Adds a new element to a queue.

@param *queue Pointer to the queue.
@param *newRear Pointer to the element that is getting added into the queue. It's called newRear because it's the new last element.

@return
*/
void enqueue(Queue *queue, QueueNode *newRear){
    if(queue->elementNumber == 0){
        queue->front = newRear;
        queue->rear = newRear;
    }
    else{
        queue->rear->next = newRear;
        queue->rear = newRear;
    }
    queue->elementNumber = queue->elementNumber + 1;
}

/*
@brief Takes the first element of the queue out of it and returns it.

@param *queue Pointer to the said queue.

@return The first element in the queue.
*/
QueueNode* dequeue(Queue *queue){
    if(queue->elementNumber == 0){
        printf("Cannot dequeue, the queue is already empty!\n");
        return NULL;
    }
    QueueNode *dequeuedNode = queue->front;
    queue->front = queue->front->next;
    queue->elementNumber = queue->elementNumber - 1;
    if(queue->elementNumber == 0)
        queue->rear = NULL;
    return dequeuedNode;
}

/*
@brief Creates a new node for a stack. Assigns the taken string into the "data" attribute of the node.

@param *data A string. It gets assigned to the "data" field of the StackNode.

@return A new created StackNode.
*/
StackNode *createStackNode(char *data){
    StackNode *newNode;
    newNode = (StackNode*) malloc(sizeof(StackNode));
    strcpy(newNode->data,data);
    newNode->next = NULL;
    return newNode;
}

/*
@brief Creates a new stack element and assigns it's attributes to default values.

@param

@return The newly created pointer to the Stack.
*/
Stack* createStack(){
    Stack *newStack;
    newStack = (Stack*) malloc(sizeof(Stack));
    newStack->elementNumber = 0;
    newStack->topNode = NULL;
    return newStack;
}

/*
@brief Creates a QueueNode and returns a pointer to it to be added or removed from the queue whenever desired.

@param *stackStored A pointer to a stack that is going to be stored in the created node.

@return A pointer to the newly created QueueNode.
*/
QueueNode* createQueueNode(Stack* stackStored){
    QueueNode* newNode;
    newNode = (QueueNode*) malloc(sizeof(QueueNode));
    newNode->next = NULL;
    newNode->stackStored = stackStored;
    return newNode;
}

/*
@brief Creates a new Queue and assigns it's attributes to a default value.

@param

@return A pointer to the newly created Queue.
*/
Queue* createQueue(){
    Queue *newQueue;
    newQueue = (Queue*) malloc(sizeof(Queue));
    newQueue->front = NULL;
    newQueue->rear = NULL;
    newQueue->elementNumber = 0;
    return newQueue;
}

/*
@brief Takes a stack that is going to be copied. Copies that stack to a new memory that is allocated. It does this by firstly creating a reversed version of the stack, and then reversing that stack again. A new StackNode gets created with the data taken and gets pushed to the new, copied stack. New stack gets returned.

@param *data The data to be pushed into the new copied stack.
@param *toBeCopied Pointer to the stack that's getting copied.

@return A pointer to the new copied stack.
*/
Stack* copyStack(char *data, Stack *toBeCopied){
    Stack *newStack = createStack();
    StackNode *tempNode = toBeCopied->topNode;
    Stack *reverseStack = createStack();
    while(tempNode != NULL){
        pushToStack(createStackNode(tempNode->data),reverseStack);
        tempNode = tempNode->next;
    }
    tempNode = reverseStack->topNode;
    while(tempNode != NULL){
        pushToStack(createStackNode(tempNode->data),newStack);
        tempNode = tempNode->next;
    }
    while(reverseStack->topNode != NULL){
        StackNode *freedNode = popFromStack(reverseStack);
        free(freedNode);
    }
    free(reverseStack);
    pushToStack(createStackNode(data),newStack);
    return newStack;
}

/*
@brief Frees the given stack from the memory. Every node gets freed one by one. The stack itself gets freed at the end.

@param *stack Pointer to the stack that's getting freed.

@return
*/
void freeStack(Stack *stack){
    StackNode *current = stack->topNode, *deletedNode = current;
    while(current->next != NULL){
        current = current->next;
        free(deletedNode);
        deletedNode = current;
    }
    free(current);
    free(stack);
}

/*
@brief Frees the given QueueNode. It first frees the stack in the node via the freeStack function, and then frees the node itself.

@param *node Pointer to the node that's getting freed.

@return
*/
void freeQueueNode(QueueNode *node){
    freeStack(node->stackStored);
    free(node);
}

/*
@brief Frees the given queue. It first frees every node in the queue via the freeQueueNode function, then frees the queue itself.

@param *queue Pointer to the queue that's getting freed.

@return
*/
void freeQueue(Queue *queue){
    QueueNode *current = queue->front, *deletedNode = current;
    while(current->next != NULL){
        current = current->next;
        freeQueueNode(deletedNode);
        deletedNode = current;
    }
    freeQueueNode(current);
    free(queue);
}

/*
@brief Prints the given stack's data to the screen.

@param *stack Pointer to the stack.

@return
*/
void printStack(Stack *stack){
    StackNode *current = stack->topNode;
    while(current->next != NULL){
        printf("%s<-",current->data);
        current = current->next;
    }
    printf("%s",current->data);
    printf("\n");
}

/*
@brief Prints the given queue's data to the screen.

@param *queue Pointer to the queue.

@return
*/
void printQueue(Queue *queue){
    QueueNode *current = queue->front;
    printf("\nThe queue: \n");
    while(current != NULL){
        printStack(current->stackStored);
        current = current->next;
    }
    printf("\n");
}

/*
@brief Checks if the checked word is eligble to be used in the program. It achieves it by checking if it has the same length as the checker word. Then checks how many letter differences it has with the checker word. If the checked word has only 1 difference and it has the same amount of letters with the checker, the function returns 1, meaning it's eligble. Otherwise, it returns 0.

@param *checker The string that checks the checked word.
@param *checked The string that's getting checked.

@return If eligble, returns 1. Otherwise, returns 0.
*/
int checkIfEligble(char* checker, char* checked){
    if(strlen(checker) != strlen(checked))
        return 0;
    int word_length = strlen(checker), differenceCount = 0, i;
    for(i=0;i<word_length;i++){
        if(checker[i] != checked[i]){
            differenceCount++;
            if(differenceCount > 1)
                return 0;
        } 
    }
    if(differenceCount == 1){
        return 1;
    }
    else{
        return 0;
    }
           
}

/*
@brief Checks if the searchedWord has been used before. If it's not used, returns 1. Otherwise, returns 0.

@param *searchedWord The word that's getting searched in an array of words.
@param usedWords[][] The array of words that contains all the used words before.
@param arrayLength The length of the array.

@return 0 if the word is used. 1 if it's not used.
*/
int wordIsNotUsed(char *searchedWord,char usedWords[LIMIT][MAX_WORD_LENGTH], int arrayLength){
    int i;
    for(i=0;i<arrayLength;i++){
        if(!strcmp(searchedWord,usedWords[i]))
            return 0;
    }
    return 1;
}

/*
@brief Scans the dictionary for every word. Checks every word for their eligblity, if so then checks if the word is equal to the target word. If it is, the function confirms that the target has been found and returns 1. If not, checks if the word is used. If not used before, then the copyStack function gets runned, and the new stack gets added into the queue to be used later, the word gets added to the usedWords array.

@param *operatedStack The pointer to the stack that the function is operating on. The function takes the data of the top node in that stack in consideration everytime.
@param *queue The pointer to the queue that the stacks are getting added to.
@param *dictionary The pointer to the file that contains the words that the function scans.
@param usedWords[][] The array that contains all the used words.
@param *usedWordsLength The pointer to the int value that counts the amount of words in the usedWords array.
@param *target The target string.

@return If the word is found at the end of scanning: returns 1. Otherwise, returns 0.
*/
int scanTheDictionary(Stack *operatedStack, Queue *queue, FILE *dictionary, char usedWords[LIMIT][MAX_WORD_LENGTH], int *usedWordsLength, char* target){
    char wordBuffer[MAX_WORD_LENGTH];
    Stack *temporaryStackHolder;
    fseek(dictionary, 0, SEEK_SET); //get back to the start point everytime the function gets runned
    while(fgets(wordBuffer,MAX_WORD_LENGTH - 1,dictionary)){
        wordBuffer[strcspn(wordBuffer,"\n")] = '\0'; //remove the newline char if the string has one to avoid problems

        if(checkIfEligble(operatedStack->topNode->data,wordBuffer) == 1){
           // printf("%s\t",wordBuffer);
            if(!strcmp(target,wordBuffer)){   
                temporaryStackHolder = copyStack(wordBuffer,operatedStack);           
                printf("Target found. The word ladder: \n");
                printStack(temporaryStackHolder);
                return 1;
            }
            if(wordIsNotUsed(wordBuffer,usedWords,*usedWordsLength) == 1){
                temporaryStackHolder = copyStack(wordBuffer,operatedStack);
                enqueue(queue,createQueueNode(temporaryStackHolder) );
                strcpy(usedWords[*usedWordsLength],wordBuffer);
                *usedWordsLength = (*usedWordsLength + 1);
                //printf("Found words: %d\n", *usedWordsLength);
            }
        }
    }
    return 0; //return 0 to inform the loop that the word is still not found
}

/*
@brief The game function. Returns nothing and takes nothing. Takes the source and target words. Checks if the game is playable. If it is, creates a first stack with the source word, enqueues it to the queue. While the target is not found, the queue is not empty, or the limit of the used words is not reached, it calls the scanTheDictionary over and over again, sending it the lates dequeued element. Frees the queue at the end.

@param

@return
*/
void game(){
    char sourceWord[MAX_WORD_LENGTH], targetWord[MAX_WORD_LENGTH], usedWords[LIMIT][MAX_WORD_LENGTH];
    int usedWordsLength = 0;
    short targetFound = 0;
    Queue *queue = createQueue();
    Stack *operatingOn;
    // QueueNode *dequeuedNode;
    FILE *dictionary = fopen("dictionary.txt","r");
    
    printf("Source word: ");
    scanf(" %s",sourceWord);
    printf("Target word: ");
    scanf(" %s",targetWord);

    if(strlen(sourceWord) != strlen(targetWord)){ //if the target and source words are not of equal size, go back to the main menu.
        printf("There can be no word ladder if the target and the source words are not of equal size.\n");
        return;
    }

    Stack *firstStack = createStack();
    StackNode *firstNode = createStackNode(sourceWord);
    pushToStack(firstNode,firstStack);
    QueueNode *firstQueueNode = createQueueNode(firstStack);
    enqueue(queue,firstQueueNode);

    while(targetFound == 0){ //keeps the cycle running until either the target is found, the queue is empty, or the limit is reached.
        //printQueue(queue);
        operatingOn = dequeue(queue)->stackStored;
        targetFound = scanTheDictionary(operatingOn,queue,dictionary,usedWords,&usedWordsLength, targetWord);
        freeStack(operatingOn);
        if(queue->elementNumber == 0){
            printf("Couldn't find the word.\n");
            targetFound = 1; 
        }      
        if(usedWordsLength == LIMIT){
            printf("The limit for the amount of words searched has been reached and the target word couldn't be found.\n");
            targetFound = 1;
        }
    }
    printf("\nNumber of scanned words: %d\n", usedWordsLength);
    //printQueue(queue);
    fclose(dictionary);
    freeQueue(queue);
}


int main(){
    short playingGame = 1;
    while(playingGame==1){
        game();
        printf("If you want to play again, type in 1. Otherwise, type in another number: ");
        scanf("%d", &playingGame);
    }
    printf("Exiting the program.\n");
    return 0;
}