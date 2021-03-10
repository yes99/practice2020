
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "..\usr\include\GL\freeglut.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

//�ݹ� �Լ�
void Render(); // �̹����� ũ��
void Reshape(int w, int h); // �迭 1024 by 1024  rgb �̹��� �̱� ����
void Timer(int id);

//����� ���� �Լ�
void CreateJuliaSet();

//Ŀ�� �Լ�
__global__ void julia_kernel(unsigned char* pImage, float cx, float cy, float R, int MaxIter);
__device__ int Julia(float a, float b, float cx, float cy, float R, int MaxIter);
__device__ void GetColorRainbow(float t, int& r, int& g, int& b);

#define TILE_WIDTH 32
const int Dim = 1024;
unsigned char Image[Dim*Dim * 3];
unsigned char *DevImage;
float theta = 0.0;

int main(int argc, char **argv)
{
	//GLUT �ʱ�ȭ
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	//������ ũ�� ���� �� ����
	glutInitWindowSize(Dim, Dim);
	glutCreateWindow("Julia Set(GPU)");

	//�ݹ� �Լ� ���
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutTimerFunc(1, Timer, 0);

	//GPU �޸� ���� �Ҵ�
	cudaSetDevice(0);
	cudaMalloc((void **)&DevImage, sizeof(unsigned char) * Dim * Dim * 3);

	//�̺�Ʈ ó�� ���� ����
	glutMainLoop();

	//�޸� ����
	cudaFree(DevImage);
	cudaDeviceReset();
	return 0;
}

void Render()
{
	//�ȼ� ����(���)�� ������� �ʱ�ȭ�Ѵ�.
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//Julia ���� ã�� �ȼ� ���۸� ä���.
	CreateJuliaSet();
	glDrawPixels(Dim, Dim, GL_RGB, GL_UNSIGNED_BYTE, Image);
	glFinish();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Timer(int id)
{
	theta += 0.01;
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
}


void CreateJuliaSet()
{
	float cx = cos(theta) * 0.7885;
	float cy = sin(theta) * 0.7885;
	float R = sqrt(cx * cx + cy * cy) * 3;
	int MaxIter = 256; //��ȭ�� �ݺ�
	
	//�׸��� ũ��� ����� ũ�� ����
	dim3 gridDim(Dim / TILE_WIDTH, Dim / TILE_WIDTH);
	dim3 blockDim(TILE_WIDTH, TILE_WIDTH);

	// Ŀ���Լ� (julia_kernel) ȣ��
	clock_t st = clock();
	julia_kernel << <gridDim, blockDim >> > (DevImage, cx, cy, R, MaxIter);
	cudaDeviceSynchronize();

	//����� CPU�� �����Ѵ�
	cudaMemcpy(Image, DevImage, sizeof (unsigned char)* Dim* Dim * 3, cudaMemcpyDeviceToHost);
	printf("Elapsed time = %u ms\n", clock() - st);
}

__global__ void julia_kernel(unsigned char* pImage, float cx, float cy, float R, int MaxIter)
{
	int x = blockIdx.x * TILE_WIDTH + threadIdx.x;
	int y = blockIdx.y * TILE_WIDTH + threadIdx.y;
	if (x < Dim && y < Dim) // �̹��� ũ�� �ȿ� ���ٸ�
	{
		float a = (x / (float)(Dim - 1) * 2.0 - 1.0) * R * 0.5;
		float b = -(y/ (float)(Dim - 1) * 2.0 - 1.0) * R * 0.5;

		int offset = (y * Dim + x) * 3;
		int Iter = Julia(a, b, cx, cy, R, MaxIter); // z(0)�� �ٸ��ƿ� ���ԵǴ��� Ȯ��
		
		float t = (float)Iter / MaxIter; //(0~MaxIter) -> (0,1)
		int R, G, B;
		GetColorRainbow(t, R, G, B);
		pImage[offset] = R;
		pImage[offset + 1] = G;
		pImage[offset + 2] = B;
	}
}


__device__ int Julia(float a, float b, float cx, float cy, float R, int MaxIter)
{
	for (int k = 0; k < MaxIter; ++k)
	{
		float re = a * a - b * b;
		float im = 2 * a * b;
		a = re + cx;
		b = im + cy;
		
		float len = sqrtf(a * a + b * b);
		if (a * a + b * b > R * R)
			return k;
	}
	return MaxIter;

}

__device__ void GetColorRainbow(float t, int& r, int& g, int& b)
{
	int X = (int)(6 * t);
	// 0.0 <= t <= 1.0
	t = 6.0 * t - X;
	switch (X)
	{
	case 0:	// ���� ~ ��Ȳ
		r = 255;
		g = t * 127;
		b = 0;
		//r = g = b = 255;
		break;

	case 1:	// ��Ȳ ~ ���
		r = 0;
		g = (1.0 - t) * 127 + t * 255;
		b = 0;
		break;

	case 2:	// ��� ~ �ʷ�
		r = (1.0 - t) * 255;
		g = 255;
		b = 0;
		break;

	case 3:	// �ʷ� ~ �Ķ�
		r = 0;
		g = (1.0 - t) * 255;
		b = t * 255;
		break;

	case 4:	// �Ķ� ~ ����
		r = t * 75;
		g = 0;
		b = (1.0 - t) * 255 + t * 130;
		break;

	case 5:	// ���� ~ ����
		r = (1.0 - t) * 75 + t * 148;
		g = 0;
		b = (1.0 - t) * 130 + t * 211;
		break;

	case 6:	// ����
		r = 148;
		g = 0;
		b = 211;
		break;
	}

	// ���� ���� �������� �Ҵ��Ѵ�.
	if (t < 0.0 || t > 1.0)
		r = g = b = 0;
}
