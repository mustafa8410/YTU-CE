#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findLongest(char **mat,int wcount){
    int k,i, wordlen=0, longestindex;
    for(k=0;k<wcount;k++){
        if(wordlen < strlen(mat[k])){
            wordlen = strlen(mat[k]);
            longestindex = k;
            }
    }
    return wordlen;
}

void fillmatrix(char **mat, int wcount, int wordlen){
    int i,j;
    for(i=0;i<wcount;i++){
        j = strlen(mat[i]);
        while(j < (wordlen)){
            mat[i][j] = '*';
            j++;
        }
    }
}

void printMatrix(char **mat, int wcount){
    int i;
     for(i=0;i<wcount;i++){
        printf(" %s\n", mat[i]);
    }
}


int main(){
    int wcount, i, j, wordlen;
    char **mat;
    printf("Kelime sayisini giriniz: ");
    scanf("%d",&wcount);
    mat = (char**)malloc(wcount*sizeof(char*));
    for(i=0;i<wcount;i++){
        mat[i] = (char*)calloc(50,sizeof(char));
    }

    for(i=0;i<wcount;i++){
        printf("Kelime %d: ", (i+1));
        scanf(" %s", mat[i]);
    }

    wordlen = findLongest(mat, wcount);

    mat = realloc(mat,sizeof(char*) * wcount);
    for(i=0;i<wcount;i++){
        mat[i] = realloc(mat[i], sizeof(char) * (wordlen));
    }

    fillmatrix(mat,wcount,wordlen);
    printMatrix(mat,wcount);
    //free the matrix

    for(i=0;i<wcount;i++){
        free(mat[i]);
    }
    free(mat);


    return 0;
}