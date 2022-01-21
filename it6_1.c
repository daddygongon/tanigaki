#include<stdio.h>
#define K 4
#define N 8

void print_gm(unsigned int gm_ns[K][N]);

int main(void)
{
	unsigned int gm_ns[K][N]; 
	unsigned int gm_sys[K][N];
	
	FILE *fp;
	int i,j;
	
	fp=fopen("generator_matrix_ns.txt","r");
	for(i=0;i<K;i++)
	{
		for(j=0;j<N;j++)
		{
			fscanf(fp,"%1d",&gm_ns[i][j]);
		}
	}
	fclose(fp);
	
	print_gm(gm_ns);
	
	return 0;
}

void print_gm(unsigned int gm_ns[K][N])
{
	int i,j;
	
	for(i=0;i<K;i++)
	{
		for(j=0;j<N;j++)
		{
			printf("%1d",gm_ns[i][j]);
		}
		printf("\n");
	}
}
