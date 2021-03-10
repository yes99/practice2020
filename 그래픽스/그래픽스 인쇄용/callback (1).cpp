#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gl\freeglut.h"
#include <math.h>

int Width = 800, Height = 600;
int x = 100, y = 100;

// 콜백 함수 선언
void Display();
void Reshape(int w, int h);
void Close();
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void PassiveMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Timer(int id);
void ColorMenu(int id);
void CreateMenu(int id);

int main(int argc, char **argv)
{
	// GLUT 초기화
	glutInit(&argc, argv);

	// 윈도우 크기 및 위치 초기화
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);

	// 디스플레이모드 설정
	glutInitDisplayMode(GLUT_RGBA);

	// 윈도우 생성
	glutCreateWindow("콜백 함수 예제");

	// 콜백 함수 등록
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutCloseFunc(Close);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotion);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, Timer, 0);

	// 메뉴 생성 예제...
	GLint ColorMenuId = glutCreateMenu(ColorMenu);
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);

	GLint CreateMenuId = glutCreateMenu(CreateMenu);
	glutAddMenuEntry("Point", 0);
	glutAddMenuEntry("Line", 1);
	glutAddMenuEntry("Polygon", 2);
	glutAddSubMenu("Color", ColorMenuId);
	glutAddMenuEntry("Exit", 3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


	// 메시지 루프 진입
	glutMainLoop();
	return 0;
}

void ColorMenu(int id)
{

}

void CreateMenu(int id)
{
	if (id == 3) // "Exit" 선택...
		exit(0);
}

void Timer(int id)
{
	x = x + 10;
	y = y + 10;
	glutPostRedisplay();
	glutTimerFunc(100, Timer, 0);
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}

void Display()
{
	// Clear color buffer with specified clear color (R, G, B, A)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// 관측 공간을 지정한다.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, Width, 0.0, Height);

	// 모델링 변환을 수행한다.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
	{
		glVertex2i(x, y);
		glVertex2i(x + 300, y);
		glVertex2i(x + 150, y + 300);
	}
	glEnd();	

	glFinish();
}

void Close()
{
	// 프로그램 종료에 따른 후처리...
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		printf("왼쪽 버튼\n");
	}

	if (button == GLUT_RIGHT_BUTTON)
	{
		printf("오른쪽 버튼\n");
	}

	if (state == GLUT_DOWN)
	{
		printf("눌림\n");
	}

	if (state == GLUT_UP)
	{
		printf("해제\n");
	}
}

void Motion(int x, int y)
{
	printf("(%d, %d)\n", x, y);
}

void PassiveMotion(int x, int y)
{
	printf("(%d, %d)\n", x, y);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
		exit(0);
}


