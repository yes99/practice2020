#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <gl\freeglut.h>

int ManipulateMode = 0;
int Width = 800, Height = 800;
double angle = 0.0;
int opt = 1;
int state = 0;

// 관측변환을 위한 변수
int StartPt[2];

// ROTATE를 위한 변수
float Axis[3] = { 1.0, 0.0, 0.0 };
float Angle = 0.0;
float RotMat[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

// PAN 을 위한 변수
float dT[3] = { 0.0, 0.0, -32.0 };

// Declaration of call back functions
void Render();
void Reshape(int w, int h);
void InitOpenGL();
void DrawAxis(float len);
void DrawAxis2(float len);
void DrawVC();
void DrawWC();
void DrawMC();
void DrawVV(int opt);
void DrawNC();
void DrawDC();
void BitmapString(float x, float y, float z, char *str, float r, float g, float b);
void StrokeString(char *str, float r, float g, float b);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void MouseMove(int x, int y);
void GetSphereCoord(int x, int y, float *px, float *py, float *pz);

int main(int argc, char **argv)
{
	// Initialize OpenGL.
	glutInit(&argc, argv);

	// Initialize window size and its position when it is created.
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);

	// Initialize OpenGL display modes for double buffering, RGB color, depth buffer enabling.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create OpenGL window.
	glutCreateWindow("A SimpleGL Program");

	// Register call back functions.
	InitOpenGL();
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);

	// Enter the message loop.
	glutMainLoop();
	return 0;
}


void Reshape(int w, int h)
{
	// View-port transformation
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}


void SetupViewTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 월드좌표계 회전
	glTranslatef(dT[0], dT[1], dT[2]);

	glRotatef(Angle, Axis[0], Axis[1], Axis[2]);
	glMultMatrixf(RotMat);

	glGetFloatv(GL_MODELVIEW_MATRIX, RotMat);
	RotMat[12] = RotMat[13] = RotMat[14] = 0.0;
}


void PrintGLMatrix(GLenum pname)
{
	float m[16];
	glGetFloatv(pname, m);

	printf("|%7.1f%7.1f%7.1f%7.1f|\n", m[0], m[4], m[8], m[12]);
	printf("|%7.1f%7.1f%7.1f%7.1f|\n", m[1], m[5], m[9], m[13]);
	printf("|%7.1f%7.1f%7.1f%7.1f|\n", m[2], m[6], m[10], m[14]);
	printf("|%7.1f%7.1f%7.1f%7.1f|\n\n", m[3], m[7], m[11], m[15]);
}

void SetupViewVolume()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)Width / (double)Height, 1.0, 100000.0);
	//glOrtho(-15.0, 15.0, -15.0, 15.0, -100.0, 100.0);
	//PrintGLMatrix(GL_PROJECTION_MATRIX);
}

void DrawTriangle()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0, 0.0, 0.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0, 1.0, 0.0);
	glEnd();
}

void DrawAxis(float len)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(len, 0.0, 0.0);
	glVertex3f(len, len / 5, -len / 5);
	glVertex3f(len, -len / 5, len / 5);
	glVertex3f(len, len / 5, len / 5);
	glVertex3f(len, -len / 5, -len / 5);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, len, 0.0);
	glVertex3f(-len / 5, len, -len / 5);
	glVertex3f(0.0, len, 0.0);
	glVertex3f(len / 5, len, -len / 5);
	glVertex3f(0.0, len, 0.0);
	glVertex3f(0.0, len, 0.0);
	glVertex3f(0.0, len, len / 5);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, len);
	glVertex3f(len / 5, len / 5, len);
	glVertex3f(-len / 5, -len / 5, len);
	glVertex3f(-len / 5, len / 5, len);
	glVertex3f(len / 5, len / 5, len);
	glVertex3f(-len / 5, -len / 5, len);
	glVertex3f(len / 5, -len / 5, len);
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void DrawAxis2(float len)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(len, 0.0, 0.0);
	glVertex3f(len, len / 5, -len / 5);
	glVertex3f(len, -len / 5, len / 5);
	glVertex3f(len, len / 5, len / 5);
	glVertex3f(len, -len / 5, -len / 5);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, len, 0.0);
	glVertex3f(-len / 5, len, -len / 5);
	glVertex3f(0.0, len, 0.0);
	glVertex3f(len / 5, len, -len / 5);
	glVertex3f(0.0, len, 0.0);
	glVertex3f(0.0, len, 0.0);
	glVertex3f(0.0, len, len / 5);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, -len);
	glVertex3f(-len / 5, len / 5, -len);
	glVertex3f(len / 5, -len / 5, -len);
	glVertex3f(-len / 5, len / 5, -len);
	glVertex3f(len / 5, len / 5, -len);
	glVertex3f(-len / 5, -len / 5, -len);
	glVertex3f(len / 5, -len / 5, -len);
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void Render()
{
	// Clear color buffer with specified clear color (R, G, B, A)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up view transformation
	SetupViewTransform();

	// Set up viewing volume and choose camera lens
	SetupViewVolume();

	glMatrixMode(GL_MODELVIEW);
	if (state > 0 && state < 5)
		DrawVC();

	if (state > 1 && state < 5)
		DrawWC();

	if (state > 2 && state < 5)
		DrawMC();

	if (state > 3 && state < 5)
		DrawVV(opt);

	if (state == 5)
		DrawNC();

	if (state == 6)
		DrawDC();

	// Swap buffers for double buffering.
	glutSwapBuffers();
}


void InitOpenGL()
{
	GLfloat light_specular0[] = { 0.8f, 0.8f, 0.8f };
	GLfloat light_position0[] = { 0.0f, 0.0f, 10000.0f, 0.0f };
	GLfloat light_ambient0[] = { 0.5f, 0.5f, 0.5f };
	GLfloat light_diffuse0[] = { 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_CULL_FACE);	
}

void DrawVC()
{
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, 0.0f);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	BitmapString(0, -3, 1, "{VC}", 1.0, 0.0, 0.0);

	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -2.0f, -0.5f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -2.0f, -0.5f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -2.0f, 0.5f);
	glEnd();
	glEnable(GL_LIGHTING);

	glPushMatrix();
	glScaled(2.0, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	DrawAxis(2.0);
	glPopMatrix();
}

void DrawWC()
{
	glPushMatrix();
	glTranslatef(5.0, 0.0, 0.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	BitmapString(0, -1.5, 1, "{WC}", 1.0, 0.0, 0.0);
	DrawAxis(2.0);
	glPopMatrix();
}

void DrawMC()
{
	glPushMatrix();
	glTranslatef(5.0, 0.0, 0.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glTranslatef(1.0, 3.0, -3.0);
	BitmapString(0, -1.5, 1, "{MC1}", 1.0, 0.0, 0.0);
	glutSolidTeapot(1.0);
	DrawAxis(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.0, 0.0, 0.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glTranslatef(-1.0, -3.0, -4.0);
	glutSolidTorus(0.3, 1.0, 20, 20);
	DrawAxis(2.0);
	BitmapString(0, -2.0, 1, "{MC2}", 1.0, 0.0, 0.0);
	glPopMatrix();
}

void DrawVV(int opt)
{
	if (opt % 2)
	{
		double s1 = 2.0 / sqrtf(3.0), s2 = 20.0 / sqrtf(3.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_LIGHTING);
		glColor4f(1.0, 1.0, 1.0, 0.7);
		glBegin(GL_QUADS);
		glVertex3f(-8.0, s1, s1);
		glVertex3f(-8.0, -s1, s1);
		glVertex3f(-8.0, -s1, -s1);
		glVertex3f(-8.0, s1, -s1);
		glVertex3f(10.0, s2, s2);
		glVertex3f(10.0, s2, -s2);
		glVertex3f(10.0, -s2, -s2);
		glVertex3f(10.0, -s2, s2);
		glEnd();
		glDisable(GL_BLEND);

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-8.0, s1, s1);
		glVertex3f(-8.0, -s1, s1);
		glVertex3f(-8.0, -s1, -s1);
		glVertex3f(-8.0, s1, -s1);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(10.0, s2, s2);
		glVertex3f(10.0, s2, -s2);
		glVertex3f(10.0, -s2, -s2);
		glVertex3f(10.0, -s2, s2);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-8.0f, s1, s1);
		glVertex3f(-8.0f, -s1, s1);
		glVertex3f(10.0f, -s2, s2);
		glVertex3f(10.0f, s2, s2);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-8.0f, s1, -s1);
		glVertex3f(-8.0f, -s1, -s1);
		glVertex3f(10.0f, -s2, -s2);
		glVertex3f(10.0f, s2, -s2);
		glEnd();
	}
	else
	{
		double s1 = 5.0f, s2 = 5.0f;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_LIGHTING);
		glColor4f(1.0, 1.0, 1.0, 0.7);
		glBegin(GL_QUADS);
		glVertex3f(-8.0, s1, s1);
		glVertex3f(-8.0, -s1, s1);
		glVertex3f(-8.0, -s1, -s1);
		glVertex3f(-8.0, s1, -s1);
		glVertex3f(10.0, s2, s2);
		glVertex3f(10.0, s2, -s2);
		glVertex3f(10.0, -s2, -s2);
		glVertex3f(10.0, -s2, s2);
		glEnd();
		glDisable(GL_BLEND);

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-8.0, s1, s1);
		glVertex3f(-8.0, -s1, s1);
		glVertex3f(-8.0, -s1, -s1);
		glVertex3f(-8.0, s1, -s1);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(10.0, s2, s2);
		glVertex3f(10.0, s2, -s2);
		glVertex3f(10.0, -s2, -s2);
		glVertex3f(10.0, -s2, s2);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-8.0f, s1, s1);
		glVertex3f(-8.0f, -s1, s1);
		glVertex3f(10.0f, -s2, s2);
		glVertex3f(10.0f, s2, s2);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(-8.0f, s1, -s1);
		glVertex3f(-8.0f, -s1, -s1);
		glVertex3f(10.0f, -s2, -s2);
		glVertex3f(10.0f, s2, -s2);
		glEnd();

	}
	glPopMatrix();
}

void BitmapString(float x, float y, float z, char *str, float r, float g, float b)
{
	glDisable(GL_LIGHTING);
	int len, i;
	glColor3f(r, g, b);
	glRasterPos3f(x, y, z);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	glEnable(GL_LIGHTING);
}

void StrokeString(char *str, float r, float g, float b)
{
	glDisable(GL_LIGHTING);

	int len, i;
	glColor3f(r, g, b);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);

	glEnable(GL_LIGHTING);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '*':
		opt++;
		break;
	case '+':
		state++;
		if (state > 6)
			state = 6;
		break;
	case '-':
		if (state < 0)
			state = 0;
		state--;
		break;
	case 'r':
	case 'R':
		Angle = 0.0;
		break;
	}
	glutPostRedisplay();
}

void DrawNC()
{
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, 0.0f);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	BitmapString(0, -2, 1.0, "{NC}", 1.0, 0.0, 0.0);
	DrawAxis2(2.0);

	glPushMatrix();
	glScaled(0.3, 0.3, 0.3);
	glTranslatef(1.0, 1.5, -2.0);
	glutSolidTeapot(1.0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.3, 0.3, 0.3);
	glTranslatef(-1.2, -1.5, -2.5);
	glutSolidTorus(0.3, 1.0, 20, 20);
	glPopMatrix();


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_LIGHTING);
	glColor4f(1.0, 1.0, 1.0, 0.7);
	glBegin(GL_QUADS);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glEnd();
	glDisable(GL_BLEND);

	glBegin(GL_LINE_LOOP);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glEnd();

	glEnable(GL_LIGHTING);

	glPopMatrix();
}


void DrawDC()
{
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, 0.0f);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	BitmapString(0, -1, 1.0, "{DC}", 1.0, 0.0, 0.0);
	DrawAxis2(2.0);

	glPushMatrix();
	glTranslatef(6.0, 7.5, -0.6);
	glScaled(1.0, 1.0, 0.1);
	glutSolidTeapot(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 3.0, -0.8);
	glScaled(1.0, 1.0, 0.1);
	glutSolidTorus(0.5, 1.0, 20, 20);
	glPopMatrix();


	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 10.0, -1.0);
	glVertex3f(10.0, 10.0, -1.0);
	glVertex3f(10.0, 0.0, -1.0);
	glEnd();


	glBegin(GL_LINE_LOOP);
	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, -1.0);
	glVertex3f(10.0, 10.0, -1.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 10.0, 0.0);
	glVertex3f(0.0, 10.0, -1.0);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		StartPt[0] = x;
		StartPt[1] = y;

		if (button == GLUT_LEFT_BUTTON)
			ManipulateMode = 1;
		else
			ManipulateMode = 2;
	}

	if (state == GLUT_UP)
	{
		ManipulateMode = 0;
		StartPt[0] = StartPt[1] = 0;
		Angle = 0.0;
	}
}

void MouseMove(int x, int y)
{
	if (ManipulateMode == 1)
	{
		float px, py, pz;
		float qx, qy, qz;

		GetSphereCoord(StartPt[0], StartPt[1], &px, &py, &pz);
		GetSphereCoord(x, y, &qx, &qy, &qz);

		Axis[0] = py * qz - pz * qy;
		Axis[1] = pz * qx - px * qz;
		Axis[2] = px * qy - py * qx;

		float len = Axis[0] * Axis[0] + Axis[1] * Axis[1] + Axis[2] * Axis[2];
		if (len < 0.0001)
		{
			Axis[0] = 1.0;
			Axis[1] = 0.0;
			Axis[2] = 0.0;
			Angle = 0.0;
		}
		else
		{
			Angle = px * qx + py * qy + pz * qz;
			Angle = acos(Angle) * 180.0f / 3.141592f;
		}
	}
	else
	{
		int dx = x - StartPt[0];
		dT[2] += dx;
	}

	StartPt[0] = x;
	StartPt[1] = y;

	glutPostRedisplay();
}

void GetSphereCoord(int x, int y, float *px, float *py, float *pz)
{
	float r;
	*px = (2.0 * x - Width) / Width;
	*py = (-2.0 * y + Height) / Height;

	r = *px * *px + *py * *py;
	if (r >= 1.0)
	{
		*px = *px / sqrt(r);
		*py = *py / sqrt(r);
		*pz = 0.0;
	}
	else
	{
		*pz = sqrt(1.0 - r);
	}
}


