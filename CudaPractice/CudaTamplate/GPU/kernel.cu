
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "..\usr\include\GL\freeglut.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

//콜백 함수
void Render(); // 이미지의 크기
void Reshape(int w, int h); // 배열 1024 by 1024  rgb 이미지 이기 때문
void Timer(int id);

//사용자 정의 함수
void CreateJuliaSet();

//커널 함수
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
	//GLUT 초기화
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	//윈도우 크기 설정 및 생성
	glutInitWindowSize(Dim, Dim);
	glutCreateWindow("Julia Set(GPU)");

	//콜백 함수 등록
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutTimerFunc(1, Timer, 0);

	//GPU 메모리 동적 할당
	cudaSetDevice(0);
	cudaMalloc((void **)&DevImage, sizeof(unsigned char) * Dim * Dim * 3);

	//이벤트 처리 루프 진입
	glutMainLoop();

	//메모리 해제
	cudaFree(DevImage);
	cudaDeviceReset();
	return 0;
}

void Render()
{
	//픽셀 버퍼(배경)을 흰색으로 초기화한다.
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//Julia 집합 찾아 픽셀 버퍼를 채운다.
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
	int MaxIter = 256; //점화식 반복
	
	//그리드 크기와 블록의 크기 결정
	dim3 gridDim(Dim / TILE_WIDTH, Dim / TILE_WIDTH);
	dim3 blockDim(TILE_WIDTH, TILE_WIDTH);

	// 커널함수 (julia_kernel) 호출
	clock_t st = clock();
	julia_kernel << <gridDim, blockDim >> > (DevImage, cx, cy, R, MaxIter);
	cudaDeviceSynchronize();

	//결과를 CPU로 복사한다
	cudaMemcpy(Image, DevImage, sizeof (unsigned char)* Dim* Dim * 3, cudaMemcpyDeviceToHost);
	printf("Elapsed time = %u ms\n", clock() - st);
}

__global__ void julia_kernel(unsigned char* pImage, float cx, float cy, float R, int MaxIter)
{
	int x = blockIdx.x * TILE_WIDTH + threadIdx.x;
	int y = blockIdx.y * TILE_WIDTH + threadIdx.y;
	if (x < Dim && y < Dim) // 이미지 크기 안에 들어간다면
	{
		float a = (x / (float)(Dim - 1) * 2.0 - 1.0) * R * 0.5;
		float b = -(y/ (float)(Dim - 1) * 2.0 - 1.0) * R * 0.5;

		int offset = (y * Dim + x) * 3;
		int Iter = Julia(a, b, cx, cy, R, MaxIter); // z(0)이 줄리아에 포함되는지 확인
		
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
	case 0:	// 빨강 ~ 주황
		r = 255;
		g = t * 127;
		b = 0;
		//r = g = b = 255;
		break;

	case 1:	// 주황 ~ 노랑
		r = 0;
		g = (1.0 - t) * 127 + t * 255;
		b = 0;
		break;

	case 2:	// 노랑 ~ 초록
		r = (1.0 - t) * 255;
		g = 255;
		b = 0;
		break;

	case 3:	// 초록 ~ 파랑
		r = 0;
		g = (1.0 - t) * 255;
		b = t * 255;
		break;

	case 4:	// 파랑 ~ 남색
		r = t * 75;
		g = 0;
		b = (1.0 - t) * 255 + t * 130;
		break;

	case 5:	// 남색 ~ 보라
		r = (1.0 - t) * 75 + t * 148;
		g = 0;
		b = (1.0 - t) * 130 + t * 211;
		break;

	case 6:	// 보라
		r = 148;
		g = 0;
		b = 211;
		break;
	}

	// 범위 밖은 검정색을 할당한다.
	if (t < 0.0 || t > 1.0)
		r = g = b = 0;
}
