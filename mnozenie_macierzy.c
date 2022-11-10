#include <stdio.h>

void mnoz(double m1[3][3], double m2[3][3], double m3[3][3]){
    int i, j, k, suma=0;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            for(int k=0; k<3; k++){
                suma = suma + (m1[i][0+k] * m2[0+k][j]);

            }
            m3[i][j] = suma;
            suma =0;
            printf("%4.0f", m3[i][j]);
        }
        printf("\n");
    }
}

void dodaj(double m1[3][3], double m2[3][3], double m3[3][3]){
    int i, j, suma=0;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            m3[i][j] = m1[i][j] + m2[i][j];
            printf("%4.0f", m3[i][j]);
        }
        printf("\n");
    }

}

void wczytaj(double m[3][3]){
    printf("Podaj 9 liczb: \n");
    for(int i = 0; i<3; i++){
        for(int j=0; j<3; j++){
            scanf("%lf", &(m[i][j]));
        }
    }
    return;
}

void wypisz(double m[3][3]){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%4.0f", m[i][j]);
        }
        printf("\n");
    }
}

int main(void){
    double m3[3][3];
    double m4[3][3];
    double m5[3][3];

    wczytaj(m3);
    printf("\n");
    
	wczytaj(m4);
    printf("\n");
    
	dodaj(m3, m4, m5);
	printf("\n");
    mnoz(m3, m4, m5);
    
	return 0;
}
