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
	//cpu �޸� ���� �Ҵ� �� �ʱ����
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
	
	//����� ��gpu����
	cudaSetDevice(0);

	//gpu�޸� �Ҵ�(1)
	float* dev_P, * dev_M, * dev_N;
	cudaMalloc((void**)&dev_P, width * width * sizeof(float));
	cudaMalloc((void**)&dev_M, width * width * sizeof(float));
	cudaMalloc((void**)&dev_N, width * width * sizeof(float));

	//cpu���� gpu�� �޵����� ����(2)
	cudaMemcpy(dev_M, M, width * width * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_N, N, width * width * sizeof(float), cudaMemcpyHostToDevice);

	//Ŀ�� �Լ��� ȣ���Ͽ� ���������� ����� ���Ѵ�
	dim3 dimGrid(1, 1);
	dim3 dimBlock(width, width);
	clock_t st = clock();

	//������ ���� �� Ŀ�� �Լ� ȣ��
	MultMatGPU<<<dimGrid, dimBlock>>>MultMatGPU(dev_P, dev_M, dev_N, width);
	//�׸���� ����� �迭, �ϳ��� �׸��� �ȿ��� �������� ���.
	//��� �ȿ��� �������� �����尡 ����ִ�.

	//ù��° �Ķ���� : �׸��� �� ��ϼ�
	//�ι��� �Ķ���� : ��� ���� ������ ��
	cudaDeviceSynchronize(); // ��� ��������� �����Ҷ� ���� ��ٸ�.
	printf("elapsed time = %u ms\n", clock() - st);

	cudaMemcpy(P, dev_P, width * width * sizeof(float), cudaMemcpyDeviceToHost);

	PrintMatrix(M, width);
	PrintMatrix(N, width);
	PrintMatrix(P, width);

	//�Ҵ�� gpu�޸� ����
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
		a[i] = rand() / (float)RAND_MAX; // 0.0 ~ 1.0 ������ ������ ��
		b[i] = -a[i];
		c[i] = 0.0;
	}

	// 1. ����� gpu�� �����Ѵ�
	cudaSetDevice(0);
	cudaError_t cudaStatus = cudaSetDevice(0);

	// 2. GPU(Device)�� �޸𸮸� �������� �Ҵ��Ѵ�.
	float* dev_a, * dev_b, * dev_c;
	cudaMalloc((void**)&dev_a, sizeof(float) * N);
	cudaMalloc((void**)&dev_b, sizeof(float) * N);
	cudaMalloc((void**)&dev_c, sizeof(float) * N);

	// 3. CPU �迭�� �����͸� GPU �迭�� �����Ѵ�.
	cudaMemcpy(dev_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_c, c, sizeof(float) * N, cudaMemcpyHostToDevice);

	// 4. GPU���� ����� �Լ��� ȣ��
	AddVecGPU<<<1, N>>>(dev_c, dev_a, dev_b);

	//��� �����尡 ������ ������ ������ ��ٸ���. 
	cudaDeviceSynchronize();

	// 5. ����� GPU�޸𸮿��� CPU�޸𸮷� �����Ѵ�.
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