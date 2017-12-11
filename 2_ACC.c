#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>
#include <accel.h>
//#include <accelmath.h>
#define N 100000
#define M 1
#define m 2
int main()
{
	int a[N][M];
	int b[M][N];
	int c=0;
	int i,j;
	struct  timeval start;
	struct  timeval end;
	long diff;
	gettimeofday( &start, NULL );
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
	#pragma acc parallel 
	{
		for(i=0;i<N;i++){
			c+=a[i][0]*b[0][i];
		}
	}
	printf("%d ",c);
	printf("\n");	
	gettimeofday( &end, NULL ); 
	diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec; 
    	printf("diff = %.16g seconds\n",  diff);  
	return 0; 
}
