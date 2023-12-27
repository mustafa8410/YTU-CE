#include <stdio.h>

void sort(int arr[], int n){
    int temp;
    int i,j;

    for (i=0; i<n-1; i++){
        for(j=0; j<n - i - 1; j++){
            if(arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void worstThree(int arr[]){
    int total = 0, i;
    printf("En kucuk 3 eleman: %d, %d, %d\n", arr[0], arr[1], arr[2]);
    for(i=0; i<=2; i++){
        total = total + arr[i];
    }
    printf("En kucuk 3 elemanin toplami = %d\n", total);
}

void bestThree(int arr[], int size){
    int total = 0,  i;
    size = size - 1;
    printf("En buyuk 3 eleman: %d, %d, %d\n", arr[size], arr[size - 1], arr[size - 2] );
    for(i=size -2; i<=size; i++){
        total = total + arr[i];
    }
    printf("En buyuk 3 elemanin toplami = %d\n", total);
}

int main(){

int size, a = 1, i;

while(a==1){
printf("Dizi boyutunu girin: ");
scanf("%d",&size);

if(size >= 6){
    a = 0;
}
else{
    printf("Ogrenci sayisi 6 veya fazla olmali.\n");
}
}
int grade[size];
printf("Dizi elemanlarini girin.\n");
for(i=0; i<size; i++){
    scanf(" %d", &grade[i]);
}

sort(grade, size);
worstThree(grade);
bestThree(grade, size);

while (a!=1)
{
    printf("Programi kapatmak için 1 tusuna basin.\n");
    scanf("%d", &a);

}


return 0;






}