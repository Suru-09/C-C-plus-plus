#include <iostream>
#include<stack>

using namespace std;

stack<int> st;
char exp[20] , rez[20] ;

int operator1(char c){

    if(c == '+' || c == '*' || c == '-' || c == '/'){

        if(c == '+' || c == '-')
            return 1;
        return 2;
    }

    return 0;
}

void polish_postfix(){

   int k = 0;

   for(int i = 0 ; exp[i] ; i++) {

       if (isdigit(exp[i])){
           rez[k++] = exp[i];
       }
       else if( operator1(exp[i]) ) {
                    while( !st.empty() &&  ( operator1(exp[i]) < operator1(st.top()) )  )  {
                        rez[k++] = st.top();
                        st.pop();
                    }
                    st.push(exp[i]);
       }
       else if (exp[i] == ')' ) {

               while (st.top() != '(') {

                   rez[k++] = st.top();
                   st.pop();
               }
               st.pop();
       }
       else{
           if(exp[i] == '('){
               st.push(exp[i]);
           }
       }
   }

   while(!st.empty()){

       rez[k++] = st.top();
       st.pop();
   }
}
int main() {

    scanf("%s" , exp);

    polish_postfix();

    for(int i = 0 ; rez[i] ; ++i){
        printf("%c" , rez[i]);
    }

    return 0;
}
