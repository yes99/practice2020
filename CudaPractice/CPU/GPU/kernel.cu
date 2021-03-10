#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void AddVecGPU(float* c, float* a, float* b)
{
	//for문이 사라졌다. 순차 진행이 병렬화 됐다
	int i = threadIdx.x;
	c[i] = a[i] + b[i];
	printf("Tread Id = %d\n", i);
}


int main()
{
	int N = 1024 * 1024;
	float* a = new float[N];
	float* b = new float[N];
	float* c = new float[N];
	for (int i = 0; i < N; ++i)
	{
		//rand() : 0~ RAND MAX
		a[i] = rand() / (float)RAND_MAX; //0.0 ~ 1.0 까지의 임의의 수
		b[i] = -a[i];
		c[i] = 0.0;
	}


	// 1. 사용할 gpu선택
	cudaError_t cudaStatus = cudaSetDevice(0);

	// 2. gpu(Device) 에 메모리를 동적으로 할당한다.
	float* dev_a, * dev_b, * dev_c;
	cudaMalloc((void**)&dev_a, sizeof(float) * N);
	cudaMalloc((void**)&dev_b, sizeof(float) * N);
	cudaMalloc((void**)&dev_c, sizeof(float) * N);

	// 3. cpu 배열의 데이터를 gpu 배열로 복사시킨다
	cudaMemcpy(dev_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_c, c, sizeof(float) * N, cudaMemcpyHostToDevice);

	// 4. gpu 에서 수행될 함수(= 커널, kernel)를 호출
	AddVecGPU<<<1, N>>>(dev_c, dev_a, dev_b);

	//모든 쓰레드가 수행을 종료할 때 까지 기다린다. 
	cudaDeviceSynchronize();

	// 5. 결과를 GPU 메모리에서 CPU 메모리로 복사한다.
	cudaMemcpy(c, dev_c, sizeof(float) * N, cudaMemcpyDeviceToHost);



	
	for (int i = 0; i < N; ++i)
	{
//		printf("c[%d] = %f\n", i, c[i]);

		if (c[i] != 0.0)
			printf("Error\n");

	}

	delete[] a;
	delete[] b;
	delete[] c;
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);




}