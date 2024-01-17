#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINELENGTH 100


struct Order{
    int orderID;
    int customerID;
    char *customerName;
    char *orderName;
    char *day;
    struct Order *next;   
};

/*void parseData(struct Order *orders, char *buff, int i){
    char *token;
    token = strtok(buff," ");
    orders[i].orderID = atoi(token);
    token = strtok(NULL," ");
    orders[i].customerID = atoi(token);
    token = strtok(NULL," ");
    strcpy(orders[i].customerName,token);
    token = strtok(NULL," ");
    strcpy(orders[i].orderName,token);
    token = strtok(NULL," ");
    token[strlen(token) - 1] = "\0";
    strcpy(orders[i].day,token);
}*/

/*void readFile(struct Order *orders){
    FILE *file = fopen("input.txt","r");
    char buff[LINELENGTH]; int i=0;
    while(fgets(buff,1,file) != NULL){

    }
}*/

int readFilev2(struct Order *orders){
    FILE *file = fopen("input.txt","r");
    int i=0;
    while(!feof(file)){
        orders = realloc((i+1),sizeof(struct Order));
        fscanf(file,"%d %d %s %s %s",&orders[i].orderID,&orders[i].customerID,&orders[i].customerName,&orders[i].orderName,&orders[i].day);
        i++;
    }

    fclose(file);
    return ++i;

}

sortData(struct Order *orders, struct Order *head,int size){
    int i=0,min; struct Order *curr;
    *head = orders[0]; head->(*next) = orders[1];
    *curr = *head;
    min=head->orderID;
    while(i<size){
        if(orders[i].orderID < curr->orderID){

        }
    }
}



int main(){
    struct Order *head,*orders;orders = (struct Order*) malloc(sizeof(struct Order)); head = (struct Order*) malloc(sizeof(struct Order));
    int size = readFilev2(orders);


    return 0;
}