#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define mod 666013

int64_t A[2][2] = { {0 , 1} , {1 , 1} };
int64_t B[2][2] = { {0 , 1} , {1 , 1} };
int64_t C[2][2] ;

void inmultire( int64_t A[2][2] , int64_t B[2][2]);
void copy( int64_t A[2][2], int64_t B[2][2] );

int64_t puterelog(int n){

        while ( n > 0 ) {
            if ( n % 2 == 1 ) {
                    inmultire( A, B );
                    copy( B, C );
                }
            n /= 2;
            inmultire( A, A );
            copy( A, C );
                }
}

void inmultire( int64_t A[2][2] , int64_t B[2][2]){


      C[0][0] = ( A[0][0] * B[0][0] +  A[0][1] * B[1][0] ) % mod;
      C[0][1] = ( A[0][0] * B[0][1] +  A[0][1] * B[1][1] ) % mod;
      C[1][0] = ( A[1][0] * B[0][0] +  A[1][1] * B[1][0] ) % mod;
      C[1][1] = ( A[1][0] * B[0][1] +  A[1][1] * B[1][1] ) % mod;
}

void copy( int64_t A[2][2], int64_t B[2][2] ) {

    int l, c;
      for ( l = 0; l < 2; l ++ ) {
          for ( c = 0; c < 2; c ++ )
                A[l][c] = B[l][c];
              }
            }

int main(){

    FILE * input , * output ;

    input = fopen( "kfib.in" , "r");
    if(!input){

          perror("nu-i bun ");
          return 0;
    }

    output = fopen ( "kfib.out" , "w ");
    if(!output){

          perror("nu-i bun ");
          return 0;
    }


    int64_t k ;
    fscanf( input , "%li" , &k );

    puterelog( k - 1 );
    fprintf(output , "%li" , B[0][1]);

  return 0;
}
