#include<stdio.h>
int main(){
    char D[4] = "aers";
    char words[4][4] = {"sera" , "ser" , "as" , "es"};
    char guess[50];
    char correct_words [4][4];
    printf("a , e, r, s harfleriyle kelimeler uretin. bitirmek icin 0'a basin.\n");
    int count = 0 , toplam = 0 , i = 0 , N = 0 , puan = 0 , flag = 1 , a = 0 , b = 0 , c = 0 , j , l , m , n , o , p ;
    jump:
    scanf("%s" , guess);
    if(guess[0] = 0){
        printf("oyun bitti. toplam puaniniz: %d" , toplam);
    }
    else
    {
        while NOT ((guess[i] = "\0"))
        {
         i++;
        }
        N = i + 1;
        if (N >= 2)
            {if (flag = 1)
            {
             for ( j = 0; i < N-1; i++)
            {
                flag = 0;
             for (l = 0; l < 3; l++){
                 if (guess[j] = D[l])
                    {
                     flag = 1;
                 }
                
                }
            }
            
            
        
            for ( m = 0; m < N-1; m++ )
            {
                for ( n = 0; n < N-1; i++)
                {
                    if (m != n)
                    {
                        if(guess[m] = guess[n]);
                        flag = 0;
                    }
                
                }
            }
            if (flag = 0)
            {
            printf("ayni harf iki kez kullanilmaz.");
            puan = puan - N;
            toplam = toplam + puan;
            goto jump;
            }
            else{
                jump2:
                if (guess[a] = words[b][c])
                {
                    if (a < N)
                    {
                    a = a + 1;
                    c = c + 1;
                    goto jump2; 
                    }
                    else
                    {if ( words[b][c + 1] = "\0")
                        {
                        a = 0;
                        b = 0;
                        c = 0;
                        jump3:
                        if (guess[a] = correct_words[b][c])
                        {   if (a < N)
                        {
                         a = a + 1;
                         c = c + 1;
                         goto jump3;
                        }
                    
                        else{
                            if (words[b][c + 1] = "\0")
                            {
                                puan = puan - N;
                                toplam = toplam + puan;
                                printf("bunu zaten yazdin. %d" , puan);
                                goto jump3;
                        }
                        else{
                            if (b < count)
                            {
                                b = b + 1;
                                goto jump3;
                            }
                            else{
                                puan = puan + N;
                                count = count + 1;
                                toplam = toplam + puan;
                                for ( o = 0; o < N-1; o++)
                                {
                                    guess[o] = correct_words[count][o];
                                }
                                 printf("dogru bildin. %d" , puan);
                                 goto jump;
                            }
                            
                        }    
                    }
                    else{
                        if (b < count)
                        {
                            b = b + 1;
                            a = 0;
                            c = 0;
                        }
                        else{
                            puan = puan + N;
                            count = count + 1;
                            toplam = toplam + puan;
                             for ( p = 0; p < N-1; p++){
                                guess[p] = correct_words[count][p];
                             }
                            printf("dogru bildin. %d" , puan);
                             goto jump;
                        }
                        }   
                    }
                }
                }
               else{
                if (b < 3)
                {
                    a = 0;
                    b = b+1;
                    c = 0;
                    goto jump2;
                }
                else{
                    puan = puan - N;
                    toplam = toplam + puan;
                    printf("girdigin sözcük yanlis. %d" , puan);
                    goto jump;
                }
            }
            }
            }    else{
            if (b < 3)
            {
                b = b+1;
                a = 0;
                c = 0;
                goto jump2;
            }
            else{
                puan = puan - N;
                toplam = toplam + puan;
                printf("girdigin sözcük yanlis. %d" , puan);
                goto jump;
            }
        }
        
        
        
        
    }
        else{
            puan = puan - N;
            toplam = toplam + puan;
            printf("gecersiz harf. %d" , puan);
            goto jump;
        }
    }    
        else{
            printf("en az iki karakterli bir kelime girin.");
            goto jump;
        }
    
return 0;
}




