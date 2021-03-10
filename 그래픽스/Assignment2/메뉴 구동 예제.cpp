#include <GL/glut.h>   // gl.h glu.h glut.h 도 포함된 헤더파일



GLboolean IsSphere = true;  // true, false 값을 전역변수로 정함
GLboolean IsSmall = true;

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);  // 배경색을 프레임 버퍼로 초기화
    glColor3f(0.5, 0.0, 0.5);  // 3가지의 색을 쓸꺼다
    if ((IsSphere) && (IsSmall))  // 값이 같으면
        glutWireSphere(0.2, 15, 15);  // 이래 만들고
    else if ((IsSphere) && (!IsSmall))  // 작지 않으면
        glutWireSphere(0.4, 15, 15);  // 요래 만들고
    else if ((!IsSphere) && (IsSmall))  // 같지 않으면
        glutWireTorus(0.1, 0.3, 40, 20);  // 이리 만들고
    else glutWireTorus(0.2, 0.5, 40, 20);  // 그외는 이케 만들어라
    glFlush();  // 한꺼번에 출력
}

void MyMainMenu(int entryID) {   // 메인메뉴 만들 함수
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
    glutInitWindowSize(300, 300);    // 창 크기
    glutInitWindowPosition(0, 0);   // 창 오픈할 지점
    glutCreateWindow("OpenGL Example");    // 창 이름
    glClearColor(1.0, 1.0, 1.0, 1.0);    // 첫번째부터 R G B 색이고 마지막은 불투명도 조절 값
    glMatrixMode(GL_PROJECTION);  // 투상행력을 변환대상으로 설정
    glLoadIdentity();   // 이 행렬에 일단 항등행렬을 실으라는 명령
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // 좌 우 하 상 전 후 면의 위치값 저장

    //여기서 부터 메뉴를 만드는군
    GLint MySubMenuID = glutCreateMenu(MySubMenu); //create 메뉴를 통해 새로운 메뉴를 만든다. 괄호 안 파라미터는 해당 메뉴 클릭시 호출될 콜백함수
    glutAddMenuEntry("Small One", 1);  // 메뉴 형성 항목 나열하면 됨
    glutAddMenuEntry("Big One", 2);  // 메뉴
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);  // create메뉴로 새로운 메뉴 생성, 이번엔 메인메뉴를 콜백할 것이다.
    glutAddMenuEntry("Draw Sphere", 1);  // 메뉴
    glutAddMenuEntry("Draw Torus", 2);  // 메뉴
    glutAddSubMenu("Change size", MySubMenuID);
    glutAddMenuEntry("Exit", 3);  // 메뉴
    glutAttachMenu(GLUT_RIGHT_BUTTON);     // 오른쪽 마우스 클릭시 메뉴바 호출
    glutDisplayFunc(MyDisplay);   // MyDisplay 함수를 디스플레이 이벤트에 대한 콜백함수로 등록
    glutMainLoop();  // 계속 돌려야하니 무한루프
    return 0;
}