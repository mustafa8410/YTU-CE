#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stddef.h>

int main(){

FILE *file = fopen("map3.txt","r");
char buff[15]; int row=0, column = 0,i,j,k;
char **matrix;
if(fgets(buff,sizeof(buff),file) != NULL){
   column = (strlen(buff));
   row++;
   matrix = (char**) malloc(row * sizeof(char*));
   matrix[0] = (char*) malloc(column * sizeof(char));
   strcpy(matrix[0],buff);
}
while(fgets(buff,sizeof(buff),file) != NULL){
   row++;
   matrix = realloc(matrix,row * sizeof(char*));
   matrix[row - 1] = (char *)malloc(column * sizeof(char));
   strcpy(matrix[row - 1],buff);
}
fclose(file);

for(i=0;i<row;i++)
   matrix[i][strcspn((matrix[i]),"\n")] = '\0';

//print
for(i=0;i<row;i++){
   for(k=0;k<column-1;k++) printf("----");
   printf("\n");
   for(j=0;j<column-1;j++){
      printf(" %c |",matrix[i][j]);
   }
   printf("\n");
}
for(k=0;k<column-1;k++) printf("----");

//print end



scanf("%d",&i);
  for (i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);

return 0;




}