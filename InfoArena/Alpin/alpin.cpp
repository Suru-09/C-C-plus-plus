#include <iostream>
#include<queue>
#include<fstream>

using namespace std;

#define nr_el 1025
int heights[nr_el][nr_el];          //matricea cu inaltimi
int viz[nr_el][nr_el] ,dp[nr_el][nr_el];    // vizitat si distanta parcursa pentru fiecare
                                            // nod in parte
int maxi =  0;
int N;
int gi = 0 , gj = 0;

int dx[] = {-1 , 0 , 1 , 0};        //dirijorul pe coordonata x
int dy[] = {0, -1 , 0 , 1};         //dirijorul pe coordonata y

//Depth First Search

void Defeu(int i , int j ){

        viz[i][j] = 1;
        dp[i][j] = 1;

        int dmax = 0;

        for(int k = 0 ; k < 4 ; k++){

            int newx = i + dx[k];
            int newy = j  + dy[k];

            if(( heights[newx][newy] > heights[i][j]) ){
                if( !viz[newx][newy]  )
                    Defeu(newx , newy);
                dmax = max(dmax , dp[newx][newy]);  //Dupa ce merge in adancime se intoarce si calculeaza
                                                    //distanta
            }
        }

    dp[i][j] = 1 + dmax;
    if(dp[i][j] > maxi){
        maxi = dp[i][j];
        gi = i;
        gj = j;
    }
}

//Functia facuta pentru reconstituirea traseului

void parcurge(int i , int j , ofstream &fout){

    if(dp[i][j] == 1)
        return;
    else
    {
        for(int k = 0; k < 4; ++k){
            int x_new = i + dx[k];
            int y_new = j + dy[k];

            if(dp[x_new][y_new] == dp[i][j] - 1){
                fout<<x_new<<" "<<y_new<<'\n';
                parcurge(x_new,y_new ,fout);
                return;
            }
        }
    }
}
int main() {

    ifstream fin;
    fin.open("alpin.in");
    fin >> N;
    ofstream fout("alpin.out");

    for(int i = 1 ; i <= N ; ++i){
        for(int j = 1; j <= N  ; ++j){
            fin >> heights[i][j];
        }
    }

    for(int i = 1 ; i <= N ; ++i){
        for(int j = 1; j <= N ; ++j){

            int copy = maxi;
            Defeu(i , j );
            //memset(viz , 0 , nr_el * nr_el );
            if(copy < maxi){
                gi =i ;
                gj =j;
            }
        }
    }
    fout<<maxi<<endl;
    fout<<gi<<" "<<gj<<'\n';
    parcurge(gi,gj ,fout);
    fout.close();
    return 0;
}


