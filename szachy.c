#include <stdio.h>
#define WIN 1000
#define GAME_OVER -1000

char PAWNS[13] = {'K', 'H', 'W', 'G', 'S', 'I', 'k', 'h', 'w', 'g', 's', 'p'};

void wypisz(int b[8][8]){

    printf("    0   1   2   3   4   5   6   7\n");
    for (int i=0; i<8; i++){
        printf("   --- --- --- --- --- --- --- ---\n");
        printf("%d ", i);
        printf("|");
        for (int j=7; j>=0; j--){
            if (b[j][i] == 12){
                printf("   |");
            }
            else{
            printf(" %c |", PAWNS[b[j][i]]);
            }
        }
        printf("\n");
    }
    printf("   --- --- --- --- --- --- --- ---\n");
}



int score(int b[8][8]){
    int result=0;

    int results[13] = {GAME_OVER, -9, -5, -3, -3, -1, WIN, 9, 5, 3, 3, 1, 0};

    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            result += results[b[i][j]];
        }
    }
    return result;
}

                                        //final x, previous x
int generator(int b[8][8], int depth, int *fx, int *fy, int *px, int *py){
    int result, x, y, max, min;
    int MAX_KIER[] = {8,8,4,4,8,3,8,8,4,4,8,3,0};
    int MAX_ODL[] = {1,7,7,7,1,1,1,7,7,7,1,1,0};
    int WX[12][8] = {{0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},{0,1,0,-1},{1,1,-1,-1},
                    {1,2,2,1,-1,-2,-2,-1},{-1,0,1},  {0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},
                    {0,1,0,-1},{1,1,-1,-1},{1,2,2,1,-1,-2,-2,-1},{-1,0,1} };
    int WY[12][8] = {{-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},{-1,0,1,0},{-1,1,1,-1},
                    {-2,-1,1,2,2,1,-1,-2},{-1,-1,-1},  {-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},
                    {-1,0,1,0},{-1,1,1,-1},{-2,-1,1,2,2,1,-1,-2},{1,1,1} };

    // Limit rekurencji
    result = score(b);
    
    if (depth == 0 || 2*result < GAME_OVER || 2*result > WIN) return result;
    // ruch komputera MAX
    if (depth % 2 == 0){
        int max=10*GAME_OVER;
        for (x=0; x<8; x++){
            for (y=0; y<8; y++){
                if (b[x][y]>=6 && b[x][y]<=11){     // sprawdzam czy na tym miejscu jest cos co nalezy do komputera
                    int *pawn = &(b[x][y]);
                    for (int direction=0; direction<MAX_KIER[*pawn]; direction++){
                        for (int distance=1; distance<=MAX_ODL[*pawn]; distance++){
                            // czy ruch nie wyjdzie poza plansze )
                            if ((x+(distance*WX[*pawn][direction]))<8 && (y+(distance*WY[*pawn][direction]))<8 && (x+(distance*WX[*pawn][direction]))>=0 && (y+(distance*WY[*pawn][direction]))>=0){
                                // czy w poprzednim ruchu nie bylo bicia
                                if (distance > 1){
                                    if (b[x+((distance-1)*WX[*pawn][direction])][y+((distance-1)*WY[*pawn][direction])]<6){
                                        distance += 20;
                                    }
                                }
                                int *place = &(b[x+distance*WX[*pawn][direction]][y+distance*WY[*pawn][direction]]);
                                // jeli ruch pionka po ukosie i nie ma nic przeciwnika po ukosie to ruch niemozliwy
                                // jesli ruch nie pionka i cos kopmutera po drodze to blad, lub ruch pionka do przodu ale po drodze wroga figura
                                if ((*pawn==11 && ((WX[*pawn][direction]!=0 && *place>5) || (WX[*pawn][direction]==0 && *place!=12))) || (*pawn!=11 && (*place>5 && *place!=12))){
                                    distance += 20;
                                }
                                else{
                                    // zapisuje w temp figure ktora komputer chce sie ruszyc,
                                    // w temp_p co bylo na polu na ktore komp bada, 
                                    // ruszam sie na badane pole
                                    // wywoluje generator i wstawiam znowu to co bylo
                                    int temp, temp_p;
                                    temp = *pawn;
                                    temp_p = *place;
                                    *place = *pawn;
                                    *pawn = 12;
                                    // promocja na hetmana
                                    if (*pawn==11 && y+distance*WY[*pawn][direction]==7){
                                        *place = 7;
                                    }
                                    // zmienne pomocnicze
                                    int pom1, pom2, pom3, pom4;
                                    result = generator(b, depth-1, &pom1, &pom2, &pom3, &pom4);
                                    *place = temp_p;
                                    *pawn = temp;
                                    if (result>=max){
                                        max = result;
                                        *fy = y+distance*WY[*pawn][direction];
                                        *fx = x+distance*WX[*pawn][direction];
                                        *px = x;
                                        *py = y;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return max;
    }
    // ruch gracza MIN
    else if (depth % 2 != 0){
        int min = 10*WIN;
        for (x=0; x<8; x++){
            for (y=0; y<8; y++){
                if (!(b[x][y]>=6 && b[x][y]<=11)){     // sprawdzam czy na tym miejscu jest cos co nalezy do gracza
                    int *pawn = &(b[x][y]);
                    for (int direction=0; direction<MAX_KIER[*pawn]; direction++){
                        for (int distance=1; distance<=MAX_ODL[*pawn]; distance++){
                            if ((x+distance*WX[*pawn][direction])<8 && (y+distance*WY[*pawn][direction])<8 && (x+distance*WX[*pawn][direction])>=0 && (y+distance*WY[*pawn][direction])>=0){
                                if (distance > 1){
                                    if (b[x+((distance-1)*WX[*pawn][direction])][y+((distance-1)*WY[*pawn][direction])]>5 && b[x+((distance-1)*WX[*pawn][direction])][y+((distance-1)*WY[*pawn][direction])]!=12){
                                        distance += 20;
                                    }
                                }
                                int *place = &(b[x+distance*WX[*pawn][direction]][y+distance*WY[*pawn][direction]]);
                                //sprawdzenie czy na inna figura nie stoi na przeszkodzie
                                // i czy pion bije a nie rusza sie po ukosie na puste pole
                                if ((*pawn==5 && ((WX[*pawn][direction]!=0 && (*place<6 || *place==12)) || (WX[*pawn][direction]==0 && *place!=12))) || (*pawn!=5 && *place<6)){
                                    distance += 20;
                                }
                                else{
                                    // zapisuje w temp figure ktora komputer chce sie ruszyc,
                                    // w temp_p co bylo na polu na ktore komp bada, 
                                    // ruszam sie na badane pole
                                    // wywoluje generator i wstawiam znowu to co bylo
                                    int temp, temp_p;
                                    temp = *pawn;
                                    temp_p = *place;
                                    *place = *pawn;
                                    *pawn = 12;
                                    // promocja na hetmana
                                    if (*pawn==5 && WY[*pawn][direction]==0){
                                        *place = 1;
                                    }
                                    // zmienne pomocnicze
                                    int pom1, pom2, pom3, pom4;
                                    result = generator(b, depth-1, &pom1, &pom2, &pom3, &pom4);
                                    *place = temp_p;
                                    *pawn = temp;
                                    if (result < min){
                                        min = result;
                                        *fy = y+distance*WY[*pawn][direction];
                                        *fx = x+distance*WX[*pawn][direction];
                                        *px = x;
                                        *py = y;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return min;
    }
}

    /*Gracz:        Komputer:
    0 - krol        6 - krol
    1 - hetman      7 - hetman
    2 - wieza       8 - wieza
    3 - goniec      9 - goniec
    4 - skoczek     10 - skoczek
    5 - pionek      11 - pionek
              12 - puste
    */

int main(void){
    int board[8][8] = {
        8, 11, 12, 12, 12, 12, 5, 2,
        10, 11, 12, 12, 12, 12, 5, 4,
        9, 11, 12, 12, 12, 12, 5, 3,
        6, 11, 12, 12, 12, 12, 5, 0,
        7, 11, 12, 12, 12, 12, 5, 1,
        9, 11, 12, 12, 12, 12, 5, 3,
        10, 11, 12, 12, 12, 12, 5, 4,
        8, 11, 12, 12, 12, 12, 5, 2
    };
    
    while (1){
        
        // ruch komputera
        int px, py, fx, fy, wynik;
        generator(board, 4, &fx, &fy, &px, &py);
        printf("%d\n", wynik);
        // promocja na hetmana
        if (board[px][py]==11 && fy==7){
            board[fx][fy] = 7;
        }
        else{
            board[fx][fy] = board[px][py];
        }
        board[px][py] = 12;
        wynik = generator(board, 4, &fx, &fy, &px, &py);
        if (wynik>100){
            printf("Przegrales :(");
            break;
        }

        wypisz(board);
        // Ruch gracza
        int sx, sy, dx, dy;
        printf("skad y skad x, dokad y dokad x : ");
        scanf("%d %d %d %d", &sy, &sx, &dy, &dx);
        
        if (board[7-dx][dy] > 5){
            board[7-dx][dy] = board[7-sx][sy];
            // promocja na hetmana
            if (board[7-dx][dy]==5 && dy==0){
                board[7-dx][dy] = 1;
            }
            board[7-sx][sy] = 12;
            wypisz(board);
        }
        wynik = generator(board, 1, &fx, &fy, &px, &py);
        if (wynik<-100){
            printf("Wygrales!!\n");
            break;
        }
    }
    return 0;
}

// BLEDY
/*
    1. Nie mam ochrony zeby cos nie przeskoczylo nad figura przeciwnika
    2. Mat komp mat gracz
    3. Pat
    4. Roszady
    5. Mala glebia
    6. W pierwszym ruchu pion 2 do przodu
    7. Czy gracz robi dobre ruchy
*/
