/***************************************************
Materia:	Gráficas Computacionales
Tarea:	    HeightMaps
Fecha:		22 de Noviembre del 2012
Autor:      Marco Chavez	
***************************************************/

#include <math.h>
#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <GL/glut.h>
#include "Particula.h"

#define TEXTURE_WIDTH  256
#define TEXTURE_HEIGHT 256

char* fileTexName = "hm2.ppm";

GLuint texName=0;
unsigned char texture[TEXTURE_WIDTH][TEXTURE_HEIGHT][3];

#define MAX 100
#define MIN 3

float rotationX=0.0;
float rotationY=0.0;
float prevX=0.0;
float prevY=0.0;
bool mouseDown=false;
float viewer[]= {0.0, 0.0, 200.0};

Particula cuadricula[MAX][MAX];
int dimensionActual=50;
int limite = MAX;

//las mias para la malla
bool polygon=true;
bool puntos=false;
bool wire=true;
bool textura=true;
bool heightMaps=true;

#define RENDER					1
#define SELECT					2
int mode=RENDER;
int cursorX,cursorY;

//fuerzas
float delta=.01;
float gravedad[3]={0,-9.8,0};

//luces
bool smoothOn =true;
float light_ambient0[]={0.0f, 0.0f, 0.0f, 1.0f};
float light_diffuse0[]={1.0f, 1.0f, 1.0f, 1.0f};
float light_specular0[]={1.0f, 1.0f, 1.0f, 1.0f};
float light_position0[]={-1000.0f, 10.0f,1000.0f, 0.0f};
float light_ambient1[]={0.0f, 0.0f, 0.0f, 1.0f};
float light_diffuse1[]={1.0f, 1.0f, 1.0f, 1.0f};
float light_specular1[]={1.0f, 1.0f, 1.0f, 1.0f};
float light_position1[]={1000.0f, 10.0f,1000.0f, 0.0f};
float light_ambient2[]={0.0f, 0.0f, 0.0f, 1.0f};
float light_diffuse2[]={1.0f, 1.0f, 1.0f, 1.0f};
float light_specular2[]={1.0f, 1.0f, 1.0f, 1.0f};
float light_position2[]={0.0f, 10.0f,-1000.0f, 0.0f};
//material creo
const GLfloat mat_ambient[]    = { .1f, 0.18725f, 0.1745f, .8f };
const GLfloat mat_diffuse[]    = { 0.396f, 0.74151f, 0.69102f, .8f };
const GLfloat mat_specular[]   = { .297254f, .30829f, .306678f, .8f };
const GLfloat high_shininess[] = { 12.8f };
const GLfloat mat_ambientb[]    = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
const GLfloat mat_diffuseb[]    = { 1.0f, 0.2775f, 0.2775f, 1.0f };
const GLfloat mat_specularb[]   = { .773911f, .773911f, .773911f, 1.0f };
const GLfloat high_shininessb[] = { 89.6f };


void vectorizar(float* v1, float* v2, float *dududu){
	dududu[0]=v2[0]-v1[0];
	dududu[1]=v2[1]-v1[1];
	dududu[2]=v2[2]-v1[2];
}

void crearCuadricula(void){
	float posicion[3];
	float incremento=(float)limite/(float)(dimensionActual);
	int id;
    for(int renglon=0; renglon<dimensionActual; renglon++){
		for(int columna=0; columna<dimensionActual; columna++){
			id=((dimensionActual*renglon)+columna)+1;
			posicion[0]=renglon*incremento-(limite/2.0)+(incremento/2.0);
			posicion[1]=0;
			posicion[2]=columna*incremento-(limite/2.0)+(incremento/2.0);
			cuadricula[renglon][columna]=Particula(id,posicion);
        }
    }
}

void dibujarCuadricula(void){
	glPointSize(1);
	glBegin(GL_POINTS);
		for(int renglon=0; renglon<dimensionActual; renglon++){
			for(int columna=0; columna<dimensionActual; columna++){
				glColor3f(1,1,1);
				glVertex3fv(cuadricula[renglon][columna].getPosicion());				
			}
		}
    glEnd();
}

void calcularAltura(void){
		for(int renglon=0; renglon<dimensionActual; renglon++){
			for(int columna=0; columna<dimensionActual; columna++){

				int indiceX = (float)renglon/dimensionActual * TEXTURE_WIDTH;
				int indiceY = (float)columna/dimensionActual * TEXTURE_HEIGHT;
				float altura = texture[indiceX][indiceY][0]/5.0;
				//printf("iX:%i, iY:%i, altura: %f\n",indiceX, indiceY, altura);
				Particula *p = &cuadricula[renglon][columna];
				p->getPosicion()[1] = altura;
			}
		}
}

void limpiarAltura(void){
		for(int renglon=0; renglon<dimensionActual; renglon++){
			for(int columna=0; columna<dimensionActual; columna++){
				cuadricula[renglon][columna].getPosicion()[1] = 0;
			}
		}
}

float* calcularVectorNormal(Particula* a, Particula* b, Particula* c, float* normal){
	Particula *p1 = a;
	Particula *p2 = b;
	Particula *p3 = c;

	float ux = p2->getPosicion()[0] - p1->getPosicion()[0];
	float uy = p2->getPosicion()[1] - p1->getPosicion()[1];
	float uz = p2->getPosicion()[2] - p1->getPosicion()[2];

	float vx = p3->getPosicion()[0] - p1->getPosicion()[0];
	float vy = p3->getPosicion()[1] - p1->getPosicion()[1];
	float vz = p3->getPosicion()[2] - p1->getPosicion()[2];

	float nx = (uy*vz - uz*vy);
	float ny = (uz*vx - ux*vz);
	float nz = (ux*vy - uy*vx);

	/* Normalizando el vector  N = (x,y,z) a  û = ( x/w, y/w, z/w) donde w = (x^2+y^2+z^2)^(1/2) */
	float w = sqrt( pow(nx,2) + pow(ny,2) + pow(nz,2) );

	/* Vector unitario de û */
	normal[0] =  nx / w;
	normal[1] =  ny / w;
	normal[2] =  nz / w;
	//printf("x: %f, y: %f,z: %f\n",normal[0],normal[1],normal[2]);
	return normal;
}

void calcularNormales(){
	float normal1[3];
	float normal2[3];
	Particula* a;
	Particula* b;
	Particula* c;

	for(int renglon=0; renglon<dimensionActual-1; renglon++){
		for(int columna=0; columna<dimensionActual-1; columna++){

			a=&cuadricula[renglon][columna+1];
			b=&cuadricula[renglon][columna];
			c=&cuadricula[renglon+1][columna+1];
			calcularVectorNormal(a,b,c,normal1);
			a->addNormal(normal1);
			b->addNormal(normal1);
			c->addNormal(normal1);

			a=&cuadricula[renglon+1][columna];
			b=&cuadricula[renglon+1][columna+1];
			c=&cuadricula[renglon][columna];
			calcularVectorNormal(a,b,c,normal2);
			a->addNormal(normal2);
			b->addNormal(normal2);
			c->addNormal(normal2);
		}
	}
}

void limpiarNormales(){
	for(int renglon=0; renglon<dimensionActual; renglon++){
		for(int columna=0; columna<dimensionActual; columna++){
			cuadricula[renglon][columna].clearNormal();
		}
	}
}

void dibujarMalla(){
	glColor3f(0,1,0);

	calcularNormales();

	float tamanioCuadro = 1.0/dimensionActual;
	float cordActualX, cordActualY = 1.0;

	for(int renglon=0; renglon<dimensionActual-1; renglon++){

		cordActualX = 0.0;
		for(int columna=0; columna<dimensionActual-1; columna++){
			
			glBegin(GL_TRIANGLES);
				glNormal3fv(cuadricula[renglon][columna].getVectorUnitario());
				glTexCoord2f(cordActualX, cordActualY);
				glVertex3fv(cuadricula[renglon][columna].getPosicion());

				glNormal3fv(cuadricula[renglon][columna+1].getVectorUnitario());
				glTexCoord2f(cordActualX + tamanioCuadro, cordActualY);
				glVertex3fv(cuadricula[renglon][columna+1].getPosicion());

				glNormal3fv(cuadricula[renglon+1][columna+1].getVectorUnitario());
				glTexCoord2f(cordActualX + tamanioCuadro, cordActualY - tamanioCuadro);
				glVertex3fv(cuadricula[renglon+1][columna+1].getPosicion());
			glEnd();

			glBegin(GL_TRIANGLES);

				glNormal3fv(cuadricula[renglon][columna].getVectorUnitario());
				glTexCoord2f(cordActualX, cordActualY);
				glVertex3fv(cuadricula[renglon][columna].getPosicion());

				glNormal3fv(cuadricula[renglon+1][columna+1].getVectorUnitario());
				glTexCoord2f(cordActualX + tamanioCuadro, cordActualY - tamanioCuadro);
				glVertex3fv(cuadricula[renglon+1][columna+1].getPosicion());

				glNormal3fv(cuadricula[renglon+1][columna].getVectorUnitario());
				glTexCoord2f(cordActualX, cordActualY - tamanioCuadro);
				glVertex3fv(cuadricula[renglon+1][columna].getPosicion());
			glEnd();

			cordActualX += tamanioCuadro;
		}
		cordActualY -= tamanioCuadro;
	}

	limpiarNormales();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,1,0);

    glRotatef(rotationX,1,0,0);
    glRotatef(rotationY,0,1,0);

	if(polygon)
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	if(textura)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);

	if (mode == SELECT){

		
		glDisable(GL_TEXTURE_2D);

		glDisable(GL_LIGHTING);
	    glDisable(GL_LIGHT0);
	    glDisable(GL_LIGHT1);
	    glDisable(GL_LIGHT2);

		mode = RENDER;

		glEnable(GL_TEXTURE_2D);
	}else{

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);

		if(wire){
			dibujarMalla();
		}
		if(puntos){
			dibujarCuadricula();
		}
		glutSwapBuffers();
	}
}


void initTextureFile(){
   int w, h, d;
   FILE *fp;
   int i, j, k;
   fp = fopen(fileTexName,"rb");
   if (fp!=NULL){
		fputs ("fopen example",fp);
		fscanf(fp,"%s ");
		fscanf(fp,"%d %d %d ", &w, &h, &d) ;
		printf("%d %d %d",w, h, d);
		for (i = 0 ; i < w ; i++)
			for (j = 0 ; j < h ; j++)
				for (k = 0 ; k < 3 ; k++)
					fscanf(fp,"%c",&(texture[i][j][k])) ;
		fclose(fp) ;

		glGenTextures(1, &texName) ;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) ;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) ;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) ;

		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGB,GL_UNSIGNED_BYTE, texture);

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

	bool recalcular = false;

   if(key == 'z') viewer[2]-= 2;
   if(key == 'Z') viewer[2]+= 2;

   if(key == '+') 
	   if(dimensionActual<MAX) {
		   dimensionActual+=1;
		   recalcular =true;
	   }
   if(key == '-') 
	   if(dimensionActual>MIN) {
		   dimensionActual-=1;
		   recalcular =true;
	   }
	if(key == 'w'){
		wire=!wire;
		 recalcular = false;
	}
	if(key == 't'){
		polygon=!polygon;
		 recalcular = false;
	}
	if(key == 'p'){
		puntos=!puntos;
		 recalcular = false;
	}
	if ((key == 's') || (key == 'S')){
		smoothOn = !smoothOn;

		if (smoothOn)
			glShadeModel(GL_SMOOTH);
		else
			glShadeModel(GL_FLAT);

		recalcular = false;
	}

	if(key == 'i'){
		recalcular= true;
	}

	if(key == 'g'){

		light_position0[0] = light_position0[0]+100;
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	 recalcular = false;

	}
	if(key == 'j'){
	     light_position0[0] = light_position0[0]-100;
		 glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
		  recalcular = false;
	}
	if(key == 'y'){
		light_position0[0] = light_position0[2]+100;
		 glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
		  recalcular = false;
	}

	if(key == 'n'){
		light_position0[0] = light_position0[2]-100;
		 glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
		 bool recalcular = false;
	}

	if(key == 'u'){
		textura = !textura;
	}

	if(key == 'h'){
		heightMaps=!heightMaps;
	}

	if(recalcular){
		crearCuadricula();
	}

	if(heightMaps){
		calcularAltura();
	}else{
		limpiarAltura();
	}
  
   glutPostRedisplay();
}


void init(void){
    glEnable(GL_DEPTH_TEST);
	//luces
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glMaterialfv(GL_BACK, GL_AMBIENT,   mat_ambientb);
	glMaterialfv(GL_BACK, GL_DIFFUSE,   mat_diffuseb);
	glMaterialfv(GL_BACK, GL_SPECULAR,  mat_specularb);
	glMaterialfv(GL_BACK, GL_SHININESS, high_shininessb);

	
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texName);

	crearCuadricula();
	initTextureFile();
	calcularAltura();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Telas Poncho");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(handleMouse);
    glutMotionFunc(handleMouseMotion);
    glutKeyboardFunc(handleKey);
	init();
	glutMainLoop();
}