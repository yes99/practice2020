#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "gl\freeglut.h"

int Width = 800, Height = 800;

// 장면 조작을 위한 변수들
int ManipulateMode = 0; // 1: 회전, 2: 이동
int StartPt[2];
float Axis[3] = {1.0, 0.0, 0.0};
float Angle = 0.0;
float RotMat[16] = {1, 0, 0, 0, 
					0, 1, 0, 0, 
					0, 0, 1, 0, 
					0, 0, 0, 1};
float Zoom = -30.0;
float Pan[3] = { 0.0, 0.0, 0.0 };

// 콜백 함수들
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void MouseWheel(int button, int dir, int x, int y);
void Render();

// 사용자 정의 함수들
void GetSphereCoord(int x, int y, float *px, float *py, float *pz);
void RenderFloor();

int main(int argc, char **argv)
{
	// GLUT 초기화(더블 칼라버퍼 사용)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 

	// 윈도우 생성
	glutInitWindowSize(Width, Height);
	glutCreateWindow("3DViewer");
	
	// 콜백함수 등록
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMouseWheelFunc(MouseWheel);
	glutDisplayFunc(Render);
		
	// 메시지 루프 진입
	glutMainLoop();
	return 0;
}

void Reshape(int w, int h)
{
	// 뷰포트 변환
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}

void SetupViewTransform()
{
	// 모델 뷰 행렬을 단위 행렬로 초기화, M = I
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

	// 줌 인/아웃을 위한 변환, M = I * T_zoom
	glTranslatef(0.0, 0.0, Zoom);

	// 새로운 회전을 적용, M = I * T_zoom * R_new
	glRotatef(Angle, Axis[0], Axis[1], Axis[2]);

	// 기존 회전을 적용, M = I * T_zoom * R_new * R_old
	glMultMatrixf(RotMat);

	// 이동 변환을 적용, M = I * T_zoom * R_new * R_old * T_pan
	glTranslatef(Pan[0], Pan[1], Pan[2]);

	// 회전 행렬 추출, R_old = R_new * R_old
	glGetFloatv(GL_MODELVIEW_MATRIX, RotMat);
	RotMat[12] = RotMat[13] = RotMat[14] = 0.0;
}

void SetupViewVolume()
{
	// 관측 공간 지정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)Width/(double)Height, 1.0, 10000.0);
}

void Render()
{
	// 색상 버퍼 초기화
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	// 관측공간 지정
	SetupViewVolume();

	// 관측변환 설정
	SetupViewTransform();	

	// 장면 렌더링
	glMatrixMode(GL_MODELVIEW);
	RenderFloor();
	glutWireTeapot(2.0);

	// 더블 버퍼링을 위한 버퍼 교환
	glutSwapBuffers();
}

void RenderFloor()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	for (float x = -10.0; x <= 10.0; x += 1.0)
	{
		glBegin(GL_LINES);
		glVertex3f(x, 0.0, -10.0f);
		glVertex3f(x, 0.0, 10.0f);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(-10.0f, 0.0, x);
		glVertex3f(10.0f, 0.0, x);
		glEnd();
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		StartPt[0] = x; StartPt[1] = y;
		if (button == GLUT_LEFT_BUTTON)
			ManipulateMode = 1;	// 회전

		if (button == GLUT_RIGHT_BUTTON)
			ManipulateMode = 2;	// 이동
	}
	if (state == GLUT_UP)		
	{	
		ManipulateMode = 0;	// 리셋
		StartPt[0] = StartPt[1] = 0;
		Angle = 0.0;
	}
}

void Motion(int x, int y)
{
	// 회전축과 회전 각도 계산
	if (ManipulateMode == 1)
	{	
		// 단위 구 위의 좌표 계산
		float px, py, pz, qx, qy, qz;
		GetSphereCoord(StartPt[0], StartPt[1], &px, &py, &pz);
		GetSphereCoord(x, y, &qx, &qy, &qz);

		// 회전 축과 각도 계산
		Axis[0] = py*qz-pz*qy; Axis[1] = pz*qx-px*qz; Axis[2] = px*qy-py*qx;
		Angle = 0.0;
		float len = Axis[0] * Axis[0] + Axis[1] * Axis[1] + Axis[2] * Axis[2];
		if (len > 0.0001) // 일정 변위 이상만 처리
			Angle = acos(px * qx + py * qy + pz * qz) * 180.0f / 3.141592f;
	}

	// 이동 변위 계산
	if (ManipulateMode == 2)
	{
		float dx = (float)(x - StartPt[0]) * 0.01f;
		float dy = (float)(StartPt[1] - y) * 0.01f;
		// 회전 행렬 및 역행렬
		// R = 0 4 8   invR = 0 1 2
		//     1 5 9          4 5 6    
		//     2 6 10         8 9 10		
		Pan[0] += RotMat[0] * dx + RotMat[1] * dy;
		Pan[1] += RotMat[4] * dx + RotMat[5] * dy;
		Pan[2] += RotMat[8] * dx + RotMat[9] * dy;
	}
	
	StartPt[0] = x;	// Update startpt as current position
	StartPt[1] = y;
	glutPostRedisplay();
}

/*!
*	\brief 마우스 스크롤을 처리하는 콜백 함수
*
*	\param button[in]	마우스 버튼 정보(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
*	\param dir[in]		스크롤의 방향
*	\param x[in]		좌측 상단을 (0, 0) 기준으로 마우스 포인터의 가로 위치
*	\param y[in]		좌측 상단을 (0, 0) 기준으로 마우스 포인터의 세로 위치
*/
void MouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
		Zoom += 1.0;
	else
		Zoom -= 1.0;
	glutPostRedisplay();
}

void GetSphereCoord(int x, int y, float *px, float *py, float *pz)
{
	*px = (2.0f * x - Width) / Width;
	*py = (-2.0f * y + Height) / Height;

	float r = (*px) * (*px) + (*py) * (*py);
	if (r >= 1.0f)
	{
		*px = *px / sqrt(r);
		*py = *py / sqrt(r);
		*pz = 0.0f;
	}
	else
		*pz = sqrt(1.0f - r);
}
