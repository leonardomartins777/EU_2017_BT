#include <iostream>
#include <bits/stdc++.h>

using namespace std;



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



// void bt_SL(Graph G, vector <int> & cor, int k,vector<int> ordem){

//     if(k == G.n){
//         cout << "=====### ROUND ###=====" << endl;
//         imprime_coloracao(cor);
//         cout << endl;

//     }else{

//         int v = -1;
//         for(int i = 0; i < ordem.size(); i++){
//             if( cor[i] == -1){
//                 v = i;
//                 break;
//             }
//         }

//       printf("colorindo vertice %d\n", v);

//         int maior_cor = -1;
//         for(int i = 0; i < G.n; i++){
//             if( cor[i] != -1 && cor[i] > maior_cor){
//                 maior_cor = cor[i];
//             }
//         }

// //        printf("maior cor usada %d\n", maior_cor);


//         // char pausa;
//         // cin >> pausa;

//         vector <bool> available;

//         available.assign(G.n, true);

//         for(int u = 0; u < G.n; u++){
//             if( G[v][u] == 1 && cor[u] != -1){
//                 available[cor[u]] = false;
//             }
//         }

//         for(int i = 0; i <= maior_cor+1; i++){
//             if( available[i] ){
//                 cor[v] = i;
//                 bt_SL(G, cor, k+1,ordem);
//                 cor[v]=-1;
//             }
//         }

//     }

// }

void bt_SL(Graph G, vector <int> & cor, int k,vector<int> ordem){


    
    if(k == G.n){
        imprime_coloracao(cor);
        cout << endl;
        
    }else{

        int v = -1;

        for(int i = 0; i < G.n; i++){
            if( cor[ordem[i]] == -1){
                v = i;
                break;
            }
        }

      printf("colorindo vertice %d\n", v);

        int maior_cor = -1;
        for(int i = 0; i < G.n; i++){
            if( cor[i] != -1 && cor[i] > maior_cor){
                maior_cor = cor[i];
            }
        }
        

        printf("maior cor usada %d\n", maior_cor);


        // char pausa;
        // cin >> pausa;

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
                bt_SL(G, cor, k+1,ordem);
                cor[v]=-1;
            }
        }

    }

}




int main(){

    Graph G(5);
    G.edge(0,3);
    G.edge(1,2);
    G.edge(1,3);
    G.edge(1,4);
    G.edge(2,3);
    G.edge(3,4);
    


    vector <int> cor;
    vector<int> ordem;
    ordem.push_back(1);
    ordem.push_back(2);
    ordem.push_back(3);
    ordem.push_back(4);
    ordem.push_back(0);

    cor.assign(5, -1);


    cout << "SEM PODA" << endl;




    bt_SL(G, cor, 0,ordem);

  

}


