#include <GL/glut.h>   // gl.h glu.h glut.h �� ���Ե� �������



GLboolean IsSphere = true;  // true, false ���� ���������� ����
GLboolean IsSmall = true;

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);  // ������ ������ ���۷� �ʱ�ȭ
    glColor3f(0.5, 0.0, 0.5);  // 3������ ���� ������
    if ((IsSphere) && (IsSmall))  // ���� ������
        glutWireSphere(0.2, 15, 15);  // �̷� �����
    else if ((IsSphere) && (!IsSmall))  // ���� ������
        glutWireSphere(0.4, 15, 15);  // �䷡ �����
    else if ((!IsSphere) && (IsSmall))  // ���� ������
        glutWireTorus(0.1, 0.3, 40, 20);  // �̸� �����
    else glutWireTorus(0.2, 0.5, 40, 20);  // �׿ܴ� ���� ������
    glFlush();  // �Ѳ����� ���
}

void MyMainMenu(int entryID) {   // ���θ޴� ���� �Լ�
    if (entryID == 1)
        IsSphere = true;
    else if (entryID == 2)
        IsSphere = false;
    else if (entryID == 3)
        exit(0);
    glutPostRedisplay();
}


void MySubMenu(int entryID) {
    if (entryID == 1)
        IsSmall = true;
    else if (entryID == 2)
        IsSmall = false;
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);    // â ũ��
    glutInitWindowPosition(0, 0);   // â ������ ����
    glutCreateWindow("OpenGL Example");    // â �̸�
    glClearColor(1.0, 1.0, 1.0, 1.0);    // ù��°���� R G B ���̰� �������� ������ ���� ��
    glMatrixMode(GL_PROJECTION);  // ��������� ��ȯ������� ����
    glLoadIdentity();   // �� ��Ŀ� �ϴ� �׵������ ������� ���
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // �� �� �� �� �� �� ���� ��ġ�� ����

    //���⼭ ���� �޴��� ����±�
    GLint MySubMenuID = glutCreateMenu(MySubMenu); //create �޴��� ���� ���ο� �޴��� �����. ��ȣ �� �Ķ���ʹ� �ش� �޴� Ŭ���� ȣ��� �ݹ��Լ�
    glutAddMenuEntry("Small One", 1);  // �޴� ���� �׸� �����ϸ� ��
    glutAddMenuEntry("Big One", 2);  // �޴�
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);  // create�޴��� ���ο� �޴� ����, �̹��� ���θ޴��� �ݹ��� ���̴�.
    glutAddMenuEntry("Draw Sphere", 1);  // �޴�
    glutAddMenuEntry("Draw Torus", 2);  // �޴�
    glutAddSubMenu("Change size", MySubMenuID);
    glutAddMenuEntry("Exit", 3);  // �޴�
    glutAttachMenu(GLUT_RIGHT_BUTTON);     // ������ ���콺 Ŭ���� �޴��� ȣ��
    glutDisplayFunc(MyDisplay);   // MyDisplay �Լ��� ���÷��� �̺�Ʈ�� ���� �ݹ��Լ��� ���
    glutMainLoop();  // ��� �������ϴ� ���ѷ���
    return 0;
}