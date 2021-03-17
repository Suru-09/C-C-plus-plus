#include <stdio.h>
#include<stdlib.h>

#define size 10000

#define image_height 1000
#define image_width 1000

unsigned reverseBits(unsigned num)
{
    unsigned nr_bits = 8;
    unsigned reverse_num = 0, i, temp;

    for (i = 0; i < nr_bits; i++)
    {
        temp = (num & (1 << i));
        if(temp)
            reverse_num |= (1 << ((nr_bits - 1) - i));
    }

    return reverse_num;
}

//Error handling function

void file_error_handler(FILE * file){

    if(!file){
        printf("ERROR at opening the file!\n");
        exit(EXIT_FAILURE);
    }
}
char * extract_text_from_image(FILE * file ){

    char * ret_str = malloc(size + 1);
    int j = 0 ;

    char format[5];
    unsigned  height , width , color;
    fscanf(file , "%s %d %d %d" , format , &height , &width , &color);

    unsigned newNumber = 0;
    for(unsigned i = 0 ; i < size; ++i) {
        unsigned red, green, blue;
        fscanf(file, "%d %d %d", &red, &green, &blue);

        newNumber = newNumber | (green & 1);
        newNumber <<= 1;
        if( i > 0 && !(i % 7)){
            if(i == 7)			//The condition for the first character met(it would be
                newNumber >>= 1;	//shifted to left 8 times instead of 7).

            newNumber = reverseBits(newNumber);	//The text was inserted from right to left
            ret_str[j++] = newNumber;			//therefore I must reverse it while extracting the text
            newNumber = 0;
        }
    }
    ret_str[j] = '\0';

    return ret_str;
}
void insert_encrypted_text(FILE * file , char * text){

    FILE * out = fopen("encrypted.ppm" , "w");
    file_error_handler(out);

    char format[5];
    unsigned   height , width , color;
    fscanf(file , "%s %d %d %d" , format , &height , &width , &color);
    fprintf(out , "%s\n %d %d \n%d\n" , format , height , width , color);

    unsigned k = 0 ;
    unsigned nr = (unsigned)text[k];

    for(unsigned i = 0 ; i < image_height * image_width ; ++i){
        unsigned red , green , blue;
        fscanf(file , "%d %d %d" , &red , &green , &blue);

        green = green & (green - 1);
        green = green | (nr & 1u );		//the text will be in reverse order !!!
        nr >>= 1;

        fprintf(out , "%d %d %d  " , red , green ,blue );

        if( i > 0 && !(i % 7) && text[k])
            nr = (unsigned)text[++k];

    }
    fclose(out);
    FILE * open = fopen("encrypted.ppm" , "r");
    file_error_handler(open);

    char * string = extract_text_from_image(open);
    printf("The text that you have encrypted is : %s\n" , string);
}
void fill_black_gradient(FILE * file){

    fprintf(file ,"P3\n%d %d\n255\n" , image_width , image_height);
    int red_index = 0 , green_index = 0 , blue_index = 0;
    for(int i = 0 ; i < image_height ; ++i){
        for(int j = 0 ; j < image_width ; ++j){
            fprintf(file ,"%d %d %d  " , red_index , green_index , blue_index);
        }
        fprintf(file , "\n");
        if( !(i % 4) ){
            ++red_index;
            ++blue_index;
            ++green_index;
        }
    }
}
void black_to_white_vertical_gradient(char *file_name){

    FILE * fp = fopen(file_name , "w");
    file_error_handler(fp);

    fill_black_gradient(fp);
    fclose(fp);
}
void fill_violet_gradient(FILE * file){

    fprintf(file ,"P3\n%d %d\n255\n" , image_width , image_height);
    int red_index = 30, green_index = 0 , blue_index = 30;
    for(int i = 0 ; i < image_height ; ++i){
        for(int j = 0 ; j < image_width ; ++j){
            fprintf(file ,"%d %d %d  " , red_index , green_index , blue_index);
        }
        fprintf(file , "\n");
        if( !(i % 5) ){
            red_index ++;
            blue_index ++;
        }
	
     }
}
void violet_gradient(char *file_name){

    FILE * fp = fopen(file_name , "w");
    file_error_handler(fp);

    fill_violet_gradient(fp);
    fclose(fp);
}
int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Too little arguments given in the command line !\n");
        exit(EXIT_FAILURE);
    }

        int choice;
        
        FILE *file = fopen(argv[1], "w+");
        file_error_handler(file);

        char text[size];
	
	while(1){
	
	printf("\n\nMenu\n");
        printf("1.Black to white vertical gradient \n");
        printf("2.Violet gradient\n");
        printf("3.Encypted text in the violet gradient(Select 2. before this)\n");
        printf("4.Press 4 in order to exit the program !\n");
        
	scanf("%d" , &choice);
	
        switch(choice){
            case 1:
                black_to_white_vertical_gradient(argv[1]);
                printf("Check your file \n");
                break;
            case 2:
                violet_gradient(argv[1]);
                printf("Check your file \n");
                break;
            case 3:
                printf("\nEnter the text that you would like to hide : \n");
                getchar();
                fgets(text , size , stdin );
                insert_encrypted_text(file , text);
                break;
            case 4:
            	printf("You have exited the program!\n");
            	exit(EXIT_SUCCESS);	
            default:
                printf("You've entered an incorrect value !\n");
                exit(EXIT_FAILURE);
        }
       }
       fclose(file);

    return 0;
}
