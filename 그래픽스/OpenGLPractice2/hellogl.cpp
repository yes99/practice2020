#include <stdio.h>
#include "freeglut.h"
#include <math.h>
int Width = 800;
int Height = 600;

double gx = 5.0;
double gy = 5.0;
double angle = 5.0;

void Circle();

void Foundtain();





//윈도우의 렌더링을 담당하는 콜백 함수
void Render()
{
	//색상 버퍼를 지울 색을 지정한다
	glClearColor(1.0, 1.0, 1.0, 1.0); // 0 ~ 1.0 RGB A

	//색상 버퍼를 지운다
	glClear(GL_COLOR_BUFFER_BIT);

	//화면에 좌표계를 설정한다.
	//관측영역을 지정한다
	glMatrixMode(GL_PROJECTION); // 현재 행렬을 투영행렬로 선택한다.
	glLoadIdentity();			// 선택된 투영행렬을 단위행렬로 초기화 한다. 
	gluOrtho2D(-gx,gx,-gy,gy);				//좌표계의 영역을 지정한다.

	glMatrixMode(GL_MODELVIEW); //현재 행렬을 모델뷰 행렬로 선택한다.

	glRotated(angle, 0.0, 0.0, 1.0);

	/*
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES); // 세개가 필요
	{
		glVertex2d(-2.0, -1.0); //점1
		glVertex2d(2.0, -1.0); //점2
		glVertex2d(0.0, 3.0); //점3
	}
	glEnd();


	glColor3d(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES); // 세개가 필요
	{
		glVertex2d(-2.0, 1.0); //점1
		glVertex2d(2.0, 1.0); //점2
		glVertex2d(0.0, -3.0); //점3
	}
	*/
	glColor3f(1.f, 0.f, 0.f);

	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(0.f, 0.f, 0.f); //원의 중심
		GLfloat x, y;
		for (float theta = 0; theta < 6.4; theta += 0.1)
		{
			x = cos(theta);
			y = sin(theta);
			glVertex3f(x, y, 0.f);
		}
	}
	glEnd();
	//렌더링 종료
	glFinish();
}
void Reshape(int width, int height) // width = 800, height = 600
{
	glViewport(0, 0, width, height); // 0 0 내가 정한 관측영역 좌측하단  (0,0)
} // 시작점, 시작점,  길이, 길이

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		gx *= 2.0;
		gy *= 2.0;
	}
	if (key == '2')
	{
		gx /= 2.0;
		gy /= 2.0;
	}
	if (key == '3')
	{
		angle += 5.0;
	}
	//강제적으로 render()을 호출한다
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	// freeglut 초기화 (무조건 똑같이...)
	glutInit(&argc, argv);


	//생성할 크기의 윈도우 지정
	glutInitWindowSize(Width, Height);


	// 윈도우의 디스플레이 모드를 RGB로 설정
	glutInitDisplayMode(GLUT_RGB);

	//윈도우를 생성
	glutCreateWindow("Hello GL?");

	//윈도우 화면이 바뀔 때, 자동으로 호출되는 콜백 함수 등록 
	glutDisplayFunc(Render);

	//윈도우의 크기가 변경될때, 자동으로 호출되는 콜백 함수
	glutReshapeFunc(Reshape);

	//키보드를 누를때, 자동으로 호출되는 콜백 함수 등록
	glutKeyboardFunc(Keyboard);

	//메시지 루프로 진입
	glutMainLoop();

	return 0;


}
