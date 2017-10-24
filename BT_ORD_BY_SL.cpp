#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int teto;



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
        
        //imprime_coloracao(cor);
        //cout << endl;
        cout << "Encontrando coloracao: "<< teto+1 << endl;
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
    
    cout << "numero de cores iniciais: " << (teto+1) << endl;

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







int main(){

	
	for(int i = 1; i <= 5; i++)
		for(int j = 1; j <= 9; j++)
			for(int k=1; k<= 10; k++){
				char filename[1024];
				sprintf(filename,"./randomgraph/%d.0.%d.%d", 10*i, 10*j, k);
			    
				FILE *infile;    
				printf("%s\n", filename);
				if((infile=fopen(filename,"r"))==NULL)
				{
					printf("Error in graph file\n");
					exit(0);
				}

				Graph G;    
				/* read graph */
				if( readFile(infile, G) == 0){
					teto = G.n;
					bt_SL(G);
					cout << (teto+1) << endl;
				}else{
					printf("Error in readFile\n");
				}
            
        }     

}


