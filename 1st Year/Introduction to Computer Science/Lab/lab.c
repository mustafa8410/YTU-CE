#include <stdio.h>
int main(){
    int M , N,  k , toplam = 0 , i , j , l , m , ft = 0;
    printf("0 sayisini da hesaba katarak goruntunun sirayla kac satir ve sutun oldugunu girin.\n");
    scanf("%d", &N);
    scanf("%d" , &M);
    printf("ayni sekilde kare matris olan filtrenin de satir sayisini girin. \n ");
    scanf("%d" , &k);
    int goruntu[N][M], filtre[k][k] , a = M - k , b = N - k , yeni[a+1][b+1];
    for ( i = 0; i < M; i++)
    {
        for ( j = 0; j < N; j++)
        {
            printf("goruntudeki %d x %d elemani girin.\n" , i , j);
            scanf("%d" , &goruntu[i][j]);
        }
        
    }
    for ( i = 0; i < k; i++)
    {
        for ( j = 0; j < k; j++)
        {
            printf("filtredeki %d x %d elemani girin.\n" , i , j);
            scanf("%d" , &filtre[i][j]);
        }
        
    }

    //solution
    for ( i = 0; i < k; i++)
        for ( j = 0; j < k; j++)
            ft = ft + filtre[i][j];
    //convolution
    for ( l = 0; l < N-k+1; l++)
        for ( m = 0; m < M-k+1; m++){
            for ( i = 0; i < k; i++)
                for ( j = 0; j < k; j++)
                    toplam = toplam + filtre[i][j] * goruntu[i+l][j+m];
            yeni[l][m] = toplam / ft;
            toplam = 0;
        }
    //solution end

    for ( i = 0; i <= a; i++)
    {
        for ( j = 0; j <= b; j++)
        {
            printf("%d ",yeni[i][j]);
        }
        printf("\n");
    }
    return 0;

}
