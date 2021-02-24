#include<stdio.h>
#include<string.h>

#define N 9

int sudoku[N][N] = {
					  					{3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}
                  };


int check_linie(int x , int y , int valoare_tabla){

	for(int i = 0 ; i < N ; ++i)
		if(sudoku[x][i] ==  valoare_tabla)
			return 0;
	return 1;

}

int check_patratel(int x , int y , int valoare_tabla){

	for(int i = 0 ; i < 3 ; ++i){
		for(int j = 0 ; j < 3 ; ++j){
			if(sudoku[x + i][ y + j ] == valoare_tabla)
				return 0;
		}
	}
	return 1;
}

int check_coloana(int x , int y , int valoare_tabla){

	for(int i = 0 ; i < N ; ++i)
		if(sudoku[i][y] == valoare_tabla )
			return 0;
	return 1;

}

int reuneste_checkurile(int x, int y , int valoare_tabla){

	return ( check_linie(x,y ,valoare_tabla) && check_coloana(x , y , valoare_tabla) &&
			check_patratel(x - x % 3 , y - y % 3 , valoare_tabla) && !sudoku[x][y] );
}

int find_locatie(int *x , int *y){

	int ok = 1;
	for(int i = 0 ; i < N  && ok ; ++i)
		for(int j = 0 ; j < N ; ++j){

			if( !sudoku[i][j] ){
				*x = i;
				*y = j;
				ok = 0;
			}
		}
	if(!ok)
		return 1;
	return 0;
}
int sudoku_fct(){

	int new_x , new_y;

	if(!find_locatie(&new_x ,&new_y) )
		return 1; // a.k.a am terminat treaba ca e plin sudoku

	//printf("Eu sunt new_x : %d si new_y : %d \n" , new_x ,new_y);

	for(int i = 1 ; i < 10 ; ++i){

			if( reuneste_checkurile(new_x , new_y , i) ){

				sudoku[new_x][new_y] = i;

				if(sudoku_fct() )
					return 1;

				sudoku[new_x][new_y] = 0;
			}
	}

	return 0;
}
void print_sudoku(){

	for(int i = 0 ; i < N ; ++i){
		for(int j = 0 ; j < N ; ++j){
			printf(" %d ", sudoku[i][j] );
		}
		printf("\n");
	}
}
int main(){

	sudoku_fct();
	print_sudoku();

	return 0;
}
