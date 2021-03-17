#include<stdio.h>
#include<stdlib.h>

#define N 8    //The matrix's number of columns & rows
#define NN N*N


#define xg 0		//Xg represents one of coords of the starting point
#define yg 0			//Yg represents the other coord of the starting point
						//They are used in the defeu(x,y) func. in main

int found;

int map[N][N];				//the 8x8 matrix

//I will be using two director vectors(the order counts !!!!!)

int dx[] = {  2, 1, -1, -2, -2, -1,  1,  2 };
int dy[] = {  1, 2,  2,  1, -1, -2, -2, -1 };

void print_map();

int check_position_valid(int x , int y){

	return (x >= 0 && x < N && y >= 0 && y < N);	
}

void init_map(){

	for(int i = 0 ; i < N ; ++i)
		for(int j = 0 ; j < N ; ++j)
					map[i][j] = -1;

	map[xg][yg] = 0;
}

void defeu(int x , int y ,int counter){

		if(counter  == NN ){
			++found;
		}
		else{
			for(int k = 0 ; k < 8 ; ++k){

				int new_x = x + dx[k];
				int new_y = y + dy[k];

						if( map[new_x][new_y] == -1 && check_position_valid(new_x , new_y)){

								map[new_x][new_y] = counter;
								defeu(new_x , new_y , counter + 1 );

								if(!found)
									map[new_x][new_y] = -1;
						}
			}
		}

}

void print_map(){

	for(int i = 0 ; i < N ; ++i){
		for(int j = 0 ; j < N ; ++j){
			if(map[i][j] < 10)
				printf("  %d " ,map[i][j]);
			else
				printf(" %d " , map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(){

	init_map();
	defeu(xg , yg , 1);
	print_map();

	return 0;
}
