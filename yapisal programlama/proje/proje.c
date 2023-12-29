#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stddef.h>
#define MAX_USER 20
#define HIGH_SCORE 5
#define LENGTH 20
#define MAX_SIZE 6
#define MAX_BOARD_SIZE 16

typedef struct{
    char name[LENGTH];
    char surname[LENGTH];
    char username[LENGTH];
    char password[LENGTH];
}user;

typedef struct{
    int score;
    char username[LENGTH];
}highScore;

void importUsers(int *userCount, user *users){
    FILE *userFile = fopen("users.bin", "ab+");
    while(!feof(userFile)){
        fread(&users[(*userCount)],sizeof(user),1,userFile);
        *userCount = *userCount + 1;
    }
    fclose(userFile);
}

void importHighScores(highScore *highScores,int *highScoreCount){
    FILE *scoreFile = fopen("highScores.bin","ab+");
    int count=0,i;
    while(!feof(scoreFile)){
        fread(&highScores[count],sizeof(highScore),1,scoreFile);
        count++;
    }
    *highScoreCount = count;
}


int login(user *users, int totalUsers, user *currentPlayer){
    char username[LENGTH];
    char password[LENGTH];
    int i=0, flag=0;
    printf("Username: "); scanf(" %s", username);
    printf("Password: "); scanf(" %s", password);
    while(flag == 0 && i < totalUsers){
        if(strcmp(users[i].username, username) == 0 && strcmp(users[i].password,password) == 0){
            user p = users[i];
            *currentPlayer = p;
            printf("Welcome %s %s.\n", users[i].name,users[i].surname);
            flag=1;
        }i++;
    }
    if(!flag) printf("Wrong username or password.");
    return flag;
}

void signUp(int *totalUsers, user *users){
    if(*totalUsers < MAX_USER){
        user new;
        printf("Note that every data field should have at most 20 characters.\n");
        printf("Name: "); scanf(" %s",new.name);
        printf("Surname: "); scanf(" %s", new.surname);
        printf("Username: "); scanf(" %s", new.username);
        printf("Password: "); scanf(" %s",new.password);
        users[*totalUsers] = new; printf("Created a new account with username %s\n", new.username);
        *totalUsers = *totalUsers + 1;
    }else printf("There are already too much users. Please login to an existing account.\n");

}

void saveNewUsers(user *users, int userCount,int totalUsers){
    int i;
    FILE *userFile = fopen("users.bin","ab");
    for(i=userCount;i<totalUsers;i++){
        fwrite(&users[i],sizeof(user),1,userFile);
    }
    fclose(userFile);
}

int mainMenu(){
    int decision;
    printf("\n\n\n\n---------Main Menu---------\n\n"); 
    do{
    printf("1-High Scores\n2-How to play\n3-Play\n4-Exit");
    scanf("%d",&decision);
    if(decision < 1 || decision > 4) printf("Invalid input!");
    }while(decision < 1 || decision > 4);

    return decision;
}

char** readMatrix(char *fileName,int* r, int* c){
    FILE *file = fopen(fileName,"r");
    char buff[MAX_BOARD_SIZE];
    char** matrix;
    int row=0,column=0,i,j;
    if(fgets(buff,sizeof(buff),file) != NULL){
        row++; column = strlen(buff);
        matrix = (char**) malloc(sizeof(char*));
        matrix[0] = (char*) malloc(column * sizeof(char));
        strcpy(matrix[0],buff);
    }else{
        printf("There's not a file named %s. Please try again.\n",*fileName);
        return NULL;
    }
    while(fgets(buff,sizeof(buff),file) != NULL){
        row++;
        matrix = realloc(matrix,row * sizeof(char*));
        matrix[row - 1] = (char *)malloc(column * sizeof(char));
        strcpy(matrix[row-1],buff);
    }
    //if newline char is added to the matrix by accident, fix it.
    for(i=0;i<row;i++) matrix[i][strcspn(matrix[i],"\n")] = '\0';
    *r = row;
    *c = column;
    
    return matrix;
}

void printMatrix(char** matrix,int row,int column){
    int i,j,k;
    for(i=0;i<row;i++){
        for(k=0;k<column-1;k++) printf("----");
        printf("\n");
        for(j=0;j<column-1;j++){
            printf(" %c |",matrix[i][j]);
            
        }
        printf("\n");
    }
    for(k=0;k<column-1;k++) printf("----");
}



void showHighScores(highScore *highScores, int highScoreCount){
    int i;
    for(i=0;i<highScoreCount;i++){
        printf("%d  -----  %s", highScores[i].score,highScores[i].username);
    }
}

void howToPlay(){}


void play(user player, highScore *highScores){
    int choice,row,column;
    char **board, fileName[LENGTH];
    do{
    printf("Do you want to play in one of the official boards, or import one?\n1-Official board\t2-Import :");
    scanf("%d",&choice);
    while(choice < 1 || choice > 2){
        printf("Please give a valid input.\n1-Official board\t2-Import :");
        scanf("%d",&choice);
    }
    switch(choice){
        case 1:
        board = readMatrix("map1.txt",&row,&column);
        printMatrix(board,row,column);
        break;
        case 2:
        printf("To create a game board, simply write the board elements like they're displayed normally without any space between in a .txt file, and place the file in the same folder as the game's .exe file.\nThe name of the .txt file you created: ");
        scanf(" %s",fileName);
        board = readMatrix(fileName,&row,&column);

    }
    }while(board == NULL);
}

//0: yol 1:duvar 2: P+ 3: P- 4: E- 5: e+ 6: X 7: K 8: G 9:Ç
int main(){
    int i,decision, userCount=0,totalUsers=0,loggedIn,highScoreCount;
    user *users, currentPlayer; highScore highScores[HIGH_SCORE];
    users = (user*) malloc(MAX_USER * sizeof(user));
    // FILE *userFile = fopen("users.bin", "rb+");

    importHighScores(highScores,&highScoreCount);
    importUsers(&userCount,users); totalUsers = userCount;
    // fclose(userFile);

    do{
        printf("\nEnter 1 to login, 2 to create a new account: ");
        scanf("%d",&decision);
        system("cls");
    
        switch(decision){
            case 1:
            if(totalUsers==0)
            printf("There are no users right now. Please create a new account.\n");
            else
            loggedIn = login(users,totalUsers,&currentPlayer);
            break;
            case 2:
            signUp(&totalUsers,users);
            loggedIn=0;
            break;
        }
    }while(loggedIn!=1);

    do{
    decision = mainMenu();
    system("cls");
    switch(decision){
        case 1:
        showHighScores(highScores,highScoreCount);break;
        case 2:
        howToPlay();break;
        case 3:
        play(currentPlayer,highScores);
        
        break;
    }
    }while(decision != 4);






    // printf("%d",totalUsers);
    saveNewUsers(users,userCount,totalUsers);
    printf("Please give any input to close the program: "); scanf("%d",&decision);
    return 0;
}