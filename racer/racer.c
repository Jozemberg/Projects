#include <stdio.h>
#include <stdlib.h>

int main(){
    double posun = 0;
    float posun_var = 1;
    int cas,multiplier = 1;
    double suma_casu = 0;
    int pocet_jazd;
    int charon;
    scanf("%d",&pocet_jazd);
    getc(stdin);
    scanf("%d",&cas);
    float array[pocet_jazd][2];
//----------POLE-----INIT-------------
    for (int i = 0; i < pocet_jazd; ++i) {
        for (int j = 0; j < 2; ++j) {
            scanf("%d",&charon);
            if(charon != 32)array[i][j] = charon;
        }
    }
    for (int i = 0; i < pocet_jazd; ++i) {
        if(posun > array[i][1])posun = array[i][1];
    }
    posun = abs(posun)+0.000001;
    for (int i = 0; i < pocet_jazd; ++i) {if((array[i][1] + posun) != 0)suma_casu += array[i][0] / (array[i][1] + posun);}
//----------------------------------------------------


    for (int i = 0; i < 7; ++i) {
        while(suma_casu > cas){
            posun += posun_var;
            suma_casu = 0;
            for (int j = 0; j < pocet_jazd; ++j) {if((array[j][1] + posun) != 0)suma_casu += array[j][0] / (array[j][1] + posun);}
        }
        while(suma_casu < cas){
            posun -= posun_var/10;
            suma_casu = 0;
            for (int j = 0; j < pocet_jazd; ++j) {if((array[j][1] + posun) != 0)suma_casu += array[j][0] / (array[j][1] + posun);}
        }
        multiplier = multiplier * 10;
        posun_var = posun_var / 10;
    }

    printf("%f\n",posun);
    return 0;
}