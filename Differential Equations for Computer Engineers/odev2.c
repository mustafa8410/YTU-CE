#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct equation{
    //right side
    int elementNumber;
    int *type;
    double *rightCoefficient;
    double *rightInsideCoefficient;
    //left side
    double *leftCoefficient;

    //generic
    double t; //ulasmamiz gereken son t degeri
    double y; // y(t)
    
};

double calculateFunction(struct equation e, double t){
    int i;
    double result=0;
    for(i=0;i<e.elementNumber;i++){
        switch(e.type[i]){
            case 1:
            result += pow(t,e.rightInsideCoefficient[i]) * e.rightCoefficient[i]; 
            break;
            case 2:
            result += exp((t * e.rightInsideCoefficient[i])) * e.rightCoefficient[i]; break;
            case 3:
            result += sin((t * e.rightInsideCoefficient[i])) * e.rightCoefficient[i]; break;
            case 4:
            result += cos((t * e.rightInsideCoefficient[i])) * e.rightCoefficient[i];break;
            case 5:
            result += tan((t * e.rightInsideCoefficient[i])) * e.rightCoefficient[i];break;
            case 6:
            result += 1.0 /( tan((t * e.rightInsideCoefficient[i])) * e.rightCoefficient[i] );break;
            case 7:
            result += 1.0 /( cos((t * e.rightInsideCoefficient[i])) * e.rightCoefficient[i] );break;
            case 8:
            result += 1.0 / (sin((t * e.rightInsideCoefficient[i])) * e.rightCoefficient[i]);break;
            case 9:
            result += sinh((t * e.rightInsideCoefficient[i])) * e.rightCoefficient[i];break;
            case 10:
            result += cosh((t * e.rightInsideCoefficient[i])) * e.rightCoefficient[i];break;
            case 11:
            result += tanh((t * e.rightInsideCoefficient[i])) * e.rightCoefficient[i];break;
            case 12:
            result += 1.0 /( tanh((t * e.rightInsideCoefficient[i])) * e.rightCoefficient[i] );break;
        }
    }
    return result;
}

void RungeKutta(struct equation e){
    double t,eps,y,k1,k2,k3,k4,oldt = t,error;
    int iteration=0;
    
    printf("Baslangic t degeri: ");
    scanf(" %lf", &t);
    printf("Baslangic t degeri icin y(t): ");
    scanf(" %lf", &y);        
    printf("Adim sayisi: ");
    scanf(" %lf", &eps);
    printf("\n");

    do{
        k1 = eps * ( calculateFunction(e,t) - y * e.leftCoefficient[0] ) / e.leftCoefficient[1];
        k2 = eps * ( calculateFunction(e,(t + eps/2.0)) - y * e.leftCoefficient[0] - k1/2.0 ) / e.leftCoefficient[1];
        k3 = eps * ( calculateFunction(e,(t + eps/2.0)) - y * e.leftCoefficient[0] - k2/2.0 ) / e.leftCoefficient[1];
        k4 = eps * ( calculateFunction(e,(t + eps)) - y * e.leftCoefficient[0] - k3) / e.leftCoefficient[1];
        y = y + ((k1 + 2.0*k2 + 2.0*k3 + k4) / 6.0 );
        oldt = t;
        t = t + eps;
        printf("%d. iterasyon:\ny=%.3lf\tt=%.3lf\n",++iteration,y,t); 
    }while(oldt < e.t && t < e.t);
    printf("\n\nSon bulunan y degeri: %.3lf\n",y);
    printf("Bunu saglayan t: %.3lf  ",t);
    error = fabs(y - e.y);
    printf("Mutlak hata: %.3lf  ",error);



}

// 1 x  2 e  3 sinx 4 cosx 5 tanx 6 cotx 7 secx 8 cosecx 9 sinh 10 cosh 11 tanh 12 coth

int main(){
    int game,i;   

    do{
    struct equation e;
    printf("Denklemin eleman sayisi: ");
    scanf(" %d", &e.elementNumber);

    e.type = (int*) malloc(e.elementNumber * sizeof(int));
    e.rightCoefficient = (double*) malloc(e.elementNumber * sizeof(double));
    e.leftCoefficient = (double*) malloc(2 * sizeof(double));
    e.rightInsideCoefficient = (double*) calloc(e.elementNumber,sizeof(double));



    for(i=0;i<e.elementNumber;i++){
        printf("%d. elemanin tipi: (1:t,2:e^t,3:sint,4:cost,5:tant,6:cott,7:sect,8:cosect,9:sinht,10:cosht,11:tanht,12:cotht)",(i+1));
        scanf(" %d",&e.type[i]);
        while(e.type[i] < 1 && e.type[i] > 12){
            printf("Lutfen min 1, max 12 veriniz.\n");
            scanf(" %d", &e.type[i]);   
        }

        if(e.type[i] == 1){
            printf("t'li terimin ussu: ");
            scanf(" %lf",&e.rightInsideCoefficient[i]);
        }
        else if(e.type[i] == 2){
            printf("e'nin ussu olan t'nin katsayisi: ");
            scanf(" %lf", &e.rightInsideCoefficient[i]);
        }
        else if(e.type[i] > 2 && e.type[i] <=12){
            printf("Trigonometrik ifadenin icindeki t'nin katsayisi: ");
            scanf(" %lf", &e.rightInsideCoefficient[i]);
        }
        printf("%d. elemanin katsayisi: ", (i+1));
        scanf(" %lf", &e.rightCoefficient[i]);
    }

    printf("Denklemin sol tarafindaki y ve y' degerleri icin katsayilari girin.\n");
    for(i=0;i<2;i++){
        switch (i){
            case 0:
            printf("y 'nin katsayisi: "); break;
            case 1:
            printf("y'nin turevinin katsayisi: ");break;
        }
        scanf(" %lf", &e.leftCoefficient[i]);
    }
    
    printf("Ulasilmak istenen y(t) degeri: ");
    scanf(" %lf",&e.y);
    printf("Bu degeri saglayan t degeri: ");
    scanf(" %lf",&e.t);

    RungeKutta(e);


    free(e.type);free(e.leftCoefficient);free(e.rightCoefficient);free(e.rightInsideCoefficient);

    printf("Cikmak icin 0'a, devam etmek icin 1'e basin: ");
    scanf(" %d",&game);
    while(game != 0 && game!=1){
        printf("Lutfen gecerli bir giris yapin: ");
        scanf(" &d",&game);
    }
    }while(game==1);

    return 0;
}
