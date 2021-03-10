
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "..\usr\include\GL\freeglut.h"

const int Dim = 1024;
unsigned char Image[Dim * Dim * 3];
float Theta = 0.0;
int MaxIter = 256;

// �ݹ� �Լ�
void Render();
void Reshape(int w, int h);
void Timer(int id);

// ����� ���� �Լ�
void CreateJuliaSet();
int Julia(float a, float b, float cx, float cy, float R);
void GetColorRainbow(float t, int &r, int &g, int &b);

int main(int argc, char **argv)
{
	// GLUT �ʱ�ȭ
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	// ������ ũ�� ���� �� ����
	glutInitWindowSize(Dim, Dim);
	glutCreateWindow("Julia Set(CPU)");

	// �ݹ� �Լ� ���
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutTimerFunc(1, Timer, 0);

	// �̺�Ʈ ó�� ���� ����
	glutMainLoop();
	return 0;
}

void Render()
{
	// �ȼ� ����(���) ������� �ʱ�ȭ
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Julia ���� ã��,�ȼ� ���۸� ä���.
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
	// Render �Լ��� ȣ���ϰ�, ���� Ÿ�̸Ӹ� �����Ѵ�.
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

