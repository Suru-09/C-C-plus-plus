#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define BLOCK 512 //This would be the max length of a line read with fgets

void format_string(char * buffer){

    int cnt = 0 ,len = strlen(buffer);
    for(int i = 0 ; buffer[i] ; ++i ){

        if(buffer[i] == '<'){
            cnt = 1;
            continue;
        }

        if( cnt && buffer[i] != '>')
            ++cnt;

        if(buffer[i] == '>' && buffer[i + 1] == '\0'){
            buffer[strlen(buffer) - cnt - 1] = '\0';
            break;
        }
        if(buffer[i] == '>'){
            for(int j = i - cnt ; buffer[j + 1]; ++j)
                buffer[j] = buffer[j + cnt + 1];
            buffer[len - cnt] = '\0';
            cnt = 0;
        }
    }
}
void handle_offset(int * hour , int *min , int *s  ,int s_offset){

    if(s_offset > 0){
        int s_add = *s + s_offset;
        if(s_add >= 60){
            *s = s_add % 60;
            int m_add = (*min + s_add) /60;
            if(m_add >= 60){
                *min = m_add % 60;
                *hour = (*hour + m_add) / 60;
                if(*hour >= 60){
                  printf("You've entered a number too big over 59 hours!\n");
                  exit(EXIT_FAILURE);
                }
            }
            else{
                *min = m_add;
            }
        } else *s = s_add;
    }
    else{
        *s += s_offset;
        while(*s < 0){
            *s += 60;
            --(*min);
            while(*min < 0){
                *min += 60;
                --(*hour);
                if(*hour < 0){
                    printf("You got some bad input there(negative hours) , my friend!\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

char * create_output_file_name(char * str){

    char *copy_str = malloc(strlen(str));
    strcpy(copy_str , str);

    int j = strlen(copy_str) - 1;
    copy_str = (char *)realloc(copy_str , strlen(copy_str) + 4);    //taking into account the fact that the file
    //may not have an extension
    while(copy_str[j] != '.' && j > 0)
        --j;

    if(!j){
        strcat(copy_str , ".out");
    }
    else{
        copy_str[j + 1] = '\0';
        strcat(copy_str , "out");
    }

    return copy_str;
}

void solve(int s_offset , char * fisier){

  FILE * fp = fopen(fisier , "r+");
  if(!fp){
      printf("There was an error opening the file !\n");
      exit(EXIT_FAILURE);
  }

  while(1){
      int cnt , h1 , h2 , m1 , m2 , s1 , s2 , ms1 , ms2;
      char * buffer = NULL;
      int buff_cnt = 1;
      char *line = malloc(BLOCK);

      if(!fgets(line , BLOCK , fp) || !strcmp(line , "\n") )
          break;
      sscanf(line,"%d" , &cnt);

      fgets(line , BLOCK , fp);
      sscanf(line, "%d:%d:%d,%d --> %d:%d:%d,%d" , &h1 , &m1 , &s1 , &ms1 , &h2 , &m2 , &s2 , &ms2);
      free(line);

      //The handle_offset function recalculates the times with the offset in seconds given as a command line argument

      handle_offset(&h1,&m1,&s1,s_offset);
      handle_offset(&h2,&m2,&s2,s_offset);

      while(1){
          char *str = malloc(BLOCK);          //str represents one line from the subtitle file(the subtitle itself)
          if(!fgets(str , BLOCK ,fp) || !str || !strcmp(str,"\n"))
              break;

          if(!buffer){
              buffer = (char *)realloc(buffer , BLOCK);
              strcpy(buffer,str);
          }
          else{
              buffer = (char *)realloc(buffer , (buff_cnt + 1) * BLOCK);
              strcat(buffer,str);
          }
          free(str);
          ++buff_cnt;
      }

     format_string(buffer);           //This function eliminates the <i> or </i> structures

     char *output_name = create_output_file_name(fisier);
     FILE * out = fopen(output_name, "a");
     if(!out){
         printf("There's an error while opening the file in  which you want to write the results !\n");
         exit(EXIT_FAILURE);
     }

     fprintf(out , "%d\n%d:%d:%d,%d ----> %d:%d:%d,%d\n" ,cnt ,  h1 , m1 , s1 , ms1 , h2 , m2 , s2 , ms2);
     fprintf(out,"%s\n" , buffer);

      printf( "%d\n%d:%d:%d,%d ----> %d:%d:%d,%d\n" ,cnt ,  h1 , m1 , s1 , ms1 , h2 , m2 , s2 , ms2);
      printf("%s\n" , buffer);
     free(buffer);
  }
  fclose(fp);
}
int main(int argc , char ** argv) {

    //!! ---The second argument is the offset in seconds and the other to come are the files from where you read

    if(argc < 2){
        printf("I need more arguments  !\n");
        exit(EXIT_FAILURE);
    }

    //Transform the seconds offset given from string to int
    int s_offset = atoi(argv[1]);

    //Apply solve function for all the given files
    for(int j = 2 ; j < argc ; ++j)
      solve(s_offset , argv[j]);

    return 0;
}
