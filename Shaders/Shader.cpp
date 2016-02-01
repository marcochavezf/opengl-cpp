#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#pragma comment(lib, "glew32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")
#define GLEW_STATIC


float t = 0.0;
float ortho = 2.0;

void display(){

	//Rellenar la pantalla con el color especificado en la máquina de estados
	glClear(GL_COLOR_BUFFER_BIT); 
	
	//Sombra del polígono
	glShadeModel(GL_SMOOTH);

	//Definir si el colo del poligono será por relleno o solo con contornos
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

	//En caso de que se dibuje con lineas
	glPointSize(60);
	glLineWidth(10);

	//Activar Anti-Aliasing
	glEnable(GL_LINE_SMOOTH);

	//Habilitar el canal Aplana e indicar la mezcla alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Da la indicación de que van a venir vertices.
	glBegin(GL_TRIANGLE_FAN); 
		//glColor4f(1.0, 0.0, 0.0, 0.5);
		glVertex2f(0.5 + t, 0.5); //El orden de los vertices deben de ir en dirección inversa a las manecillas del reloj.
		//glColor3f(0.0, 1.0, 0.0);
		glVertex2f(-0.5 + t, 0.5);
		//glColor3f(0.0, 0.0, 1.0);
		glVertex2f(-0.5 + t, -0.5);
		//glColor3f(1.0, 1.0, 0.0);
		glVertex2f(0.5 + t, -0.5);
	glEnd();

	//Forzar la salida del buffer y desplegarlo en la pantalla.
	//glFlush(); //Single
	 glutSwapBuffers(); //Double
}

void handleKey(unsigned char key, int x, int y){
	if(key=='Q' || key=='q'){
		exit(0);
	}
}

void handleSpecialKey(int key, int x, int y){
	if(key==GLUT_KEY_RIGHT){
		ortho += 0.1;
	}else

	if(key==GLUT_KEY_LEFT){
		ortho -= 0.1;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-ortho, ortho, -ortho, ortho);
	glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y){
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
		exit(0);
	}
}
	
void init(){
	glClearColor(0,0,0,1);
	glColor3f(1.0, 0.0, 0.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-ortho, ortho, -ortho, ortho);
}

void reshape(GLsizei w, GLsizei h){
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     if(w<=h)
             gluOrtho2D(-ortho,ortho,-ortho*(GLfloat)h/(GLfloat)w,ortho*(GLfloat)h/(GLfloat)w);
     else
             gluOrtho2D(-ortho*(GLfloat)w/(GLfloat)h,ortho*(GLfloat)w/(GLfloat)h,-ortho,ortho);
     glMatrixMode(GL_MODELVIEW);
     glViewport(0,0,w,h);
}

void handleMenu(int entryId){
	if(entryId==1)
		glColor3f(1.0, 0.0, 0.0);
	
	if(entryId==2)
		glColor3f(0.0, 1.0, 0.0);
	
	if(entryId==3)
		glColor3f(0.0, 0.0, 1.0);

	glutPostRedisplay();
}

void createMenu(){
	glutCreateMenu(handleMenu);
	glutAddMenuEntry("rojo", 1);
	glutAddMenuEntry("verde", 2);
	glutAddMenuEntry("azul", 3);
	glutAttachMenu(GLUT_LEFT_BUTTON);
}

void animate(/*int i*/){
	t += 0.001;
	glutPostRedisplay();
	//glutTimerFunc(33, animate, 1);
}

void animate(int i){
	t += 0.1;
	glutPostRedisplay();
	glutTimerFunc(33, animate, 1);
}

void main(int argc, char **argv) {

	glutInit(&argc, argv);
	glewInit();
	
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Sensishito");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(handleKey);
	glutSpecialFunc(handleSpecialKey);
	glutMouseFunc(handleMouse);
	//glutTimerFunc(33, animate, 1);
	//glutIdleFunc(animate);

	init();
	createMenu();

	glutMainLoop();
}