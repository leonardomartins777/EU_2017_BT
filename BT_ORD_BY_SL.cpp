#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int teto = 10000;



class Graph{
 private:
 vector< vector<int> > M;
 vector <int> _grau;

 public:

  int n;
  // int maior_Grau = 0;

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
    // if(_grau[a] > maior_Grau){
    //     maior_Grau = a;
    // }
    // if(_grau[b] > maior_Grau){
    //     maior_Grau = b;
    // }

  }


  int grau(int i){ return _grau[i]; }
  vector< vector<int> > get_M(){ return M;}
};


vector<int> SL(Graph G) {
    map<int, int> g;
    map<int, bool> removed;
    vector<int> order;
    pair<int, int> less;
    less = pair<int, int>(10000000, -1);
    int n = G.n;
    while (n != 0){
        less = pair<int, int>(1000000, -1);
        for (int i = 0; i < G.n; i++) {
            if (removed[i]) continue;
            for (int j = 0; j < G.n; j++) {
                if (G[i][j] && !removed[i] && !removed[j]) {
                    g[i]++;
                }
            }
            if (less.first > g[i]){
                less.first = g[i];
                less.second = i;
            }
        }
        removed[less.second] = true;
        order.push_back(less.second);
        n--;
    }
    return order;
}



void imprime_coloracao(vector <int> cor){
    int n = cor.size();

    for(int i = 0; i < n; i++)
        printf("cor[%d] = %d\n", i, cor[i]);
}



void bt_SL_Aux(Graph G, vector <int> & cor, int k,vector<int> ordem/*,int teto*/){
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
        cout << "Melhor cor Atual: "<< teto << endl;
        cout << endl << endl;
        

        
    }else{


        int v = -1;

        for(int i = 0; i < ordem.size(); i++){
            if( cor[ordem[i]] == -1){
                v = ordem[i];
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
            if( available[i]){
                cor[v] = i;
                bt_SL_Aux(G, cor, k+1,ordem);
                cor[v]=-1;
            }
        }

    }

}
int coloring(vector <int> vertices, int V, vector<vector<int> > M) {
    int color[V];
    bool available[V];

    for(int u = 0; u < V; u++)
        color[u] = -1;

    for(int i = 0; i < vertices.size(); i++) {
        int v = vertices[i];

        for(int c = 0; c < V; c++)
            available[c] = true;

        for(int j = 0; j < V; j++) {
            if(M[v][j] == 1 && color[j] != -1) 
                available[color[j]] = false;
        }

        for(int c = 0; c < V; c++) {
            if(available[c]) {
                color[v] = c;
            break;
            }
        }
    }
    int teto = -1;
    for (int i = 0; i < V; i++){
        if (color[i] > teto){
            teto = color[i];
        }
    }

    return teto;
}


void bt_SL(Graph G){


    vector <int> cor;
    cor.assign(G.n, -1);


    vector<int> ordem = SL(G);
    int teto = coloring(ordem,G.n,G.get_M());

    cout << "teto : " << teto << endl;


    bt_SL_Aux(G,cor,0,ordem);





}




int main(){

    // Graph G(5);
    // G.edge(0,3);
    // G.edge(1,2);
    // G.edge(1,3);
    // G.edge(1,4);
    // G.edge(2,3);
    // G.edge(3,4);
    


    
    // ordem.push_back(1);
    // ordem.push_back(2);
    // ordem.push_back(3);
    // ordem.push_back(4);
    // ordem.push_back(0);


    // cor.assign(5, -1);


    // cout << "SEM PODA" << endl;

    int n, m;

        cin >> n >> m;

        Graph G(n);

        for(int i = 1; i <= m; i++) {
            int a, b;
            cin >> a >> b;
            G.edge(a, b);
        }


    bt_SL(G);

  

}


