#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gl\freeglut.h"
#include <math.h>



#define NUMBER_OF_POINT        1000     // �׸� �� �ִ� �� ���� ����



enum __shape    // �׸� ������ ������ �����ϴ� Enumerator

{

    GLPOINT = 1,

    LINE = 2,

    POLYGON = 3

}          Shape;



GLfloat myVertices[NUMBER_OF_POINT][2];            // �׷��� ���� ��ġ�� �����ϴ� �迭

GLfloat currentWidth = 640.0;      // ������ â ũ�⸦ �����ϴ� ����

GLfloat currentHeight = 480.0;

GLfloat initWidth = 640.0;           // ó�� â ũ�⸦ �����ϴ� ����

GLfloat initHeight = 480.0;



GLint count = 0;                                 // ��ü ���� ������ �����ϴ� ����



void MyDisplay()

{

    GLint index;



    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0); // �׷����� ��ü�� ����, ���⼭�� R ���� 1�̹Ƿ� ������

    glPointSize(3.0f);  // �׷����� ���� ũ��



    glEnableClientState(GL_VERTEX_ARRAY);     // �迭�� ��� �����ϵ��� ��



    // myVertices �迭 �ȿ� ��ǥ�� �ϳ��� �� �ִٸ�

    if (count > 0)

    {

        switch (Shape)

        {

            // ���� ��´�

        case POINT:

            for (index = 0; index < count; index++)

            {

                glBegin(GL_POINTS);

                glVertex2f(myVertices[index][0], myVertices[index][1]);

            }

            break;

            // ���� �׸���

        case LINE:

            glBegin(GL_LINE_STRIP);

            for (index = 0; index < count; index++)

            {

                glVertex2f(myVertices[index][0], myVertices[index][1]);

            }

            break;

            // ������ �׸���

        case POLYGON:

            glBegin(GL_POLYGON);

            for (index = 0; index < count; index++)

            {

                glVertex2f(myVertices[index][0], myVertices[index][1]);

            }

            break;

        }

    }

    glEnd();

    glFlush();

}



// �޴� �̺�Ʈ Call Back �Լ�

void MyMainMenu(int entryID)

{

    if (entryID == 1)

    {

        Shape = POINT;

    }

    else if (entryID == 2)

    {

        Shape = LINE;

    }

    else if (entryID == 3)

    {

        Shape = POLYGON;

    }

    else if (entryID == 4)

    {

        exit(0);

    }



    glutPostRedisplay();

}







// �ٽ� �׷��ִ� �Լ�

void MyReshape(int NewWidth, int NewHeight)

{

    // â ũ�Ⱑ �ٲ� �� ���ο� â�� ũ�⸦ ����

    currentWidth = NewWidth;

    currentHeight = NewHeight;



    // ����Ʈ ����

    glViewport(0, 0, NewWidth, NewHeight);

    glLoadIdentity();



    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}



// ���콺 Ŭ�� �̺�Ʈ Call Back �Լ�

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)

{

    // ���콺�� ���ʹ�ư�� Ŭ���Ǿ��� ��

    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)

    {

        // Ŭ���� ���콺�� ��ġ�� X, Y ��ǥ�� ����

        myVertices[count][0] = X / currentWidth;
        myVertices[count][1] = (currentHeight - Y) / currentHeight;
        count++;          // ��ü ��ǥ�� ���� ����
        MyDisplay();       // ���콺�� Ŭ���� ������ �ٽ� �׷���

    }

}



int main(int argc, char** argv)

{

    Shape = POINT;



    // ���� ������ �ʱ�ȭ

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(currentWidth, currentHeight);

    glutInitWindowPosition(0, 0);

    glutCreateWindow("OpenGL�� �̿��� �����, ���׸���, �����׸��� By 2003721181 �̼���");

    glClearColor(1.0, 1.0, 1.0, 1.0);



    glMatrixMode(GL_PROJECTION);



    // Call Back �Լ� ���

    glutDisplayFunc(MyDisplay);

    glutReshapeFunc(MyReshape);

    glutMouseFunc(MyMouseClick);



    // �޴� Call Back �Լ��� ����ϰ� �� �޴��� Label�� ��ȣ�� �Ҵ�

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);

    glutAddMenuEntry("�� ���", 1);

    glutAddMenuEntry("�� �׸���", 2);

    glutAddMenuEntry("���� �׸���", 3);

    glutAddMenuEntry("���α׷� ����", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);



    glutMainLoop();



    return 0;

}