#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE 50

typedef struct Edge{
    int distance;
    int destination;
    struct Edge* next;

}Edge;

typedef struct Vertex{
    int data;
    Edge* edgeListHead;
}Vertex;

typedef struct ShapeList{
    int* path;
    struct ShapeList *next;
    int perimeter;
}ShapeListNode;

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
@brief Creates a node for the linked list of the shapes.

@param pathLength The amount of edges of the shape.
@param *path The array that holds the ASCII values of the vertexes in the shape.
@param perimeter Perimeter of the shape.

@return Pointer to the node created.
*/
ShapeListNode *createShapeListNode(int pathLength, int* path, int perimeter){
    ShapeListNode* new = (ShapeListNode*) malloc(sizeof(ShapeListNode));
    new->path = (int*) malloc(sizeof(int) * pathLength);
    int i;
    for(i=0;i<pathLength;i++){
        new->path[i] = path[i];
    }
    new->next = NULL;
    new->perimeter = perimeter;
    return new;
}

/*
@brief Inserts the found shape in the graph to the linked list of the shapes.

@param pathLength The amount of edges of the shape.
@param **shapes The array that holds the pointers to the heads of the linked lists, each list holds shapes with a specific number of edges.
@param *newShape Pointer to the shape that's to be inserted.

@return
*/
void insertShape(int pathLength, ShapeListNode** shapes, ShapeListNode *newShape){
    int index = pathLength-3,i=0;
    ShapeListNode* current = shapes[index], *prev;
    prev = current;
    while(current != NULL){
        if(newShape->path[i] < current->path[i]){
            if(prev == current){
                newShape->next = current;
                shapes[index] = newShape;
                return;
            }
            else{
                prev->next = newShape;
                newShape->next = current;
                return;
            }
        }
        else if(newShape->path[i] == current->path[i]){
            i++;
        }
        prev = current;
        current = current->next;
    }
    if(prev == NULL){
        shapes[index] = newShape;
        return;
    }
    else{
        prev->next = newShape;
        return;
    }
}

/*
@brief Checks if the given shape is already found.

@param **shapes The array that holds the pointers to the heads of the linked lists, each list holds shapes with a specific number of edges.
@param pathLength The amount of edges of the shape.
@param *path The array that holds the ASCII values of the vertexes in the shape.

@return 1 if the shape is found, 0 if it's not.
*/
int shapeAlreadyFound(ShapeListNode** shapes, int pathLength, int* path) {
    if(pathLength < 3)
        return 0;
    ShapeListNode* current = shapes[pathLength - 3];
    int currentCopy[pathLength], pathCopy[pathLength], i,flag;
    for(i=0;i<pathLength;i++)
        pathCopy[i] = path[i];
    quickSort(pathCopy,0,pathLength-1);
    while(current!=NULL){
        
        for(i=0;i<pathLength;i++){
            //printf("Reached here.\n");
            currentCopy[i] = current->path[i];
        }
            
        quickSort(currentCopy,0,pathLength-1);
        i=0;
        flag=1;
        
        while(i<pathLength && flag==1){
            if(pathCopy[i] != currentCopy[i])
                flag = 0;
            else
                i++;
        }
        if(flag == 0)
            current = current->next;
        else
            return 1;
    }
    return 0;
    
}

/*
@brief Creates a vertex of the data structure graph.

@param data ASCII value of the char data that's stored in the vertex.

@return Pointer to the created vertex.
*/
Vertex* createVertex(int data){
    Vertex *new;
    new = (Vertex*) malloc(sizeof(Vertex));
    new->edgeListHead = NULL;
    new->data = data;
    return new;
}

/*
@brief Creates an edge, which connects two vertexes in a graph.

@param distance The distance between the two vertexes.
@param v1 ASCII value of the data stored in the vertex 1.
@param v2 ASCII value of the data stored in the vertex 2.

@return Two instances of the same edge, the only difference being the destination field so it can be added to the adjacency list of both of the vertexes respectively.
*/
Edge** createEdge(int distance, int v1, int v2){
    int i;
    Edge** instances;
    instances = (Edge**) malloc(sizeof(Edge*) * 2);
    for(i=0;i<2;i++){
        instances[i] = (Edge*) malloc(sizeof(Edge));
        instances[i]->next = NULL;
        instances[i]->distance = distance;
        //printf("%d\n",instances[i]->distance);
    }
    instances[0]->destination = v2;
    instances[1]->destination = v1;
    //printf("%c %c\n",instances[0]->destination, instances[1]->destination);
    return instances;
}

/*
@brief Initializes the adjacency list. The list holds the pointers to the vertexes.

@param vertexNumber Amount of vertexes in the graph.
@param *vertexDatas Array of integers, all hold the ASCII values of datas stored in the vertexes.

@return Adjacency List.
*/
Vertex** initializeAdjList(int vertexNumber, int* vertexDatas){
    Vertex** adjList;
    adjList = (Vertex**) malloc(sizeof(Vertex*) * vertexNumber);
    int i;
    for(i=0;i<vertexNumber;i++){
        adjList[i] = createVertex(vertexDatas[i]);
    }
    return adjList;
}

// void printAdjList(Vertex** adjList, int vertexNumber){
//     int i;
//     for(i=0;i<vertexNumber;i++){
//         printf("%c",adjList[i]->data);
//     }
// }

/*
@brief Prints all the found shapes in the graph in alphabetic order.

@param **foundShapes The array that holds the pointers to the heads of the linked lists, each list holds the found shapes with a specific number of edges.
@param vertexNumber Amount of vertexes in the graph.
@param shapeCount Amount of shapes that are found.
@param *shapeCounts Stores the amount of shapes that are found for every different type of shape respectively.

@return
*/
void printShapes(ShapeListNode** foundShapes, int vertexNumber, int shapeCount, int *shapeCounts){
    int i,j;
    ShapeListNode* current;
    printf("Number of total shapes: %d\n", shapeCount);
    for(i=0;i<vertexNumber-2;i++)
        printf("Number of shapes with %d edge: %d\n", i+3, shapeCounts[i]);
    for(i=0;i<vertexNumber-2;i++){
        current = foundShapes[i];
        while(current != NULL){
            printf("%d edged shape: %c", i+3, current->path[0]);
            for(j=1;j<i+3;j++){
                printf("-%c", current->path[j]);
            }
            printf("-%c, Perimeter: %d\n", current->path[0], current->perimeter);
            current = current->next;
        }
    }
}

/*
@brief Finds the index of the vertex that has the given data.

@param data ASCII value of the data that's stored in the searched vertex.
@param **adjacencyList Array which stores the pointers to the vertexes in the graph.
@param vertexNumber Amount of vertexes in the graph.

@return The index of the vertex with the data, -1 if there's no such vertex with data.
*/
int getIndex(int data, Vertex** adjacencyList, int vertexNumber){
    int i=0;
    while(i<vertexNumber){
        if(adjacencyList[i]->data == data)
            return i;
        i++;
    }
    return -1;
}

/*
@brief Creates and adds an edge to the vertexes with the given data. Gets the indexes of the vertexes with the data first. Then checks if any of the indexes are -1, which means that vertex doesn't exist. Then, adds that edge to the edge list of both of the vertexes respectively.

@param vertex1 ASCII value of the data that's stored in the vertex 1.
@param vertex2 ASCII value of the data that's stored in the vertex 2.
@param distance The length of the edge that's to be created and added.
@param **adjacencyList Array which stores the pointers to the vertexes in the graph.
@param vertexNumber Amount of vertexes in the graph.

@return 1 if the edge is added successfully, 0 if not.
*/
int addEdge(int vertex1, int vertex2, int distance, Vertex** adjacencyList,int vertexNumber){
    int i;
    int index1 = getIndex(vertex1, adjacencyList, vertexNumber);
    int index2 = getIndex(vertex2, adjacencyList, vertexNumber);
    //printf("%d %d ",index1,index2);
    if(index1 == -1 || index2 == -1)
        return 0;
    Edge **edgeInstances = createEdge(distance,vertex1,vertex2);
    edgeInstances[0]->next = adjacencyList[index1]->edgeListHead;
    adjacencyList[index1]->edgeListHead = edgeInstances[0];
    edgeInstances[1]->next = adjacencyList[index2]->edgeListHead;
    adjacencyList[index2]->edgeListHead = edgeInstances[1];
    return 1;
    // for(i=0;i<2;i++){
    //     free(edgeInstances[i]);
    // }
    // free(edgeInstances);
}

/*
@brief Frees the allocated memories to avoid memory leaks at the end of the program, just before shutting down.

@param **adjList Array which stores the pointers to the vertexes in the graph.
@param **shapes The array that holds the pointers to the heads of the linked lists, each list holds shapes with a specific number of edges.
@param vertexNumber Amount of vertexes in the graph.

@return
*/
void freeAll(Vertex** adjList, ShapeListNode** shapes, int vertexNumber){
    int i;
    Edge* currentEdge, *nextEdge;
    ShapeListNode *currentShape, *nextShape;
    for(i=0;i<vertexNumber;i++){
        currentEdge = adjList[i]->edgeListHead;
        while(currentEdge != NULL){
            nextEdge = currentEdge->next;
            free(currentEdge);
            currentEdge = nextEdge;      
        }
        free(adjList[i]);
        if(i<vertexNumber-2){
            currentShape = shapes[i];
            while(currentShape != NULL){
                nextShape = currentShape->next;
                free(currentShape->path);
                free(currentShape);
                currentShape = nextShape;
            }
            
        }
    }
    free(adjList);
}

/*
@brief Reads the edges from a file that the user provides. Every line in the .txt file means an edge. The first and two chars are the datas in the vertexes, the 3rd integer is the distance between them. The function casts the chars to their ASCII values, and calls the addEdge function for each one of them. Also checks if there's any mismatch between the user's input of the datas of the vertexes or the amount of edges that the user provides at the start and the edges that are scanned from the file.

@param **adjList Array which stores the pointers to the vertexes in the graph.
@param vertexNumber Amount of vertexes in the graph.
@param edgeNumber Amount of edges in the graph.

@return 1 if there's no mismatch between user inputs and the file scans, 0 if there is.
*/
int readEdgesFromFile(Vertex** adjacencyList, int vertexNumber, int edgeNumber){
    char vertex1, vertex2;
    int v1Int, v2Int,edgeCounter=0, vertexCorrect;
    char fileName[MAX_FILE];
    int distance;
    FILE *file;
    do{
        printf("Name of the file to read edges from: ");
        scanf(" %s", fileName);
        file = fopen(fileName, "r");
        if(file == NULL)
            printf("An error happened while opening the file. Please try again.\n");
    }while(file == NULL);
    while(!feof(file)){
        fscanf(file, "%c %c %d\n", &vertex1, &vertex2, &distance);
        v1Int = (int) vertex1;
        v2Int = (int) vertex2;
        vertexCorrect = addEdge(vertex1,vertex2,distance,adjacencyList,vertexNumber);
        if(!vertexCorrect)
            return 0;
        edgeCounter++;
    }
    printf("Reading complete.\n");
    fclose(file);

    if(edgeCounter != edgeNumber)
        return 0;
    else
        return 1;
}

/*
@brief The recursive function for the Depth First Search. It's used to find the shapes in the graph in this program. If the next edge that is to be used is connected to the first vertex of the path array, it calls shapeAlreadyFound function to check if that shape was found earlier. If not found, it adds the shape to the foundShapes list. If the edge isn't connected to the first vertex and not visited until now, it calls itself with some updated values.

@param **foundShapes The array which holds the pointers to the shape lists, each holds a different type of shapes.
@param **adjList Array which stores the pointers to the vertexes in the graph.
@param *visited An array that consists of 0's and 1's. 0 means that vertex is not visited and 1 means it's visited. Each vertex is represented with it's index in the adjList.
@param *path Array that holds the ASCII values of the datas of the vertexes that's been traveled until now.
@param pathLength The amount of vertexes that's been traversed until now.
@param perimeter The length of all the edges that's been traversed until now.
@param vertex The index of the vertex in the adjList.
@param *shapeCount Pointer to the counter of the shapes that are found until now.
@param vertexNumber Amount of vertexes in the graph.
@param *shapeCounts Holds the number of shapes that are found for each different type.

@return
*/
void dfs(ShapeListNode** foundShapes, Vertex** adjList,int* visited, int* path, int pathLength, int perimeter, int vertex, int* shapeCount, int vertexNumber, int* shapeCounts){
    int i;
    int nextIndex;
    Vertex* currentVertex = adjList[vertex];
    visited[vertex] = 1;
    path[pathLength] = currentVertex->data;
    //printf("Path[%d]: %c\n",pathLength,path[pathLength]);
    pathLength++;
    Edge* currentEdge = currentVertex->edgeListHead;
    //for(i=0;i<vertexNumber;i++){
        //printf("%d ",visited[i]);
    //}
    while(currentEdge != NULL){
        //printf("\n%c\t%d\n",currentEdge->destination,currentEdge->distance);
        nextIndex = getIndex(currentEdge->destination,adjList,vertexNumber);
        //printf("Next Index: %d\n", nextIndex);
        if(path[0] == currentEdge->destination && pathLength >= 3){
            //printf("Perimeter: %d\n",perimeter);
            if(!shapeAlreadyFound(foundShapes,pathLength,path)){
                //printf("New shape found!\n");
                (shapeCounts[pathLength-3])++;
                ShapeListNode* newShape = createShapeListNode(pathLength,path,(perimeter + currentEdge->distance));
                insertShape(pathLength,foundShapes,newShape);
                (*shapeCount)++;
            }
        }
        else if(visited[nextIndex] != 1){
            //printf("Ok.\n");
            dfs(foundShapes,adjList,visited,path,pathLength,(perimeter + currentEdge->distance),nextIndex,shapeCount,vertexNumber, shapeCounts);
        }


        currentEdge = currentEdge->next;
    }
    visited[vertex] = 0;
}

/*
@brief Finds the shapes by allocating memory for some of the arrays that are going to be used in the dfs function and calling the dfs function for every vertex in the graph.

@param **foundShapes The array which holds the pointers to the shape lists, each holds a different type of shapes.
@param **adjList Array which stores the pointers to the vertexes in the graph.
@param vertexNumber Amount of vertexes in the graph.
@param *shapeCounts Holds the number of shapes that are found for each different type.

@return The amount of shapes that are found in the graph.
*/
int findShapes(ShapeListNode** foundShapes, Vertex** adjList, int vertexNumber, int* shapeCounts){
    int* path = (int*) calloc(vertexNumber-1,sizeof(int));
    int* visited = (int*) calloc(vertexNumber,sizeof(int));
    int i, pathLength=0, perimeter=0,shapeCount = 0;
    for(i=0;i<vertexNumber;i++){
        dfs(foundShapes,adjList,visited,path,pathLength,perimeter,i, &shapeCount,vertexNumber,shapeCounts);
    }

    free(path);
    free(visited);
    return shapeCount;
}

int main(){
    int edgeNumber, vertexNumber,i, shapeCount, validInput;
    char dataInput;
    Vertex** adjacencyList;
    ShapeListNode** foundShapes;
    printf("Number of vertexes: ");
    scanf(" %d", &vertexNumber);
    printf("Number of edges: ");
    scanf(" %d", &edgeNumber);
    int vertexDatas[vertexNumber];
    for(i=0;i<vertexNumber;i++){
        printf("Data in vertex %d: ", i+1);
        scanf(" %c", &dataInput);
        vertexDatas[i] = (int) dataInput;
    }
    foundShapes = (ShapeListNode**) malloc(sizeof(ShapeListNode*) * (vertexNumber-2));
    for(i=0;i<vertexNumber-2;i++){
        foundShapes[i] = NULL;
    }
    int *shapeCounts = (int*) calloc(vertexNumber-2,sizeof(int));
    adjacencyList = initializeAdjList(vertexNumber,vertexDatas);
    validInput = readEdgesFromFile(adjacencyList,vertexNumber,edgeNumber);
    if(validInput==0){
        printf("Number of edges or the datas of the vertexes given doesn't match with the file provided.\n");
    }
    else{
        shapeCount = findShapes(foundShapes,adjacencyList,vertexNumber, shapeCounts);
        printShapes(foundShapes,vertexNumber,shapeCount, shapeCounts);
        freeAll(adjacencyList,foundShapes,vertexNumber);
    }
    printf("Shutting down...\n");
    return 0;
}