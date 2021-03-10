#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void MultMatGPU(float* P, float* M, float* N, int width)
{
	int i = threadIdx.y;
	int j = threadIdx.x;

	float sum = 0.0;
	for (int k = 0; k < width; ++k)
	{
		float a = M[i * width + k];
		float b = N[k * width + j];
		sum += a * b;
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

int main()
{
	//cpu 메모리 동적 할당 및 초기ㅗ하
	int width = 32;
	float* P = new float[width * width];
	float* M = new float[width * width];
	float* N = new float[width * width];
	for (int i = 0; i < width * width; ++i)
	{
		// rand() : 0~ RAND_MAX
		M[i] = rand() % 3 - 1.0;
		N[i] = rand() % 3 - 1.0;
		P[i] = 0.0;
	}
	
	//사용하 ㄹgpu선택
	cudaSetDevice(0);

	//gpu메모리 할당(1)
	float* dev_P, * dev_M, * dev_N;
	cudaMalloc((void**)&dev_P, width * width * sizeof(float));
	cudaMalloc((void**)&dev_M, width * width * sizeof(float));
	cudaMalloc((void**)&dev_N, width * width * sizeof(float));

	//cpu에서 gpu로 메데이터 전송(2)
	cudaMemcpy(dev_M, M, width * width * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_N, N, width * width * sizeof(float), cudaMemcpyHostToDevice);

	//커널 함수를 호출하여 병렬적으로 행렬을 곱한다
	dim3 dimGrid(1, 1);
	dim3 dimBlock(width, width);
	clock_t st = clock();

	//쓰레드 생성 및 커널 함수 호출
	MultMatGPU<<<dimGrid, dimBlock>>>MultMatGPU(dev_P, dev_M, dev_N, width);
	//그리드는 블록의 배열, 하나의 그리드 안에는 여러가지 블록.
	//블록 안에는 여러개의 스레드가 들어있다.

	//첫번째 파라미터 : 그리드 내 블록수
	//두번재 파라미터 : 블록 내의 쓰레드 수
	cudaDeviceSynchronize(); // 모든 쓰레드들이 종료할때 까지 기다림.
	printf("elapsed time = %u ms\n", clock() - st);

	cudaMemcpy(P, dev_P, width * width * sizeof(float), cudaMemcpyDeviceToHost);

	PrintMatrix(M, width);
	PrintMatrix(N, width);
	PrintMatrix(P, width);

	//할당된 gpu메모리 해제
	delete[] M;
	delete[] N;
	delete[] P;

	cudaFree(dev_P);
	cudaFree(dev_M);
	cudaFree(dev_N);
}

























/*
__global__ void AddVecGPU(float* c, float* a, float* b)
{
	int i = threadIdx.x;
	c[i] = a[i] + b[i];

}


int main()
{
	int N = 32;
	float* a = new float[N];
	float* b = new float[N];
	float* c = new float[N];
	for (int i = 0; i < N; ++i)
	{
		// rand() : 0~ RAND_MAX
		a[i] = rand() / (float)RAND_MAX; // 0.0 ~ 1.0 까지의 임의의 수
		b[i] = -a[i];
		c[i] = 0.0;
	}

	// 1. 사용할 gpu를 선택한다
	cudaSetDevice(0);
	cudaError_t cudaStatus = cudaSetDevice(0);

	// 2. GPU(Device)에 메모리를 동적으로 할당한다.
	float* dev_a, * dev_b, * dev_c;
	cudaMalloc((void**)&dev_a, sizeof(float) * N);
	cudaMalloc((void**)&dev_b, sizeof(float) * N);
	cudaMalloc((void**)&dev_c, sizeof(float) * N);

	// 3. CPU 배열의 데이터를 GPU 배열로 복사한다.
	cudaMemcpy(dev_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_c, c, sizeof(float) * N, cudaMemcpyHostToDevice);

	// 4. GPU에서 수행될 함수를 호출
	AddVecGPU<<<1, N>>>(dev_c, dev_a, dev_b);

	//모든 쓰레드가 수행을 종료할 때까지 기다린다. 
	cudaDeviceSynchronize();

	// 5. 결과를 GPU메모리에서 CPU메모리로 복사한다.
	cudaMemcpy(c, dev_c, sizeof(float) * N, cudaMemcpyDeviceToHost);

	for (int i = 0; i < N; ++i)
	{
		printf("c[%d] = %f\n", i, c[i]);
		//if (c[i] != 0.0)
		//	printf("Error\n");

	}
	delete[] a;
	delete[] b;
	delete[] c;

	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

}

*/