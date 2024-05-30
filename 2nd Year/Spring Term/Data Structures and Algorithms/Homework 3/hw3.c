#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct heap{
    int *heapArray;
    int currentSize;
    int capacity;
}Heap;

/*
@brief Creates a heap with the given capacity.

@param capacity The capacity of the created heap.

@return Newly created heap.
*/
Heap* createHeap(int capacity){
    Heap *newHeap;
    newHeap = (Heap*) malloc(sizeof(Heap));
    newHeap->currentSize=0;
    newHeap->capacity = capacity;
    newHeap->heapArray = (int*) malloc(sizeof(int) * (capacity+1));
    return newHeap;
}

/*
@brief Prints the matrix of the priority queues. It's actually not a matrix so, after the size of the queue is exceeded, it prints the "imaginary" parts of the matrix with -1.

@param **priorityQueues An array of pointers to the priority queues which are basically heaps.
@param row The amount of rows in the matrix, also the number of priority queues.
@param column The amount of columns in the matrix, also the max capacity the user can give to the priority queues.

@return
*/
void printMatrix(Heap** priorityQueues,int row,int column){
    int i,j,placeholder = -1;
    for(i=0;i<row;i++){
        j=1;
        while(j<=priorityQueues[i]->currentSize){
            printf("%4d|",priorityQueues[i]->heapArray[j]);
            j++;
        }
        while(j<=column){
            printf("%4d|",placeholder);
            j++;
        }
        printf("\n");
    }
    printf("\n");
}

/*
@brief Swaps the integers that are held in the addresses.

@param *a Pointer to the first integer.
@param *b Pointer to the second integer.

@return
*/
void swap(int* a, int* b){ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

/*
@brief Heapifies an array. Starts from the last indexed parent, heapifies the subtree of it. Then moves on to the other parents and heapifies them recursively.

@param *heapArray The array to be heapified.
@param size The size of the array.
@param root The root of the subtree that is to be heapified.

@return
*/
void maxHeapify(int *heapArray, int size, int root){
    int i,largest,leftChild,rightChild;
    for(i=size/2;i>=1;i--){
        largest = i;
        leftChild = i * 2;
        rightChild = i * 2 + 1;
        if(leftChild <=size && heapArray[leftChild] > heapArray[largest]) largest = leftChild;
        if(rightChild <= size && heapArray[rightChild] > heapArray[largest]) largest = rightChild;
        if(largest != i){
            swap(&heapArray[i],&heapArray[largest]);
            maxHeapify(heapArray,size,largest);
        }
    }
}
/*
@brief Takes an array of pointers to the priority queues which are formed with heaps, then heapifies all of the queues.

@param **priorityQueues Holds the pointers to the priority queues.
@param row The amount of pointers to the priority queues in the array.

@return
*/
void maxHeapifyAll(Heap** priorityQueues,int row){
    int i;
    for(i=0;i<row;i++){
        maxHeapify(priorityQueues[i]->heapArray,priorityQueues[i]->currentSize,1);
    }
}

/*
@brief Extracts the largest value in the heap, i.e. the first element. Then max-heapifies it back.

@param *heap The heap that it's max value is going to be extracted.

@return The value of the maximum value in the heap.
*/
int extractMax(Heap *heap){
    int max = heap->heapArray[1];
    if(heap->currentSize == 1){
    	heap->heapArray[1] = -1;
	}
	else{
		heap->heapArray[1] = heap->heapArray[heap->currentSize];
	}
    
    heap->currentSize = heap->currentSize - 1;
    maxHeapify(heap->heapArray,heap->currentSize,1);
    return max;
}

/*
@brief Simple quick sort alghoritm. Appoints a pivot, elements that are smaller then the pivot are moved to it's left, and elements that are bigger are moved to it's right. After the elements that are right to it are bigger and that are left to it are lesser. Then appoints a new pivot and partitions the array to it's subarrays and repeats the same process until the array is sorted.

@param *arr The array to be sorted.
@param low The start point of the array/subarray.
@param high The end point of the array/subarray.

@return
*/
void quickSort(int *arr, int low, int high){ 
    int pivot,i,j,partitionIndex;
    if (low < high) { 
        pivot = arr[low]; 
        i = low; 
        j = high; 
        while (i < j) { 
            while (arr[i] <= pivot && i <= high - 1){ 
                i++; 
            } 
            while (arr[j] > pivot && j >= low + 1){ 
                j--; 
            } 
            if (i < j){ 
                swap(&arr[i], &arr[j]); 
            } 
        } 
        swap(&arr[low], &arr[j]); 
        partitionIndex = j;
        quickSort(arr, low, partitionIndex - 1); 
        quickSort(arr, partitionIndex + 1, high); 
    } 
}

/*
@brief Binary search alghoritm. Takes an array and divides it into two halves. Checks if the searched number is bigger or smaller than the middle. Divides the next part according to it. Only works if the array is already sorted.

@param *arr The array which a value is searched.
@param low The start point of the array/subarray.
@param high The end point of the array/subarray.
@param x The searched value.

@return The index of the searched value in the array. If not found, returns -1.
*/
int binarySearch(int *arr, int low,int high,int x){
    int middle;
    while (low <= high) {
        middle = low + (high - low) / 2;
        if (arr[middle] == x) return middle;
        if (arr[middle] < x) low = middle + 1;
        else high = middle - 1;
    }
    return -1;
}

/*
@brief Searches the array from the start to it's end, a brute-force alghoritm. Used if the array isn't sorted, or can't be sorted for some reason.

@param *arr The array which a value is searched.
@param size The size of the array.
@param x The value that's being searched.

@return The index of the searched value in the array. If not found, returns -1.
*/
int linearSearch(int *arr, int size, int x){
    int i=0;
    while(i < size){
        if(arr[i] == x) return i;
        i++;
    }
    return -1;
}

/*
@brief Fills the priority queues with all-unique random numbers. To achieve uniqueness, uses an array to hold used values. Generates a new random number, and searches the array for that number using binary search. If it's not in the array, it gets added. Everytime a new value is added, quick-sorts that array. This sorting and binary searching process is useful if the number of values that are going to be in the priority queues are too high.

@param **priorityQueues The array of pointers to the priority queues.
@param maxValue The limit to the values that are getting generated.
@param row The amount of priority queues.
@param *usedValues The array that holds the values that are already generated.

@return
*/
void fillTheQueues(Heap **priorityQueues,int maxValue,int row,int *usedValues){
    srand(time(NULL));
    int i,j;
    int randomNumber, usedValuesLength=0;
    for(i=0;i<row;i++){
        j=1;
        while(j<=priorityQueues[i]->capacity){
            randomNumber = rand() % maxValue;
            while(binarySearch(usedValues,0,usedValuesLength, randomNumber) != -1){
                randomNumber = rand() % maxValue;
            }
            usedValues[usedValuesLength] = randomNumber;
            quickSort(usedValues,0,usedValuesLength);
            usedValuesLength++;
            priorityQueues[i]->heapArray[j] = randomNumber;
            priorityQueues[i]->currentSize = priorityQueues[i]->currentSize + 1;
            j++;
        }
    }
    
}

/*
@brief The main game function. Max-heapifies all the priority queues first. Then looks through all the priority queues' maximum values, and extracts the highest value from it's respective priority queue. This process is repeated until all the priority queues are empty. Then the emptied priority queues gets printed in order.

@param **priorityQueues The array of pointers to the priority queues.
@param row The amount of priority queues.
@param The "imaginary" number of columns in the matrix, also the maximum allowed length for a queue.

@return
*/
void game(Heap **priorityQueues, int row,int column){
    printf("Matrix with random numbers:\n");
    printMatrix(priorityQueues,row,column);
    maxHeapifyAll(priorityQueues,row);
    printf("Matrix with max heapified queues:\n");
    printMatrix(priorityQueues,row,column);
    int game = 1, i,max,extractedValue, *emptiedQueues,emptyCounter=0;
    emptiedQueues = (int*) malloc(sizeof(int) * row);
    while(game == 1){
        max = -1;
        printf("The maximum value of every queue: ");
        for(i=0;i<row;i++){
            if(priorityQueues[i]->currentSize > 0){
                if(max == -1) max = i;
                else if(priorityQueues[i]->heapArray[1] > priorityQueues[max]->heapArray[1])
                    max = i;
                printf("%d  ",priorityQueues[i]->heapArray[1]);
            }
        }
        printf("\n");
        if(max == -1){
            printf("The game is over, every priority queue is empty.\n");
            game = 0;
        }
        else{
            extractedValue = extractMax(priorityQueues[max]);
            if(priorityQueues[max]->currentSize < 1 && linearSearch(emptiedQueues,emptyCounter,max) == -1){
                emptiedQueues[emptyCounter] = max;
                emptyCounter++;
            }
            printf("Selected value: %d\n\nNew matrix:\n",extractedValue);
            printMatrix(priorityQueues,row,column);
        }
        
    }
    printf("The queues that are emptied in order: ");
    for(i=0;i<emptyCounter;i++){
        printf("%d ",emptiedQueues[i] + 1);
    }
        

}

int main(){
    int row,column,i, maxValue,capacity, *usedValues, actualMatrixSize=0;
    Heap** priorityQueues;
    printf("How many priority queues do you want: ");
    scanf("%d",&row);
    printf("Maximum length of a priority queue: ");
    scanf("%d",&column);
    maxValue = row * column * 2; //designed a max value
    priorityQueues = (Heap**) malloc(sizeof(Heap*) * row);
    
    printf("Give the length of the following priority queues:\n");
    for(i=0;i<row;i++){
        printf("Max length of queue %d: ", i + 1);
        scanf("%d", &capacity);
        while(capacity > column){
            printf("This is not a valid length. Please enter the maximum length you defined earlier.\nMax length of queue %d: ", i+1);
            scanf("%d",&capacity);
        }
        actualMatrixSize += capacity;
        priorityQueues[i] = createHeap(capacity);
    }
    usedValues = (int*) malloc(sizeof(int) * actualMatrixSize);
    fillTheQueues(priorityQueues,maxValue,row,usedValues);
    game(priorityQueues,row,column);

    //free the allocated memories
    free(usedValues); 
    for(i=0;i<row;i++){
        free(priorityQueues[i]->heapArray);
        free(priorityQueues[i]);
    }
    free(priorityQueues);

    printf("\nShutting down...\n");



    return 0;
}
