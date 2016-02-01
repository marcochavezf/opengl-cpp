// This program simulates a simple landscape illuminated by the sun.
// Programming "tricks" include:
// - use glClearColor() to change background ("sky") colour;
// - Move "sun" in a circle around the "terrain".
// - Make the sun an emissive object and illuminate it.
// - The terrain is actually flat, but random normals give it
//   a textured appearance.
#include <windows.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>

const GLfloat PI = 3.1415926535f;

// Convert degrees to radians.
const GLfloat DEG_RAD = PI / 180.0;

// Convert hours to degrees
const GLfloat HOUR_DEG = 15.0;

// Current window size (pixels).
int window_width = 900;
int window_height = 600;

// Use 's' key to toggle normal display.
bool show_normals = false;

const GLfloat HEIGHT = 1.0;		// Height of viewer above terrain.
const GLfloat SIDE = 6.0;		// Size of terrain.
const GLfloat DEV = 0.7f;		// Deviation of normals.
const int NUM = 20;				// Number of divisions on a side.
const int RATE = 10;			// Rate of change (steps per hour).

// Colours and properties of materials.
const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat earth[] = { 0.6f, 0.7f, 0.2f, 1.0 };
const GLfloat sun[] = { 0.9f, 0.9f, 0.6f, 1.0 };
const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat polished[] = { 100.0 };
const GLfloat dull[] = { 0.0 };

// The light is always at the current origin.
const GLfloat light_pos[] = { 0.0, 0.0, 0.0, 1.0 };

// Coordinates for moving the light (light_x is actually constant).
GLfloat light_x = 0.0;
GLfloat light_y = 0.0;
GLfloat light_z = 0.0;

GLfloat time_of_day = 0.0;
GLfloat distance = 0.6 * SIDE;
GLfloat axis = 0.0;
GLfloat back_red = 0.0;
GLfloat back_green = 0.0;
GLfloat back_blue = 0.0;

GLfloat vert[NUM][NUM][3];		// Vertex coordinates.
GLfloat norm[NUM][NUM][3];		// Normal components at each vertex.

void make_surface () {
	// Construct a flat surface in the (x,z) plane.  The normals "should" be
	// (0,1,0), but we deflect the normal a bit to give a textured appearance.
	for (int x = 0; x < NUM; x++)
		for (int z = 0; z < NUM; z++) {
			vert[x][z][0] = SIDE * (GLfloat(x)/GLfloat(NUM) - 0.5);
			vert[x][z][1] = 0.0;
			vert[x][z][2] = SIDE * (GLfloat(z)/GLfloat(NUM) - 0.5);;
			GLfloat u = DEV * rand() / RAND_MAX;
			GLfloat w = DEV * rand() / RAND_MAX;
			GLfloat v = sqrt(1.0 - u * u - w * w);
			norm[x][z][0] = u;
			norm[x][z][1] = v;
			norm[x][z][2] = w;
		}
}

void display () {

	// Set background colour to match time of day.
	glClearColor(back_red, back_green, back_blue, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Move model into view; `distance' is controlled by mouse.
	gluLookAt (
		0.0, HEIGHT, distance,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0 );

	glPushMatrix();

		// Set axis for sun's rotation and go to position of sun.
		glRotatef(axis, 0.0, 1.0, 0.0);
		glTranslatef(light_x, light_y, light_z);

		glPushMatrix();
			// Put a light between the viewer and the sun to illuminate the sun.
			glTranslatef(0.0, 0.0, 2.0);
			glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glPopMatrix();

		// Show the "sun" in this light.
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sun);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun);
		glutSolidSphere(0.05, 15, 15);
		glMaterialfv(GL_FRONT, GL_EMISSION, black);

		// Now move the light to the position of the sun to illuminate the plane.
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glPopMatrix();

	// Set model properties for terrain and render it.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, earth);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, polished);
	glBegin(GL_QUADS);
		for (int x = 0; x < NUM - 1; x++)
			for (int z = 0; z < NUM - 1; z++) {
				glNormal3fv(norm[x][z]);
				glVertex3fv(vert[x][z]);
				glNormal3fv(norm[x+1][z]);
				glVertex3fv(vert[x+1][z]);
				glNormal3fv(norm[x+1][z+1]);
				glVertex3fv(vert[x+1][z+1]);
				glNormal3fv(norm[x][z+1]);
				glVertex3fv(vert[x][z+1]);
			}
	glEnd();

	// Optionally, display surface normals.
	if (show_normals) {
		glDisable(GL_LIGHTING);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
			for (int x = 0; x < NUM; x++)
				for (int z = 0; z < NUM; z++) {
					glVertex3fv(vert[x][z]);
					glVertex3f(
						vert[x][z][0] + norm[x][z][0],
						vert[x][z][1] + norm[x][z][1],
						vert[x][z][2] + norm[x][z][2]);
				}
		glEnd();
		glEnable(GL_LIGHTING);
	}

	glutSwapBuffers();
	glFlush();
}

// Static variables used to display time.
int count = 0;
int clock = 6;

void move () {
	// The idle function advances the time of day.
	// The day has 12 hours, from sunrise to sunset.
	// The time of day is converted to degrees and then to radians.
	time_of_day += 1.0f / RATE;
	if (time_of_day > 12.0)
		time_of_day = 0.0;
	light_y = 0.6 * SIDE * sin(time_of_day * HOUR_DEG * DEG_RAD);
	light_z = 0.6 * SIDE * cos(time_of_day * HOUR_DEG * DEG_RAD);

	// Calculate sky colour according to time of day.
	GLfloat sin_t = sin(PI * time_of_day / 12.0);
	back_red = 0.3 * (1.0 - sin_t);
	back_green = 0.9 * sin_t;
	back_blue = sin_t + 0.4, 1.0;
	if (count++ % RATE == 0) {
		printf("The time is %02d:00.  Colours: %3.1f %3.1f %3.1f\n",
			clock, back_red, back_green, back_blue);
		if (clock == 18)
			clock = 6;
		else
			clock++;
	}

	glutPostRedisplay();
}

void mouse_movement (int x, int y) {

	// Left-right movement changes axis of sun's circle.
	axis = 180.0 * x / window_width;

	// Up-down movement changes distance from viewer to centre of plane.
	distance = SIDE * y / window_height;

	glutPostRedisplay();
}

void keys (unsigned char key, int x, int y) {
	switch (key) {
	case 27:				// ESC exits
		exit(0);
	case 's':				// s toggles display of surface normals
		show_normals = ! show_normals;
		glutPostRedisplay();
		break;
	}
}

void resize_window (int w, int h) {
	// The resizing function is conventional.
	window_width = w;
	window_height = h;
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, GLfloat(window_width)/GLfloat(window_height), 0.5, 3 * SIDE);
	glutPostRedisplay();
}

void init () {

	// Construct the surface.
	make_surface();
	glEnable(GL_NORMALIZE);

	// Initialize the light.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun);

	// Request hidden surface elimination and register callbacks.
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutIdleFunc(move);
	glutMotionFunc(mouse_movement);
	glutKeyboardFunc(keys);
	glutReshapeFunc(resize_window);
}

int main (int argc, char *argv[]) {

	// Initialize OpenGL and enter loop.
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("A rough surface illuminated by the sun.");
	init();
	printf("Move mouse left/right to change solar axis.\n");
	printf("Move mouse up/down to change viewpoint.\n");
	printf("Press 's' to see surface normals.\n");
	glutMainLoop();
	return 0;
}

