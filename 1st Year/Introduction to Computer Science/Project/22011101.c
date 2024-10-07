#include <stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void){
    int rows, columns, num_food, i, j, snake_start_row, snake_start_column, snake_body_row[50], snake_body_column[50], num1, num2, flag, food_rows[50], food_columns[50], game = 1, new_row, new_col, count = 0, length = 1, food2;
    char board[50][50], direction;
    char snake[50], food3;
    srand(time(0));
    printf("welcome to the snake game. enter the number of the rows you want.\n");
    scanf("%d",&rows);
    printf("now, enter the number of the columns you want.\n");
    scanf("%d",&columns);
    printf("how many foods do you want?\n");
    scanf("%d",&num_food);
    food2 = num_food;
    food3 = num_food;
    while (num_food >= rows * columns - 1 || num_food == 0)
    {
        printf("this number of foods is impossible to place. try again.");
        scanf("%d",&num_food);
        food2 = num_food;
        food3 = num_food;
    }
    for ( i = 0; i < rows; i++)
    {
        for ( j = 0; j < columns; j++)
        {
            board[i][j] = '-';
        }  
    }
    snake_start_row = rand() % rows;
    snake_start_column = rand() % columns;
    snake_body_row[1] = snake_start_row;
    snake_body_column[1] = snake_start_column;
    board[snake_start_row][snake_start_column] = '1';
    i = 1;
    while (i <= num_food)
    {
        num1 = rand() % rows;
        num2 = rand() % columns;
        if(num1 != snake_body_row[1] && num2 != snake_body_column[1]){
            flag = 0;
            for(j = 1; j <= num_food; j++){
                if (num1 == food_rows[j] && num2 == food_columns[j])
                {
                    flag = 1;
                }
                
            }
            if(flag==0){
                food_rows[i] = num1;
                food_columns[i] = num2;
                board[num1][num2] = '0';
                i++;
            }
        }    
    }
    for ( i = 0; i < rows; i++)
    {
        for ( j = 0; j < columns; j++)
        {
            printf("%c\t",board[i][j]);
        }
        printf("\n");
    }
    while (game == 1)
    {
        printf("enter which way you want the snake to go. u for up, r for right, d for down and l for left.\n");
        scanf("%c",&direction);
        direction = getchar();
        if (direction == 'u')
        {
            new_row = snake_body_row[1] - 1;
            new_col = snake_body_column[1];
        }else if (direction == 'l')
        {
            new_row = snake_body_row[1];
            new_col = snake_body_column[1] - 1;
        }else if (direction == 'd')
        {
            new_row = snake_body_row[1] + 1;
            new_col = snake_body_column[1];
        }else if (direction == 'r')
        {
            new_row = snake_body_row[1];
            new_col = snake_body_column[1] + 1;
        }
        if (new_row < 0 || new_row >= rows || new_col < 0 || new_col >= columns)
        {
            game = 0;
            printf("game over.\n");
            break;
        }else{
            count++;
        }
        
            board[snake_body_row[length]][snake_body_column[length]] = '-';
          for ( i = 1; i <= food3; i++)
        {
            if (food_rows[i] == new_row && food_columns[i] == new_col)
            {
                food_rows[i] = 60;
                food_columns[i] = 60;
                num_food--;
                length++;
                printf("you ate a food.\n");

            }
        }
        snake_body_row[0] = new_row;
        snake_body_column[0] = new_col;
        
        if(food2 == num_food){
        for ( i = length; i > 0; i--){
        
            snake_body_row[i] = snake_body_row[i - 1];
            snake_body_column[i] = snake_body_column[i - 1];
        }
       
        for ( i = length; i > 0; i--)
        {
            
            board[snake_body_row[i]][snake_body_column[i]] = i;
        }
        }
         else{
            snake_body_row[length] = snake_body_row[length - 1];
            snake_body_column[length] = snake_body_column[length - 1];
            for(i = length - 1; i > 0; i--){
            snake_body_row[i] = snake_body_row[i - 1];
            snake_body_column[i] = snake_body_column[i - 1];}
            for ( i = length - 1; i > 0; i--)
            {
                board[snake_body_row[i]][snake_body_column[i]] = i;
            }
            food2 = num_food;
         }   
        
        for ( i = 0; i < rows; i++)
        {
            for ( j = 0; j < columns; j++)
            {
                printf("%c\t",board[i][j]);
            }
            printf("\n");
        }
        if (num_food == 0)
        {
            printf("congratulations! you ate all the foods.\n");
            game = 0;
        } 
    }
    printf("Total move: %d\n",count);
    printf("Food left: %d\n",num_food);
    printf("Length of the snake: %d\n", length);
    return 0;
    }