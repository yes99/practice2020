#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gl\freeglut.h"
#include <math.h>



#define NUMBER_OF_POINT        1000     // 그릴 수 있는 총 점의 갯수



enum __shape    // 그릴 도형의 종류를 지정하는 Enumerator

{

    GLPOINT = 1,

    LINE = 2,

    POLYGON = 3

}          Shape;



GLfloat myVertices[NUMBER_OF_POINT][2];            // 그려질 점의 위치를 저장하는 배열

GLfloat currentWidth = 640.0;      // 현재의 창 크기를 저장하는 변수

GLfloat currentHeight = 480.0;

GLfloat initWidth = 640.0;           // 처음 창 크기를 저장하는 변수

GLfloat initHeight = 480.0;



GLint count = 0;                                 // 전체 점의 갯수를 저장하는 변수



void MyDisplay()

{

    GLint index;



    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0); // 그려지는 객체의 색상, 여기서는 R 값만 1이므로 붉은색

    glPointSize(3.0f);  // 그려지는 점의 크기



    glEnableClientState(GL_VERTEX_ARRAY);     // 배열을 사용 가능하도록 함



    // myVertices 배열 안에 좌표가 하나라도 들어가 있다면

    if (count > 0)

    {

        switch (Shape)

        {

            // 점을 찍는다

        case POINT:

            for (index = 0; index < count; index++)

            {

                glBegin(GL_POINTS);

                glVertex2f(myVertices[index][0], myVertices[index][1]);

            }

            break;

            // 선을 그린다

        case LINE:

            glBegin(GL_LINE_STRIP);

            for (index = 0; index < count; index++)

            {

                glVertex2f(myVertices[index][0], myVertices[index][1]);

            }

            break;

            // 도형을 그린다

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



// 메뉴 이벤트 Call Back 함수

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







// 다시 그려주는 함수

void MyReshape(int NewWidth, int NewHeight)

{

    // 창 크기가 바뀔 때 새로운 창의 크기를 저장

    currentWidth = NewWidth;

    currentHeight = NewHeight;



    // 뷰포트 설정

    glViewport(0, 0, NewWidth, NewHeight);

    glLoadIdentity();



    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}



// 마우스 클릭 이벤트 Call Back 함수

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)

{

    // 마우스의 왼쪽버튼이 클릭되었을 때

    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)

    {

        // 클릭된 마우스의 위치를 X, Y 좌표로 저장

        myVertices[count][0] = X / currentWidth;
        myVertices[count][1] = (currentHeight - Y) / currentHeight;
        count++;          // 전체 좌표의 수를 증가
        MyDisplay();       // 마우스가 클릭될 때마다 다시 그려줌

    }

}



int main(int argc, char** argv)

{

    Shape = POINT;



    // 메인 윈도우 초기화

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(currentWidth, currentHeight);

    glutInitWindowPosition(0, 0);

    glutCreateWindow("OpenGL을 이용한 점찍기, 선그리기, 도형그리기 By 2003721181 이성우");

    glClearColor(1.0, 1.0, 1.0, 1.0);



    glMatrixMode(GL_PROJECTION);



    // Call Back 함수 등록

    glutDisplayFunc(MyDisplay);

    glutReshapeFunc(MyReshape);

    glutMouseFunc(MyMouseClick);



    // 메뉴 Call Back 함수를 등록하고 각 메뉴의 Label과 번호를 할당

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);

    glutAddMenuEntry("점 찍기", 1);

    glutAddMenuEntry("선 그리기", 2);

    glutAddMenuEntry("도형 그리기", 3);

    glutAddMenuEntry("프로그램 종료", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);



    glutMainLoop();



    return 0;

}