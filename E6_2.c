#include<stdio.h>
#define K 4
#define N 8

void print_gm(unsigned int gm_ns[K][N]);
void ns_to_sys(unsigned int gm_ns[K][N],unsigned int gm_sys[K][N]);
void swap_i_j( unsigned int gm_ns[K][N],	unsigned int i,	unsigned int j);
void add_i_j(  unsigned int gm_ns[K][N],	unsigned int i,	unsigned int j);

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
	// swap_i_j(gm_ns, 0, 1);
	ns_to_sys(gm_ns,gm_sys);
	//add_i_j(gm_ns, 1, 3);
	print_gm(gm_ns);
	
	return 0;
}

void swap_i_j
(
	unsigned int gm_ns[K][N],
	unsigned int i,
	unsigned int j
)
{
	unsigned int temp;
	int k;
	
	for(k=0;k<N;k++){
		temp=gm_ns[i][k];
		gm_ns[i][k]=gm_ns[j][k];
		gm_ns[j][k]=temp;
	}
}

void add_i_j
(
	unsigned int gm_ns[K][N],
	unsigned int i,
	unsigned int j
)
{
	int k;
	
	for(k=0;k<N;k++){
		gm_ns[j][k]=gm_ns[i][k]+gm_ns[j][k];
		if (gm_ns[j][k] == 2){
			gm_ns[j][k] = 0;
		}
	}
}

void ns_to_sys(unsigned int gm_ns[K][N],unsigned int gm_sys[K][N])
{
	int i,j;
	unsigned int tmp;
	for(i=0;i<2;i++){ // 最初のi-loop (0からK-1))
		if(gm_ns[i][i]==1){ // g_{i,i} = 1 であるなら，基本行操作を行う
			for(j=i+1;j<K;j++){
				add_i_j(gm_ns,i,j);
			}
		} else	{ // g_{i,i} = 0 であるなら，
			for(j=i+1;j<K;j++)	{ 
				if(gm_ns[j][i]==1)	{// g_{j,i} = 1 であるような j を探し
					swap_i_j(gm_ns, i, j); // 第 i 行と第 j 行の成分 を交換する
					break;
				}
			}
			for(j=i+1;j<K;j++)	{
				add_i_j(gm_ns,i,j);
			}
		}
	}
	for(i=0;i<K;i++)	{ // gm_nsをgm_sysに入れ直す
		for(j=0;j<N;j++)	{
			gm_sys[i][j]=gm_ns[i][j];
		}
	}
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
	printf("\n");
}
