#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "random.h"
#define MAX_VERTEX 4000

int g[MAX_VERTEX][MAX_VERTEX];
int d[MAX_VERTEX];
int w[MAX_VERTEX];


int main(int argc, char *argv[])
{
	int n;
	double p;
	unsigned Gseed;
	int i,j;
	int m;
	
	if (argc < 4)
	{
	   printf("usage: %s [number of vertices] [edge probability] [seed] \n", argv[0]);
	   exit(1);
	}

	n = atoi( argv[1]);
	p = atof( argv[2]);
	Gseed = atoi( argv[3] );


	srand( time( NULL));

	memset(g, 0, sizeof(g));

	m = 0;

	for(i=0; i < n; i++) d[i] = 0;

	for (i = 0;  i < n;  ++i)
	{
		
		for (j = i+1;  j < n;  ++j)
		{
			if (drand(&Gseed) <= p)
			{

				g[i][j] = 1;
				g[j][i] = 1;
				m++;
			}
		}
	}

   printf("p edge %d %d\n", n, m);
   for(i =0 ; i < n; i++)
   {
		for(j=0; j < i; j++)
			if( g[i][j] )
				printf("e %d %d\n", i+1, j+1);
   }







}
