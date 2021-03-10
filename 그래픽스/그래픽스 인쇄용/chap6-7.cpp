//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <cmath>
//#include <vector>
//#include <GL/freeglut.h>
//
//using namespace std;
//
//// Variables for rotation and zooming
//float Angle = 0.0;
//float Angle1 = 0.0;
//float Angle2 = 0.0;
//float Zoom = -30.0;
//
//// Callback functions.
//void Reshape(int w, int h);
//void Render();
//void Keyboard(unsigned char key, int x, int y);
//
//// User-defined funtions.
//void RenderFloor();
//
//int Width = 800, Height = 800;
//int main(int argc, char **argv)
//{
//	// GLUT �ʱ�ȭ
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA);
//
//	// ������ ����
//	glutInitWindowSize(Width, Height);
//	glutCreateWindow("Hello GL3D");
//	
//	// �ݹ� �Լ� ���
//	glutReshapeFunc(Reshape);
//	glutDisplayFunc(Render);
//	glutKeyboardFunc(Keyboard);
//		
//	// �޽��� ó�� ���� ����
//	glutMainLoop();
//	return 0;
//}
//
//void Reshape(int w, int h)
//{
//	// ����Ʈ ��ȯ (NC -> DC)
//	glViewport(0, 0, w, h);
//	Width = w;
//	Height = h;
//}
//
//void SetupViewTransform()
//{
//	glMatrixMode(GL_MODELVIEW);	
//	glLoadIdentity();
//
//	// Translate for zooming in/out
//	glTranslatef(0.0, 0.0, Zoom);
//
//	// For rotation
//	glRotatef(Angle, 1.0, 0.0, 0.0);
//	glRotatef(Angle1, 0.0, 1.0, 0.0);
//	glRotatef(Angle2, 0.0, 0.0, 1.0); 
//}
//
//void SetupViewVolume()
//{
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(30.0, (double)Width/(double)Height, 1.0, 10000.0);
//	//glOrtho(-10.0, 10.0, -10.0, 10.0, 1.0, 1000.0);
//}
//
//void Keyboard(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case '1':
//		Zoom++;
//		break;
//	case '2':
//		Zoom--;
//		break;
//	case '3':
//		Angle++;
//		break;
//	case '4':
//		Angle--;
//		break;
//	case '5':
//		Angle1++;
//		break;
//	case '6':
//		Angle1--;
//		break;
//	case '7':
//		Angle2++;
//		break;
//	case '8':
//		Angle2--;
//		break;
//	}
//	glutPostRedisplay();
//}
//
//void Render()
//{
//	// ����� ������� �ʱ�ȭ
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//	// ���� ������ �����ϴ� ����� ���� �Լ�
//	SetupViewVolume();
//
//	// ���� ��ȯ�� �����ϴ� ����� ���� �Լ� {VC} -> {WC}
//	SetupViewTransform();	
//
//	glMatrixMode(GL_MODELVIEW);
//	RenderFloor();
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//
//	// �𵨸� ��ȯ1
//	glPushMatrix();
//	{
//		glTranslatef(3.0, 3.0, 0.0);
//		glutSolidTeapot(1.0);
//	}
//	glPopMatrix();
//
//	// �𵨸� ��ȯ2
//	glPushMatrix();
//	{
//		glTranslatef(-3.0, 3.0, 0.0);
//		glutSolidCylinder(0.5, 1.0, 10, 10);
//	}
//	glPopMatrix();
//
//	// �𵨸� ��ȯ3
//	glPushMatrix();
//	{
//		glTranslatef(-3.0, -3.0, 0.0);
//		glutSolidTorus(0.3, 0.5, 10, 10);
//	}
//	glPopMatrix();
//	
//
//	// �׸��� ��ħ
//	glFinish();
//}
//
//void RenderFloor()
//{
//	glColor3f(0.0f, 0.0f, 0.0f);
//	for (float x = -10.0; x <= 10.0; x += 1.0)
//	{
//		glBegin(GL_LINES);
//		glVertex3f(x, 0.0, -10.0f);
//		glVertex3f(x, 0.0, 10.0f);
//		glEnd();
//
//		glBegin(GL_LINES);
//		glVertex3f(-10.0f, 0.0, x);
//		glVertex3f(10.0f, 0.0, x);
//		glEnd();
//	}
//}
//
