#include <iostream>
#include<vector>
#include<fstream>
#include<cstring>

using namespace std;

#define nr_el 100005
vector<int> graph[nr_el];
int viz[nr_el];
int nr_conex = 0;

void add_edge(vector<int> adj[] ,int u , int v){

    adj[u].push_back(v);
    adj[v].push_back(u);
}

//void print_g(vector<int> adj[] , int V){
//
//    for(int v = 1 ; v <= V ; ++v){
//
//        cout<<"\n Adjacency list of vertex " << v << " :"<<endl;
//
//        for(auto x : adj[v]){
//            cout<<" "<< x;
//        }
//    }
//}
void Defeu(int st){

        viz[st] = 1;
        for(auto it : graph[st])
            if(!viz[it])
                Defeu(it);
}
int main() {

    int N , M;
    ifstream in;
    in.open("dfs.in");
    ofstream out;
    out.open("dfs.out");

    in >> N >> M;

    for(int i = 1 ; i <= M ; ++i){

        int x,y;
        in >> x >> y;
        add_edge(graph , x , y);
    }
    in.close();

    for(int i = 1; i <= N ; i++){
        if(!viz[i]){
            nr_conex++;
            Defeu(i);
        }
    }
    out  << nr_conex;
    out.close();

    return 0;
}
