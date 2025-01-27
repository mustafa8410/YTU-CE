#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct heapElement{
    int value;
    int subarrayIndex;
}HeapElement;

typedef struct minHeap{
    HeapElement *heapArray;
    int currentSize;
    int capacity;
}Heap;


/*
@brief Swaps the heap elements that are held in the addresses.

@param *a Pointer to the first element.
@param *b Pointer to the second element.

@return
*/
void swapHeap(HeapElement* a, HeapElement* b){ 
    HeapElement temp = *a; 
    *a = *b; 
    *b = temp; 
} 

/*
@brief Swaps the integers that are held in the addresses.

@param *a Pointer to the first integer.
@param *b Pointer to the second integer.

@return
*/
void swapInt(int* a, int* b){ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

/*
@brief Sorts the given array with insertion sort algorithm.

@param *array The array to be sorted.
@param arraySize The size of the array.
@param low The lower bound of the array.
@param high The upper bound of the array.

@return
*/
void insertionSort(int *array, int arraySize, int low, int high){
    int i,j,key;
    for(i=low+1; i<=high; i++){
        key = array[i];
        j = i-1;
        while(j>=low && array[j] > key){
            array[j+1] = array[j];
            j = j-1;
        }
        array[j+1] = key;
    }
}

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
    newHeap->heapArray = (HeapElement*) malloc(sizeof(HeapElement) * (capacity+1));
    return newHeap;
}

/*
@brief Heapifies an array. Starts from the last indexed parent, heapifies the subtree of it. Then moves on to the other parents and heapifies them recursively.

@param *heapArray The array to be heapified.
@param size The size of the array.
@param root The root of the subtree that is to be heapified.

@return
*/
void heapify(HeapElement *heapArray, int size, int root){
    int i,smallest,leftChild,rightChild;
    for(i=size/2;i>=1;i--){
        smallest = i;
        leftChild = i * 2;
        rightChild = i * 2 + 1;
        if(leftChild <=size && heapArray[leftChild].value < heapArray[smallest].value) smallest = leftChild;
        if(rightChild <= size && heapArray[rightChild].value < heapArray[smallest].value) smallest = rightChild;
        if(smallest != i){
            swapHeap(&heapArray[i],&heapArray[smallest]);
            heapify(heapArray,size,smallest);
        }
    }
}

/*
@brief Extracts the smallest value in the heap, i.e. the first element.

@param *heap The heap that it's minimum value is going to be extracted.

@return The value of the minimum value in the heap.
*/
HeapElement extractMin(Heap *heap){
    HeapElement min = heap->heapArray[1];
    if(heap->currentSize == 1){
    	heap->heapArray[1].value = -1;
	}
	else{
		heap->heapArray[1] = heap->heapArray[heap->currentSize];
	}
    
    heap->currentSize = heap->currentSize - 1;
    // heapify(heap->heapArray,heap->currentSize,1);
    return min;
}


/*
@brief Merges the k sorted subarrays into a single sorted array. It copies the elements in the main array to the temporary arrays, then it creates a heap with the first elements of the subarrays. Then it extracts the minimum element from the heap and assigns it to the main array. Then it takes the next element from the subarray that the minimum element is taken from and assigns it to the heap. This process continues until the heap is empty.

@param *array The array that the subarrays are going to be merged into, also the main array.
@param *startingIndices The starting indices of the subarrays in the main array.
@param k The number of subarrays.
@param arraySize The size of the main array.

@return
*/
void merge(int* array, int* startingIndices, int k, int arraySize){
    Heap* heap = createHeap(k);
    HeapElement element;
    int i, j = 0, length, sorted = 0, **tempArray = (int**) malloc(sizeof(int*) * k), *trackIndices = (int*) malloc(sizeof(int) * k);
    for(i=0;i<k;i++){ // get the length of each subarray and copy them to the temporary arrays' 0th index.
        length = startingIndices[i+1] - startingIndices[i];
        tempArray[i] = (int*) malloc(sizeof(int) * (length + 1));
        tempArray[i][0] = length;
        for(j=1;j<=length;j++){ // copy the subarray to the temporary array.
            tempArray[i][j] = array[startingIndices[i] + j - 1];
        }
        trackIndices[i] = 2; // all first elements will be assigned to the heap so 2 is assigned.
    }
    for(i=0;i<k;i++){ // assign the first elements of the subarrays to the heap.
        element.value = tempArray[i][1];
        element.subarrayIndex = i;
        heap->heapArray[i+1] = element;
        heap->currentSize++;
    }
    heapify(heap->heapArray, heap->currentSize, 1);
    while(heap->currentSize > 0){ // extract the minimum element from the heap and assign it to the main array and continue the loop until the heap is empty.
        HeapElement minimum = extractMin(heap);
        array[startingIndices[0] + sorted] = minimum.value;
        sorted++;
        if(trackIndices[minimum.subarrayIndex] <= tempArray[minimum.subarrayIndex][0]){
            element.value = tempArray[minimum.subarrayIndex][trackIndices[minimum.subarrayIndex]];
            element.subarrayIndex = minimum.subarrayIndex;
            heap->heapArray[heap->currentSize + 1] = element;
            heap->currentSize++;
            trackIndices[minimum.subarrayIndex]++;
        }
        heapify(heap->heapArray, heap->currentSize, 1);

    }
    free(heap->heapArray);
    free(heap);
    for(i=0;i<k;i++)
        free(tempArray[i]);
    free(tempArray);
    free(trackIndices);
}

/*
@brief Sorts the given array with k-way merge sort algorithm. It splits the array into k subarrays and sorts them recursively. Then it merges the subarrays into a single sorted array. If the size of the array is less than k, it sorts the array with insertion sort algorithm. Starting indices of the subarrays are kept in a separate array.

@param *array The array to be sorted.
@param low The lower bound of the array.
@param high The upper bound of the array.
@param k The number of subarrays that the array is going to be split into.
@param arraySize The size of the array.

@return
*/
void kWayMergeSort(int* array, int low, int high, int k, int arraySize){
    if(arraySize >= k){ // if the array size is greater or equal than k, it can be splitted into k subarrays.
        int i, splitLow, splitHigh, stepSize = arraySize / k, remainder = arraySize % k;

        // starting indices of the subarrays will be saved in an array. A notable thing is that the high value is increased by 1 while saving to state that the last subarray ends at array[high].
        int* startingIndices = (int*) malloc((k+1) * sizeof(int));
        startingIndices[0] = low;
        startingIndices[k] = high+1;

        for(i=1; i< k; i++){ // find each starting index for each subarray.
            startingIndices[i] = startingIndices[i-1] + stepSize;
            if(remainder > 0){
                startingIndices[i] = startingIndices[i] + 1;
                remainder--;
            }
            splitLow = startingIndices[i-1];
            splitHigh = (startingIndices[i] - 1);
            kWayMergeSort(array, splitLow, splitHigh, k, (splitHigh - splitLow + 1));
        }
        kWayMergeSort(array, (splitHigh + 1), high, k, (high - splitHigh));
        merge(array, startingIndices, k, arraySize);  
        free(startingIndices);
    }
    else if(arraySize > 1)
        insertionSort(array, arraySize, low, high);

}

/*
@brief Shuffles the given array by starting from the last element and swapping it with a randomly selected element.

@param *array The array to be shuffled.
@param size The size of the array.

@return
*/
void shuffle(int *array, int size) {
	int temp, i, j;
    for (i=size-1; i>0; i--) {
        j = rand() % (i + 1);
        swapInt(&array[i], &array[j]);
    }
}

/*
@brief Generates a random array with the given size. It creates an array with the numbers from 1 to N, then shuffles it.

@param N The size of the array.

@return The generated array.
*/
int* generateRandomArray(int N){
    int i, *array = (int*) malloc(sizeof(int) * N);
    for(i=0;i<N;i++)
        array[i] = (i+1);
    shuffle(array, N);
    return array;
}

/*
@brief Saves the given array of integers in another array and returns it.

@param *array The array to be saved.
@param N The size of the array.

@return The saved array.
*/
int* saveArray(int* array, int N){
    int i, *newArray = (int*) malloc(sizeof(int) * N);
    for(i=0;i<N;i++)
        newArray[i] = array[i];
    return newArray;
}

/*
@brief Checks if the array is sorted properly by comparing each element with the next.

@param *array The array to be checked.
@param N The size of the array.

@return 1 if the array is sorted properly, 0 otherwise.
*/
int checkSorted(int* array, int N){
    int i;
    for(i=0;i<N-1;i++){
        if(array[i] > array[i+1])
            return 0;
    }
    return 1;
}

/*
@brief Computes the average time for each k value for the given N value.

@param *times The array that holds the times for each k value.
@param N The size of the array.

@return
*/
void computeAverageTime(double* times, int N){
    int i;
    for(i=0; i<9; i++){
        times[i] = times[i] / 10.0;
        printf("The average time for N = %d, k = %d is %.7f\n", N, i+2, times[i]);
    }

}

/*
@brief Clears the time array by assigning 0 to each element.

@param *times The array that holds the times for each k value.

@return
*/
void clearTimeArray(double* times){
    int i;
    for(i=0; i<9; i++){
        times[i] = 0;
    }
}

/*
@brief Runs the merge sort algorithm for different N-sized arrays and different values of k. It generates random arrays 10 times for each N value, sorts them with k-way merge sort algorithm and checks if the array is sorted properly. It also prints the time taken for sorting the array.

@return
*/
void runMergeSort(){
    int i, k, N = 100, *array, *savedArray;
    double *times = (double*) calloc(9, sizeof(double)), time;
    clock_t start, end;
    while(N <= 10000000){
        for(i=0; i<10; i++){ // 10 different arrays for each N value
            printf("\n%d. iteration for N: %d\n", i+1, N);
            array = generateRandomArray(N);
            savedArray = saveArray(array, N);
            for(k=2; k<=10; k++){
                printf("\nN: %d, k: %d\n", N, k);
                start = clock();
                kWayMergeSort(array, 0, N-1, k, N);
                end = clock();
                time = (double)(end - start) / CLOCKS_PER_SEC;
                times[k-2] += time;
                if(checkSorted(array, N))
                    printf("Array is sorted successfully.\n");
                else
                    printf("There's been an error while sorting the array.\n");
                printf("Time: %.7f\n", time);
                array = saveArray(savedArray, N);
            }
            free(array);
            free(savedArray);
            //scanf(" %d", &ph);
        }
        computeAverageTime(times, N);
        N *= 10;
        clearTimeArray(times);
    }
    free(times);
}

int main(){
    srand(time(0));
    runMergeSort();
    return 0;
}
