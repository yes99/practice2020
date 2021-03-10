
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include "gl\freeglut.h"
#include <math.h>
#define NULL 0 
#define LINE 1					// �� �׸���
#define RECTANGLE 2				// �簢�� �׸���
#define TRIANGLE  3				// �ﰢ�� �׸���
#define POINTS 4				// �� �׸���
#define TEXT 5					// ���� ����ϱ�
#define CIRCLE 6				// �� �׸���
#define DRAW 7					// �귯�� 
#define REMOVE 8				// ���찳
#define SPRAY 9					// ��������
#define STAR 10					// �� �׸���
#define HEART 11				// ��Ʈ �׸���



void mouse(int, int, int, int);		// ���콺 �ݹ��Լ�
void mouse2(int x, int y);			// ���콺 ��� �ݹ��Լ�
void key(unsigned char, int, int);		// Ű �ݹ��Լ�
void display(void);
void drawSquare(int, int);			// �� �׸���
void myReshape(GLsizei, GLsizei);

void myinit(void);

void screen_box(int, int, int);
void right_menu(int);
void middle_menu(int);
void color_menu(int);			// ���� ����
void pixel_menu(int);			// ũ�� ����
void fill_menu(int);
void alias_menu(int);			// ��Ƽ������� �޴�
void anti_alias(int);			// ��Ƽ�������
void bcolor_menu(int);			// ��� ����
void line_menu(int);			// �� ��� �޴�
void line_dotted(int);			// �� ��� ����
int pick(int, int);
void captureScreen();			// �̹��� ����
void loadImage();				// �̹��� �ε�
void random_color();			// ���� ����

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
		if (ran_check == 1)						// 1�̸� ���� ���� ����
			random_color();
		where = pick(x, y);
		line_dotted(line);						// �׸��� �Ӽ� ����
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
		case(LINE):                 // ���׸���
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
		case(RECTANGLE):                 // �簢�� �׸���
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
		case (TRIANGLE):                 // �ﰢ�� �׸���
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
		case(POINTS):                 // �� ���
		{
			drawSquare(x, y);
			count++;
		}
		break;
		case(TEXT):                  // ���� �Է��ϱ�
		{
			rx = x;
			ry = wh - y;
			glRasterPos2i(rx, ry);
			count = 0;
		}
		case(CIRCLE):				// ���׸���
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
				for (Angle = 0.0; Angle < 1800; Angle++) {                   // ����ǥ �̿�
					glVertex3f(((a / 2) * cos(Angle)) + (xp[0] + x) / 2, ((b / 2) * sin(Angle)) + wh - (yp[0] + y) / 2, 0.0);
				}
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		}
		case(STAR):						// �� �׸���
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
				for (Angle = 0.0; Angle < 3600; Angle++) {						// ����� ����ǥ ������ �̿�
					glVertex3f((a / 12) * (5 * cos(2 * Angle) + 2 * cos(3 * Angle)) + ((xp[0] + x) / 2),
						(b / 12) * (2 * sin(3 * Angle) - 5 * sin(2 * Angle)) + wh - (yp[0] + y) / 2, 0.0);

				}
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		}
		case(HEART):						 // ��Ʈ �׸���
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
				for (Angle = 0.0; Angle < 3600; Angle++) {						// ��Ʈ��� ����ǥ ������ �̿�
					glVertex3f((a / 25) * (12 * sin(Angle) - 4 * sin(3 * Angle)) + ((xp[0] + x) / 2),
						(b / 25) * (13 * cos(Angle) - 5 * cos(2 * Angle) - 2 * cos(3 * Angle) - cos(4 * Angle)) + wh - (yp[0] + y) / 2, 0.0);
				}
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		}
		case(REMOVE):                   // �߶󳻱�
			if (erase == 1)				// ������ 1�̸� ���찳, 0�̸� �߶󳻱�
				break;
			glColor3f(r2, g2, b2);
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{								// ��� �������� �簢�� �׷��� �߶󳻱� ȿ��
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

void mouse2(int x, int y) {               // �귯�� ���콺 �ݹ� �Լ�
	if (ran_check == 1)
		random_color();
	if (DRAW == draw_mode) {                // ��ο�	
		anti_alias(alias);
		glColor3f(r, g, b);
		y = wh - y;
		if (y < (wh - ww / 11) - size) {
			glBegin(GL_POLYGON);							// ���� �ݺ������� ����ǥ�� �����ν� ����
			for (int Angle = 0.0; Angle < 360; Angle++) {
				glVertex3f(size * cos(Angle) + x, size * sin(Angle) + y, 0.0);
			}
			glEnd();
			glFlush();
		}
	}
	else if (REMOVE == draw_mode && erase == 1)             // ���찳
	{
		anti_alias(alias);
		glColor3f(r2, g2, b2);
		y = wh - y;
		if (y < (wh - ww / 11) - size) {
			glBegin(GL_POLYGON);							// ���� ����, ���� �������� �����Ͽ� ���찳 ȿ��
			for (int Angle = 0.0; Angle < 360; Angle++) {
				glVertex3f(size * cos(Angle) + x, size * sin(Angle) + y, 0.0);
			}
			glEnd();
			glFlush();
		}
	}
	else if (SPRAY == draw_mode)             // ��������
	{
		anti_alias(alias);
		glColor3f(r, g, b);
		y = wh - y;
		if (y < (wh - ww / 11) - size) {
			glBegin(GL_POINTS);                    // ���׸��� �˰��򿡼� rand() �ɼ����� ����, ���� �׸� �� �������� ���� ����
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

void captureScreen() {								// ���� ���� �Լ�
	BITMAPFILEHEADER bmpfile; // ��Ʈ�� ���� ���
	BITMAPINFOHEADER bmpinfo; // ��Ʈ�� ���� ���
	GLubyte* pixels = new GLubyte[sizeof(GLubyte) * ww * (wh - ww / 11) * 3]; // ������ �ȼ� �޸� ����, ��ü ����(C++)
	FILE* file = fopen("capture.bmp", "wb");
	glReadPixels(0, 0, ww, (wh - ww / 11), GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);      // �ȼ� �б�

	memset(&bmpfile, 0, sizeof(bmpfile)); // bmpfile �޸𸮿� �����ϱ� ���� �ʱ�ȭ
	memset(&bmpinfo, 0, sizeof(bmpinfo)); // bmpinfo �޸𸮿� �����ϱ� ���� �ʱ�ȭ
	bmpfile.bfType = 'MB';
	bmpfile.bfSize = sizeof(bmpfile) + sizeof(bmpinfo) + ww * (wh - ww / 11) * 3;		// ���� ������
	bmpfile.bfOffBits = sizeof(bmpfile) + sizeof(bmpinfo);		// ���Ͽ��� ��Ʈ�� �����Ͱ� �ִ� ��ġ

	bmpinfo.biSize = sizeof(bmpinfo); // ����ü ũ��
	bmpinfo.biWidth = ww; // �̹��� ����
	bmpinfo.biHeight = (wh - ww / 11); // �̹��� ����
	bmpinfo.biPlanes = 1; // �÷��μ�
	bmpinfo.biBitCount = 24; // ��Ʈ�� 
	bmpinfo.biSizeImage = ww * (wh - ww / 11) * 3; // �̹�����ũ��

	fwrite(&bmpfile, sizeof(bmpfile), 1, file);
	fwrite(&bmpinfo, sizeof(bmpinfo), 1, file);
	fwrite(pixels, sizeof(unsigned char), (wh - ww / 11) * ww * 3, file);		// ����

	fclose(file);
	free(pixels);
}

void loadImage() {
	BITMAPFILEHEADER bmpfile; // ��Ʈ���������
	BITMAPINFOHEADER bmpinfo; // ��Ʈ���������
	FILE* fp = fopen("capture.bmp", "rb");
	if (fp == NULL) return;

	fread(&bmpfile, sizeof(BITMAPFILEHEADER), 1, fp); //���Ϸκ��� header�� BITMAPFILEHEADER ������ �����ϱ�
	fread(&bmpinfo, sizeof(BITMAPINFOHEADER), 1, fp); //���Ϸκ��� bmp�� BITMAPINFO ������ �����ϱ�

	DWORD bitsize = bmpinfo.biSizeImage; // bits�� ũ�� ����
	GLubyte* bits = new GLubyte[sizeof(GLubyte) * bitsize * 3];		// bits�� �޸� �Ҵ�, ��ü ���� (C++)
	fread(bits, 1, bitsize, fp); // bits�� �̹��� ���� �����ϱ�

	glEnableClientState(GL_VERTEX_ARRAY);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);       // ����
	glDrawPixels(ww, wh - ww / 11, GL_BGR_EXT, GL_UNSIGNED_BYTE, bits);		// ȭ�鿡 �Ѹ���
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

void alias_menu(int id)              // ��Ƽ������� �޴��κ��� �� ����
{
	alias = id;
}

void anti_alias(int id)              // ��Ƽ������� ����
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

void bcolor_menu(int id) {						// ���� ���� 
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

void line_dotted(int id) {			// �� ��� ����
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
	glBegin(GL_POINTS);											// �� �׸��� ����ǥ ������ �̿�
	for (int i = 0.0; i < 720; i++)
		glVertex3f(ww / 170 * (5 * cos(2 * i) + 2 * cos(3 * i)) + ww / 1.16,
			ww / 170 * (2 * sin(3 * i) - 5 * sin(2 * i)) + wh - ww / 22, 0.0);
	glEnd();
	glBegin(GL_POINTS);
	for (int i = 0.0; i < 720; i++) {							// ��Ʈ �׸��� ����ǥ ������ �̿�
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