#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

#define nr_el 512

struct vector{

    int c;
    int frequency;

}my_vector[nr_el];

struct node{

    int frequency;
    char c;
    int f[2];       //f(0) e stanga  ,  f(1) e dreapta
};


int n ;                        //Nr of letters in the file
struct node queue[nr_el];      //Theoretically I'm using 2 queues , practically it is easier with only one
int vector_aparitie[nr_el];    //The vector in which I'll save the elements and sort them
struct node encoded[nr_el];    //The final result
int T = 0;                     //The minimum tree size that I obtain

int l[2] , r[2];            //The left and right of the queues

void swap (int i , int j){
    int aux;
    char aux1;

    aux = my_vector[i].frequency;
    aux1 = my_vector[i].c;

    my_vector[i].frequency = my_vector[j].frequency;
    my_vector[i].c = my_vector[j].c;

    my_vector[j].frequency = aux;
    my_vector[j].c = aux1;
}
void sort_vector_struct(){

    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            if (my_vector[i].frequency > my_vector[j].frequency)
                swap(i , j);
}

void open_file_sort_vector_print(){

    FILE *in;
    in = fopen("huffman.in" , "r");

    if(!in){
        printf("An error occured while opening the file\n");
        exit(1);
    }

    //------------- This Section does the sorting and counting of the letters --------------//
   int i = 0;
   while(1){

       ++i;
       fscanf(in , "%lc" , &my_vector[i].c);
       if(feof(in))
           break;
   }
   n = i;

   for(int i = 1 ; i <= n ; i++){
       vector_aparitie[my_vector[i].c] ++;
   }

   n = 0;
   for(int k = 1 ; k <= 255 ; k++){
       if(vector_aparitie[k]){
           ++n;
           my_vector[n].c = k;
           my_vector[n].frequency = vector_aparitie[k];
       }
   }
   sort_vector_struct();

    fclose(in);
}
void defeu(int tot , int bits ){

        if(queue[tot].f[0] && queue[tot].f[1] ){

            defeu(queue[tot].f[0] , bits * 2 );
            defeu(queue[tot].f[1] , bits* 2 + 1 );
            return;
        }
        encoded[tot].frequency = bits;
        encoded[tot].c = queue[tot].c;
}
void initialise_node(struct node * temp){

    temp->frequency = 0;
    temp->c = 0;
    temp->f[0] = 0;
    temp->f[1] = 0;

}
bool empty_both_queues(){

    if( (r[0] - l[0]) && (r[1] - l[1]))
        return 0;
    return 1;
}
bool empty_first_queue(){

    if(r[0] - l[0])
        return 0;
    return 1;
}
void fill_queue(){

    for(int j = 1 ; j <= n ; ++j){
            queue[j].frequency = my_vector[j].frequency;
            queue[j].c = my_vector[j].c;
    }

   l[0] = 1;
   r[0] = n + 1;
   l[1] = n + 1;
   r[1] = l[1];

    for(int i = 1 ; i < n ; ++i){

        struct node temp;
        initialise_node(&temp);

        for(int j = 0 ; j < 2 ; ++j){

            if( !empty_both_queues() ){
                if( queue[l[0]].frequency < queue[l[1]].frequency){

                    temp.frequency += queue[l[0]].frequency;
                    temp.f[j] = l[0];
                    ++l[0];
                }
                else{
                    temp.frequency += queue[l[1]].frequency;
                    temp.f[j] = l[1];
                    ++l[1];
                }
            }
            else{
                if( !empty_first_queue() ){
                    temp.frequency += queue[l[0]].frequency;
                    temp.f[j] = l[0];
                    ++l[0];
                }
                else{
                    temp.frequency += queue[l[1]].frequency;
                    temp.f[j] = l[1];
                    ++l[1];
                }
            }
        }
        T += temp.frequency;
        queue[r[1]] = temp;
        ++r[1];
    }
}
void print_bits(int j , FILE * out) {

        unsigned i;
        for (i = 1 << sizeof(int); i > 0; i = i / 2) {
            if (encoded[j].frequency & i) {
                fwrite("1" , 1 , sizeof(char) , out);
            } else
                fwrite("0" , 1 , sizeof(char) , out);
        }
}
void solve(){

    open_file_sort_vector_print();
    fill_queue();
    defeu(2* n - 1, 0 );

//    for(int i = 1 ; i <= 2 * n - 1 ; i++){
//        printf("\n%c %d %d %d" , queue[i].c , queue[i].frequency , queue[i].f[0] , queue[i].f[1]);
//    }

    FILE  * out;
    out = fopen("huffman.out" , "w");

    for(int j = 1 ; j <= n ;j++) {
        if(!isprint(encoded[j].c) || isspace(encoded[j].c)){
            fprintf(out , "%u  ", encoded[j].c );
        }
        else{
            fputc(encoded[j].c , out);
            fputs("  " , out);
        }
        print_bits(j , out);
        fputc('\n' , out);
    }
    fprintf(out  ,"\nThe minimum tree size that I obtained is : %d" , T  );
    fclose(out);
}
int main() {

    solve();
    return 0;
}
