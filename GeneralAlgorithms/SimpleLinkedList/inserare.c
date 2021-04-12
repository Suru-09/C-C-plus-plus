#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct lnode{

    int key;
    struct lnode *next;
};

void insert_sorted_lnode(int key , struct lnode ** pnode){

   struct lnode * node = *pnode;
   if(!node){
     node =(struct lnode *)malloc(sizeof(struct lnode));
     node->key = key;
     node->next = NULL;
     (*pnode) = node;
   }
   else{

     struct lnode *new_node = (struct lnode *) malloc(sizeof(struct lnode));
     struct lnode *current = (*pnode);
     struct lnode *prev = current;
     int cnt = 0;

     while( current->key < key && current->next){
       prev = current;
       current = current->next;
       ++cnt;
     }

      if(current->key >= key){
        new_node->key = key;
        new_node->next = current;

        if(!cnt){
          (*pnode) = new_node;
        }
        else{
          prev->next = new_node;
        }
      }
      else{
        new_node->key = key;
        new_node->next = NULL;

        current->next = new_node;
      }
   }

}

void print_sllist(struct lnode *list){

  while(list){
    printf("I am the key : %d\n" , list->key);
    list = list->next;
  }
}
int main(){

  struct lnode *root = NULL;
  srand(time(0));

  for(int i = 0 ; i < 200 ; ++i){
      int x = rand() % 10000;
      insert_sorted_lnode(x, &root);
  }
  
  print_sllist(root);
  return 0;
}
