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
#define MAX_VALOR 40

float rotationX=0.0;
float rotationY=0.0;
float prevX=0.0;
float prevY=0.0;
bool mouseDown=false,
	dibuajarPuntosFuera = true,
	dibuajarPuntosDentro = true,
	dibuajarPuntosSuperf = true,
	dibuajarPuntosEsquel = true,
	pausa = false,
	versionPuntos = false,
	wireframe = false,
	marchingSquares = true,
	dibujarContornoBold = true;
float viewer[]= {0.0, 0.0, 200.0};

Punto cuadricula[MAX][MAX];
int dimensionActual=50;
int limite = MAX;

Punto esqueletos[20];
float pesos[20];
int cantidadEsqueletos = 2;

float a = 0.01;
float b = 5;
float t = 3;

float gauss(float d){
	return (b * exp(-a*d*d));
}

float distancia(Punto p1, Punto p2){
	float x1 = p1.getX();
	float y1 = p1.getY();
	float x2 = p2.getX();
	float y2 = p2.getY();

	return  sqrt( pow(x2-x1,2) + pow(y2-y1,2) );
}

float calcularValor(int renglon, int columna){
	Punto p1 = cuadricula[renglon][columna];
	float suma = 0.0;
	for(int i=0; i<cantidadEsqueletos; i++){
		Punto p2 = esqueletos[i];
		suma += pesos[i]*gauss(distancia(p1, p2));
	}
	return suma-t;
}

void crearEsqueletos(void){
	float x,y,vx,vy;
	srand(time(0));
	cantidadEsqueletos = (rand()%20+1);
	for(int i= 0; i<cantidadEsqueletos; i++){
		x = rand()%30;
		y = rand()%30;
		vx = rand()%2+1;
		vy = rand()%2+1;
		esqueletos[i] = Punto(x,y,3,255,0,0,vx,vy);
		pesos[i] = rand()%5+1;
	}
	
}

void dibujarEsqueletos(void){
	if(!dibuajarPuntosEsquel)
		return;

	glPointSize(6);
	glBegin(GL_POINTS);
	for(int i=0; i<cantidadEsqueletos; i++){
		Punto p = esqueletos[i];
		glColor3ub(p.getR(),p.getG(),p.getB());
		glVertex3f(p.getX(),p.getY(),p.getZ());
	}
    glEnd();
}

void moverEsqueletos(void){

	if(pausa)
		return;

	for(int i=0; i<cantidadEsqueletos; i++){
		Punto e = esqueletos[i];
		float nuevaX = e.getX() + e.getVx();
		float nuevaY = e.getY() + e.getVy();
		float nuevaZ = e.getZ();
		esqueletos[i].setXYZ(nuevaX,nuevaY,nuevaZ);

		if(nuevaX > 40 || nuevaX < -40)
			esqueletos[i].setVx(-e.getVx());
		if(nuevaY > 40 || nuevaY < -40)
			esqueletos[i].setVy(-e.getVy());
	}
	glutPostRedisplay();
}

void crearCuadricula(void){
	int r=0;
	int g=0;
	int b=255;
	float z=0.0;
	float vx=0;
	float vy=0;

	float incremento=(float)limite/(float)(dimensionActual);

    for(int renglon=0; renglon<dimensionActual; renglon++){
		for(int columna=0; columna<dimensionActual; columna++){
			float x=columna*incremento-(limite/2.0)+(incremento/2.0);
			float y=renglon*incremento-(limite/2.0)+(incremento/2.0);
			cuadricula[renglon][columna]=Punto(x,y,z,r,g,b,vx,vy);
        }
    }
}

void getColorCromatico(float valor, Punto *p){
	/*
		Azul		0,0,1
		Cyan		0,1,1
		Verde		0,1,0
		Amarillo	1,1,0
		Rojo		1,0,0
	*/
	float div = MAX_VALOR/4.0;
	float rango = valor-(int(valor/div))*div;
	int valorColor = rango/div*255;

	if(valor < div*1){
		//Azul a Cyan
		p->setColor(0,valorColor,255);
	}else
	if(valor < div*2){
		//Cyan a Verde
		p->setColor(0,255,255-valorColor);
	}else
	if(valor < div*3){
		//Verde a Amarillo
		p->setColor(valorColor,255,0);
	}else
	if(valor < div*4){
		//Amarillo a Rojo
		p->setColor(255,255-valorColor,0);
	}else{
		//Rojo
		p->setColor(255,0,0);
	}

}

void calcularColores(void){
		for(int renglon=0; renglon<dimensionActual; renglon++){
			for(int columna=0; columna<dimensionActual; columna++){

				float valor = calcularValor(renglon, columna);

				//Dibujar superficie
				if(valor > -1 && valor < 1){
					if(dibujarContornoBold)
						cuadricula[renglon][columna].setColor(0,0,0);
				}else

				//Dibujar puntos que están fuera de la superficie
				if(valor<0){
					if(dibuajarPuntosFuera)
						cuadricula[renglon][columna].setColor(0,0,255);
					else
						cuadricula[renglon][columna].setColor(0,0,0);

				//Dibujar puntos que estén dentro de la superficie
				}else{
					if(dibuajarPuntosDentro)
						getColorCromatico(valor,&cuadricula[renglon][columna]);
					else
						cuadricula[renglon][columna].setColor(0,0,0);
				}

				Punto p = cuadricula[renglon][columna];
				cuadricula[renglon][columna].setXYZ(p.getX(), p.getY(), valor);
			}
		}
}

void dibujarPuntos(void){
	glPointSize(2);
	glBegin(GL_POINTS);
		for(int renglon=0; renglon<dimensionActual; renglon++){
			for(int columna=0; columna<dimensionActual; columna++){
				Punto p = cuadricula[renglon][columna];
				glColor3ub(p.getR(), p.getG(), p.getB());
				glVertex3f(p.getX(), p.getY(), p.getZ());
			}
		}
    glEnd();
}

void rellenarCuadricula(void){

	for(int renglon=0; renglon<dimensionActual-1; renglon++){
		for(int columna=0; columna<dimensionActual-1; columna++){
				
			Punto p1 = cuadricula[renglon][columna];
			Punto p2 = cuadricula[renglon][columna+1];
			Punto p3 = cuadricula[renglon+1][columna+1];
			Punto p4 = cuadricula[renglon+1][columna];

			if(wireframe)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glBegin(GL_TRIANGLES);
				glColor3ub(p1.getR(), p1.getG(), p1.getB());
				glVertex3f(p1.getX(), p1.getY(), p1.getZ());

				glColor3ub(p2.getR(), p2.getG(), p2.getB());
				glVertex3f(p2.getX(), p2.getY(), p2.getZ());
					
				glColor3ub(p3.getR(), p3.getG(), p3.getB());
				glVertex3f(p3.getX(), p3.getY(), p3.getZ());
			glEnd();

			glBegin(GL_TRIANGLES);
				glColor3ub(p3.getR(), p3.getG(), p3.getB());
				glVertex3f(p3.getX(), p3.getY(), p3.getZ());

				glColor3ub(p4.getR(), p4.getG(), p4.getB());
				glVertex3f(p4.getX(), p4.getY(), p4.getZ());

				glColor3ub(p1.getR(), p1.getG(), p1.getB());
				glVertex3f(p1.getX(), p1.getY(), p1.getZ());
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

void dibujarSupMarchSquares(){
	glColor3f(1,1,1);
		for(int renglon=0; renglon<dimensionActual-1; renglon++){
			for(int columna=0; columna<dimensionActual-1; columna++){

				/*
					p1---p2
					 |	 |
					p4---p3
				*/
				Punto p1 = cuadricula[renglon][columna];
				Punto p2 = cuadricula[renglon][columna+1];
				Punto p3 = cuadricula[renglon+1][columna+1];
				Punto p4 = cuadricula[renglon+1][columna];
				Punto temp;

				glBegin(GL_LINES);

				if(p1.getZ() >= 0.0){
					if(p2.getZ() < 0.0){
						temp = calcularPuntoMedio(p1,p2);
						glVertex3f(temp.getX(), temp.getY(), temp.getZ());
					}
					if(p4.getZ() < 0.0){
						temp = calcularPuntoMedio(p1,p4);
						glVertex3f(temp.getX(), temp.getY(), temp.getZ());
					}
				}
				if(p2.getZ() >= 0.0){
					if(p3.getZ() < 0.0){
						temp = calcularPuntoMedio(p2,p3);
						glVertex3f(temp.getX(), temp.getY(), temp.getZ());
					}
					if(p1.getZ() < 0.0){
						temp = calcularPuntoMedio(p2,p1);
						glVertex3f(temp.getX(), temp.getY(), temp.getZ());
					}
				}
				if(p3.getZ() >= 0.0){
					if(p4.getZ() < 0.0){
						temp = calcularPuntoMedio(p3,p4);
						glVertex3f(temp.getX(), temp.getY(), temp.getZ());
					}
					if(p2.getZ() < 0.0){
						temp = calcularPuntoMedio(p3,p2);
						glVertex3f(temp.getX(), temp.getY(), temp.getZ());
					}
				}
				if(p4.getZ() >= 0.0){
					if(p3.getZ() < 0.0){
						temp = calcularPuntoMedio(p4,p3);
						glVertex3f(temp.getX(), temp.getY(), temp.getZ());
					}
					if(p1.getZ() < 0.0){
						temp = calcularPuntoMedio(p4,p1);
						glVertex3f(temp.getX(), temp.getY(), temp.getZ());
					}
				}
				glEnd();
			}
		}
}

void display(void){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,1,0);

    glRotatef(rotationX,1,0,0);
    glRotatef(rotationY,0,1,0);

	calcularColores();
	if(versionPuntos)
		dibujarPuntos();
	else
		rellenarCuadricula();
	dibujarEsqueletos();

	if(marchingSquares)
		dibujarSupMarchSquares();

    glutSwapBuffers();
}

void reshape(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble)w/(GLdouble)h, 1.0, 1000.0);
    glViewport(0,0,w,h);
}

void handleMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        mouseDown = true;
        prevX = x - rotationY;
        prevY = y - rotationX;
    }else{
        mouseDown = false;
    }
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
   }
   if(key == '-'){
	   if(dimensionActual>MIN){
			dimensionActual-=1;
	   }
   }

   if(key == 'i') crearEsqueletos();
   if(key == 'f') dibuajarPuntosFuera = !dibuajarPuntosFuera;
   if(key == 'd') dibuajarPuntosDentro = !dibuajarPuntosDentro;
   if(key == 's') dibuajarPuntosSuperf = !dibuajarPuntosSuperf;
   if(key == 'e') dibuajarPuntosEsquel = !dibuajarPuntosEsquel;
   if(key == 'p') pausa = !pausa;
   if(key == 'v') versionPuntos = !versionPuntos;
   if(key == 'w') wireframe = !wireframe;
   if(key == 's') marchingSquares = !marchingSquares;
   if(key == 'c') dibujarContornoBold = !dibujarContornoBold;

   crearCuadricula();
   glutPostRedisplay();
}


void init(void){
    glEnable(GL_DEPTH_TEST);
	crearCuadricula();
	crearEsqueletos();
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
	glutIdleFunc(moverEsqueletos);
    init();
   glutMainLoop();
}


