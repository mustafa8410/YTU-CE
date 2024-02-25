#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX 20
#define MAXPLAYER 10

void ClearMatrix(int matrix[MAX][MAX],int size){ //simply clears the gameboard for another round. takes the matrix and the size of the matrix, clears it for the next round.
    int i,j;
    for (i = 0; i<size; i++){
        for (j=0;j<size;j++){
            matrix[i][j] = 0;
        }
    }
}

int CalculatePoint(int matrixsize,int undo, int moves, int matrixmethod){ //calculates the points. Uses the matrix size, amount of undos, moves and the method used to create the matrix.
    int point;
    point = (matrixsize * matrixsize * matrixsize) - (undo/2) - (moves);
    if(matrixmethod == 1){
        point = (5*point) / 4;
    }
}

int CheckZero(int gameboard[MAX][MAX],int gamesize){ //checks if there are still any zeroes left. Takes gameboard and the size of the board.
    int flag = 0;
    int i,j;
    for(i=0;i<gamesize;i++){
        for(j=0;j<gamesize;j++){
            if(gameboard[i][j] == 0){
                flag = 1;
            }
        }
    }
    return flag;
}

int LinkUpControl(int row,int column,int drow[21],int dcolumn[21],int NextNumber){ /*checks if the player successfully linked up his numbers. Takes the current row,*/
    int control;                                                                      // column and the destination row/column arrays and the number to link up                                                                    
    if (row == drow[NextNumber] && column == dcolumn[NextNumber]){
        control = 1;
    }else{
        control = 0;
    }
    return control;
}

void ShiftRight(int row, int column, int oldrow[5], int oldcolumn[5]){ //Shifts the oldrow and oldcolumn arrays to the right to make up space for the new coming move
    int i;
    for (i=4;i>0;i--){
        oldrow[i] = oldrow[i-1];
        oldcolumn[i] = oldcolumn[i-1];
    }
    oldrow[0] = row;
    oldcolumn[0] = column;
}
void ShiftLeft(int oldrow[5], int oldcolumn[5]){ //Shifts the arrays to left when undoing a move
    int i;
    for (i=0;i<4;i++){
        oldrow[i]=oldrow[i+1];
        oldcolumn[i] = oldcolumn[i+1];
    }
    oldrow[4] = -1;
    oldcolumn[4] = -1;
}

void FindNumber(int gameboard[MAX][MAX],int gamesize, int number, int* startrow, int* startcolumn, int drow[MAX], int dcolumn[MAX]){ //Finds the NextNumber integer, uses the gameboard and it's size and the destination row/column arrays
    int i,j,frow,fcolumn,fr1, fc1, fr2, fc2;
    int count = 0;
    for (i=0;i<gamesize;i++){
        for (j=0;j<gamesize;j++){
            if(gameboard[i][j]==number){
                if(count == 0){
                    fr1 = i;
                    fc1 = j;
                    count++;
                }else{
                    fr2 = i;
                    fc2 = j;
                }

            }
        }
    }
    *startrow = fr2;
    *startcolumn = fc2;
    drow[number] = fr1;
    dcolumn[number] = fc1;
}

void drawBoard(int matris[][MAX], int N){ //Draws the board
    int i,j,k;
    for(i=0;i<N;i++){
        printf("\n");
        for (k=0;k<N;k++)
            printf("-------");
        printf("\n");
        for(j=0;j<N;j++)
            if (matris[i][j]!=0)
                printf("  %d   |",matris[i][j]);
            else
                 printf("      |",matris[i][j]);
    }
}

void readFromFile(int matris[][MAX], char *fileName){
	int i,j, temp;
	FILE *data = fopen(fileName,"r");
	if(!data){
        printf("Dosya Acilamadi!");
		return;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %d\n",&i,&j,&temp);  
		matris[i][j]=temp; 
    }  
  	fclose(data); 
}

void RandomBoard(int gameboard[MAX][MAX],int gamesize){ //Gets a random board
    int i, j, random_row, random_column, count = 0;
    srand(time(NULL));
    for(i=1;i<=gamesize;i++){
        count = 0;
        while(count != 2){
            random_row = rand() % gamesize;
            random_column = rand() % gamesize;
            if(gameboard[random_row][random_column] == 0){
                gameboard[random_row][random_column] = i;
                count ++;
            }

        }
    }
}
int PlayGameManually(int gameboard[MAX][MAX],int menuchoice){ //Takes gameboard and the choice made in the menu about the method to create the gameboard.
    int playing = 1;
    int boardsize, gaming, movement, column, row, startrow, startcolumn,NextNumber, undo, hamle,wrongmoves,gamepoint,numbercount;
    int totalpoint = 0;
    int drow[21] = {-1};
    int dcolumn[21] = {-1};
    char filename[20];
    while(playing == 1){
        boardsize = 0;
        ClearMatrix(gameboard, MAX);
            if(menuchoice == 1){
                printf("How big should be the nXn gameboard? Max is 20:");
                scanf("%d",&boardsize);
                RandomBoard(gameboard,boardsize);
                numbercount = boardsize;
                
            }
            if(menuchoice == 2){
                printf("First of all, please enter the size of your matrix. Note that max number is 20. :");
                scanf("%d",&boardsize);
                printf("Please enter the amount of numbers to link up in your matrix. :");
                scanf("%d",&numbercount);
                printf("Please enter the name of your file.");
                scanf(" %s",filename);
                readFromFile(gameboard,filename);
                

            }
        gaming = 1;
        gamepoint = 0;
        int control, flag;
        int oldrow[5]= {-1};
        int oldcolumn[5]= {-1};
        NextNumber = 1;
        FindNumber(gameboard,boardsize,NextNumber,&startrow,&startcolumn,drow,dcolumn);
        row = startrow;
        column = startcolumn;
        undo = 0;
        hamle = 0;
        wrongmoves = 0;
        printf("The game starts now. You'll need to link up the same numbers. Whole matrix should be full.\n");
        printf("You should play this game using your NumPad. 8 to go up, 6 to go right, 4 to go left, 5 to go down.\n");
        printf("You can enter 1 to generate a new matrix anytime.\n");
        printf("You can enter 0 to stop playing anytime you want.\n");
        printf("While playing, enter 2 to undo your last movement.\n ");

        while(gaming == 1){
            
            drawBoard(gameboard,boardsize);
            printf("\n Your number to link up: %d \n",NextNumber);
            printf("You are now at %d x %d \n", (row + 1), (column + 1));
            scanf("%d",&movement);
            if(movement == 8){
                if((row-1) == drow[NextNumber] && column == dcolumn[NextNumber]){
                    ShiftRight(row,column,oldrow,oldcolumn);
                    row--;
                    hamle++;
                }
                else if(gameboard[row-1][column] != 0 || row == 0){
                    printf("You can't do this move!\n");
                    wrongmoves++;

                }else{
                    ShiftRight(row,column,oldrow,oldcolumn);
                    row--;
                    gameboard[row][column] = NextNumber;
                    hamle++;

                }
            }
            else if(movement == 6){
                if((column+1) == dcolumn[NextNumber] && row == drow[NextNumber]){
                ShiftRight(row,column,oldrow,oldcolumn);
                column++;
                hamle++;
                }
                else if(gameboard[row][column+1] != 0 || column == (boardsize -1)){
                        printf("You can't do this move!\n");
                        wrongmoves++;
                    }
                else{
                ShiftRight(row,column,oldrow,oldcolumn);
                column++;
                gameboard[row][column] = NextNumber;
                hamle++;
                }
            }
            else if(movement == 4){
                if( (column - 1) == dcolumn[NextNumber] && row == drow[NextNumber]){
                    ShiftRight(row,column,oldrow,oldcolumn);
                    column--;
                    hamle++;
                }
                else if(gameboard[row][column-1] != 0 || column == 0){
                        printf("You can't do this move!\n");
                        wrongmoves++;
                }else{
                    ShiftRight(row,column,oldrow,oldcolumn);
                    column--;
                    gameboard[row][column] = NextNumber;
                    hamle++;
                }
            }
            else if(movement == 5){
                if( (row + 1) == drow[NextNumber] && column == dcolumn[NextNumber]){
                    ShiftRight(row,column,oldrow,oldcolumn);
                    row++;
                    hamle++;
                }
                if((gameboard[row+1][column]) != 0 || row == (boardsize-1)){
                        printf("You can't do this move!\n");
                        wrongmoves++;
                }else{
                    ShiftRight(row,column,oldrow,oldcolumn);
                    row++;
                    gameboard[row][column] = NextNumber;
                    hamle++;

                }
            }
            else if(movement == 1){
                gaming = 0;
            }
            else if(movement == 0){
                gaming = 0;
                playing = 0;
            }
            else if(movement == 2){
                if(oldrow[0] == -1 && oldcolumn[0] == -1){
                    printf("You can't go back anymore!\n");

                }else{
                    if(gameboard[oldrow[0]][oldcolumn[0]] == (NextNumber - 1)){

                        NextNumber--;
                    }else{
                        gameboard[row][column] = 0;
                    }
                    row = oldrow[0];
                    column = oldcolumn[0];
                    ShiftLeft(oldrow,oldcolumn);
                    undo++;

                }
            }
            control = LinkUpControl(row,column,drow,dcolumn,NextNumber);
            if (control == 1){
                NextNumber++;
            }
            flag = CheckZero(gameboard,boardsize);
            if(NextNumber > numbercount && flag == 0){
               gamepoint = CalculatePoint(boardsize,undo,hamle,menuchoice);
               printf("Congratulations! You completed the game correctly. You gained %d points. Would you want to have another go? Enter 1 to have another go, 0 to stop.\n", gamepoint);
               totalpoint = totalpoint + gamepoint;
               scanf("%d",&playing);
               gaming = 0;
            }
            else if(NextNumber > numbercount && flag == 1){
                gamepoint = numbercount*numbercount;
                printf("You linked all numbers, but there are still blank spaces. Since you managed to solve this anyways, you gain %d points.\n",gamepoint);
                totalpoint = totalpoint + gamepoint;
                printf("Do you want to play again? Enter 0 to stop playing, enter 1 to play again.\n");
                scanf("%d",&playing);
                gaming = 0;
            }
            if(NextNumber <= numbercount && control == 1){
                FindNumber(gameboard,boardsize,NextNumber,&row,&column,drow,dcolumn);
            }
        }
    }
    return totalpoint;
}

int main(){
    int player_count, i, game = 1, menuchoice, player, gamemenuchoice, boardsize, point;
    char players[MAXPLAYER][MAX];
    int scoreboard[MAXPLAYER][1] = {0};
    int gameboard[MAX][MAX] = {0};
    
    printf("Welcome to the game! First off, you need to tell me how many different players are playing the game. Total is 10 :  ");
    scanf("%d",&player_count);
    printf("Wonderful! Now, you'll need to assign usernames to each player. Maximum amount of characther number allowed is 20.\n");
    for(i=1;i<=player_count;i++){
        printf("Enter the username for Player %d: ",i);
        scanf( " %[^\n]s", players[i-1]);
        printf("Player %d = %s\n", i,players[i-1]);
    }
    while (game == 1){
        menuchoice = 0;
        printf("MAIN MENU\n");
        printf("1 - Generate a random matrix\n");
        printf("2 - Take a matrix from a document\n");
        printf("3 - Scoreboard\n");
        printf("4 - Exit the game.\n");
        scanf("%d",&menuchoice);
        if(menuchoice == 4){
            printf("Thanks for playing. Shutting down.");
            game = 0;
        }
        else if(menuchoice == 3){
            for(i=0;i<player_count;i++){
                printf("%s : %d\n", players[i],scoreboard[i][0]);
            }
        }
        else if(menuchoice == 1 || menuchoice == 2){
        printf("Which player are you? Player number: ");
        scanf("%d", &player);
        printf("GAME MENU\n");
        printf("1 - Automatic Mode (Unavailable)\n");
        printf("2 - Manual Mode\n");
        printf("3 - Exit to Main Menu\n");
        scanf("%d", &gamemenuchoice);
        if(gamemenuchoice==3){}
        else if(gamemenuchoice == 2){
            point = PlayGameManually(gameboard,menuchoice);
            scoreboard[player - 1][0] = scoreboard[player - 1][0] + point;
            point = 0;
        }
        }
        else{
            printf("This number wasn't in the main menu\n");
        }
    }
}

