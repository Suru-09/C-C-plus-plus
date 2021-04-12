#include<iostream>
#include<stack>

#define N 4     //dimension of the know_matrix (number of people at the party)
using namespace std;


//// !!!!! -------- THE CELEBRITY PROBLEM -------- !!!!!! //////

/*
In a party of N people, only one person is known to everyone. Such a
person may be present in the party, if yes, (s)he doesn’t know anyone in
the party. We can only ask questions like “does A know B? “. Find the stranger
(celebrity) in minimum number of questions.

We can describe the problem input as an array of numbers/characters
representing persons in the party. We also have a hypothetical function
p1_knows_p2 which returns true if person1 knows perons2,false otherwise.

*/



//function return true if the person doesn't know anybody and that person is
//known by everybody (kind of the celebrity condition )
int is_celebrity(int person, bool know_matrix[][N]) {
    for(int i = 0 ; i < N; ++i)
        if(i != person)  //condition so we don't check the cel with (her)himself
            if(know_matrix[person][i] || !know_matrix[i][person])
                return false;

    return true;
}

//true if person1 knows person2, false otherwise
bool p1_knows_p2(int p1, int p2, bool know_matrix[][N]) {

    if(know_matrix[p1][p2] == 1)
        return true;
    return false;
}

int celebrity(bool know_matrix[][N]) {

    stack<int> people;
    int celebrity;

    for(int i = 0 ; i < N ; ++i)
        people.push(i);

    int p1 = people.top();
    people.pop();

    int p2 = people.top();
    people.pop();

    while(people.size() > 1) {

        if( !p1_knows_p2(p1, p2, know_matrix) ) {
            p2 = people.top();
            people.pop();
        }
        else {
            p1 = people.top();
            people.pop();
        }
    }

    //If we have only 2 people there is no celebrity
    if(people.empty() )
        return -1;


    //Pop last element from stack which is unchecked
    celebrity = people.top();
    people.pop();

    //if the potential celebrity knows sb, we change the potential celebrity
    //to that someone
    if(p1_knows_p2(celebrity, p1, know_matrix) )
        celebrity = p1;

    //same here
    if(p1_knows_p2(celebrity, p2, know_matrix) )
        celebrity = p2;

    //we check if the celebrity doesn't know anybody
    if( is_celebrity(celebrity, know_matrix) ) {
        return celebrity;
    }


    return -1;
}


int main() {

    bool know_matrix[N][N] = {
        {0, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 0 , 0, 0}
    };

    cout << celebrity(know_matrix) << "\n";

    return 0;
}
