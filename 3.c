#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>
#include <accel.h>
int main()
{
	int i,j;
	int k=0;
	struct  timeval start;
	struct  timeval end;
	long diff;
	FILE *fp;
	fp = fopen ("result.txt","w");
	if (fp ==NULL)
	{
		printf ("faile open the file!\n");
		exit (-1);
	}
	gettimeofday( &start, NULL );
	//pragma acc parallel 
	#pragma acc loop //copyin(a[0:n]) copyout(r[0:n])
	for (i = 2; i < 100000; i++)
       	{
		for (j = 2; j <= sqrt(i); j++)
              	{
                      	if (i % j == 0)
                       	{
                               	break;
                       	}
               	}
               	if(j > sqrt(i))
               	{
                       	fprintf (fp,"%d ",i);
			k++;
                }
	}
	gettimeofday( &end, NULL ); 
	printf("素数的个数为:%d ",k); 
	printf("\n");
	diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec; 
    	printf("acc并行时间差为：diff = %.16g seconds\n",  diff); 
	//串行程序
	k = 0;
	double start1 = clock();
	for (i = 2; i < 100000; i++)
       	{
		for (j = 2; j <= sqrt(i); j++)
              	{
                      	if (i % j == 0)
                       	{
                               	break;
                       	}
               	}
               	if(j > sqrt(i))
               	{
                       	fprintf (fp,"%d ",i);
			k++;
                }
	}
	double end1 = clock();
	//printf("素数的个数为:%d ",k); 
	//printf("\n");
	printf("串行时间差为：diff = %.16g seconds\n",  end1-start1);
	return 0;
}
