#include <stdio.h>
#include <omp.h>
#define N 1000
#define M 1
#define m 2
int main()
{
	int a[N][M];
	int b[M][N];
	int c=0;
	int i,j;
	//some initializations
	 double start = omp_get_wtime( );
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			a[i][j]=1;
		}
	}
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			b[i][j]=1;
		}
	}
	omp_set_num_threads(m);
#pragma omp parallel shared(a,b,c) private(i,j)
{
#pragma omp for reduction(+:c)
	for(i=0;i<N;i++){
		c+=a[i][0]*b[0][i];
	}
}
	printf("%d ",c);
	printf("\n");
	
	double end = omp_get_wtime( );  
  
    	printf("start = %.16g\nend = %.16g\ndiff = %.16g seconds\n",  
             		start, end, end - start); 
	return 0; 
}
