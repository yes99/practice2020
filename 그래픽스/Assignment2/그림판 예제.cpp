#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gl\freeglut.h"
#include <math.h>



typedef enum { POINT2, LINE, RECTANGLE, TRIANGLE, CIRCLE, POLYLINE }Paint;// 그릴도형의종류를지정하는Enumerator

GLfloat windowWidth = 640.0;    // 현재의창크기를저장하는변수    
GLfloat windowHeight = 480.0;
GLfloat initWidth = 640.0;        // 처음창크기를저장하는변수
GLfloat initHeight = 480.0;
GLboolean isfull = false;        //채우기할것인가를정하는변수
int LineWidth = 1;                //선두께정하는변수
GLfloat Rvalue = 0.0, Gvalue = 0.0, Bvalue = 0.0;//컬러값

class PaintTool {

public:
    PaintTool* next;    //다음노드
    int LineWidth;        //선두께
    GLboolean isfull;    //채우기
    GLfloat Rvalue, Gvalue, Bvalue;
    GLfloat vertex[4];        // 그려질점의위치를저장하는배열
    Paint Shape;            //도형선택

public:
    PaintTool* getNext() { return next; }
    void OnPaint() {//객체그리기함수.
        int i;
        glColor3f(Rvalue, Gvalue, Bvalue);    //컬러와선두께를정한뒤그린다.
        glLineWidth(LineWidth);
        switch (Shape) {
        case RECTANGLE: // 객체의타입이사각형일경우그리기.
            if (!isfull) glBegin(GL_LINE_LOOP);
            else glBegin(GL_POLYGON);
            glVertex3f(vertex[0], vertex[1], 0.0);
            glVertex3f(vertex[0], vertex[3], 0.0);
            glVertex3f(vertex[2], vertex[3], 0.0);
            glVertex3f(vertex[2], vertex[1], 0.0);
            glEnd();
            break;

        case TRIANGLE:    //삼각형일경우
            if (!isfull) glBegin(GL_LINE_LOOP);
            else glBegin(GL_POLYGON);
            glVertex3f(vertex[0] + (vertex[2] - vertex[0]) / 2, vertex[1], 0.0);
            glVertex3f(vertex[0], vertex[3], 0.0);
            glVertex3f(vertex[2], vertex[3], 0.0);
            glEnd();
            break;
        }
    }
};



PaintTool* head, * tail, * save;    //연결리스트연결고리생성

Paint OnPaint_mode;                //객체타입변수



void MyDisplay() {                //처음부터끝까지계속그려준다. 노드를돌면서
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
    PaintTool* temp_object = head;
    while (temp_object != NULL) {
        temp_object->OnPaint(); // 물체그리기(일반적인경우)
        temp_object = temp_object->getNext();
    }
    glutSwapBuffers(); //스왑버퍼.
}



void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {

    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {

        switch (OnPaint_mode) {

        case RECTANGLE://타입이사각형일경우마우스down 이벤트.

            if (save == NULL) {

                save = new PaintTool();

                save->Rvalue = Rvalue; save->Gvalue = Gvalue; save->Bvalue = Bvalue;

                save->Shape = RECTANGLE;

                save->isfull = isfull;

                save->LineWidth = LineWidth;

                save->vertex[0] = X / windowWidth;

                save->vertex[1] = (windowHeight - Y) / windowHeight;

                save->next = NULL;

                if (tail != NULL)tail->next = save;

                tail = save;

                if (head == NULL)head = tail;

            }

            break;

        case TRIANGLE://타입이사각형일경우마우스down 이벤트.

            if (save == NULL) {    //현재옵션값들을저장한다.

                save = new PaintTool();

                save->Rvalue = Rvalue; save->Gvalue = Gvalue; save->Bvalue = Bvalue;

                save->Shape = TRIANGLE;

                save->isfull = isfull;

                save->LineWidth = LineWidth;

                save->vertex[0] = X / windowWidth;

                save->vertex[1] = (windowHeight - Y) / windowHeight;

                save->next = NULL;

                if (tail != NULL)tail->next = save;

                tail = save;

                if (head == NULL)head = tail;

            }

            break;

        default:;
        }
    }

    else

        //button up

        if (State == GLUT_UP) {

            switch (OnPaint_mode) {

            case TRIANGLE:

            case RECTANGLE://타입이타원,선,사각형일경우마우스up 이벤트.

                if (save != NULL) {

                    save->vertex[2] = X / windowWidth;

                    save->vertex[3] = (windowHeight - Y) / windowHeight;

                    //좌표값저장

                    save = NULL;

                }

                break;

            }

        }

}

void MyMouseMove(GLint X, GLint Y) {    //move시좌표값들을저장한다.

    if (save != NULL) {

        switch (OnPaint_mode) {

        case TRIANGLE:

        case RECTANGLE:

            save->vertex[2] = X / windowWidth;

            save->vertex[3] = (windowHeight - Y) / windowHeight;

            break;

        default:

            ;

        }

    }

    glutPostRedisplay();

}



void MyKeyboard(unsigned char KeyPressed, int X, int Y) {



    PaintTool* erase;//탐색노드

    erase = head;//시작지정

    switch (KeyPressed) {

    case 'Q':

        exit(0); break;

    case 'q':

        exit(0); break;

    case 27:        //'ESC' 누르면전체삭제

        head = 0;//노드삭제

        glutPostRedisplay(); //재출력

        break;

    case '1':Rvalue = 1.0, Gvalue = 0.0, Bvalue = 0.0; break;    //RGB값설정

    case '2':Rvalue = 1.0, Gvalue = 0.5, Bvalue = 0.0; break;

    case '3':Rvalue = 1.0, Gvalue = 1.0, Bvalue = 0.0; break;

    case '4':Rvalue = 0.0, Gvalue = 1.0, Bvalue = 0.0; break;

    case '5':Rvalue = 0.0, Gvalue = 0.0, Bvalue = 1.0; break;

    case '6':Rvalue = 0.0, Gvalue = 0.0, Bvalue = 0.5; break;

    case '7':Rvalue = 0.25, Gvalue = 0.0, Bvalue = 0.5; break;

    case 'r':OnPaint_mode = RECTANGLE; break;            //사각형

    case 'R':OnPaint_mode = RECTANGLE; break;

    case 'f':isfull = true; break;                        //채우기하기

    case 'F':isfull = true; break;

    case 'e':isfull = false; break;                        //채우기안하기

    case 'E':isfull = false; break;

    case 't':OnPaint_mode = TRIANGLE; break;                //삼각형

    case 'T':OnPaint_mode = TRIANGLE; break;

    case '[':LineWidth += 3; break;                        //선두께조절

    case ']':LineWidth -= 3; break;

    case VK_TAB:                                        //하나씩지우기

        while (erase->next != tail && tail != head) {

            erase = erase->next;

        }//마지막노드전으로이동

        tail = erase;

        erase->next = 0;//마지막에그린것삭제

        glutPostRedisplay(); //다시그리기

        break;

    }

}



int main(int argc, char** argv) {

    Rvalue = 0.0, Gvalue = 0.0, Bvalue = 0.0;

    OnPaint_mode = POINT2;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);    //더블버퍼를사용함

    glutInitWindowSize(windowWidth, windowHeight);            //초기창설정

    glutInitWindowPosition(0, 0);                            //시작지점(좌표)

    glutCreateWindow("KAU computer engineering");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);                            //행렬변환

    glLoadIdentity();

    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);                    //가시부피설정

    glutDisplayFunc(MyDisplay);                                //콜백함수들

    glutMouseFunc(MyMouseClick);

    glutMotionFunc(MyMouseMove);

    glutKeyboardFunc(MyKeyboard);

    glutMainLoop();                                            //무한루프

    return 0;

}