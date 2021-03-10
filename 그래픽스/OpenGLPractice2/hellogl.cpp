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





//�������� �������� ����ϴ� �ݹ� �Լ�
void Render()
{
	//���� ���۸� ���� ���� �����Ѵ�
	glClearColor(1.0, 1.0, 1.0, 1.0); // 0 ~ 1.0 RGB A

	//���� ���۸� �����
	glClear(GL_COLOR_BUFFER_BIT);

	//ȭ�鿡 ��ǥ�踦 �����Ѵ�.
	//���������� �����Ѵ�
	glMatrixMode(GL_PROJECTION); // ���� ����� ������ķ� �����Ѵ�.
	glLoadIdentity();			// ���õ� ��������� ������ķ� �ʱ�ȭ �Ѵ�. 
	gluOrtho2D(-gx,gx,-gy,gy);				//��ǥ���� ������ �����Ѵ�.

	glMatrixMode(GL_MODELVIEW); //���� ����� �𵨺� ��ķ� �����Ѵ�.

	glRotated(angle, 0.0, 0.0, 1.0);

	/*
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES); // ������ �ʿ�
	{
		glVertex2d(-2.0, -1.0); //��1
		glVertex2d(2.0, -1.0); //��2
		glVertex2d(0.0, 3.0); //��3
	}
	glEnd();


	glColor3d(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES); // ������ �ʿ�
	{
		glVertex2d(-2.0, 1.0); //��1
		glVertex2d(2.0, 1.0); //��2
		glVertex2d(0.0, -3.0); //��3
	}
	*/
	glColor3f(1.f, 0.f, 0.f);

	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(0.f, 0.f, 0.f); //���� �߽�
		GLfloat x, y;
		for (float theta = 0; theta < 6.4; theta += 0.1)
		{
			x = cos(theta);
			y = sin(theta);
			glVertex3f(x, y, 0.f);
		}
	}
	glEnd();
	//������ ����
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
