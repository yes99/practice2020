#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void AddVecGPU(float* c, float* a, float* b)
{
	//for���� �������. ���� ������ ����ȭ �ƴ�
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
		a[i] = rand() / (float)RAND_MAX; //0.0 ~ 1.0 ������ ������ ��
		b[i] = -a[i];
		c[i] = 0.0;
	}


	// 1. ����� gpu����
	cudaError_t cudaStatus = cudaSetDevice(0);

	// 2. gpu(Device) �� �޸𸮸� �������� �Ҵ��Ѵ�.
	float* dev_a, * dev_b, * dev_c;
	cudaMalloc((void**)&dev_a, sizeof(float) * N);
	cudaMalloc((void**)&dev_b, sizeof(float) * N);
	cudaMalloc((void**)&dev_c, sizeof(float) * N);

	// 3. cpu �迭�� �����͸� gpu �迭�� �����Ų��
	cudaMemcpy(dev_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_c, c, sizeof(float) * N, cudaMemcpyHostToDevice);

	// 4. gpu ���� ����� �Լ�(= Ŀ��, kernel)�� ȣ��
	AddVecGPU<<<1, N>>>(dev_c, dev_a, dev_b);

	//��� �����尡 ������ ������ �� ���� ��ٸ���. 
	cudaDeviceSynchronize();

	// 5. ����� GPU �޸𸮿��� CPU �޸𸮷� �����Ѵ�.
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