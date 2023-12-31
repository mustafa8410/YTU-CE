#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <conio.h>
#define MAX_USER 20
#define HIGH_SCORE 5
#define LENGTH 20
#define MAX_SIZE 6
#define MAX_BOARD_SIZE 16
#define MAX_ELEMENT 10

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
    while(fread(&users[(*userCount)],sizeof(user),1,userFile)){
        
        *userCount = *userCount + 1;
    }
    fclose(userFile);
}

void importHighScores(highScore *highScores,int *highScoreCount){
    FILE *scoreFile = fopen("highScores.bin","rb");
    int count=0,i;
    if(scoreFile == NULL) return;
    while(fread(&highScores[count],sizeof(highScore),1,scoreFile)){
        count++;
    }
    *highScoreCount = count;

    fclose(scoreFile);
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

void saveHighScores(highScore *highScores,int highScoreCount){
    FILE *scoreFile = fopen("highScores.bin","wb"); int i;
    for(i=0;i<highScoreCount;i++){
        fwrite(&highScores[i],sizeof(highScore),1,scoreFile);
    }
    fclose(scoreFile);
}

int mainMenu(){
    int decision;
    printf("n---------Main Menu---------\n\n"); 
    do{
    printf("1-High Scores\n2-How to play\n3-Play\n4-Exit: ");
    scanf("%d",&decision);
    if(decision < 1 || decision > 4) printf("Invalid input!");
    }while(decision < 1 || decision > 4);

    return decision;
}

char** readMatrix(char *fileName,int* r, int* c){
    FILE *file = fopen(fileName,"r");
    *r = 0; *c = 0;
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
    printf("There are %d highscores.\n\n",highScoreCount);
    for(i=0;i<highScoreCount;i++){
        printf("%d  -----  %s\n", highScores[i].score,highScores[i].username);
        
    }
    printf("\nGive any input to continue: "); scanf("%d",&i); system("cls");
}

void howToPlay(){
    int check;
    printf("Welcome to the maze game.\nIn this game, you select one of the official gameboards or import one yourself to play. (it's very easy!)\n\nGameboard has 10 different elements.\n0:Paths you can go through\n1:Walls that you can't move to\nK:Black holes. If you move there, it's game over for you.\nX:It's you!\nG:The entrance of the maze.\nC:The exit of the maze.\nE,e,P,p:The elements that can be collected.\n------------\nThe elements and how to win the game\n\nTo complete and (hopefully) win the game, you should create opposite Hydrogen. To do this, you have to have only p and E in your inventory. If you have any other element, e or P, you will not be able to create the Opposite Hydrogen.\nThe more you create Opposite Hydrogen, the more points you get.\nIf you collect elements other than the neccessary ones and get to the exit, you'll still get your points, but not much.\n\n----------\nMovement\n\nIt is simple, use arrow keys to move around, and press Esc anytime to quit!\n\n\nGive any input to go back to the main menu: ");
    scanf("%d",&check); system("cls");
}

void findX(int *cRow,int * cColumn, char **board,int row,int column){
    int i=0,j=0;
    *cRow = -1; *cColumn = -1;
    while(i < row){
        j=0;
        while(j<column){
            if(board[i][j] == 'X'){
                *cRow = i; *cColumn = j; return;
            }
            j++;
        }
        i++;
    }
}

void prepareForNextMove(char **board,char *currentLocation,int cRow,int cColumn, char* collectedElements,int *elementCount){
    board[cRow][cColumn] = 'X';
    if((*currentLocation) != '0' && (*currentLocation) != 'G' && (*currentLocation) != 'C' && (*currentLocation) != 'K' ){
        collectedElements[*elementCount] = *currentLocation;
        *elementCount = *elementCount + 1;
        *currentLocation = '0';
    }
}

int calculateCreatedAntiMaterialNumber(char* collectedElements,int elementCount){
    int i=0,pCount=0,Ecount=0,created=0;
    while(i<elementCount){
        if(collectedElements[i] == 'p') pCount++;
        else if(collectedElements[i] == 'E') Ecount++;
        else{
            printf("You have to have only p or E to win the game!\n");
            return 0;
        }
        i++;

    }
    if(pCount < Ecount) created = pCount;
    else created=Ecount;
    return created;

}

/*void findC(int *eRow,int * eColumn, char **board,int row,int column){
    int i=0,j=0;
    while(i < row && board[i][j] != 'C'){
        while(j<column && board[i][j] != 'C'){
            j++;
        }
        j=0;
        i++;
    }
    *eRow = i; *eColumn = j;
} */

void newHighScore(int score, int *highScoreCount, highScore *highScores, user player) {
    int i=0,j;
    if(*highScoreCount < HIGH_SCORE){
        while(i < *highScoreCount && score <= highScores[i].score){
            i++;
        }
        if(i==(*highScoreCount)){
            *highScoreCount = (*highScoreCount) + 1;
            highScores[i].score = score;
            strcpy(highScores[i].username,player.username);
        }
        else{
            for(j=(*highScoreCount);j>i;j--){
                highScores[j].score = highScores[j-1].score;
                strcpy(highScores[j].username,highScores[j-1].username);
            }
            highScores[i].score = score;
            strcpy(highScores[i].username,player.username);
            *highScoreCount = (*highScoreCount) + 1;
        } 
        printf("Congratulations, you scored a new high score at the place %d.\n",(i+1));
    }
    else{
        while(i<HIGH_SCORE && score <= highScores[i].score) i++;
        if(i==HIGH_SCORE) return;
        else{
            for(j=(HIGH_SCORE-1);j>i;j--){
                highScores[j].score = highScores[j-1].score;
                strcpy(highScores[j].username,highScores[j-1].username);
            }
            highScores[i].score = score;
            strcpy(highScores[i].username,player.username);
            printf("Congratulations, you scored a new high score at the place %d.\n",(i+1));
        }
    }

}




void manualPlay(char **board,int row, int column,int *highScoreCount, user player, highScore *highScores){ //sag ok 77, sol ok 75, yukari 72, aşagi 80

    int i,j;
    char collectedElements[MAX_ELEMENT],currentLocation = 'G', a;
    int score, currentRow, currentColumn, elementCount=0, moveCount=0,invalid=0,createdMaterials;   //int exitRow,exitColumn;
    findX(&currentRow,&currentColumn,board,row,column); //findC(&exitRow,&exitColumn,board,row,column);
    while(currentLocation != 'C' && currentLocation != 'K'){
    printf("\n"); printMatrix(board,row,column);
    printf("\n\nYou are currently at %d x %d.\n",currentRow,currentColumn); printf("Collected elements: ");
    for(i=0;i<elementCount;i++) printf("%c ",collectedElements[i]); printf("\n");

    a = getch(); if(a==27){printf("Exiting the game with 0 score.\n");return;}
    else{
        a=getch();
        switch (a){
            case 77:
            if((currentColumn + 1) >= (column-1) || board[currentRow][currentColumn+1] == '1'){printf("Invalid move!\n");invalid++;}
            else{
                moveCount++;
                board[currentRow][currentColumn] = currentLocation;
                currentColumn++;
                currentLocation = board[currentRow][currentColumn];
                prepareForNextMove(board,&currentLocation,currentRow,currentColumn,collectedElements,&elementCount);
            }
            break;
            case 75:
            if((currentColumn - 1) < 0 || board[currentRow][currentColumn-1] == '1'){printf("Invalid move!\n");invalid++;}
            else{
                moveCount++;
                board[currentRow][currentColumn] = currentLocation;
                currentColumn--;
                currentLocation = board[currentRow][currentColumn];
                prepareForNextMove(board,&currentLocation,currentRow,currentColumn,collectedElements,&elementCount);
            }
            break;
            case 72:
            if((currentRow - 1) < 0 || board[currentRow-1][currentColumn] == '1'){printf("Invalid move!\n");invalid++;}
            else{
                moveCount++;
                board[currentRow][currentColumn] = currentLocation;
                currentRow--;
                currentLocation = board[currentRow][currentColumn];
                prepareForNextMove(board,&currentLocation,currentRow,currentColumn,collectedElements,&elementCount);
            }
            break;
            case 80:
            if((currentRow + 1) >= row || board[currentRow+1][currentColumn] == '1'){printf("Invalid move!\n");invalid++;}
            else{
                moveCount++;
                board[currentRow][currentColumn] = currentLocation;
                currentRow++;
                currentLocation = board[currentRow][currentColumn];
                prepareForNextMove(board,&currentLocation,currentRow,currentColumn,collectedElements,&elementCount);
            }
            break;
        }

        sleep(1);system("cls");
    }
    
    }//while end

    
    if(currentLocation == 'C'){
        printf("You have reached to the exit.\n");
        createdMaterials = calculateCreatedAntiMaterialNumber(collectedElements,elementCount);
        printf("You have managed to create %d materials.\n",createdMaterials);
        score = (200*createdMaterials) - (invalid * 10) - (moveCount * 2);
        printf("Your score: %d\n",score);
        newHighScore(score,highScoreCount,highScores,player);
    }
    else{
        score=0;
        printf("You've entered into a black hole and lost.\n");
    }
}
void autoPlay(){}

void play(user player, highScore *highScores,int *highScoreCount){
    int choice,row,column,i,game=1;
    char **board, fileName[LENGTH];
    while(game==1){
    do{
    printf("Do you want to select one of the 5 official boards to play, or import a gameboard?\n1-Official board\t2-Import : ");
    scanf("%d",&choice); system("cls");
    while(choice < 1 || choice > 2){
        printf("Please give a valid input.\n1-Official board\t2-Import :");
        scanf("%d",&choice); system("cls");
    }
    switch(choice){
        case 1:
        printf("Please provide with a choice of these boards:\n");
        int boardChoice;

        board = readMatrix("map1.txt",&row,&column);
        printf("1)\n"); printMatrix(board,row,column); for(i=0;i<row;i++) free(board[i]); free(board);
        board = readMatrix("map2.txt",&row,&column);
        printf("\n2)\n"); printMatrix(board,row,column);for(i=0;i<row;i++) free(board[i]); free(board);
        board = readMatrix("map3.txt",&row,&column);
        printf("\n3)\n"); printMatrix(board,row,column);for(i=0;i<row;i++) free(board[i]); free(board);
        board = readMatrix("map4.txt",&row,&column);
        printf("\n4)\n"); printMatrix(board,row,column);for(i=0;i<row;i++) free(board[i]); free(board);
        board = readMatrix("map5.txt",&row,&column);
        printf("\n5)\n"); printMatrix(board,row,column); printf("\n");for(i=0;i<row;i++) free(board[i]); free(board);
        do{
            printf("Your choice: "); scanf("%d",&boardChoice);
            if(boardChoice < 1 || boardChoice > 5) printf("Please provide a valid input.\n\n");
        }while(boardChoice < 1 || boardChoice > 5); printf("Selected map %d. Please wait...\n",boardChoice); sleep(1); system("cls");

        switch (boardChoice){
            case 1:
            board = readMatrix("map1.txt",&row,&column);
            break;
            case 2:
            board = readMatrix("map2.txt",&row,&column);
            break;
            case 3:
            board = readMatrix("map3.txt",&row,&column);
            break;
            case 4:
            board = readMatrix("map4.txt",&row,&column);
            break;
            case 5:
            board = readMatrix("map5.txt",&row,&column);
            break;
        }

        break;
        case 2:
        printf("To create a game board, simply write the board elements like they're displayed normally without any space between in a .txt file, and place the file in the same folder as the game's .exe file.\nThe name of the .txt file you created: ");
        scanf(" %s",fileName); system("cls");
        board = readMatrix(fileName,&row,&column);
    }
    }while(board == NULL);
    printf("\n\n1-Manual Play\n2-Auto Play(unavailable)\n"); 
    scanf("%d",&choice); system("cls");
    while(choice != 1 && choice != 2){
        printf("Invalid input. Please provide a valid one. 1 for manual play, 2 for auto play(unavailable): ");
        scanf("%d",&choice); system("cls");
    }
    switch(choice){
        case 1:
        manualPlay(board,row,column,highScoreCount,player,highScores);
        printf("If you want to play again, enter 1. Otherwise, enter any input else: ");
        scanf("%d",&game); system("cls");
        
        break;
        case 2:
        autoPlay();break;

    }

    }


}



int main(){
    int i,decision, userCount=0,totalUsers=0,loggedIn,highScoreCount=0;
    user *users, currentPlayer; highScore *highScores;
    highScores = (highScore*) calloc(HIGH_SCORE,sizeof(highScore));
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
        play(currentPlayer,highScores,&highScoreCount);
        
        break;
    }
    }while(decision != 4);






    // printf("%d",totalUsers);
    saveNewUsers(users,userCount,totalUsers);
    saveHighScores(highScores,highScoreCount);
    printf("Please give any input to close the program: "); scanf("%d",&decision);
    return 0;
}