#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stddef.h>
#define MAX_USER 20
#define HIGH_SCORE 5
#define LENGTH 20

typedef struct{
    char name[LENGTH];
    char surname[LENGTH];
    char username[LENGTH];
    char password[LENGTH];
}user;

typedef struct{
    int *score;
    char *user;
}highScores;

void importUsers(FILE *file, int *userCount, user *users){
    while(fread(&users[*userCount], sizeof(user),1, file)){
    *userCount = *userCount + 1;
    }
    }


int login(user *users, int totalUsers){
    char username[LENGTH];
    char password[LENGTH];
    int i=0, flag=0;
    printf("Username: "); scanf(" %s", username);
    printf("Password: "); scanf(" %s", password);
    while(flag == 0 && i < totalUsers){
        if(strcmp(users[i].username, username) == 0 && strcmp(users[i].password,password) == 0){
            printf("Welcome %s %s.", users[i].name,users[i].surname);
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

void saveNewUsers(FILE *userFile, user *users, int userCount, int totalUsers){
    int i;
    for(i=userCount;i<totalUsers;i++) fwrite(&users[i],sizeof(user),1,userFile);
}


int main(){
    int i,decision, userCount=0,totalUsers=0,loggedIn;
    user *users;
    //allocating memory for users and it's fields
    users = (user*) malloc(MAX_USER * sizeof(user));
    FILE *userFile = fopen("users.bin", "rb+");
    
    importUsers(userFile,&userCount,users); totalUsers = userCount;
    fclose(userFile);

    do{
        printf("\nEnter 1 to login, 2 to create a new account: ");
        scanf("%d",&decision);
    
        switch(decision){
            case 1:
            if(totalUsers==0)
            printf("There are no users right now. Please create a new account.");
            else
            loggedIn = login(users,totalUsers);
            break;
            case 2:
            signUp(&totalUsers,users);
            loggedIn=0;
            break;
        }
    }while(loggedIn!=1);
    printf("%d",totalUsers);

    userFile = fopen("users.bin","ab+");
    saveNewUsers(userFile,users,userCount,totalUsers);
    fclose(userFile);
    return 0;
}