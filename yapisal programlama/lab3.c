#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int code;
    char *isim;
    float birimFiyat;
    float kgFiyat;
}product;

void listProducts(product* products){
    int i;
    printf("Kod\tIsim\tBirim fiyat\tKilo fiyat\n");
    for(i=0;i<6;i++){
        printf("%d\t%s\t%.2f\t\t%.2f\n",products[i].code,products[i].isim,products[i].birimFiyat,products[i].kgFiyat);
    }
}

double calculateCost(double cost, int uCode, int type, int amount, product* products){
    uCode--;
    if(type == 1) cost += products[uCode].birimFiyat * amount;
    else cost += products[uCode].kgFiyat * amount;
    return cost;

}

double calculateDiscountedCost(double cost){
    if(cost>=50 && cost<100){
        cost = cost * (95.0 / 100.0);
    }
    else if(cost >100){
        cost = cost * (90.0 / 100.0);
    }
    return cost;
}

double shopping(product* products){
    char check='E';
    int uCode,amount,type;
    float totalcost = 0;
    while(check=='E'){
        listProducts(products);
        printf("Urun kodu giriniz: ");
        scanf("%d",&uCode);
        while(uCode < 1 || uCode >6){
            printf("Lutfen gecerli bir kod giriniz: ");
            scanf("%d", &uCode);
        }
        printf("Alis tipi (1 miktar, 2 kilo): ");
        scanf("%d",&type);
        while(type != 1 && type != 2){
            printf("Lutfen gecerli bir alis tipini seciniz.\n(Alis tipi (1 miktar, 2 kilo): ");
            scanf("%d",&type);
        }
        printf("Miktar giriniz: ");
        scanf("%d", &amount);
        totalcost = calculateCost(totalcost,uCode,type,amount,products);
        printf("Toplam tutar: %.2f\n", totalcost);
        printf("Devam etmek istiyor musunuz? (E/H):");
        scanf(" %c", &check);
        while(check != 'E' && check != 'H'){
            printf("Lutfen gecerli bir secenek seciniz ve buyuk harf kullaniniz.\nDevam etmek istiyor musunuz? (E: Evet   H: Hayir): ");
            scanf(" %c", &check);
        }
    }
    return totalcost;
}

int main(){
    int i;
    float totalcost;
    product products[6];
    product domates; domates.code = 1; domates.isim = "domates"; domates.birimFiyat = 8.25; domates.kgFiyat = 23.75; products[0] = domates;
    product biber; biber.code = 2; biber.isim = "biber"; biber.birimFiyat = 6.25; biber.kgFiyat = 29.50; products[1] = biber;
    product sut; sut.code = 3; sut.isim = "sut"; sut.birimFiyat = 15.85; sut.kgFiyat = 27.15; products[2] = sut;
    product peynir; peynir.code = 4; peynir.isim="peynir";peynir.birimFiyat = 23.00;peynir.kgFiyat=95.50;products[3] = peynir;
    product muz;muz.code=5;muz.isim= "muz";muz.birimFiyat=13.45;muz.kgFiyat=45.50;products[4] = muz;
    product armut; armut.code=6;armut.isim="armut";armut.birimFiyat=5.50;armut.kgFiyat=20.15;products[5] = armut;
    totalcost = shopping(products);
    printf("Toplam tutar: %.2f\n",totalcost);
    totalcost = calculateDiscountedCost(totalcost);
    printf("Indirimli tutar: %.2f\n", totalcost);
    printf("Programdan cikis yapiliyor.");





return 0;
}
