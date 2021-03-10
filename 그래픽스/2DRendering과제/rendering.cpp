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

void Circle(float circlex, float circley, float r) //�� �׸���
{
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(circlex, circley, 0.f); //���� �߽�
		//glVertex3f(0.f, 0.f, 0.f); //���� �߽�

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

void Ellipse(float circlex, float circley, float r) // Ÿ���� �׸���
{
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(circlex, circley, 0.f); //���� �߽�
		//glVertex3f(0.f, 0.f, 0.f); //���� �߽�

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

void Sector(float circlex, float circley, float r, float start, float end) // ��ä�� �׸���
{
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(circlex, circley, 0.f); //���� �߽�
		//glVertex3f(0.f, 0.f, 0.f); //���� �߽�

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

void Water (float circlex, float circley, float r) // ��ä�� �׸���
{

	glColor3d(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(circlex, circley, 0.f); //���� �߽�
		//glVertex3f(0.f, 0.f, 0.f); //���� �߽�
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
		glVertex2d(5, -8); //��1
		glVertex2d(5, -6); //��1
		glVertex2d(2, -6); //��1
		glVertex2d(2, -8); //��1
	}
	glEnd();
	Sector(2, -8, 2, 90, 180);
	Sector(5, -8, 2, 0, 90);
	Sector(3.5, -6, 1.5, 0, 180);
	glColor3d(0.52, 0.804, 0.91); //RGB
	Sector(3.5, -5.8, 1.0, 0, 180);
	//Ÿ�̾�
	glColor3d(0.0, 0.0, 0.0); //RGB
	Circle(2, -8, 1);
	Circle(5, -8, 1);
}




void Foundtain() //�м�
{
	glColor3d(0.5, 0.5, 0.5); //RGB
	glBegin(GL_POLYGON);
	{
		glVertex2d(1.0, -4.0); //��1
		glVertex2d(9.0, -4.0); //��1
		glVertex2d(9.0, -2.0); //��1
		glVertex2d(1.0, -2.0); //��1
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex2d(4.0, -2.0); //��1
		glVertex2d(6.0, -2.0); //��1
		glVertex2d(6.0, 0.0); //��1
		glVertex2d(4.0, 0.0); //��1
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glVertex2d(2.0, 0.0); //��1
		glVertex2d(2.0, 1.0); //��1
		glVertex2d(8.0, 1.0); //��1
		glVertex2d(8.0, 0.0); //��1
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
	//����
	glColor3d(1.0, 0.0, 0.0); //RGB
	glBegin(GL_TRIANGLES); // ������ �ʿ�
	{
		glVertex2d(-10.0, -2.0); //��1
		glVertex2d(-1.0, -2.0); //��2
		glVertex2d(-5.5, 3.0); //��3
	}
	glEnd();
	//�� ��ü
	glColor3d(1.0, 0.0, 1.0); //RGB
	glBegin(GL_POLYGON);
	{
		glVertex2d(-3.0, -8.0); //��1
		glVertex2d(-3.0, -2.0); //��1
		glVertex2d(-8.0, -2.0); //��1
		glVertex2d(-8.0, -8.0); //��1
	}
	glEnd();
	//â��
	glColor3d(0.52, 0.804, 0.91); //RGB
	glBegin(GL_POLYGON);
	{
		glVertex2d(-7.0, -4.0); //��1
		glVertex2d(-4.0, -4.0); //��1
		glVertex2d(-4.0, -7.0); //��1
		glVertex2d(-7.0, -7.0); //��1
	}
	glEnd();
	//âƲ
	glBegin(GL_LINES);
	{
		glVertex2d(-7, -5.5); //��1
		glVertex2d(-4, -5.5); //��1
	}
	glEnd();
	glBegin(GL_LINES);
	{
		glVertex2d(-5.5, -4); //��1
		glVertex2d(-5.5, -7); //��1
	}
	glEnd();
	//����
	glColor3d(0.8, 0.8, 0.8); //RGB
	glBegin(GL_POLYGON);
	{
		glVertex2d(-2.0, -1.0); //��1
		glVertex2d(-2.0, 3.0); //��1
		glVertex2d(-4.0, 3.0); //��1
		glVertex2d(-4.0, -1.0); //��1
	}
	glEnd();

	// ����
	glColor3d(0.9, 0.9, 0.9); //RGB
	Ellipse(0, 4, 1);
	Ellipse(3, 5, 1);
	Ellipse(6, 6, 1);
}



//�������� �������� ����ϴ� �ݹ� �Լ�
void Render()
{
	//���� ���۸� ���� ���� �����Ѵ�
	glClearColor(0.1, 0.0, 0.5, 1.0); // 0 ~ 1.0 RGB A

	//���� ���۸� �����
	glClear(GL_COLOR_BUFFER_BIT);

	//ȭ�鿡 ��ǥ�踦 �����Ѵ�.
	//���������� �����Ѵ�
	glMatrixMode(GL_PROJECTION); // ���� ����� ������ķ� �����Ѵ�.
	glLoadIdentity();			// ���õ� ��������� ������ķ� �ʱ�ȭ �Ѵ�. 
	gluOrtho2D(-gx, gx, -gy, gy);				//��ǥ���� ������ �����Ѵ�.

	glMatrixMode(GL_MODELVIEW); //���� ����� �𵨺� ��ķ� �����Ѵ�.

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
	glViewport(0, 0, width, height); // 0 0 ���� ���� �������� �����ϴ�  (0,0)
} // ������, ������,  ����, ����

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
	//���������� render()�� ȣ���Ѵ�
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	// freeglut �ʱ�ȭ (������ �Ȱ���...)
	glutInit(&argc, argv);


	//������ ũ���� ������ ����
	glutInitWindowSize(Width, Height);


	// �������� ���÷��� ��带 RGB�� ����
	glutInitDisplayMode(GLUT_RGB);

	//�����츦 ����
	glutCreateWindow("Hello GL?");

	//������ ȭ���� �ٲ� ��, �ڵ����� ȣ��Ǵ� �ݹ� �Լ� ��� 
	glutDisplayFunc(Render);

	//�������� ũ�Ⱑ ����ɶ�, �ڵ����� ȣ��Ǵ� �ݹ� �Լ�
	glutReshapeFunc(Reshape);

	//Ű���带 ������, �ڵ����� ȣ��Ǵ� �ݹ� �Լ� ���
	glutKeyboardFunc(Keyboard);

	//�޽��� ������ ����
	glutMainLoop();

	return 0;


}
