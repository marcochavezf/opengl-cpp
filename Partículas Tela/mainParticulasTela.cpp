/***************************************************
Materia:	Gráficas Computacionales
Tarea:	    6 - Isosuperficies
Fecha:		8 de octubre del 2012
Autor:      Marco Chavez
***************************************************/
#include <math.h>
#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <GL/glut.h>
#include "Punto.h"

#define MAX 100
#define MIN 10

#define RENDER 1
#define SELECT 2
int mode=RENDER;

float rotationX=0.0;
float rotationY=0.0;
float prevX=0.0;
float prevY=0.0;
float cursorX=0.0;
float cursorY=0.0;
bool mouseDown=false,
	pausa = false,
	versionPuntos = true,
	wireframe = true,
	malla = true;
float viewer[]= {0.0, 0.0, 100.0};

Punto cuadricula[MAX][MAX];
int dimensionActual=30;
int limite = MAX;

float distancia(Punto p1, Punto p2){
	float x1 = p1.getX();
	float y1 = p1.getY();
	float x2 = p2.getX();
	float y2 = p2.getY();

	return  sqrt( pow(x2-x1,2) + pow(y2-y1,2) );
}

void crearCuadricula(void){
	float z=0.0;
	float vx=0;
	float vy=0;

	float incremento=(float)limite/(float)(dimensionActual);

    for(int renglon=0; renglon<dimensionActual; renglon++){
		for(int columna=0; columna<dimensionActual; columna++){
			float x=columna*incremento-(limite/2.0)+(incremento/2.0);
			float y=renglon*incremento-(limite/2.0)+(incremento/2.0);
			cuadricula[renglon][columna]=Punto(x,y,z,renglon,columna,1,vx,vy);
        }
    }
}

void dibujarPuntos(void){
	glPointSize(8);
	glBegin(GL_POINTS);
		for(int renglon=0; renglon<dimensionActual; renglon++){
			for(int columna=0; columna<dimensionActual; columna++){
				Punto p = cuadricula[renglon][columna];

				if(mode==SELECT)
					glColor3ub(p.getR(),p.getG(),p.getB());
				else
					if(p.isFixed())
						glColor3f(1,0,0);
					else
						glColor3f(0,0,1);
				
				glVertex3f(p.getX(), p.getY(), p.getZ());
			}
		}
    glEnd();
}

void dibujarMalla(void){

	if(wireframe){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(1,1,1);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(0,1,0);
	}

	for(int renglon=0; renglon<dimensionActual-1; renglon++){
		for(int columna=0; columna<dimensionActual-1; columna++){
				
			Punto p1 = cuadricula[renglon][columna];
			Punto p2 = cuadricula[renglon][columna+1];
			Punto p3 = cuadricula[renglon+1][columna+1];
			Punto p4 = cuadricula[renglon+1][columna];

			//1-2-3
			glBegin(GL_TRIANGLES);
				glVertex3f(p1.getX(), p1.getY(), p1.getZ());
				glVertex3f(p2.getX(), p2.getY(), p2.getZ());
				glVertex3f(p3.getX(), p3.getY(), p3.getZ());
			glEnd();

			//2-3-4
			glBegin(GL_TRIANGLES);
				glVertex3f(p2.getX(), p2.getY(), p2.getZ());
				glVertex3f(p3.getX(), p3.getY(), p3.getZ());
				glVertex3f(p4.getX(), p4.getY(), p4.getZ());
			glEnd();

			//3-4-1
			glBegin(GL_TRIANGLES);
				glVertex3f(p3.getX(), p3.getY(), p3.getZ());
				glVertex3f(p4.getX(), p4.getY(), p4.getZ());
				glVertex3f(p1.getX(), p1.getY(), p1.getZ());
			glEnd();

			//4-1-2
			glBegin(GL_TRIANGLES);
				glVertex3f(p4.getX(), p4.getY(), p4.getZ());
				glVertex3f(p1.getX(), p1.getY(), p1.getZ());
				glVertex3f(p2.getX(), p2.getY(), p2.getZ());
			glEnd();
		}
	}
}

Punto calcularPuntoMedio(Punto pA, Punto pB){
	float x = (pA.getX() < pB.getX()) ?  pA.getX() + (pB.getX()-pA.getX())/2: pB.getX() + (pA.getX()-pB.getX())/2 ;
	float y = (pA.getY() < pB.getY()) ?  pA.getY() + (pB.getY()-pA.getY())/2: pB.getY() + (pA.getY()-pB.getY())/2 ;
	float z = (pA.getZ() < pB.getZ()) ?  pA.getZ() + (pB.getZ()-pA.getZ())/2: pB.getZ() + (pA.getZ()-pB.getZ())/2 ;
	return Punto(x,y,z,0,0,0,0,0);
}

void processPick ()
{
	GLint viewport[4];
	GLubyte pixel[3];

	glGetIntegerv(GL_VIEWPORT,viewport);

	glReadPixels(cursorX,viewport[3]-cursorY,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);
	if(pixel[2]==0 || (pixel[0]==255 && pixel[1]==255 && pixel[2]==255)){
		puts("Click en otra parte");
	}else{
		GLubyte renglon=pixel[0];
		GLubyte columna=pixel[1];
		Punto *p = &cuadricula[renglon][columna];
		p->setFixed(!p->isFixed());
	}
}

void display(void){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,1,0);

    glRotatef(rotationX,1,0,0);
    glRotatef(rotationY,0,1,0);

	if(malla)
		dibujarMalla();

	if(versionPuntos)
		dibujarPuntos();

    if (mode == SELECT) {
		processPick();
		mode = RENDER;
	}
	else{
		glutSwapBuffers();
	}
}

void reshape(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble)w/(GLdouble)h, 1.0, 1000.0);
    glViewport(0,0,w,h);
}

void handleMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		cursorX = x;
		cursorY = y;
		mode=SELECT;
        mouseDown = true;
        prevX = x - rotationY;
        prevY = y - rotationX;
    }else{
        mouseDown = false;
    }
	glutPostRedisplay();
}

void handleMouseMotion(int x, int y){
    if(mouseDown){
        rotationX = y - prevY;
        rotationY = x - prevX;
        glutPostRedisplay();
    }
}

void handleKey(unsigned char key, int x, int y){
   if(key == 'z') viewer[2]-= 10;
   if(key == 'Z') viewer[2]+= 10;

   if(key == '+'){
	   if(dimensionActual<MAX){ 
			dimensionActual+=1;
	   }
	   crearCuadricula();
   }
   if(key == '-'){
	   if(dimensionActual>MIN){
			dimensionActual-=1;
	   }
	   crearCuadricula();
   }

   if(key == 'p') pausa = !pausa;
   if(key == 'v') versionPuntos = !versionPuntos;
   if(key == 'w') wireframe = !wireframe;
   if(key == 'm') malla = !malla;

   glutPostRedisplay();
}


void init(void){
    glEnable(GL_DEPTH_TEST);
	crearCuadricula();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Isosuperficies");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(handleMouse);
    glutMotionFunc(handleMouseMotion);
    glutKeyboardFunc(handleKey);
    init();
   glutMainLoop();
}


