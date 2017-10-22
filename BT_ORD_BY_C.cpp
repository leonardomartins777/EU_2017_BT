#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int teto = 1000;


class Graph{
 private:
 vector< vector<int> > M;
 vector <int> _grau;

 public:

  int n;
  int maior_Grau = 0;

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
    if(_grau[a] > maior_Grau){
        maior_Grau = a;
    }
    if(_grau[b] > maior_Grau){
        maior_Grau = b;
    }

  }


  int grau(int i){ return _grau[i]; }
};

void imprime_coloracao(vector <int> cor){
    int n = cor.size();

    for(int i = 0; i < n; i++)
        printf("cor[%d] = %d\n", i, cor[i]);
}



vector<int> Clique_ORD(Graph G,vector<int> cor){
    int _maior_G = G.maior_Grau;
    vector<int> C;
    C.push_back(_maior_G);
    vector< int > Adj_maior;
    for (int i = 0; i < G.n; i++){
        if (G[i][_maior_G]){
            Adj_maior.push_back(i);
        }
    }
    int count = Adj_maior.size();
    while(count > 0){
        int aux_ = 0;
        for (int i = 0; i < Adj_maior.size(); i++){
            if (G.grau(Adj_maior[i]) > G.grau(aux_)){
                aux_ = Adj_maior[i];
            }

        }
        for (int i = 0; i < Adj_maior.size(); i++){
            
            if (Adj_maior[i] == aux_){
                  Adj_maior.erase (Adj_maior.begin()+i);

            }

        }
        int n_adj_na_clique = 0;
        for (int i = 0; i < C.size(); i++){
            if (G[aux_][C[i]]){
                n_adj_na_clique++;
            }
        }
        if (n_adj_na_clique == C.size()){
            C.push_back(aux_);
        }



        count--;
    }

    for (int i = 0; i < C.size(); i++){
        
        cor[C[i]] = i;
    }

    return cor;

}

    


void bt_aux(Graph G, vector <int> & cor, int k){
    int maior_cor = -1;
        for(int i = 0; i < G.n; i++){
            if( cor[i] != -1 && cor[i] > maior_cor){
                maior_cor = cor[i];
            }
        }


    if (maior_cor >= teto){
        return;
    }

    if(k == G.n){
         if (teto > maior_cor){
            teto = maior_cor;
        }
        imprime_coloracao(cor);
        cout << endl;
    }else{

        int v = -1;
        for(int i = 0; i < G.n; i++){
            if( cor[i] == -1){
                v = i;
                break;
            }
        }


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
                bt_aux(G, cor, k+1);
                cor[v]=-1;
            }
        }

    }

}


void bt_Clique(Graph G){

    vector <int> cor;
    cor.assign(G.n, -1);
    cor = Clique_ORD(G,cor);

    // cout << "cor_inicial"  << endl;
    // imprime_coloracao(cor);


    int v_colorido = 0;
    for (int i = 0; i < G.n ; i++){
        if (cor[i] != -1){
            v_colorido ++;
        }
    }
    teto = G.n-1;

    cout << "teto : " << teto << endl;

    bt_aux(G,cor,v_colorido);




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


    bt_Clique(G);    
    
}


