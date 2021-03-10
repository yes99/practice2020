#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gl\freeglut.h"
#include <math.h>

int Width = 800, Height = 600;
int x = 100, y = 100;
GLint color;
GLint pattern;
GLint width;
GLint gx1;
GLint gy1;
GLint dotx;
GLint doty;
GLint gx2;
GLint gy2;
GLint px1[500];
GLint py1[500];
GLint px2[500];
GLint py2[500];

// 콜백 함수 선언
void Display();
void Reshape(int w, int h);
void Close();
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void PassiveMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void ColorMenu(int id);
void WidthMenu(int id);
void PatternMenu(int id);
void CreateMenu(int id);
void initBackcolor();

int main(int argc, char** argv)
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

	// 메뉴 생성 예제...
	GLint ColorMenuId = glutCreateMenu(ColorMenu);
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);

	GLint WidthMenuId = glutCreateMenu(WidthMenu);
	glutAddMenuEntry("1.0", 0);
	glutAddMenuEntry("3.0", 1);
	glutAddMenuEntry("5.0", 2);


	GLint PatternMenuId = glutCreateMenu(PatternMenu);
	glutAddMenuEntry("Solid", 0);
	glutAddMenuEntry("Dotted", 1);

	GLint CreateMenuId = glutCreateMenu(CreateMenu);
	
	glutAddSubMenu("Color", ColorMenuId);
	glutAddSubMenu("Width", WidthMenuId);
	glutAddSubMenu("Pattern", PatternMenuId);

	glutAddMenuEntry("Exit", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


	// 메시지 루프 진입
	initBackcolor();

	glutMainLoop();
	return 0;
}

void ColorMenu(int id)
{
	if (id == 0) //R
	{
		color = 0;
		//glColor3d(1.0, 0.0, 0.0); //RGB

	}
	else if (id == 1) //G
	{
		color = 1;
		//glColor3d(0.0, 1.0, 0.0); //RGB

	}
	else if (id == 2) //B
	{
		color = 2;
		//glColor3d(0.0, 0.0, 1.0); //RGB

	}
	//glutPostRedisplay();
}
void WidthMenu(int id)
{
	if (id == 0) //1.0
	{
		width = 0;
		//glLineWidth(1.0);
	}
	else if (id == 1) // 3.0
	{
		width = 1;
		//glLineWidth(3.0);
	}
	else if (id == 2) // 5.0
	{
		width = 2;
		//glLineWidth(5.0);
	}
	//glutPostRedisplay();
}


void line()
{

}

void PatternMenu(int id)
{
	if (id == 0) //solid
	{
		pattern = 0;
		//glLineStipple(1, 0xFFFF);
	}
	else if (id == 1) //dot
	{
		pattern = 1;
		//glLineStipple(1, 0xF0F0);
	}
	//glutPostRedisplay();
}

void CreateMenu(int id)
{
	if (id == 0) // "Exit" 선택...
		exit(0);
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}
void initBackcolor()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Display()
{
	// Clear color buffer with specified clear color (R, G, B, A)
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	// 관측 공간을 지정한다.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, Width, 0.0, Height);
	glMatrixMode(GL_MODELVIEW); //현재 행렬을 모델뷰 행렬로 선택한다.


	if (color == 0)
	{
		glColor3d(1.0, 0.0, 0.0); //RGB
	}
	else if (color == 1)
	{
		glColor3d(0.0, 1.0, 0.0); //RGB
	}
	else if (color == 2)
	{
		glColor3d(0.0, 0.0, 1.0); //RGB
	}

	if (width == 0)
	{
		glLineWidth(1.0);
	}
	else if (width == 1)
	{
		glLineWidth(3.0);
	}
	else if (width == 2)
	{
		glLineWidth(5.0);
	}
	glEnable(GL_LINE_STIPPLE);
	if (pattern == 0) //solid
	{
		glLineStipple(1, 0xFFFF);
	}
	else if (pattern == 1) //dot
	{
		glLineStipple(1, 0xF0F0);
	}

	/*	gx1 = px1[i];
		dotx = px2[i];
		gy1 = py1[i];
		doty = py2[i];*/
	
		glPushMatrix();
		glBegin(GL_LINES);
		{
			//glVertex2i(px1[i], Height - py1[i]);
			//glVertex2i(px2[i], Height - py2[i]);
			glVertex2i(gx1, Height - gy1);
			glVertex2i(dotx, Height - doty);

			glVertex2i(gx2, Height - gy2);
		}
		glEnd();

		glPopMatrix();

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

	if (state == GLUT_DOWN)
	{
		printf("눌림\n");
		printf("%d  %d", x, y);
		gx1 = x;
		gy1 = y;
	}

	if (state == GLUT_UP)
	{
		printf("해제\n");
		printf("%d  %d", x, y);
		gx2 = x;
		gy2 = y;
	}
}

void Motion(int x, int y)
{
	printf("(%d, %d)\n", x, y);
	dotx = x;
	doty = y;
	//glutPostRedisplay();
}

void PassiveMotion(int x, int y)
{
	//printf("(%d, %d)\n", x, y);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
		exit(0);
}


