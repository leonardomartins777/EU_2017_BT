#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int coloracoes_possiveis =0;

class Graph{
 private:
 vector< vector<int> > M;
 vector <int> _grau;
 public:

  int n;

  Graph(int N): n(N){
   M.resize(N);
   _grau.assign(N, 0);
   for(int j=0;j<N;j++){
    M[j].resize(N,0);
   }
  }

  vector<int>& operator [](int i) { return M[i]; }

  void edge(int a, int b){
    M[a][b]=1;
    M[b][a]=1;
    _grau[b]++;
    _grau[a]++;

  }


  int grau(int i){ return _grau[i]; }
};

void imprime_coloracao(vector <int> cor){
    int n = cor.size();

    for(int i = 0; i < n; i++)
        printf("cor[%d] = %d\n", i, cor[i]);
}


void bt(Graph G, vector <int> & cor, int k){

    if(k == G.n){
        imprime_coloracao(cor);
        cout << endl;
        coloracoes_possiveis++;
    }else{

        int v = -1;
        for(int i = 0; i < G.n; i++){
            if( cor[i] == -1){
                v = i;
                break;
            }
        }

//        printf("colorindo vertice %d\n", v);

        int maior_cor = -1;
        for(int i = 0; i < G.n; i++){
            if( cor[i] != -1 && cor[i] > maior_cor){
                maior_cor = cor[i];
            }
        }

        // printf("maior cor usada %d\n", maior_cor);


        //  char pausa;
        //  cin >> pausa;

        vector <bool> available;

        available.assign(G.n, true);

        for(int u = 0; u < G.n; u++){
            if( G[v][u] == 1 && cor[u] != -1){
                available[cor[u]] = false;
            }
        }

        for(int i = 0; i <= maior_cor+1; i++){
            if( available[i] ){
                cor[v] = i;
                bt(G, cor, k+1);
                cor[v]=-1;
            }
        }

    }

}


int main(){

    // Graph G(4);
    // G.edge(0,3);
    // G.edge(1,3);
    // G.edge(2,3);
    // G.edge(1,2);

    vector <int> cor;
    

    int n, m;

    cin >> n >> m;

    Graph G(n);
    cor.assign(n, -1);

    for(int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        G.edge(a, b);
    }


    bt(G,cor,0);

    cout << "coloracoes_possiveis: " << coloracoes_possiveis << endl;
}


