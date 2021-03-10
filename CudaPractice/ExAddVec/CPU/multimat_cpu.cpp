#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void AddVecCpu(float* C, float* A, float* B, int size)
{
	for (int i = 0; i < size; ++i)
		C[i] = A[i] + B[i];
}

void MultiMatCPU(float* P, float* M, float* N, int width)
{
	for (int i = 0; i < width; ++i)
	{
		for (int j =0; j<width; ++j)
			//P[i][j] 원소 = M 의 i번째 행과 N의 j열의 내적
			for (int k = 0; k < width; ++k)
			{
				float a = M[i * width + k];// M[i][k];
				float b = M[k * width + j];//N[k][j];
			    P[i * width + j] += a * b;
			}
	}
}
void PrintMatrix(float* M, int width)
{
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			printf("%3.0f   ", M[i * width + j]);
		}
		printf("\n");
	}
	printf("\n");
}

void main()
{
	int width = 2;
	float *M = new float[width* width];
	float *N = new float[width * width];
	float *P = new float[width * width];

	for (int i = 0; i < width* width; ++i)
	{
		M[i] = rand() % 3 - 1.0;
		N[i] = rand() % 3 - 1.0;
		P[i] = 0.0;
	}

	clock_t st = clock();
	MultiMatCPU(P, M, N, width);
	printf("Elapsed time = %u ms \n" ,clock() - st);
	PrintMatrix(M, width);
	PrintMatrix(N, width);
	PrintMatrix(P, width);

	delete[] M;
	delete[] N;
	delete[] P;
}