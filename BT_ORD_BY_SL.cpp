#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int teto = 10000;



class Graph{
private:
    
public:
    vector<vector<int> > M;
    int n;
    
    Graph(int N): n(N) {
        M.resize(N);
        
        for(int j = 0; j < N; j++) {
            M[j].resize(N,0);
        }
    }
    
   Graph() {};

   void resize(int N){
        n = N;
        M.resize(N);
        
        for(int j = 0; j < N; j++) {
            M[j].resize(N,0);
        }
   }		 

   vector<int>& operator [](int i) { return M[i]; }
    
    void edge(int a, int b, int w = 1, bool directed = false){
        M[a][b] = w;
        
        if(!directed) {
            M[b][a] = w;
        }
    }
};





vector<int> SL(Graph G) {
    int n = G.n;
    
    vector<int> order;
    vector <int> grau;
    vector <bool> marc;
    
    grau.assign(G.n, 0);
    
    marc.assign(G.n, false);
    
    
    for(int i = 0; i < n; i++){
        grau[i] = 0;
        for(int j = 0; j < n; j++){
            if( G[i][j] == 1)
                grau[i]++;
        }
    }
    
    order.resize(n);
    
    while (n != 0){
        
        int min_grau = n + 1;
        int p = -1;
        
        for (int i = 0; i < G.n; i++) {
            if (marc[i]) continue;
            if( grau[i] < min_grau){
                p = i;
                min_grau = grau[i];
            }
        }
        
        //cout << "vertice " << p << " com grau " << grau[p] << endl;
        
        marc[p] = true;
        n--;
        order[n] = p;
        for (int i = 0; i < G.n; i++) {
            if( G[p][i]==1 && !marc[i])
                grau[i]--;
        }
    }
    return order;
}


void imprime_coloracao(vector <int> cor){
    int n = cor.size();

    for(int i = 0; i < n; i++)
        printf("cor[%d] = %d\n", i, cor[i]);
}



void bt_SL_Aux(Graph G, vector <int> & cor, int k,vector<int> ordem){
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
        /*cout << endl;
        cout << "Melhor cor Atual: "<< teto << endl;
        cout << endl << endl;*/
        

        
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
int coloring(vector <int> vertices, int V, Graph G) {
    int color[V];
    bool available[V];

    for(int u = 0; u < V; u++)
        color[u] = -1;

    for(int i = 0; i < vertices.size(); i++) {
        int v = vertices[i];

        for(int c = 0; c < V; c++)
            available[c] = true;

        for(int j = 0; j < V; j++) {
            if(G[v][j] == 1 && color[j] != -1) 
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
    int teto = coloring(ordem,G.n,G);

    //cout << "teto : " << teto << endl;


    bt_SL_Aux(G,cor,0,ordem);





}


int readFile(FILE * graphFile, Graph & G) {
    char               type  = ' ';
    char               linestr[1024];
    char *             datastr;
    long               i, j;
    int                nedges;
    int                n,m;
    
    while (type != 'p') {
        type = fgetc(graphFile);
        if (type != EOF) {

            /* header */
            if (type == 'c') {
                datastr = fgets(linestr, 1024, graphFile);
                if (datastr == NULL)
                    return -1;
            }

            /* Vertices */
            if (type == 'p') {
                datastr = fgets(linestr, 1024, graphFile);
                if (datastr == NULL)
                    return -1;

                datastr = strtok(linestr," ");

                datastr = strtok(NULL," ");
                n = atoi(datastr);

                datastr = strtok(NULL," ");
                m = atoi(datastr);

            }
        }
    }

    double density = (double)(2*m)/(n*(n-1));

    printf("Graph with %d vertices and %d edges density %lf\n", n, m, density );

    G.resize(n);    

    nedges = 0;
    type = fgetc(graphFile);
    
    while (type != EOF) {
        /* header */
        if (type == 'c') {
            datastr = fgets(linestr, 1024, graphFile);
            if (datastr == NULL)
                return -1;
        }
        /* Edges */
        if (type == 'e') {
            
            datastr = fgets(linestr, 100, graphFile);

            if (datastr == NULL)
                return -1;

            datastr = strtok(linestr," ");
            i = atol(datastr) - 1;

            datastr = strtok(NULL," ");
            j = atol(datastr) - 1;

            nedges++;
            G.edge(i,j);

        }
        type = fgetc(graphFile);
    }

    
    return 0;
}

char filename[121][1024] = {"./graph_color/le450_25d.col","./graph_color/mug100_25.col",
    "./graph_color/4-Insertions_4.col","./graph_color/2-Insertions_4.col","./graph_color/myciel7.col",
    "./graph_color/queen10_10.col","./graph_color/3-FullIns_4.col","./graph_color/4-FullIns_4.col",
    "./graph_color/le450_5c.col","./graph_color/le450_25c.col","./graph_color/le450_5d.col",
    "./graph_color/5-FullIns_4.col","./graph_color/queen16_16.col","./graph_color/mug88_1.col",
    "./graph_color/miles250.col","./graph_color/2-FullIns_4.col","./graph_color/queen12_12.col",
    "./graph_color/le450_25a.col","./graph_color/myciel3.col","./graph_color/queen8_8.col",
    "./graph_color/DSJC250.5.col","./graph_color/qg.order40.col","./graph_color/mulsol.i.4.col",
    "./graph_color/le450_15a.col","./graph_color/queen5_5.col","./graph_color/inithx.i.1.col",
    "./graph_color/DSJC500.5.col","./graph_color/queen8_12.col","./graph_color/le450_5a.col",
    "./graph_color/games120.col","./graph_color/DSJR500.1.col","./graph_color/DSJR500.5.col",
    "./graph_color/DSJC500.1.col","./graph_color/school1_nsh.col","./graph_color/4-FullIns_5.col",
    "./graph_color/3-Insertions_3.col","./graph_color/1-Insertions_5.col","./graph_color/myciel4.col",
    "./graph_color/zeroin.i.3.col","./graph_color/wap08a.col","./graph_color/1-FullIns_5.col",
    "./graph_color/fpsol2.i.1.col","./graph_color/3-FullIns_5.col","./graph_color/abb313GPIA.col",
    "./graph_color/david.col","./graph_color/1-Insertions_6.col","./graph_color/mulsol.i.3.col",
    "./graph_color/2-Insertions_5.col","./graph_color/miles1500.col","./graph_color/queen13_13.col",
    "./graph_color/DSJC1000.9.col","./graph_color/wap02a.col","./graph_color/DSJC1000.5.clq",
    "./graph_color/DSJC125.1.col","./graph_color/wap04a.col","./graph_color/2-Insertions_3.col",
    "./graph_color/le450_15c.col","./graph_color/5-FullIns_3.col","./graph_color/queen6_6.col",
    "./graph_color/fpsol2.i.2.col","./graph_color/mulsol.i.2.col","./graph_color/miles750.col",
    "./graph_color/inithx.i.3.col","./graph_color/myciel5.col","./graph_color/wap05a.col",
    "./graph_color/inithx.i.2.col","./graph_color/myciel6.col","./graph_color/le450_15b.col",
    "./graph_color/queen9_9.col","./graph_color/miles1000.col","./graph_color/DSJC1000.1.col",
    "./graph_color/ash958GPIA.col","./graph_color/1-Insertions_4.col","./graph_color/4-Insertions_3.col",
    "./graph_color/queen11_11.col","./graph_color/3-Insertions_5.col","./graph_color/2-FullIns_3.col",
    "./graph_color/huck.col","./graph_color/zeroin.i.2.col","./graph_color/anna.col","./graph_color/DSJC250.1.col",
    "./graph_color/DSJC125.9.col","./graph_color/zeroin.i.1.col","./graph_color/mulsol.i.5.col",
    "./graph_color/3-Insertions_4.col","./graph_color/DSJC125.5.col","./graph_color/will199GPIA.col",
    "./graph_color/jean.col","./graph_color/wap07a.col","./graph_color/mug100_1.col","./graph_color/le450_15d.col",
    "./graph_color/le450_5b.col","./graph_color/mug88_25.col","./graph_color/mulsol.i.1.col","./graph_color/wap06a.col",
    "./graph_color/wap03a.col","./graph_color/queen15_15.col","./graph_color/latin_square_10.col",
    "./graph_color/DSJC500.5.clq","./graph_color/wap01a.col","./graph_color/homer.col","./graph_color/school1.col",
    "./graph_color/DSJR500.1c.col","./graph_color/ash608GPIA.col","./graph_color/le450_25b.col",
    "./graph_color/DSJC1000.5.col","./graph_color/DSJC250.9.col","./graph_color/qg.order100.col",
    "./graph_color/qg.order30.col","./graph_color/queen14_14.col","./graph_color/3-FullIns_3.col",
    "./graph_color/fpsol2.i.3.col","./graph_color/1-FullIns_4.col","./graph_color/1-FullIns_3.col",
    "./graph_color/ash331GPIA.col","./graph_color/2-FullIns_5.col","./graph_color/4-FullIns_3.col",
    "./graph_color/miles500.col","./graph_color/DSJC500.9.col","./graph_color/queen7_7.col","./graph_color/qg.order60.col"};






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

    // int n, m;

    //     cin >> n >> m;

    //     Graph G(n);

    //     for(int i = 1; i <= m; i++) {
    //         int a, b;
    //         cin >> a >> b;
    //         G.edge(a, b);
    //     }


    // bt_SL(G);

    for(int i = 0; i < 121; i++){
            FILE *infile;    
            printf("%s\n", filename[i]);
            if((infile=fopen(filename[i],"r"))==NULL)
            {
                printf("Error in graph file\n");
                exit(0);
            }

            Graph G;    
            /* read graph */
            if( readFile(infile, G) == 0){
                vector <int> order;
                order = SL(G);
                //int chi;
                //chi = tet;//coloring(order, G.n, G.M);
                //cout << (chi+1) << endl;
            }else{
                printf("Error in readFile\n");
            }
            
        }     

}


