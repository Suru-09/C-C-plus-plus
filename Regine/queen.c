#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define Q 1
#define liber 0

void print_map(int N ,int map[N][N]);

int is_winner(int x , int N){

    if(x == N)
        return 1;
    return 0;
}

int check_row(int x , int N , int map[N][N]){

    for(int i = 0 ; i < N ; ++i)
        if(map[x][i] == Q)
            return 0;
    return 1;
}
int check_column(int y , int N , int map[N][N]){

    for(int i = 0 ; i < N ; ++i)
        if(map[i][y] == Q)
            return 0;
    return 1;
}

int valid_pos(int x , int y , int N){

      return ( x >= 0 && x < N && y >= 0 && y < N );
}
int check_diag(int x , int y , int N , int map[N][N]){

        int dx , dy;

        for(int i = 0 ; i < N ; ++i){
          for(int j = 0 ; j < N ; ++j){

              dx = abs( x - i );
              dy = abs( y - j );

              if(dx == dy && map[i][j] == Q && i != x && j != y)
                    return 0;
          }
        }

        return 1;
}
int check_all_good(int x , int y , int N , int map[N][N] ){

    return ( check_row(x , N , map) && check_column(y , N , map )
            && map[x][y] == liber && valid_pos(x , y , N) && check_diag(x , y , N , map) );
}

void queen(int N , int map[N][N] , int x , int y , int nr_queens , int * winner){

    if( is_winner(nr_queens , N) ){
          print_map(N , map);
          (*winner)++;
          return;
      }
      else{
          for(int  k = 0 ; k < N ; ++k){

              if( check_all_good(x , k , N , map) ){

                  map[x][k] = Q;
                  queen(N , map , x + 1 , k , nr_queens + 1 , winner );
                  map[x][k] = liber;
              }
          }
      }
}
void print_map(int N ,int map[N][N]){

      for(int i = 0 ; i < N ; ++i){
          for(int j = 0 ; j < N  ; ++j){
            printf(" %d " , map[i][j]);
          }
          printf("\n");
      }
      printf("\n\n");
}
int main(){

    int N;
    printf("The dimensions of the table  : ");
    scanf("%d" , &N);

    int map[N][N];
    memset(map , 0 , N * N * sizeof(int));

    int winner_count = 0;
    queen(N ,  map , 0 , 0 , 0 , &winner_count);
    printf("\n\nWe have this many solutions : %d\n" , winner_count);


  return 0;
}
