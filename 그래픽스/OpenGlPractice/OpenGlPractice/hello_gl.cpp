#include <stdio.h>
#include "GL\freeglut.h"

int Width = 800;
int Height = 600;

//�������� �������� ����ϴ� �ݹ� �Լ�
void Render()
{
	//���� ���۸� ���� ���� �����Ѵ�
	glClearColor(1.0, 1.0, 0.0, 1.0); // 0 ~ 1.0

	//���� ���۸� �����
	glClear(GL_COLOR_BUFFER_BIT);

	//������ ����
	glFinish();
}
void Reshape(int w, int h)
{

}

void Keyboard(unsigned char key, int x, int y)
{

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
