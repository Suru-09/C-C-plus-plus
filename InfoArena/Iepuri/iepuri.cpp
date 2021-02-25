#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#define mod 666013

int64_t F[3][3];

void reset(){

      for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                  F[i][j] = 0;
}
void inmultire(int64_t A[3][3] , int64_t B[3][3]){

      for(int i = 0 ; i < 3 ; i++)
          for(int j =0 ; j < 3 ; j++)
              for(int k =0 ; k < 3 ; k++){

                      F[i][j] = ( F[i][j] +  A[i][k] * B[k][j] ) % mod;
              }
}

void copy(int64_t A[3][3]){

        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++){
                    A[i][j] = F[i][j] ;
            }
            reset(); //trebuie reset F-ul dupa fiecare apelare la inmultire
                    // pentru ca se salvaeza inmultirea in el si se aduna dupa

}
void expo( int n, int64_t A[3][3] , int64_t B[3][3] ){

        while(n){

            if(n & 1){

                inmultire(A , B);
                copy(B);
            }

            n = n / 2;
            inmultire(A , A );
            copy(A);
        }
}
int main(){

    FILE *input , *output;

    input = fopen("iepuri.in" , "r");
    if(!input){
            perror("Nu-i bun");
            return 0;
    }

    output = fopen("iepuri.out" , "w");
    if(!output){
            perror("Al doilea nu-i bun");
            return 0;
    }

    int T ;     //numarul de seturi
    fscanf(input , "%d" , &T);

    if(T > 100){
          perror("prea multe seturi");
          return 0;
    }

    int X , Y , Z , A , B, C ;
    int n;
    int res = 7 ;

    while(res == 7){

      res = 0;
      res += fscanf(input ,"%d %d %d" , &X , &Y , &Z);
      res += fscanf(input ,"%d %d %d" , &A , &B , &C);
      res += fscanf(input , "%d" , &n);

      int64_t D[3][3] = { {A , B , C} , {1 , 0 ,0 } , { 0 , 1 ,0 } };
      int64_t E[3][3] = { {A , B , C} , {1 , 0 ,0 } , { 0 , 1 ,0 } };

      //printf("%d  %d %d \n" , X , Y , Z);
      //printf("%d %d %d \n" , A , B , C);
      //printf("%d\n\n" , n);

      expo(n - 2 , D , E );
      if(res == 7 )
            fprintf(output , "%li\n" , ( (E[1][0] * Z ) + (E[1][1] * Y ) + (E[1][2] * X)  ) % mod);

        /*
          for(int i = 0 ; i < 3 ; i++){
              for(int j = 0 ; j < 3 ; j++){
                    printf("%li " , E[i][j]);
                  }
                printf("\n");
          }

        printf("\n\n");
        */
      //Resetam C-ul

      reset();

    }

    fclose(input);
    fclose(output);

  return 0;
}
