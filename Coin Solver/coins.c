#include<stdio.h>
#include<stdlib.h>

int is_over(int sum , int current_sum){

  if(current_sum == sum)
      return 1;
  return 0;
}
int is_valid(int sum , int current_sum , int value){

  if( current_sum + value > sum)
      return 0;
  return 1;
}

void print_road(int step , int road[]){

  for(int i = 0 ; i < step ; ++i)
      printf(" %d " , road[i]);
  printf("\n");
}

void coins_solver(int sum , int current_sum , int step , int * road){

    const static int coins[] = {20 , 10 , 5 , 1};           //This is my set of coins modify if you want another one

    if(is_over(sum , current_sum) ){
        print_road(step , road);
        return;
    }
    else{
        for(int k = 0 ; k < 4 ; ++k){
            if(is_valid(sum , current_sum , coins[k])  ){

                 if(step >= 1 && coins[k] > road[step - 1] )
                          continue;

                road = (int *)realloc(road , (step + 1) * sizeof(int) );
                road[step] = coins[k];

                coins_solver(sum , current_sum + coins[k], step + 1  , road);
            }
        }
   }
}
int main(){

  int sum;
  static int * road = NULL;

  printf("Enter the given amount of money : ");
  scanf("%d" , &sum);

  coins_solver(sum , 0 , 0 , road);
  free(road);
  return 0;
}
