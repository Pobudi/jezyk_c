#include <stdio.h>
#define WYGRANA 1000
#define PRZEGRANA -1000

int ocena(char board[3][3]){
    int i, j, remis=1;
    for (i=0; i<3; i++){
        if (board[i][0]=='x' && board[i][1]=='x' && board[i][2] == 'x') return WYGRANA;
        if (board[i][0]=='o' && board[i][1]=='o' && board[i][2] == 'o') return PRZEGRANA;
        if (board[0][i]=='x' && board[1][i]=='x' && board[2][i] == 'x') return WYGRANA;
        if (board[0][i]=='o' && board[1][i]=='o' && board[2][i] == 'o') return PRZEGRANA;   
    }
    if (board[0][0]=='x' && board[1][1]=='x' && board[2][2]=='x') return WYGRANA;
    if (board[0][0]=='o' && board[1][1]=='o' && board[2][2] == 'o') return PRZEGRANA;
    if (board[0][2]=='x' && board[1][1]=='x' && board[2][0]=='x') return WYGRANA;
    if (board[0][2]=='o' && board[1][1]=='o' && board[2][0] == 'o') return PRZEGRANA;

    for (i=0; i<3; i++){
        for (j=0; j<3; j++){
            if (board[i][j] == ' '){
                remis=0;
            }
        }
    }
    return remis;   
}


void wypisz(char board[3][3]){
    printf("%c|%c|%c\n", board[0][0], board[0][1], board[0][2]);
    printf("------\n");
    printf("%c|%c|%c\n", board[1][0], board[1][1], board[1][2]);
    printf("------\n");
    printf("%c|%c|%c\n", board[2][0], board[2][1], board[2][2]);
}


int generator(char board[3][3], int tryb, int *x, int *y){
    long int wynik;
    long int max_wynik, min_wynik; 
    int nx, ny, puste=1, i, j;
    wynik = ocena(board);
    if (wynik == PRZEGRANA || wynik == WYGRANA || tryb==0){
        return wynik;
    }
    // Ruch komputera
    if (tryb%2==0){
        for (i=0, max_wynik=2*PRZEGRANA; i<3; i++){
            for(j=0; j<3; j++){
                if (board[i][j] == ' '){
                    board[i][j] = 'x';
                    wynik = generator(board, tryb-1, &nx, &ny);
                    board[i][j] = ' ';
                    if (wynik > max_wynik){
                        //printf("%ld\n",wynik);
                        max_wynik = wynik;
                        *x = i;
                        *y = j;
                        puste = 0;
                    }
                }
            }
        }
        if (puste) return 0;
        else return max_wynik;
    }
    // Ruch gracza
    else if (tryb%2!=0){
        for (i=0, min_wynik=2*WYGRANA; i<3; i++){
            for (j=0; j<3; j++){
                if (board[i][j] == ' '){
                    board[i][j] = 'o';
                    wynik = generator(board, tryb-1, &nx, &ny);
                    board[i][j] = ' ';
                    if (wynik < min_wynik){
                        min_wynik = wynik;
                        *x = i;
                        *y = j;
                        puste = 0;
                    }
                }
            }
        }
        if (puste) return 0;
        else return min_wynik;
    }
}


int main(){
    char board[3][3];
    int wynik, i, j, tx, ty, numer=0, x, y, check=1, remis=0;
    for (i=0; i<3; i++){
        for(j=0; j<3; j++){
            board[i][j] = ' ';
        }
    }
    while (1){
        if (check){ 
            generator(board,10, &x, &y);
            board[x][y]='x';
            wypisz(board);
            wynik = ocena(board);
        }
        if (wynik==WYGRANA){
            printf("przegrales\n");
            return 0;
        }
        else if (wynik==PRZEGRANA){
            printf("wygrales\n");
            return 0;
        }
        else if (wynik == 1){
            printf("remis\n");
            return 0;
        }
        printf("podaj miejsce: ");
        scanf("%d %d", &tx, &ty);
        if (board[tx][ty] == ' ' && tx<3 && ty<3){
            check = 1;
            board[tx][ty] = 'o';
            wypisz(board);
        }
        else{
            printf("podano zle miejce\n");
            check = 0;
        }
        printf("\n");
    }

    return 0;
}

