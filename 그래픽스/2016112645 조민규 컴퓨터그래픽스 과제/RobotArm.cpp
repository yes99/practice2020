#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <gl/glut.h>

using namespace std;


// Variables for window creation
int Width = 800, Height = 800;

// Variables for robot control
double UpperArmAngle = 0.0;
double LowerArmAngle = 0.0;
double FingerDistance = 0.0;

// Variables for rotation and zooming
int ManipulateMode = 0;
int StartPt[2];

// Variables for rotation and zooming
float Axis[3] = { 1.0, 0.0, 0.0 };
float Angle = 0.0;
float RotMat[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
float Zoom = -60.0;

// Callback functions.
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void MouseMove(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Render();
void SetMaterial(int c);

// User-defined funtions.
void SetupViewVolume();
void SetupViewTransform();
void GetSphereCoord(int x, int y, float *px, float *py, float *pz);
void RenderFloor();
void Sub(double out[3], double a[3], double b[3]);
void Add(double out[3], double a[3], double b[3]);
void Cross(double out[3], double a[3], double b[3]);
void RenderRobot();
void drawCube(float sx, float sy, float sz);

void Mygl();

struct Vertex
{
	double P[3];
	double N[3];
};

struct Face
{
	int vIdx[3];
};

struct Object
{
	vector<Vertex> VertList;
	vector<Face> FaceList;
};
Object MyModel;


int main(int argc, char **argv)
{
	// Initialize GLUT and display mode
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// Create OpenGL window of size Width by Height
	glutInitWindowSize(Width, Height);
	glutCreateWindow("2016112645 Á¶¹Î±Ô ÄÄÇ»ÅÍ±×·¡ÇÈ½º °úÁ¦");

	// Setup OpenGL
	glEnable(GL_DEPTH_TEST);


	// Register call back functions.
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Render);	

	// Enter the message loop.
	glutMainLoop();
	return 0;
}

void Mygl()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light0_position[] = { 15.0f, 35.0f, 5.0f, 1.0f };
	GLfloat light0_ambient[] = { 0.2, 0.2, 0.2 };
	GLfloat light0_diffuse[] = { 0.8, 0.8, 0.8 };
	GLfloat light0_specular[] = { 0.7, 0.7, 0.7 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

}

void Render()
{
	// Clear color buffer
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mygl();
	// Set up viewing volume
	SetupViewVolume();

	// Set up viewing transformation
	SetupViewTransform();

	glMatrixMode(GL_MODELVIEW);
	RenderFloor();
	RenderRobot();


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Swap buffers for double buffering.
	glutSwapBuffers();
}

void RenderRobot()
{
	
	SetMaterial(1);
	drawCube(10.0, 1.0, 10.0); //¹Ù´Ú Á÷À°¸éÃ¼

	SetMaterial(2);
	glTranslatef(0.0, 1.0, 0.0);
	glRotatef(1.0 * UpperArmAngle, 0.0, 1.0, 0.0);
	drawCube(1.0, 5.0, 1.0); // ¾Æ·§ºÎºÐ ÆÈ

	SetMaterial(3);
	glTranslatef(0.0, 5.0, 0.0);
	glutSolidSphere(1.0, 10, 10); //Áß°£ºÎºÐ ±¸

	SetMaterial(4);
	glRotatef(1.0 * LowerArmAngle, 0.0, 0.0, 1.0);
	drawCube(1.0, 5.0, 1.0); // À­ºÎºÐ ÆÈ

	SetMaterial(5);
	glPushMatrix();
	{
		glTranslatef(-0.6 + 0.03 * FingerDistance, 5.0, 0.0);
		drawCube(0.1, 2.0, 1.0); //¿ÞÂÊ ¼Õ°¡¶ô
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.6 - 0.03 * FingerDistance, 5.0, 0.0);
		drawCube(0.1, 2.0, 1.0); //¿À¸¥ÂÊ ¼Õ°¡¶ô
	}
	glPopMatrix();

}

void SetMaterial(int c)
{
	switch(c) {
	case 1: {
		float ambient1[] = { 0.7, 0.7, 0.7 };
		float diffuse1[] = { 0.2, 0.2, 0.2 };
		float specular1[] = { 0.9, 0.9, 0.9 };
		float shininess1 = 35;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess1);
		break;
	}
	case 2: {
		float ambient1[] = { 0.7, 0.0, 0.0 };
		float diffuse1[] = { 0.5, 0.0, 0.0 };
		float specular1[] = { 0.5, 0.0, 0.0 };
		float shininess1 = 35;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess1);
		break;
	}
	case 3: {
		float ambient1[] = { 0.0, 0.7, 0.0 };
		float diffuse1[] = { 0.0, 0.5, 0.0 };
		float specular1[] = { 0.0, 0.5, 0.0 };
		float shininess1 = 35;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess1);
		break;
	}
	case 4: {
		float ambient1[] = { 0.0, 0.0, 0.7 };
		float diffuse1[] = { 0.0, 0.0, 0.5 };
		float specular1[] = { 0.0, 0.0, 0.5 };
		float shininess1 = 35;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess1);
		break;
	}
	case 5: {
		float ambient1[] = { 0.2, 0.5, 0.7 };
		float diffuse1[] = { 0.7, 0.5, 0.2 };
		float specular1[] = { 0.2, 0.7, 0.5 };
		float shininess1 = 35;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess1);
		break;
	}
	default :{
		break;
	}
	}
}



void Keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(-1);

	if (key == '1')
	{
		UpperArmAngle += 3.5;
	}

	if (key == '2')
	{
		UpperArmAngle -= 3.5;
	}

	if (key == '3')
	{
		LowerArmAngle += 2.0;
	}

	if (key == '4')
	{
		LowerArmAngle -= 2.0;
	}

	if (key == '5')
	{
		if (FingerDistance > 15)
			FingerDistance += 0.0;
		else
			FingerDistance += 1.0;
	}

	if (key == '6')
	{
		if (FingerDistance == 0)
			FingerDistance -= 0.0;
		else
			FingerDistance -= 1.0;
	}

	if (key == 'q')
	{

	}

	glutPostRedisplay();
}

void drawCube(float sx, float sy, float sz)
{
	glPushMatrix();
	glTranslatef(0.0, sy * 0.5, 0.0);
	glScalef(sx, sy, sz);
	glutSolidCube(1.0);
	glPopMatrix();
}

void Reshape(int w, int h)
{
	// Viewport transformation
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}

void SetupViewTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Translate for zooming in/out
	glTranslatef(0.0, 0.0, Zoom);

	// For rotation
	glRotatef(Angle, Axis[0], Axis[1], Axis[2]);
	glMultMatrixf(RotMat);

	// Save the rotation of current modelview mat.
	glGetFloatv(GL_MODELVIEW_MATRIX, RotMat);
	RotMat[12] = RotMat[13] = RotMat[14] = 0.0;
}

void SetupViewVolume()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)Width / (double)Height, 1.0, 10000.0);
}


void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		StartPt[0] = x; StartPt[1] = y;
		if (button == GLUT_LEFT_BUTTON)
			ManipulateMode = 1;	// For rotation

		if (button == GLUT_RIGHT_BUTTON)
			ManipulateMode = 2;	// For zooming
	}
	if (state == GLUT_UP)
	{
		ManipulateMode = 0;	// Reset 
		StartPt[0] = StartPt[1] = 0;
		Angle = 0.0;
	}


}

void MouseMove(int x, int y)
{
	if (ManipulateMode == 1) {	// Rotation
		float px, py, pz, qx, qy, qz;
		GetSphereCoord(StartPt[0], StartPt[1], &px, &py, &pz);
		GetSphereCoord(x, y, &qx, &qy, &qz);

		// Compute rotation axis and angle
		Axis[0] = py*qz - pz*qy; Axis[1] = pz*qx - px*qz; Axis[2] = px*qy - py*qx;
		Angle = 0.0;

		float len = Axis[0] * Axis[0] + Axis[1] * Axis[1] + Axis[2] * Axis[2];
		if (len > 0.0001) // ingnore small changes 
			Angle = acos(px * qx + py * qy + pz * qz) * 180.0f / 3.141592f;
	}
	if (ManipulateMode == 2) {	// Zooming
		double dy = (StartPt[1] - y) * 0.1;
		Zoom += dy;
	}

	StartPt[0] = x;	// Update startpt as current position
	StartPt[1] = y;
	glutPostRedisplay();
}

void GetSphereCoord(int x, int y, float *px, float *py, float *pz)
{
	*px = (2.0 * x - Width) / Width;
	*py = (-2.0 * y + Height) / Height;

	float r = (*px) * (*px) + (*py) * (*py);
	if (r >= 1.0)
	{
		*px = *px / sqrt(r);
		*py = *py / sqrt(r);
		*pz = 0.0;
	}
	else
		*pz = sqrt(1.0 - r);
}


void Cross(double out[3], double a[3], double b[3])
{
	out[0] = a[1] * b[2] - a[2] * b[1];
	out[1] = a[2] * b[0] - a[0] * b[2];
	out[2] = a[0] * b[1] - a[1] * b[0];
}

void Sub(double out[3], double a[3], double b[3])
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}

void Add(double out[3], double a[3], double b[3])
{
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
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