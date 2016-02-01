/* include the library header files */
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>


// current camera position
GLfloat cameraPosition[] = {0, 0, 7};

// window dimensions
GLint windowWidth  = 800;
GLint windowHeight = 400;

// are we using smooth shading or flat?
int smoothOn =1;


// initially position the light source at (10,10,10), we move it later
GLfloat lightPosition[] = { 10.0, 10.0, 10.0, 1.0 };

// a material that is all zeros
GLfloat zeroMaterial[]	= { 0.0, 0.0, 0.0, 1.0 };
// a red ambient material
GLfloat redAmbient[]	= { 0.83, 0.0, 0.0, 1.0 };
// a blue diffuse material
GLfloat blueDiffuse[]	= { 0.1, 0.5, 0.8, 1.0 };
// a red diffuse material
GLfloat redDiffuse[]	= { 1.0, 0.0, 0.0, 1.0 };
// a white specular material
GLfloat whiteSpecular[]	= { 1.0, 1.0, 1.0, 1.0 };

// the degrees of shinnines (size of the specular highlight, bigger number means smaller highlight)
GLfloat noShininess	    =  0.0;
GLfloat highShininess	= 50.0;


/************************************************************************

	Function:		myDisplay

	Description:	Display callback, clears frame buffer and depth buffer,
				    and draws the balls.

*************************************************************************/
void myDisplay(void)
{

	// sphere resolution
	int resolution = 40;

	if (smoothOn)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);

	// clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load the identity matrix into the model view matrix
	glLoadIdentity();

	// set the camera position
	gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2],
			  0,   0,    0,
			  0,   1,    0);


	// position light 0
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);



	// draw the middle sphere, blue with a white highlight
    glMaterialfv(GL_FRONT, GL_AMBIENT,   zeroMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   blueDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,	 whiteSpecular);
    glMaterialf(GL_FRONT,  GL_SHININESS, highShininess);
	// glutSolidSphere(radius, slices - lines of longitude, stacks - lines of latitude);
    glutSolidSphere(1.0,resolution,resolution);		  // glutSolidSphere automatically computes normals for us


	// draw the left sphere, blue with hightlight
	glMaterialfv(GL_FRONT, GL_AMBIENT,   zeroMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   blueDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
	glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);
    glPushMatrix();
		glTranslatef (-3.75, 0, 0);
		// glutSolidSphere(radius, slices - lines of longitude, stacks - lines of latitude);
		glutSolidSphere(1.0,resolution,resolution);   // glutSolidSphere automatically computes normals for us
    glPopMatrix();


	// draw the right sphere, blue with red ambient
	glMaterialfv(GL_FRONT, GL_AMBIENT,   redAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   blueDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
	glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);
	glPushMatrix();
		glTranslatef (3.75, 0, 0);
		// glutSolidSphere(radius, slices - lines of longitude, stacks - lines of latitude);
		glutSolidSphere(1.0,resolution,resolution);   // glutSolidSphere automatically computes normals for us
	glPopMatrix();


/*	// draw a red floor
	glMaterialfv(GL_FRONT, GL_AMBIENT,   zeroMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   redDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  zeroMaterial);
	glMaterialf(GL_FRONT,  GL_SHININESS, noShininess);

 	glNormal3d(0, 1, 0);  // normal of the floor is pointing up

	glPushMatrix();
		glTranslatef (1.5, -1, 0);
		glScalef(3,0,3);
		glBegin(GL_POLYGON);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 1);
			glVertex3f(1, 0, 1);
			glVertex3f(1, 0, 0);
		glEnd();
	glPopMatrix();

*/
	// swap the drawing buffers
	glutSwapBuffers();
}




/************************************************************************

	Function:		initializeGL

	Description:	Initializes the OpenGL rendering context for display.

*************************************************************************/
void initializeGL(void)
{
	// define the light color and intensity
    GLfloat ambientLight[]	= { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuseLight[]	= { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specularLight[]	= { 1.0, 1.0, 1.0, 1.0 };

	//  the global ambient light level
    GLfloat globalAmbientLight[] = { 0.0, 0.0, 0.0, 1.0 };

	// set the global ambient light level
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);

	// define the color and intensity for light 0
    glLightfv(GL_LIGHT0, GL_AMBIENT,   ambientLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR,  diffuseLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,   specularLight);

	// enable lighting
    glEnable(GL_LIGHTING);
	// enable light 0
    glEnable(GL_LIGHT0);


	// turn on depth testing so that polygons are drawn in the correct order
	glEnable(GL_DEPTH_TEST);

	// make sure the normals are unit vectors
	glEnable(GL_NORMALIZE);



}


/************************************************************************

	Function:		myResize

	Description:	Handles a user resize of the window.

*************************************************************************/
void myResize(int newWidth, int newHeight)
{

	// update the new width
	windowWidth = newWidth;
	// update the new height
	windowHeight = newHeight;

	// update the viewport to still be all of the window
	glViewport (0, 0, windowWidth, windowHeight);

	// change into projection mode so that we can change the camera properties
    glMatrixMode(GL_PROJECTION);

	// load the identity matrix into the projection matrix
    glLoadIdentity();

    // gluPerspective(fovy, aspect, near, far)
    gluPerspective(45, (float)windowWidth/(float)windowHeight, 0.1, 300);

    // change into model-view mode so that we can change the object positions
	glMatrixMode(GL_MODELVIEW);
}



/************************************************************************

	Function:		myKeys

	Description:	Handles keyboard input.

*************************************************************************/
void myKeys(unsigned char key, int x, int y)
{

	if ((key == 's') || (key == 'S'))
		smoothOn = !smoothOn;

	if ((key == 'q') || (key == 'Q'))
		exit(0);

	glutPostRedisplay();
}


/************************************************************************

	Function:		printControlInfo

	Description:	Print out control information.

*************************************************************************/
void printControlInfo()
{/*
	printf("\n\n\n");
	printf(" Scene Controls\n");
	printf(" -----------------\n");
	printf(" s   : toggle shading modes\n");
	printf(" q   : quit\n");
	printf("\n");
*/
}


/************************************************************************

	Function:		main

	Description:	Sets up the openGL rendering context and the windowing
					system, then begins the display loop.

*************************************************************************/
 main(int argc, char** argv)
{
	// initialize the toolkit
	glutInit(&argc, argv);
	// set display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	// set window size
	glutInitWindowSize(windowWidth, windowHeight);
	// set window position on screen
	glutInitWindowPosition(100, 100);
	// open the screen window
	glutCreateWindow("Modelo de Phong");

	// register redraw function
	glutDisplayFunc(myDisplay);
	// register keyboard handler
	glutKeyboardFunc(myKeys);
	// register the resize function
	glutReshapeFunc(myResize);

	// print out control info
	printControlInfo();

	//initialize the rendering context
	initializeGL();
	// go into a perpetual loop
	glutMainLoop();
}

