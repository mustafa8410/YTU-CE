#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILE_LENGTH 50
#define TYPE_LENGTH 6
#define NAME_LENGTH 20
#define BUFFER_SIZE 100

typedef struct node{
    char type[TYPE_LENGTH];
    char name[NAME_LENGTH];
    int normalAddress;
} Node;

typedef struct hashTable{
    Node** table;
    int m;
    int count;
} HashTable;

Node* createNode(char* type, char* name);
HashTable* createHashTable(int m);
int isPrime(int value);
int determineTheTableSize(int count, int debugMode);
int hornerMethod(char* str);
int h1(int key, int m);
int h2(int key, int m);
int hashFunction(int key, int i, int m);
int lookup(HashTable* hashTable, char* name);
int insert(HashTable* hashTable, char* type, char* name);
int getRidOfWhiteSpace(char* str);
int findTotalVariableCount(FILE* file);
void findVariableCountInLine(char* line, int *variableCount);
void parseLine(char* line, HashTable* hashTable);
void parseFile(FILE* file, HashTable* hashTable);
void printHashTable(HashTable* hashTable);



int main(int argc, char* argv[]){
    char fileName[FILE_LENGTH];
    FILE* file;
    int debugMode;
    if(argc < 2)
        debugMode = 0;
    else if(!strcmp(argv[1], "debug"))
        debugMode = 1;
    else if(!strcmp(argv[1], "normal"))
        debugMode = 0;
    else{
        printf("Error: Invalid argument.\n");
        return -1;
    }
    //debugMode = 1;
    printf("Please provide the file name: ");
    scanf(" %s", fileName);
    //printf("File name:%s\n", fileName);
    file = fopen(fileName, "r");
    if(file == NULL){
        printf("Error: File could not be opened.\n");
        return -1;
    }
    int variableCount = findTotalVariableCount(file);
    int tableSize = determineTheTableSize(variableCount, debugMode);
    fseek(file, 0, SEEK_SET);
    //printf("check");
    HashTable* hashTable = createHashTable(tableSize);
    parseFile(file, hashTable);
    if(debugMode){
        printf("Hashtable size: %d\tVariable count: %d\n", hashTable->m, hashTable->count);
        printHashTable(hashTable);
    }


    fclose(file);
    return 0;
}

/*
@brief Creates a new node for the hash table.

@param type: Type of the variable.
@param name: Name of the variable.

@return Node*: Pointer to the created node.
*/
Node* createNode(char* type, char* name){
    Node *newNode = (Node*) malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->type, type);
    newNode->normalAddress = -1;
    return newNode;
}


/*
@brief Creates a new hash table with the given size.

@param m: Size of the hash table.

@return HashTable*: Pointer to the created hash table.
*/
HashTable* createHashTable(int m){
    HashTable *newTable = (HashTable*) malloc(sizeof(HashTable));
    newTable->count = 0;
    newTable->m = m;
    newTable->table = (Node**) malloc(m * sizeof(Node*));
    int i;
    for(i=0; i<m; i++){
        newTable->table[i] = NULL;
    }
    return newTable;
}


/*
@brief Determines whether the given value is prime or not.

@param value: Value to be checked.

@return int: 1 if the value is prime, 0 otherwise.
*/
int isPrime(int value){
    if(value <= 1)
        return 0;
    int i;
    for(i=2; i<=sqrt(value); i++)
        if(value % i == 0)
            return 0;
    return 1;
}

/*
@brief Determines the size of the hash table according to the given variable count.

@param count: Total number of variables found in the first check of the file.
@param debugMode: Debug mode flag.

@return int: Size of the hash table.
*/
int determineTheTableSize(int count, int debugMode){
    int size = 2 * count + 1;
    while(!isPrime(size))
        size++;
    return size;
}

/*
@brief Calculates the hash value of the given string with the Horner's method.

@param str: String to be hashed.

@return int: Hash value of the string.
*/
int hornerMethod(char* str){
    int hash = 0;
    int i;
    for(i=0; i<strlen(str); i++)
        hash = (hash * 31) + str[i];
    return hash;
}

/*
@brief First hash function of the double hashing.

@param key: Key to be hashed.
@param m: Size of the hash table.

@return int: Result of the first hash function.
*/
int h1(int key, int m){
    return (key % m);
}

/*
@brief Second hash function of the double hashing.

@param key: Key to be hashed.
@param m: Size of the hash table.

@return int: Result of the second hash function.
*/
int h2(int key, int m){
    return (1 + ( key % (m-3) ) );
}

/*
@brief Calculates the index of the given key with the double hashing.

@param key: Key to be hashed.
@param i: The value that gets incremented if the previous address was full.
@param m: Size of the hash table.

@return int: Index of the key.
*/
int hashFunction(int key, int i, int m){
    return ( ( h1(key,m) + i*h2(key,m) ) % m );
}

/*
@brief Checks whether the given variable is in the hash table or not. If present, returns the index of the variable. Otherwise, returns -1.

@param hashTable: Pointer to the hash table.
@param name: Name of the variable to be checked.

@return int: Index of the variable if it's in the hash table, -1 otherwise.
*/
int lookup(HashTable* hashTable, char* name){
    int key = hornerMethod(name);
    int i, index;
    for(i=0; i<hashTable->m; i++){
        index = hashFunction(key, i, hashTable->m);
        if(hashTable->table[index] == NULL)
            return -1;
        else if(!strcmp(hashTable->table[index]->name, name))
            return index;
    }
    return -1;
}

/*
@brief Inserts the variable with the given name and type to the hash table if it's not already present.

@param hashTable: Pointer to the hash table.
@param type: Type of the variable.
@param name: Name of the variable.

@return int: Index of the inserted variable if it's inserted successfully, -1 otherwise.
*/
int insert(HashTable* hashTable, char* type, char* name){
    int key = hornerMethod(name);
    int i, index;
    if(lookup(hashTable, name) >= 0){
        printf("Error: Variable with name %s is already declared.\n", name);
        return -1;
    }
    index = hashFunction(key, 0, hashTable->m);
    if(hashTable->table[index] == NULL){
        hashTable->table[index] = createNode(type, name);
        hashTable->count++;
        hashTable->table[index]->normalAddress = index;
        // if(debugMode)
        //     printf("Variable %s of type %s is inserted to the table at index: %d\n", name, type, index);
        return index;
    }
    int normalAddress = index;
    for(i=1; i<hashTable->m; i++){
        index = hashFunction(key, i, hashTable->m);
        if(hashTable->table[index] == NULL){
            hashTable->table[index] = createNode(type, name);
            hashTable->table[index]->normalAddress = normalAddress;
            hashTable->count++;
            // if(debugMode)
            //     printf("Variable %s of type %s is inserted to the table at index: %d\n", name, type, index);
            return index;
        }
    }
    printf("Error: Table is full.\n");
    return -1;
}

/*
@brief Gets rid of the white spaces at the beginning and the end of the given string.

@param str: String to be processed.

@return int: Index of the first non-white space character.
*/
int getRidOfWhiteSpace(char* str){
    int startIndex = strspn(str, " \t\n\r"), len = strlen(str);
    str[strcspn(str, "\t\n\r")] = '\0';
    if(str[len - 1] == '\0')
    	len--;
    while(len > 0 && str[len-1] == ' ')
        len--;
    str[len] = '\0';
    return startIndex;
}

/*
@brief Finds the assumed total number of variables in the file at first check.

@param file: Pointer to the file.

@return int: Total assumed number of variables.
*/
int findTotalVariableCount(FILE* file){
    char buffer[BUFFER_SIZE];
    int variableCount = 0;

    while(fgets(buffer, BUFFER_SIZE, file) != NULL){
    	//printf("%s", buffer);
        findVariableCountInLine(buffer, &variableCount);
    }
    //printf("Variable count: %d", variableCount);
    return variableCount;
}

/*
@brief Finds the number of variables in the given line and increments the total variable count.

@param line: Line to be processed.
@param variableCount: Pointer to the total variable count.

@return
*/
void findVariableCountInLine(char* line, int *variableCount){
	//printf("Working on: %s\n", line);
    int i = getRidOfWhiteSpace(line);
    char buffer[BUFFER_SIZE];
    strcpy(buffer, (line + i));
    //printf("%s\n", line+i);
    //printf("New buffer: %s\n", buffer);
    char* token = strtok(buffer, " ,;");
    if(strcmp(token, "int") != 0 && strcmp(token, "char") != 0 && strcmp(token, "float") != 0)
        return;
    int count = 0;
    token = strtok(NULL, " ,;");
    while(token != NULL){
        i = getRidOfWhiteSpace(token);
        //printf("Current token: %s\n", token);
        if(token[i] == '_')
            count++;
            //printf("Count: %d\n", count);
        token = strtok(NULL, " ,;");
    }
    (*variableCount) = (*variableCount) + count;
    //printf("Variable count: %p", variableCount);
}

/*
@brief Parses the given line. If the line contains variable declarations, inserts them to the hash table. Otherwise, checks whether the used variables are declared before or not, and also checks for type mismatches.

@param line: Line to be parsed.
@param hashTable: Pointer to the hash table.

@return
*/
void parseLine(char* line, HashTable* hashTable){
    int i = getRidOfWhiteSpace(line);
    char buffer[BUFFER_SIZE], type[TYPE_LENGTH], name[NAME_LENGTH];
    strcpy(buffer, line + i);
    char* token = strtok(buffer, " ,;");
    if(strcmp(token, "int") == 0 || strcmp(token, "char") == 0 || strcmp(token, "float") == 0){ // variables are getting declared
        strcpy(type, token);
        token = strtok(NULL, " ,;");
        while(token != NULL){
            i = getRidOfWhiteSpace(token);
            if(token[i] == '_'){
                strcpy(name, token + i);
                insert(hashTable, type, name);
            }
            token = strtok(NULL, " ,;");
        }
        return;
    }
    // no variables are getting declared
    int typeGiven = 0, index;
    while(token != NULL){
        i = getRidOfWhiteSpace(token);
        if(token[i] == '_'){
            strcpy(name, token + i);
            index = lookup(hashTable, name);
            if(index >= 0){
                if(!typeGiven)
                    strcpy(type, hashTable->table[index]->type);
                else if(strcmp(type, hashTable->table[index]->type) != 0)
                    printf("Error: Type mismatch for variable %s: %s is a %s but a %s was used earlier in the line.", name, name, hashTable->table[index]->type, type);

            }
            else
                printf("Error: Variable %s is not declared.\n", name);
        }
        token = strtok(NULL, " ,;");
    }
}

/*
@brief Parses the given file by reading it line by line. Calls the parseLine function for each line.

@param file: Pointer to the file.
@param hashTable: Pointer to the hash table.

@return
*/
void parseFile(FILE* file, HashTable* hashTable){
    char buffer[BUFFER_SIZE];
    while(fgets(buffer, BUFFER_SIZE, file) != NULL){
    	//printf("%s\n", buffer);
        parseLine(buffer, hashTable);
    }
}

/*
@brief Prints the hash table. Used for debug mode. Prints the variables and their types, and also the indexes they are inserted to. Also prints the supposed indexes of the variables.

@param hashTable: Pointer to the hash table.

@return
*/
void printHashTable(HashTable* hashTable){
    int i;
    for(i=0; i<hashTable->m; i++){
        if(hashTable->table[i] != NULL)
            printf("Variable %s of type %s is calculated to be inserted at %d, and it's inserted to %d.\n", hashTable->table[i]->name, hashTable->table[i]->type, hashTable->table[i]->normalAddress, i);
    }
    for(i=0; i<hashTable->m; i++){
        printf("Index %d: ", i);
        if(hashTable->table[i] != NULL)
            printf("Variable name: %s, Type: %s\n", hashTable->table[i]->name, hashTable->table[i]->type);
        else
            printf("Empty\n");
    }
}


