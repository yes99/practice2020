#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gl\freeglut.h"
#include <math.h>



typedef enum { POINT2, LINE, RECTANGLE, TRIANGLE, CIRCLE, POLYLINE }Paint;// �׸������������������ϴ�Enumerator

GLfloat windowWidth = 640.0;    // ������âũ�⸦�����ϴº���    
GLfloat windowHeight = 480.0;
GLfloat initWidth = 640.0;        // ó��âũ�⸦�����ϴº���
GLfloat initHeight = 480.0;
GLboolean isfull = false;        //ä����Ұ��ΰ������ϴº���
int LineWidth = 1;                //���β����ϴº���
GLfloat Rvalue = 0.0, Gvalue = 0.0, Bvalue = 0.0;//�÷���

class PaintTool {

public:
    PaintTool* next;    //�������
    int LineWidth;        //���β�
    GLboolean isfull;    //ä���
    GLfloat Rvalue, Gvalue, Bvalue;
    GLfloat vertex[4];        // �׷���������ġ�������ϴ¹迭
    Paint Shape;            //��������

public:
    PaintTool* getNext() { return next; }
    void OnPaint() {//��ü�׸����Լ�.
        int i;
        glColor3f(Rvalue, Gvalue, Bvalue);    //�÷��ͼ��β������ѵڱ׸���.
        glLineWidth(LineWidth);
        switch (Shape) {
        case RECTANGLE: // ��ü��Ÿ���̻簢���ϰ��׸���.
            if (!isfull) glBegin(GL_LINE_LOOP);
            else glBegin(GL_POLYGON);
            glVertex3f(vertex[0], vertex[1], 0.0);
            glVertex3f(vertex[0], vertex[3], 0.0);
            glVertex3f(vertex[2], vertex[3], 0.0);
            glVertex3f(vertex[2], vertex[1], 0.0);
            glEnd();
            break;

        case TRIANGLE:    //�ﰢ���ϰ��
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



PaintTool* head, * tail, * save;    //���Ḯ��Ʈ���������

Paint OnPaint_mode;                //��üŸ�Ժ���



void MyDisplay() {                //ó�����ͳ�������ӱ׷��ش�. ��带���鼭
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
    PaintTool* temp_object = head;
    while (temp_object != NULL) {
        temp_object->OnPaint(); // ��ü�׸���(�Ϲ����ΰ��)
        temp_object = temp_object->getNext();
    }
    glutSwapBuffers(); //���ҹ���.
}



void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {

    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {

        switch (OnPaint_mode) {

        case RECTANGLE://Ÿ���̻簢���ϰ�츶�콺down �̺�Ʈ.

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

        case TRIANGLE://Ÿ���̻簢���ϰ�츶�콺down �̺�Ʈ.

            if (save == NULL) {    //����ɼǰ����������Ѵ�.

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

            case RECTANGLE://Ÿ����Ÿ��,��,�簢���ϰ�츶�콺up �̺�Ʈ.

                if (save != NULL) {

                    save->vertex[2] = X / windowWidth;

                    save->vertex[3] = (windowHeight - Y) / windowHeight;

                    //��ǥ������

                    save = NULL;

                }

                break;

            }

        }

}

void MyMouseMove(GLint X, GLint Y) {    //move����ǥ�����������Ѵ�.

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



    PaintTool* erase;//Ž�����

    erase = head;//��������

    switch (KeyPressed) {

    case 'Q':

        exit(0); break;

    case 'q':

        exit(0); break;

    case 27:        //'ESC' ��������ü����

        head = 0;//������

        glutPostRedisplay(); //�����

        break;

    case '1':Rvalue = 1.0, Gvalue = 0.0, Bvalue = 0.0; break;    //RGB������

    case '2':Rvalue = 1.0, Gvalue = 0.5, Bvalue = 0.0; break;

    case '3':Rvalue = 1.0, Gvalue = 1.0, Bvalue = 0.0; break;

    case '4':Rvalue = 0.0, Gvalue = 1.0, Bvalue = 0.0; break;

    case '5':Rvalue = 0.0, Gvalue = 0.0, Bvalue = 1.0; break;

    case '6':Rvalue = 0.0, Gvalue = 0.0, Bvalue = 0.5; break;

    case '7':Rvalue = 0.25, Gvalue = 0.0, Bvalue = 0.5; break;

    case 'r':OnPaint_mode = RECTANGLE; break;            //�簢��

    case 'R':OnPaint_mode = RECTANGLE; break;

    case 'f':isfull = true; break;                        //ä����ϱ�

    case 'F':isfull = true; break;

    case 'e':isfull = false; break;                        //ä�����ϱ�

    case 'E':isfull = false; break;

    case 't':OnPaint_mode = TRIANGLE; break;                //�ﰢ��

    case 'T':OnPaint_mode = TRIANGLE; break;

    case '[':LineWidth += 3; break;                        //���β�����

    case ']':LineWidth -= 3; break;

    case VK_TAB:                                        //�ϳ��������

        while (erase->next != tail && tail != head) {

            erase = erase->next;

        }//����������������̵�

        tail = erase;

        erase->next = 0;//���������׸��ͻ���

        glutPostRedisplay(); //�ٽñ׸���

        break;

    }

}



int main(int argc, char** argv) {

    Rvalue = 0.0, Gvalue = 0.0, Bvalue = 0.0;

    OnPaint_mode = POINT2;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);    //������۸������

    glutInitWindowSize(windowWidth, windowHeight);            //�ʱ�â����

    glutInitWindowPosition(0, 0);                            //��������(��ǥ)

    glutCreateWindow("KAU computer engineering");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);                            //��ĺ�ȯ

    glLoadIdentity();

    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);                    //���ú��Ǽ���

    glutDisplayFunc(MyDisplay);                                //�ݹ��Լ���

    glutMouseFunc(MyMouseClick);

    glutMotionFunc(MyMouseMove);

    glutKeyboardFunc(MyKeyboard);

    glutMainLoop();                                            //���ѷ���

    return 0;

}