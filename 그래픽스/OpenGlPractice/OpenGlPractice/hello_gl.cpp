#include <stdio.h>
#include "GL\freeglut.h"

int Width = 800;
int Height = 600;

//윈도우의 렌더링을 담당하는 콜백 함수
void Render()
{
	//색상 버퍼를 지울 색을 지정한다
	glClearColor(1.0, 1.0, 0.0, 1.0); // 0 ~ 1.0

	//색상 버퍼를 지운다
	glClear(GL_COLOR_BUFFER_BIT);

	//렌더링 종료
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
	// freeglut 초기화 (무조건 똑같이...)
	glutInit(&argc, argv);


	//생성할 크기의 윈도우 지정
	glutInitWindowSize(Width, Height);


	// 윈도우의 디스플레이 모드를 RGB로 설정
	glutInitDisplayMode(GLUT_RGB);

	//윈도우를 생성
	glutCreateWindow("Hello GL?");

	//윈도우 화면이 바뀔 때, 자동으로 호출되는 콜백 함수 등록 
	glutDisplayFunc(Render);

	//윈도우의 크기가 변경될때, 자동으로 호출되는 콜백 함수
	glutReshapeFunc(Reshape);

	//키보드를 누를때, 자동으로 호출되는 콜백 함수 등록
	glutKeyboardFunc(Keyboard);

	//메시지 루프로 진입
	glutMainLoop();

	return 0;


}
