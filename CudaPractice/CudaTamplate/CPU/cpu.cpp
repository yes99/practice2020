
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "..\usr\include\GL\freeglut.h"

const int Dim = 1024;
unsigned char Image[Dim * Dim * 3];
float Theta = 0.0;
int MaxIter = 256;

// 콜백 함수
void Render();
void Reshape(int w, int h);
void Timer(int id);

// 사용자 정의 함수
void CreateJuliaSet();
int Julia(float a, float b, float cx, float cy, float R);
void GetColorRainbow(float t, int &r, int &g, int &b);

int main(int argc, char **argv)
{
	// GLUT 초기화
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	// 윈도우 크기 설정 및 생성
	glutInitWindowSize(Dim, Dim);
	glutCreateWindow("Julia Set(CPU)");

	// 콜백 함수 등록
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutTimerFunc(1, Timer, 0);

	// 이벤트 처리 루프 진입
	glutMainLoop();
	return 0;
}

void Render()
{
	// 픽셀 버퍼(배경) 흰색으로 초기화
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Julia 집합 찾아,픽셀 버퍼를 채운다.
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
	// Render 함수를 호출하고, 다음 타이머를 설정한다.
	Theta += 0.01;
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
}

void CreateJuliaSet()
{
	float cx = cos(Theta) * 0.7885, cy = sin(Theta) * 0.7885;
	float R = sqrt(cx * cx + cy * cy) * 3;
	clock_t st = clock();
	for (int y = 0; y < Dim; ++y) {
		for (int x = 0; x < Dim; ++x) {
			// z = a + bi;
			float a = (x / (float)(Dim - 1) * 2.0 - 1.0) * R * 0.5;
			float b = -(y / (float)(Dim - 1) * 2.0 - 1.0) * R * 0.5;

			int offset = (y * Dim + x) * 3;
			int Iter = Julia(a, b, cx, cy, R);
			float t = (float)Iter / MaxIter;
			int R, G, B;
			GetColorRainbow(t, R, G, B);
			Image[offset] = R;
			Image[offset + 1] = G;
			Image[offset + 2] = B;
		}
	}
	printf("Elapsed time = %u ms\n", clock() - st);
}

int Julia(float a, float b, float cx, float cy, float R)
{
	// z = a + ib;
	for (int k = 0; k < MaxIter; ++k)
	{
		// z = z * z + c;
		float re = a * a - b * b;
		float im = 2 * a * b;
		a = re + cx;
		b = im + cy;
		if (a * a + b * b > R * R)
			return k;
	}
	return MaxIter;
}

void GetColorRainbow(float t, int &r, int &g, int &b)
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

