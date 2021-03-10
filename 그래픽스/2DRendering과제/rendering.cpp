#include <stdio.h>
#include "freeglut.h"
#include <math.h>
#include <time.h>
int Width = 800;
int Height = 800;
double pi = 3.141592653;

double gx = 10.0;
double gy = 10.0;
double angle = 5.0;

void Circle(float circlex, float circley, float r);

void Foundtain();

void House();

void Car();

void Circle(float circlex, float circley, float r) //원 그리기
{
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(circlex, circley, 0.f); //원의 중심
		//glVertex3f(0.f, 0.f, 0.f); //원의 중심

		GLfloat x, y;
		for (float theta = 0; theta < 6.4; theta += 0.1)
		{
			x = circlex + r * cos(theta);
			y = circley + r * sin(theta);
			glVertex3f(x, y, 0.f);
		}
	}
	glEnd();
}

void Ellipse(float circlex, float circley, float r) // 타원형 그리기
{
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(circlex, circley, 0.f); //원의 중심
		//glVertex3f(0.f, 0.f, 0.f); //원의 중심

		GLfloat x, y;
		for (float theta = 0; theta < 6.4; theta += 0.1)
		{
			x = circlex + 2*  r * cos(theta);
			y = circley + r * sin(theta);
			glVertex3f(x, y, 0.f);
		}
	}
	glEnd();
}

void Sector(float circlex, float circley, float r, float start, float end) // 부채꼴 그리기
{
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(circlex, circley, 0.f); //원의 중심
		//glVertex3f(0.f, 0.f, 0.f); //원의 중심

		float startR = start * pi / 180;
		float endR = end * pi / 180;


		GLfloat x, y;
		for (float theta = startR; theta < endR; theta += 0.01)
		{
			x = circlex + r * cos(theta);
			y = circley + r * sin(theta);
			glVertex3f(x, y, 0.f);
		}
	}
	glEnd();
}

void Water (float circlex, float circley, float r) // 부채꼴 그리기
{

	glColor3d(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(circlex, circley, 0.f); //원의 중심
		//glVertex3f(0.f, 0.f, 0.f); //원의 중심
		int start = 60;
		int end = 120;
		float startR = start * pi / 180;
		float endR = end * pi / 180;


		GLfloat x, y;
		for (float theta = startR; theta < endR; theta += 0.01)
		{
			x = circlex + r * cos(theta);
			y = circley + r * sin(theta);
			glVertex3f(x, y, 0.f);
		}
	}
	glEnd();
}

void Car()
{
	glColor3d(0.5, 0, 0.5); //RGB
	glBegin(GL_POLYGON);
	{
		glVertex2d(5, -8); //점1
		glVertex2d(5, -6); //점1
		glVertex2d(2, -6); //점1
		glVertex2d(2, -8); //점1
	}
	glEnd();
	Sector(2, -8, 2, 90, 180);
	Sector(5, -8, 2, 0, 90);
	Sector(3.5, -6, 1.5, 0, 180);
	glColor3d(0.52, 0.804, 0.91); //RGB
	Sector(3.5, -5.8, 1.0, 0, 180);
	//타이어
	glColor3d(0.0, 0.0, 0.0); //RGB
	Circle(2, -8, 1);
	Circle(5, -8, 1);
}




void Foundtain() //분수
{
	glColor3d(0.5, 0.5, 0.5); //RGB
	glBegin(GL_POLYGON);
	{
		glVertex2d(1.0, -4.0); //점1
		glVertex2d(9.0, -4.0); //점1
		glVertex2d(9.0, -2.0); //점1
		glVertex2d(1.0, -2.0); //점1
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex2d(4.0, -2.0); //점1
		glVertex2d(6.0, -2.0); //점1
		glVertex2d(6.0, 0.0); //점1
		glVertex2d(4.0, 0.0); //점1
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex2d(2.0, 0.0); //점1
		glVertex2d(2.0, 1.0); //점1
		glVertex2d(8.0, 1.0); //점1
		glVertex2d(8.0, 0.0); //점1
	}
	glEnd();
	Water(2, -2, 2);
	Water(8, -2, 2);
	Water(3, 1, 2);
	Water(5, 1, 2);
	Water(7, 1, 2);

}




void House()
{
	//지붕
	glColor3d(1.0, 0.0, 0.0); //RGB
	glBegin(GL_TRIANGLES); // 세개가 필요
	{
		glVertex2d(-10.0, -2.0); //점1
		glVertex2d(-1.0, -2.0); //점2
		glVertex2d(-5.5, 3.0); //점3
	}
	glEnd();
	//집 몸체
	glColor3d(1.0, 0.0, 1.0); //RGB
	glBegin(GL_POLYGON);
	{
		glVertex2d(-3.0, -8.0); //점1
		glVertex2d(-3.0, -2.0); //점1
		glVertex2d(-8.0, -2.0); //점1
		glVertex2d(-8.0, -8.0); //점1
	}
	glEnd();
	//창문
	glColor3d(0.52, 0.804, 0.91); //RGB
	glBegin(GL_POLYGON);
	{
		glVertex2d(-7.0, -4.0); //점1
		glVertex2d(-4.0, -4.0); //점1
		glVertex2d(-4.0, -7.0); //점1
		glVertex2d(-7.0, -7.0); //점1
	}
	glEnd();
	//창틀
	glBegin(GL_LINES);
	{
		glVertex2d(-7, -5.5); //점1
		glVertex2d(-4, -5.5); //점1
	}
	glEnd();
	glBegin(GL_LINES);
	{
		glVertex2d(-5.5, -4); //점1
		glVertex2d(-5.5, -7); //점1
	}
	glEnd();
	//굴뚝
	glColor3d(0.8, 0.8, 0.8); //RGB
	glBegin(GL_POLYGON);
	{
		glVertex2d(-2.0, -1.0); //점1
		glVertex2d(-2.0, 3.0); //점1
		glVertex2d(-4.0, 3.0); //점1
		glVertex2d(-4.0, -1.0); //점1
	}
	glEnd();

	// 연기
	glColor3d(0.9, 0.9, 0.9); //RGB
	Ellipse(0, 4, 1);
	Ellipse(3, 5, 1);
	Ellipse(6, 6, 1);
}



//윈도우의 렌더링을 담당하는 콜백 함수
void Render()
{
	//색상 버퍼를 지울 색을 지정한다
	glClearColor(0.1, 0.0, 0.5, 1.0); // 0 ~ 1.0 RGB A

	//색상 버퍼를 지운다
	glClear(GL_COLOR_BUFFER_BIT);

	//화면에 좌표계를 설정한다.
	//관측영역을 지정한다
	glMatrixMode(GL_PROJECTION); // 현재 행렬을 투영행렬로 선택한다.
	glLoadIdentity();			// 선택된 투영행렬을 단위행렬로 초기화 한다. 
	gluOrtho2D(-gx, gx, -gy, gy);				//좌표계의 영역을 지정한다.

	glMatrixMode(GL_MODELVIEW); //현재 행렬을 모델뷰 행렬로 선택한다.

	//glRotated(angle, 0.0, 0.0, 1.0);

	srand((unsigned int)time(NULL));
	House();
	Foundtain();
	Car();
	glColor3d(1.0, 1.0, 0.0); //RGB
	Circle(8.2, 8.2, 1.5);
	float xposition, yposition;
	for (int i = 0; i < 30; i++)
	{
		xposition = rand() % 20 - 10;
		yposition = rand() %5 + 5;
		Circle(xposition, yposition, 0.1);
	}


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
