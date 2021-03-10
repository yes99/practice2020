#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void AddVecCPU(float* C, float* A, float* B, int size)
{
	for (int i = 0; i < size; ++i)
		C[i] = A[i] + B[i];

}
// gpu 에서는 for문이 사라진다
void main()
{
	int N = 1024 * 1024;
	float *a = new float[N];
	float* b = new float[N];
	float* c = new float[N];
	for (int i = 0; i < N; ++i)
	{
		//rand() : 0~ RAND MAX
		a[i] = rand() / (float)RAND_MAX; //0.0 ~ 1.0 까지의 임의의 수
		b[i] = -a[i];
		c[i] = 0.0;
	}


	clock_t st = clock(); //start
	AddVecCPU(c, a, b, N);
	clock_t ed = clock(); // end

	printf("elpased time = %u ms\n", ed - st);
	for (int i = 0; i < N; ++i)
	{
		if (c[i] != 0.0)
			printf("Error\n");

	}

	delete[] a;
	delete[] b;
	delete[] c;
}