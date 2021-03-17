#include<stdio.h>
#include<stdlib.h>

#define Mmax 1000
#define Nmax 100001

int n , m , s , y = 1 ;    //nodes , edges and the starting node
int A[Mmax][Mmax]  , viz[Nmax] , C[Mmax];


void BFS(){

      int first = 0 , last = 0  ;
     printf("\n %d " , s);
      viz[s] = 1 ;
      C[0] = s ;


      while( first <= last ){

            s = C[first++] ;
            for(int i = 1 ; i <= A[s][0] ; i++){

                  if( viz[ A[s][i] ] != 1 ){

                        viz[ A[s][i] ] = 1;
                        printf(" %d " , A[s][i]);
                        C[++last] = A[s][i] ;
                  }
            }
      }

}
void read(FILE * input){

      int x , y , copy;
      fscanf(input , "%d %d %d " , &n , &m , &s);
      copy = m ;

      while( copy ){

            fscanf(input , "%d %d" , &x , &y);
            A[x][0] ++;
            A[x][ A[x][0] ] = y;
            --copy;
      }

}

int main(){

  FILE * input ;

  input = fopen( "bfs.in" , "r");
  if(!input){
        perror("Eror while opening file");
        return 0;
  }

  read( input );


  for(int i = 0 ; i <= n ; i++){
    for(int j = 0 ; j <= m ; j++)
            printf(" %d " , A[i][j]);
      printf("\n");
  }

//printf("\n\n%d" , sizeof(float));

  return 0;
}
