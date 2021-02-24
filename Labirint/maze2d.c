#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// !!!!! ----- The name of the file is map.txt  !!!!! ----- ////

#define N 200       //Max dimensions of the labyrinth

#define liber '.'
#define blocaj '#'
#define marcaj 'X'

#define start_x 1     //The starting coordinates
#define start_y 1


int shortest_path = 0x7FFFFFFF ;
char map[N][N];
int road[N*N];
int n , m;

//Versorii

int dx[] = {1 , 0 , 0 , -1};
int dy[] = {0 , -1 , 1 , 0};

void print_map();

int all_right(int x , int y){

    if(x >= 0  &&  x < n && y >= 0 && y < m)
      if(map[x][y] == liber)
         return 1;
    return 0;
}
int check_winner(int x , int y){

      if(x == 0  || y == 0 || x == (n - 1) || y == (m - 1) )
          if(map[x][y] == liber || map[x][y] == marcaj)
                return 1;
      return 0;
}
void minim(int x){

    if(x < shortest_path)
        shortest_path = x + 1;
}
void print_road(int step){

    printf("This is the road : \n\n(%d , %d)\n" , start_x , start_y);
    for(int i = 0 ; i < step ; i = i + 2)
        printf("(%d , %d)\n" , road[i] , road[i + 1]);

    printf("\n\n");
}

void maze_2d(int x , int y , int step){

      map[x][y] = marcaj;

      if( check_winner(x , y) ){

          minim(step / 2);
          print_map();
          print_road(step);
          return;
      }
      else{
            for(int k = 0 ; k < 4 ; ++k){

                int new_x = x + dx[k];
                int new_y = y + dy[k];

                if( all_right(new_x , new_y) ){

                  road[step] = new_x;
                  road[step + 1] = new_y;

                  maze_2d(new_x  ,new_y , step + 2);

                  map[new_x][new_y] = liber;
                }
            }
      }
}

void read_map(){

      FILE *fp;
      fp = fopen ("maze.txt","r");
      if(!fp){
        perror("Something went wrong while opening the file");
        exit(0);
      }

      int i = 0 , j = 0;
      while(1){

        if(feof(fp))
              break;

        char c;
        c = fgetc(fp);
        if( c != '\n'){
            map[i][j] = c;
            ++j;
        }
        else{
          m = j;
          j = 0;
          ++i;
        }
      }
      n = i ;
      fclose(fp);
}
void print_map(){

      printf("This is the maze : \n\n");

      for(int i = 0 ; i < n ; ++i){
          for(int j = 0 ; j < m ; ++j){
              printf("%c" , map[i][j]);
         }
         printf("\n");
      }
      printf("\n\n");
}
int main(){

    read_map();
    print_map();
    maze_2d(start_x , start_y , 0);
    printf("\nThe shortest path is : %d\n\n" , shortest_path );

   return 0;
}
