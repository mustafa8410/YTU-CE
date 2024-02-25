#include <stdio.h>
#define MAX 50

void PrintMatrix(int head,int N, int jobs[MAX][3]){
    int current;
    int duration, i;
    char job;
    printf("Output:\n");
    current = head;
    while(current != -1){
        job = jobs[current][0];
        duration = jobs[current][1];
        for(i=0;i<duration;i++){
            printf("%c ",job);
        }
        current = jobs[current][2];
    }
    printf("\n");

}

void CreateMatrix(int head,int N, int jobs[MAX][3]){
    char code,flag;
    int duration, link, i,j,temp;
    for(i=0;i<N;i++){
        printf("Enter the job code for %d:", (i+1));
        scanf(" %c",&code);
        int temp = code;
        jobs[i][0] = temp;
        printf("Enter the duration of the job %d:", (i+1));
        scanf(" %d",&duration);
        jobs[i][1] = duration;
        printf("Enter the link for %d:",(i+1));
        scanf("%d",&link);
        jobs[i][2] = link;
    }
}


int main(){
    int N, head,flag;
    int jobs [MAX][3] = {0};
    printf("Enter the number of jobs. :");
    scanf("%d",&N);
    if(N>MAX){
        flag = 0;
        while(flag = 0){
            printf("Try again.");
            scanf("%d",&N);
            if(N<=MAX){
                flag = 1;
            }
        }
    }
    printf("Enter the head value:");
    scanf("%d",&head);
    CreateMatrix(head,N,jobs);
    PrintMatrix(head,N,jobs);


}