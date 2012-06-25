#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "do_computations.h"
#define N_PROC 2
#define SIZE 100


 // calculate A*B+C, where A, B and C are squared matrices, N times, with size being the submatrix
 // used for the computation size and matsize the length of A, B and C (N).
int main(int argc, char** argv)
{
	double t[1000];
	double min, average;
	int i,j;
	for(i=0; i<1000; ++i)
		t[i] = omp_get_wtime();
	min = t[1]-t[0];
	for(i=1; i<999; ++i)
	if(t[i+1]-t[i] < min)
		min = t[i+1]-t[i];
	average = (t[999] - t[0]) / 999;
	printf("the average time is tav = %e \n", average);
	printf("the minimum time is tmin = %e \n", min);
	double init, end;

	// the cache size of the procs is 1024kb 
	//double A[1000][1000] = {1}; // that makes it 8*10e6 bytes, which means 8 MB.
	//double B[1000][1000] = {0.5}; 
	//double C[1000][1000] = {2};

	double **A,**B, **C;
	int length = 1000;
	A = malloc(length*sizeof(double*));
	for(i=0; i<length; ++i)
		A[i] = malloc(1000*sizeof(double*));
	B = malloc(length*sizeof(double*));
	for(i=0; i<length; ++i)
		B[i] = malloc(1000*sizeof(double*));
	C = malloc(length*sizeof(double*));
	for(i=0; i<length; ++i)
		C[i] = malloc(1000*sizeof(double*));
	// in total, 24 MB.
	for(i=0;i<length;++i)
		for(j=0;j<length;++j)
		{
			// we put values in A B and C
			A[i][j] = 0.5;
			B[i][j] = 0.2;
			C[i][j] = 0.4;
		}

	int size = 20;
	// the cache size of the procs is 1024kB, 20*20*8 (doubles) = 2400 bytes = 2,4 kB
	init = omp_get_wtime();
	do_computations(A,B,C, N_PROC, size, length);
	end = omp_get_wtime();
	printf("max threads : %d \nnumber proc : %d \n", omp_get_max_threads(), omp_get_num_procs());
	//result = N/(end-init);
	printf("computation time : %e \n", end-init);
	//printf("%e flops \n", result);
	return 1;
}
