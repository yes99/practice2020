#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>

#define NULL 0 
#define LINE 1					// 선 그리기
#define RECTANGLE 2				// 사각형 그리기
#define TRIANGLE  3				// 삼각형 그리기
#define POINTS 4				// 점 그리기
#define TEXT 5					// 문자 출력하기
#define CIRCLE 6				// 원 그리기
#define DRAW 7					// 브러쉬 
#define REMOVE 8				// 지우개
#define SPRAY 9					// 스프레이
#define STAR 10					// 별 그리기
#define HEART 11				// 하트 그리기



void mouse(int, int, int, int);		// 마우스 콜백함수
void mouse2(int x, int y);			// 마우스 모션 콜백함수
void key(unsigned char, int, int);		// 키 콜백함수
void display(void);
void drawSquare(int, int);			// 점 그리기
void myReshape(GLsizei, GLsizei);

void myinit(void);

void screen_box(int, int, int);
void right_menu(int);
void middle_menu(int);
void color_menu(int);			// 색깔 선택
void pixel_menu(int);			// 크기 조정
void fill_menu(int);
void alias_menu(int);			// 안티엘리어싱 메뉴
void anti_alias(int);			// 안티엘리어싱
void bcolor_menu(int);			// 배경 선택
void line_menu(int);			// 선 모양 메뉴
void line_dotted(int);			// 선 모양 선택
int pick(int, int);
void captureScreen();			// 이미지 저장
void loadImage();				// 이미지 로드
void random_color();			// 랜덤 색상

/* globals */

GLsizei wh = 500, ww = 500; /* initial window size */
GLfloat size = 12.0;   /* half side length of square */
int draw_mode = 0; /* drawing mode */
int rx, ry; /*raster position*/
int alias = 0;
int line = 0;
int erase = 1;
int ran_check = 0;

GLfloat r = 1.0, g = 1.0, b = 1.0; /* drawing color */
GLfloat r2 = 0.8, g2 = 0.8, b2 = 0.8; /* Background color */
int fill = 0; /* fill flag */


void drawSquare(int x, int y)
{

	y = wh - y;
	glColor3ub((char)rand() % 256, (char)rand() % 256, (char)rand() % 256);
	glBegin(GL_POLYGON);
	glVertex2f(x + size, y + size);
	glVertex2f(x - size, y + size);
	glVertex2f(x - size, y - size);
	glVertex2f(x + size, y - size);
	glEnd();
}


/* rehaping routine called whenever window is resized
or moved */

void myReshape(GLsizei w, GLsizei h)
{

	/* adjust clipping box */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* adjust viewport and  clear */

	glViewport(0, 0, w, h);
	display();

	ww = w;
	wh = h;
}

void myinit(void)
{

	glViewport(0, 0, ww, wh);


	/* Pick 2D clipping window to match size of X window
	This choice avoids having to scale object coordinates
	each time window is resized */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)ww, 0.0, (GLdouble)wh, -1.0, 1.0);

	/* set clear color to black and clear window */



}

void mouse(int btn, int state, int x, int y)
{
	static int count;
	int where;
	static int xp[2], yp[2];
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		if (ran_check == 1)						// 1이면 랜덤 색상 적용
			random_color();
		where = pick(x, y);
		line_dotted(line);						// 그리기 속성 설정
		anti_alias(alias);
		glColor3f(r, g, b);
		glPointSize(size);
		glLineWidth(size);
		if (where != 0)
		{
			count = 0;
			draw_mode = where;
		}
		else switch (draw_mode)
		{
		case(LINE):                 // 선그리기
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				glBegin(GL_LINES);
				glVertex2i(x, wh - y);
				glVertex2i(xp[0], wh - yp[0]);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		case(RECTANGLE):                 // 사각형 그리기
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				if (fill) glBegin(GL_POLYGON);
				else glBegin(GL_LINE_LOOP);
				glVertex2i(x, wh - y);
				glVertex2i(x, wh - yp[0]);
				glVertex2i(xp[0], wh - yp[0]);
				glVertex2i(xp[0], wh - y);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		case (TRIANGLE):                 // 삼각형 그리기
			switch (count)
			{
			case(0):
				count++;
				xp[0] = x;
				yp[0] = y;
				break;
			case(1):
				count++;
				xp[1] = x;
				yp[1] = y;
				break;
			case(2):
				if (fill) glBegin(GL_POLYGON);
				else glBegin(GL_LINE_LOOP);
				glVertex2i(xp[0], wh - yp[0]);
				glVertex2i(xp[1], wh - yp[1]);
				glVertex2i(x, wh - y);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		case(POINTS):                 // 점 찍기
		{
			drawSquare(x, y);
			count++;
		}
		break;
		case(TEXT):                  // 문자 입력하기
		{
			rx = x;
			ry = wh - y;
			glRasterPos2i(rx, ry);
			count = 0;
		}
		case(CIRCLE):				// 원그리기
		{
			float a, b;
			float Angle;
			switch (count)
			{
			case (0):
				count++;
				xp[0] = x;
				yp[0] = y;
				break;
			case (1):
				a = abs(xp[0] - x);
				b = abs(yp[0] - y);
				if (fill) glBegin(GL_POLYGON);
				else glBegin(GL_POINTS);
				for (Angle = 0.0; Angle < 1800; Angle++) {                   // 극좌표 이용
					glVertex3f(((a / 2) * cos(Angle)) + (xp[0] + x) / 2, ((b / 2) * sin(Angle)) + wh - (yp[0] + y) / 2, 0.0);
				}
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		}
		case(STAR):						// 별 그리기
		{
			float a, b;
			float Angle;
			switch (count)
			{
			case (0):
				count++;
				xp[0] = x;
				yp[0] = y;
				break;
			case (1):
				a = abs(xp[0] - x);
				b = abs(yp[0] - y);
				if (fill) glBegin(GL_LINES);
				else glBegin(GL_POINTS);
				for (Angle = 0.0; Angle < 3600; Angle++) {						// 별모양 극좌표 방정식 이용
					glVertex3f((a / 12) * (5 * cos(2 * Angle) + 2 * cos(3 * Angle)) + ((xp[0] + x) / 2),
						(b / 12) * (2 * sin(3 * Angle) - 5 * sin(2 * Angle)) + wh - (yp[0] + y) / 2, 0.0);

				}
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		}
		case(HEART):						 // 하트 그리기
		{
			float a, b;
			float Angle;
			switch (count)
			{
			case (0):
				count++;
				xp[0] = x;
				yp[0] = y;
				break;
			case (1):
				a = abs(xp[0] - x);
				b = abs(yp[0] - y);
				if (fill) glBegin(GL_POLYGON);
				else glBegin(GL_POINTS);
				for (Angle = 0.0; Angle < 3600; Angle++) {						// 하트모양 극좌표 방정식 이용
					glVertex3f((a / 25) * (12 * sin(Angle) - 4 * sin(3 * Angle)) + ((xp[0] + x) / 2),
						(b / 25) * (13 * cos(Angle) - 5 * cos(2 * Angle) - 2 * cos(3 * Angle) - cos(4 * Angle)) + wh - (yp[0] + y) / 2, 0.0);
				}
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		}
		case(REMOVE):                   // 잘라내기
			if (erase == 1)				// 변수가 1이면 지우개, 0이면 잘라내기
				break;
			glColor3f(r2, g2, b2);
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{								// 배경 색상으로 사각형 그래서 잘라내기 효과
				glBegin(GL_POLYGON);
				glVertex2i(x, wh - y);
				glVertex2i(x, wh - yp[0]);
				glVertex2i(xp[0], wh - yp[0]);
				glVertex2i(xp[0], wh - y);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		}
		glPopAttrib();
		glFlush();
	}
}

void mouse2(int x, int y) {               // 브러쉬 마우스 콜백 함수
	if (ran_check == 1)
		random_color();
	if (DRAW == draw_mode) {                // 드로우	
		anti_alias(alias);
		glColor3f(r, g, b);
		y = wh - y;
		if (y < (wh - ww / 11) - size) {
			glBegin(GL_POLYGON);							// 원을 반복적으로 누적표현 함으로써 구현
			for (int Angle = 0.0; Angle < 360; Angle++) {
				glVertex3f(size * cos(Angle) + x, size * sin(Angle) + y, 0.0);
			}
			glEnd();
			glFlush();
		}
	}
	else if (REMOVE == draw_mode && erase == 1)             // 지우개
	{
		anti_alias(alias);
		glColor3f(r2, g2, b2);
		y = wh - y;
		if (y < (wh - ww / 11) - size) {
			glBegin(GL_POLYGON);							// 드루와 동일, 색상만 배경색으로 적용하여 지우개 효과
			for (int Angle = 0.0; Angle < 360; Angle++) {
				glVertex3f(size * cos(Angle) + x, size * sin(Angle) + y, 0.0);
			}
			glEnd();
			glFlush();
		}
	}
	else if (SPRAY == draw_mode)             // 스프레이
	{
		anti_alias(alias);
		glColor3f(r, g, b);
		y = wh - y;
		if (y < (wh - ww / 11) - size) {
			glBegin(GL_POINTS);                    // 원그리기 알고리즘에서 rand() 옵션으로 구현, 원을 그릴 때 무작위로 정점 선택
			for (int Angle = 0.0; Angle < 3 * size; Angle++) {
				glVertex3f(rand() % (int)(size + 1) * cos(Angle) + x, rand() % (int)(size + 1) * sin(Angle) + y, 0.0);
			}
			glEnd();
			glFlush();
		}
	}
}
int pick(int x, int y)
{
	y = wh - y;
	if (y < wh - ww / 11) return 0;
	else if (x < ww / 11) return LINE;
	else if (x < 2 * ww / 11) return RECTANGLE;
	else if (x < 3 * ww / 11) return TRIANGLE;
	else if (x < 4 * ww / 11) return POINTS;
	else if (x < 5 * ww / 11)  return TEXT;
	else if (x < 6 * ww / 11) return CIRCLE;
	else if (x < 7 * ww / 11) return DRAW;
	else if (x < 8 * ww / 11) return REMOVE;
	else if (x < 9 * ww / 11) return SPRAY;
	else if (x < 10 * ww / 11) return STAR;
	else if (x < ww) return HEART;
}

void screen_box(int x, int y, int s)
{
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + s, y);
	glVertex2i(x + s, y + s);
	glVertex2i(x, y + s);
	glEnd();
}

void right_menu(int id)
{
	if (id == 1) exit(1);
	else if (id == 2) display();
	else if (id == 3)
		captureScreen();
	else
		loadImage();
}

void captureScreen() {								// 파일 저장 함수
	BITMAPFILEHEADER bmpfile; // 비트맵 파일 헤더
	BITMAPINFOHEADER bmpinfo; // 비트맵 정보 헤더
	GLubyte* pixels = new GLubyte[sizeof(GLubyte) * ww * (wh - ww / 11) * 3]; // 저장할 픽셀 메모리 변수, 객체 생성(C++)
	FILE* file = fopen("capture.bmp", "wb");
	glReadPixels(0, 0, ww, (wh - ww / 11), GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);      // 픽셀 읽기

	memset(&bmpfile, 0, sizeof(bmpfile)); // bmpfile 메모리에 저장하기 위해 초기화
	memset(&bmpinfo, 0, sizeof(bmpinfo)); // bmpinfo 메모리에 저장하기 위해 초기화
	bmpfile.bfType = 'MB';
	bmpfile.bfSize = sizeof(bmpfile) + sizeof(bmpinfo) + ww * (wh - ww / 11) * 3;		// 버퍼 사이즈
	bmpfile.bfOffBits = sizeof(bmpfile) + sizeof(bmpinfo);		// 파일에서 비트맵 데이터가 있는 위치

	bmpinfo.biSize = sizeof(bmpinfo); // 구조체 크기
	bmpinfo.biWidth = ww; // 이미지 가로
	bmpinfo.biHeight = (wh - ww / 11); // 이미지 세로
	bmpinfo.biPlanes = 1; // 플레인수
	bmpinfo.biBitCount = 24; // 비트수 
	bmpinfo.biSizeImage = ww * (wh - ww / 11) * 3; // 이미지의크기

	fwrite(&bmpfile, sizeof(bmpfile), 1, file);
	fwrite(&bmpinfo, sizeof(bmpinfo), 1, file);
	fwrite(pixels, sizeof(unsigned char), (wh - ww / 11) * ww * 3, file);		// 저장

	fclose(file);
	free(pixels);
}

void loadImage() {
	BITMAPFILEHEADER bmpfile; // 비트맵파일헤더
	BITMAPINFOHEADER bmpinfo; // 비트맵정보헤더
	FILE* fp = fopen("capture.bmp", "rb");
	if (fp == NULL) return;

	fread(&bmpfile, sizeof(BITMAPFILEHEADER), 1, fp); //파일로부터 header로 BITMAPFILEHEADER 데이터 저장하기
	fread(&bmpinfo, sizeof(BITMAPINFOHEADER), 1, fp); //파일로부터 bmp로 BITMAPINFO 데이터 저장하기

	DWORD bitsize = bmpinfo.biSizeImage; // bits의 크기 지정
	GLubyte* bits = new GLubyte[sizeof(GLubyte) * bitsize * 3];		// bits에 메모리 할당, 객체 생성 (C++)
	fread(bits, 1, bitsize, fp); // bits에 이미지 정보 저장하기

	glEnableClientState(GL_VERTEX_ARRAY);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);       // 포맷
	glDrawPixels(ww, wh - ww / 11, GL_BGR_EXT, GL_UNSIGNED_BYTE, bits);		// 화면에 뿌리기
	glFlush();
	fclose(fp);
}

void middle_menu(int id)
{

}

void color_menu(int id)
{
	ran_check = 0;
	if (id == 1) { r = 1.0; g = 0.0; b = 0.0; }
	else if (id == 2) { r = 0.0; g = 1.0; b = 0.0; }
	else if (id == 3) { r = 0.0; g = 0.0; b = 1.0; }
	else if (id == 4) { r = 0.0; g = 1.0; b = 1.0; }
	else if (id == 5) { r = 1.0; g = 0.0; b = 1.0; }
	else if (id == 6) { r = 1.0; g = 1.0; b = 0.0; }
	else if (id == 7) { r = 1.0; g = 1.0; b = 1.0; }
	else if (id == 8) { r = 0.0; g = 0.0; b = 0.0; }
	else {
		ran_check = 1;
	}

}

void random_color() {
	r = (float)(rand() % 256) / 255;
	g = (float)(rand() % 256) / 255;
	b = (float)(rand() % 256) / 255;
}

void pixel_menu(int id)
{
	if (id == 1) size = 2 * size;
	else if (size > 1) size = size / 2;
}

void alias_menu(int id)              // 안티엘리어싱 메뉴로부터 값 전달
{
	alias = id;
}

void anti_alias(int id)              // 안티엘리어싱 적용
{
	if (id == 1) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);

	}
	else {
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POLYGON_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
	}
}

void bcolor_menu(int id) {						// 배경색 설정 
	if (id == 1) { r2 = 1.0; g2 = 0.0; b2 = 0.0; }
	else if (id == 2) { r2 = 0.0; g2 = 1.0; b2 = 0.0; }
	else if (id == 3) { r2 = 0.0; g2 = 0.0; b2 = 1.0; }
	else if (id == 4) { r2 = 0.0; g2 = 1.0; b2 = 1.0; }
	else if (id == 5) { r2 = 1.0; g2 = 0.0; b2 = 1.0; }
	else if (id == 6) { r2 = 1.0; g2 = 1.0; b2 = 0.0; }
	else if (id == 7) { r2 = 1.0; g2 = 1.0; b2 = 1.0; }
	else if (id == 8) { r2 = 0.0; g2 = 0.0; b2 = 0.0; }
	else if (id == 9) { r2 = 0.8; g2 = 0.8; b2 = 0.8; }
	else {
		r2 = (float)(rand() % 256) / 255;
		g2 = (float)(rand() % 256) / 255;
		b2 = (float)(rand() % 256) / 255;
	}
	display();
}

void line_dotted(int id) {			// 선 모양 설정
	if (id == 1) {
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 0xAAAA);
	}
	else if (id == 2) {
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(2, 0xAAAA);
	}
	else if (id == 3) {
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(3, 0xAAAA);
	}
	else if (id == 4) {
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(4, 0xAAAA);
	}
	else if (id == 5) {
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 0x00FF);
	}
	else if (id == 6) {
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(2, 0x00FF);
	}
	else
		glDisable(GL_LINE_STIPPLE);
}

void line_menu(int id)
{
	line = id;
}

void erase_menu(int id)
{
	erase = id;
}

void fill_menu(int id)
{
	if (id == 1) fill = 1;
	else fill = 0;
}

void key(unsigned char k, int xx, int yy)
{
	if (draw_mode != TEXT) return;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(rx, ry);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, k);
	/*glutStrokeCharacter(GLUT_STROKE_ROMAN,i); */
	rx += glutBitmapWidth(GLUT_BITMAP_9_BY_15, k);

}

void display(void)
{
	int shift = 0;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glClearColor(r2, g2, b2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	screen_box(0, wh - ww / 11, ww / 11);
	glColor3f(1.0, 0.0, 0.0);
	screen_box(ww / 11, wh - ww / 11, ww / 11);
	glColor3f(0.0, 1.0, 0.0);
	screen_box(2 * ww / 11, wh - ww / 11, ww / 11);
	glColor3f(0.0, 0.0, 1.0);
	screen_box(3 * ww / 11, wh - ww / 11, ww / 11);
	glColor3f(1.0, 1.0, 0.0);
	screen_box(4 * ww / 11, wh - ww / 11, ww / 11);
	glColor3f(1.0, 0.2, 0.5);
	screen_box(5 * ww / 11, wh - ww / 11, ww / 11);
	glColor3f(0.0, 0.6, 0.1);
	screen_box(6 * ww / 11, wh - ww / 11, ww / 11);
	glColor3f(0.5, 0.1, 0.1);
	screen_box(7 * ww / 11, wh - ww / 11, ww / 11);
	glColor3f(0.8, 0.3, 0.7);
	screen_box(8 * ww / 11, wh - ww / 11, ww / 11);
	glColor3f(0.1, 0.7, 0.6);
	screen_box(9 * ww / 11, wh - ww / 11, ww / 11);
	glColor3f(1.0, 0.5, 0.8);
	screen_box(10 * ww / 11, wh - ww / 11, ww / 11);
	glColor3f(0.0, 0.0, 0.0);
	screen_box(ww / 9.5, wh - ww / 13.8, ww / 16);

	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2i(ww / 80, wh - ww / 22);
	glVertex2i(ww / 13, wh - ww / 22);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2i(ww / 5.2, wh - ww / 11 + ww / 40);
	glVertex2i(ww / 4.4, wh - ww / 50);
	glVertex2i(ww / 3.8, wh - ww / 11 + ww / 40);
	glEnd();
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glVertex2i(3 * ww / 11 + ww / 22, wh - ww / 22);
	glEnd();
	glPointSize(5.0);
	glBegin(GL_POINTS);
	for (int i = 0.0; i < 360; i++)
		glVertex3f(ww / 27 * cos(i) + ww / 2, ww / 27 * sin(i) + wh - ww / 22, 0.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(ww / 1.78, wh - ww / 70);
	glVertex2i(ww / 1.62, wh - ww / 13);
	glEnd();
	glPointSize(16.0);
	glBegin(GL_POINTS);
	glVertex2i(ww / 1.62, wh - ww / 13);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(ww / 1.54, wh - ww / 70);
	glVertex2i(ww / 1.4, wh - ww / 13);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(ww / 1.4, wh - ww / 70);
	glVertex2i(ww / 1.54, wh - ww / 13);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(ww / 1.345, wh - ww / 70);
	glVertex2i(ww / 1.255, wh - ww / 13);
	glEnd();
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2i(ww / 1.235, wh - ww / 13);
	glVertex2i(ww / 1.245, wh - ww / 13);
	glVertex2i(ww / 1.255, wh - ww / 13);
	glVertex2i(ww / 1.265, wh - ww / 13);
	glVertex2i(ww / 1.275, wh - ww / 13);
	glEnd();
	glBegin(GL_POINTS);											// 별 그리기 극좌표 방정식 이용
	for (int i = 0.0; i < 720; i++)
		glVertex3f(ww / 170 * (5 * cos(2 * i) + 2 * cos(3 * i)) + ww / 1.16,
			ww / 170 * (2 * sin(3 * i) - 5 * sin(2 * i)) + wh - ww / 22, 0.0);
	glEnd();
	glBegin(GL_POINTS);
	for (int i = 0.0; i < 720; i++) {							// 하트 그리기 극좌표 방정식 이용
		glVertex3f((ww / 400) * (12 * sin(i) - 4 * sin(3 * i)) + ww / 1.048,
			(ww / 400) * (13 * cos(i) - 5 * cos(2 * i) - 2 * cos(3 * i) - cos(4 * i)) + wh - ww / 25, 0.0);
	}
	glEnd();
	glRasterPos2i(2.0 * ww / 5, wh - ww / 22);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	shift = glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');
	glRasterPos2i(2.0 * ww / 5 + shift, wh - ww / 22);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');
	glRasterPos2i(2.0 * ww / 5 + shift, wh - ww / 22);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glFlush();
	glPopAttrib();
}


int main(int argc, char** argv)
{
	int c_menu, p_menu, f_menu, a_menu, b_menu, l_menu, e_menu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1600, 900);
	glutCreateWindow("My Drawing Board");
	glutDisplayFunc(display);
	c_menu = glutCreateMenu(color_menu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Cyan", 4);
	glutAddMenuEntry("Magenta", 5);
	glutAddMenuEntry("Yellow", 6);
	glutAddMenuEntry("White", 7);
	glutAddMenuEntry("Black", 8);
	glutAddMenuEntry("Random Color", 9);
	p_menu = glutCreateMenu(pixel_menu);
	glutAddMenuEntry("increase pixel size", 1);
	glutAddMenuEntry("decrease pixel size", 2);
	a_menu = glutCreateMenu(alias_menu);
	glutAddMenuEntry("anti aliasing ON", 1);
	glutAddMenuEntry("anti aliasing OFF", 2);
	f_menu = glutCreateMenu(fill_menu);
	glutAddMenuEntry("fill on", 1);
	glutAddMenuEntry("fill off", 2);
	b_menu = glutCreateMenu(bcolor_menu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Cyan", 4);
	glutAddMenuEntry("Magenta", 5);
	glutAddMenuEntry("Yellow", 6);
	glutAddMenuEntry("White", 7);
	glutAddMenuEntry("Black", 8);
	glutAddMenuEntry("Default", 9);
	glutAddMenuEntry("Random Color", 10);
	l_menu = glutCreateMenu(line_menu);
	glutAddMenuEntry("Dotted Line 1", 1);
	glutAddMenuEntry("Dotted Line 2", 2);
	glutAddMenuEntry("Dotted Line 3", 3);
	glutAddMenuEntry("Dotted Line 4", 4);
	glutAddMenuEntry("Dotted Line 5", 5);
	glutAddMenuEntry("Dotted Line 6", 6);
	glutAddMenuEntry("Full Line", 7);
	e_menu = glutCreateMenu(erase_menu);
	glutAddMenuEntry("Eraser", 1);
	glutAddMenuEntry("Crop", 2);
	glutCreateMenu(right_menu);
	glutAddMenuEntry("quit", 1);
	glutAddMenuEntry("clear", 2);
	glutAddMenuEntry("save", 3);
	glutAddMenuEntry("load", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutCreateMenu(middle_menu);
	glutAddSubMenu("Colors", c_menu);
	glutAddSubMenu("Pixel Size", p_menu);
	glutAddSubMenu("Anti Aliasing", a_menu);
	glutAddSubMenu("Fill", f_menu);
	glutAddSubMenu("Background Color", b_menu);
	glutAddSubMenu("Line", l_menu);
	glutAddSubMenu("Erase Type", e_menu);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	myinit();
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse2);
	glutMainLoop();


}