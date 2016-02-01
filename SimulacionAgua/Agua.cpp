#include <stdlib.h>
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GLUT/glut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/glut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") // Compiler directive to include the GLEW library.
#endif

#include <stdio.h>
#include <math.h>

#include "ttable.h"							// Tabla de triángulos comprendido en el algoritmo de Marching Cubes

#define MB_DETAIL		40					//Número de divisiones del cubo usado por el algoritmo de Marching Cubes (mientras más alto, más suave es la superficie y más tardada de calcular)
#define MB_METABALLS	0.5					//Número que determina el tamaño de las esferas (mientras más alto, mayor el radio)

static int programHandle; // Reference to program object.
static int vertexShaderHandle; // Reference to vertex shader object.
static int fragmentShaderHandle; // Reference to fragment shader object.

bool mouseDown = false;						//Variables usadas para rotar toda la escena alrededor de los ejes X, Y
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;


typedef struct {							// Un vértice guarda su posición y normal
	float  x, y, z;|
	float nx,ny,nz;
} vertex_type;

typedef struct {							// Una cara triangular guarda los índices de los 3 vértices que la forman
	int v1,v2,v3;
} face_type;

vertex_type *vertex;						// Lista de vértices
int			nb_vertices;					// Número de vértices

face_type	*face;							// Lista de caras
int			nb_faces;						// Número de caras

int         *vertices_grid;					// Tabla con los índices de los vértices que se encuentran en la cuadrícula 3D
float		*pot_grid;						// Tabla con los potenciales en cada vértice de la cuadrícula 3D

float		mbx1,mbx2,mby1,mby2,mbz1,mbz2;	// Límites de cálculo (x mínima, x máxima, y mínima, y máxima, z mínima, z máxima)
int			mbnx,mbny,mbnz;					// Número de cubos usados en x, y, z  (en este código usan el valor de MB_DETAIL para inicializar las 3 variables)
int			mbnx_x_mbny,mbnx_x_mbny_x_mbnz;	// Números usados frecuentemente
float		mbk;							// Valor del equipotencial


int edge[12*4] = { 0,0,0,0, 0,0,1,0, 0,0,0,1, 0,0,1,1,
				   1,0,0,0, 1,1,0,0, 1,0,0,1, 1,1,0,1,
                   2,0,0,0, 2,1,0,0, 2,0,1,0, 2,1,1,0  };


#define PART_MAX  1000						   // Número máximo de particulas que puede haber 
int num_parts=0;							   // Número actual de partículas (esqueletos)
float tx[PART_MAX],ty[PART_MAX],tz[PART_MAX];  // Arreglos con las coordenadas de las partículas (x,y,z)

void dibujarCaja()
{
	
	// Material property vectors.
    float matAmbAndDif[] = {1.0, 0.0, 0.0, 1.0};
    float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float matShine[] = { 50.0 };

    // Material properties.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	// Material property vectors.
    float matAmbAndDifb[] = {0.0, 1.0, 0.0, .1};
    float matSpecb[] = { .5, .5, .5, .1 };
    float matShineb[] = { 50.0 };

    // Material properties.
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifb);
    glMaterialfv(GL_BACK, GL_SPECULAR, matSpecb);
    glMaterialfv(GL_BACK, GL_SHININESS, matShineb);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor4f(0,1,0,.5);

	glPushMatrix();
		glTranslatef(+0,-4,+0);
		glBegin(GL_QUADS);
			glVertex3f(-4,+0,-4);
			glVertex3f(+4,+0,-4);
			glVertex3f(+4,+0,+4);
			glVertex3f(-4,+0,+4);
		glEnd();
	glPopMatrix();
	
}

void display(void)
{
	glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  	
	gluLookAt(0.0,0.0,20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  // La cámara está 20 unidades atrás para ver la escena completa

    glRotatef(xrot, 1.0f, 0.0f, 0.0f);			// Rotación general alrededor del eje X
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);			// Rotación general alrededor del eje Y

    dibujarCaja();

		// Material property vectors.
	   float matAmbAndDif[] = {0.0, 0.0, 1.0, 1.0};
	   float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	   float matShine[] = { 50.0 };

	   // Material properties.
	   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

	   GLfloat emission[] = {0.0, 0.0, 0.3, 1.0};
	   glMaterialfv(GL_FRONT, GL_EMISSION, emission);

	   glColor3f(1,0,1);

		// Dibujo de las caras
		glBegin(GL_TRIANGLES);
		for (int i=0; i<nb_faces; i++) {
			glVertex3f(vertex[face[i].v1].x,vertex[face[i].v1].y,vertex[face[i].v1].z);
			glVertex3f(vertex[face[i].v2].x,vertex[face[i].v2].y,vertex[face[i].v2].z);
			glVertex3f(vertex[face[i].v3].x,vertex[face[i].v3].y,vertex[face[i].v3].z);
		}
		glEnd();

	glutSwapBuffers();
	glFlush ();
}

void reshape (int w, int h)
{
	glViewport (0, 0, w, h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0,(float)w/(float)h,1.0,100.0);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:								// Terminar y cerrar la ventana con ESC
			exit(0);
		break;

		case 'n':								// Con la tecla n se crea una nueva partícula (esqueleto) en el centro
			if(num_parts==PART_MAX)				// Sólo se crea si no se ha excedido el número máximo de partículas
				break;
			tx[num_parts]=0;
			ty[num_parts]=0;
			tz[num_parts]=0;
			num_parts++;
		break;
   }
}

#define f(i,j,k) pot_grid[(i)+(j)*(mbnx+1)+(k)*(mbnx_x_mbny+mbnx+mbny+1)]

void compute_f()
{
	int i,j,k, p;
	float x,y,z;
	float deltax,deltay,deltaz;
	int index;

	deltax = (mbx2-mbx1) / mbnx;      // Se calcula cuántas unidades tiene cada cubito de la cuadrícula 3D a lo ancho, alto y profundidad
	deltay = (mby2-mby1) / mbny;
	deltaz = (mbz2-mbz1) / mbnz;

	// Se recorre la cuadrícula 3D
	z = mbz1;
	for (k=0; k<=mbnz; k++) {
		y = mby1;
		for (j=0; j<=mbny; j++) {
			x = mbx1;
			for (i=0; i<=mbnx; i++) {
				index = i+j*(mbnx+1)+k*(mbnx+1)*(mbny+1);

				pot_grid[index] = 0.0;    // Se inicializa en 0 el potencial en ese vértice de la cuadrícula

				for(p=0;p<num_parts;p++) {  // Se aculuma la aportación de cada partícula (esqueleto).  La suma da un valor escalar que corresponde al potencial en ese vértice de la cuadrícula 3D
					pot_grid[index] += 
						MB_METABALLS*MB_METABALLS/((x-tx[p])*(x-tx[p]) + (y+ty[p])*(y+ty[p]) + (z-tz[p])*(z-tz[p]));  // El denominador es la distancia que hay del vértice de la cuadrícula 3D a la partícula (esqueleto) en cuestión, al cuadrado.
					                                                                                                  // Podrían cambiar a otra función de blending como la de Gauss
				}

				x += deltax;
			}
			y+= deltay;
		}
		z += deltaz;
	}
}


// Esta función se manda llamar sólo una vez en el main.
// Sirve para abrir espacio para las listas de vértices y caras, y para las tablas de índices y potenciales.
// También inicializa los límites del cubo de Marching Cubes y el equipotencial
void init_marching_cubes(float x1,float x2,float y1,float y2,float z1,float z2,int m,int n,int p,float pot)
{
	int i,j,k;
	if ( !(vertices_grid = (int *) malloc(sizeof(int)*3*m*n*p)) ) {
		printf("Problemas con el malloc al apartar memoria para la tabla de índices de los vértices!\n");
		exit(-1);
	}
	if ( !(vertex = (vertex_type *) malloc(sizeof(vertex_type)*3*m*n*p)) ) {
		printf("Problemas con el malloc al apartar memoria para los vértices!\n");
		exit(-1);
	}
	if ( !(face = (face_type *) malloc(sizeof(face_type)*4*m*n*p)) ) {
		printf("Problemas con el malloc al apartar memoria para las caras!\n");
		exit(-1);
	}
	if ( !(pot_grid = (float *) malloc(sizeof(float)*4*(m+1)*(n+1)*(p+1))) ) {
		printf("Problemas con el malloc al apartar memoria para la tabla de potenciales!\n");
		exit(-1);
	}

	mbx1 = x1; mbx2 = x2; mbnx = m;			// Inicialización de los límites en el eje X y el número de cubitos en X
	mby1 = y1; mby2 = y2; mbny = n;			// Inicialización de los límites en el eje Y y el número de cubitos en Y
	mbz1 = z1; mbz2 = z2; mbnz = p;			// Inicialización de los límites en el eje Z y el número de cubitos en Z
	mbnx_x_mbny = mbnx * mbny;
	mbnx_x_mbny_x_mbnz = mbnx * mbny * mbnz;
	mbk  = pot;								// Inicialización del equipotencial
	for (k=0; k<=mbnz; k++) 
		for (j=0; j<=mbny; j++) 
			for (i=0; i<=mbnx; i++) 
				pot_grid[i+j*(mbnx+1)+k*(mbnx+1)*(mbny+1)] = 0.0;   // Inicialización de los potenciales de todos los vértices de la cuadrícula 3D a 0.0

}

// Algoritmo de Marching Cubes
void marching_cubes()
{
	float deltax,deltay,deltaz;
	float x,y,z;
	float ax,ay,az,bx,by,bz,nx,ny,nz,n;
	float f1,f2;
	int i,j,k,l;
	int v1,v2,v3;
	float coef;
	int index;
	int eindex;		// Índice de la arista

	nb_vertices = 0;
	nb_faces = 0;
	compute_f();

	deltax = (mbx2-mbx1) / mbnx;
	deltay = (mby2-mby1) / mbny;
	deltaz = (mbz2-mbz1) / mbnz;

	// Cálculo de la posición de los vértices (los vértices pertenecientes a los planos x = x2, y = y2 et z = z2 no se calculan)
	z = mbz1;
	for (k=0; k<mbnz; k++) {
		y = mby1;
		for (j=0; j<mbny; j++) {
			x = mbx1;
			for (i=0; i<mbnx; i++) {
				index = i+j*(mbnx+1)+k*(mbnx_x_mbny+mbnx+mbny+1);
				f1 = pot_grid[index];
				f2 = pot_grid[index+1];
				if ( ((f1 >= mbk) && (f2 < mbk)) || ((f1 < mbk) && (f2 >= mbk)) ) {
					vertices_grid[i+j*mbnx+k*mbnx_x_mbny+0] = nb_vertices;
					vertex[nb_vertices].nx = 0.0;
					vertex[nb_vertices].ny = 0.0;
					vertex[nb_vertices].nz = 0.0;
					coef = (mbk-f1) / (f2-f1);
					vertex[nb_vertices].x = x + deltax*coef;
					vertex[nb_vertices].y = y;
					vertex[nb_vertices].z = z;
					nb_vertices++;
				}
				f1 = pot_grid[index];
				f2 = pot_grid[index+mbnx+1];
				if ( ((f1 >= mbk) && (f2 < mbk)) || ((f1 < mbk) && (f2 >= mbk)) ) {
					vertices_grid[i+j*mbnx+k*mbnx_x_mbny+mbnx_x_mbny_x_mbnz] = nb_vertices;
					vertex[nb_vertices].nx = 0.0;
					vertex[nb_vertices].ny = 0.0;
					vertex[nb_vertices].nz = 0.0;
					coef = (mbk-f1) / (f2-f1);
					vertex[nb_vertices].x = x;
					vertex[nb_vertices].y = y + deltay*coef;
					vertex[nb_vertices].z = z;
					nb_vertices++;
				}

				f1 = pot_grid[index];
				f2 = pot_grid[index+mbnx_x_mbny+mbnx+mbny+1];
				if ( ((f1 >= mbk) && (f2 < mbk)) || ((f1 < mbk) && (f2 >= mbk)) ) {
					vertices_grid[i+j*mbnx+k*mbnx_x_mbny+mbnx_x_mbny_x_mbnz+mbnx_x_mbny_x_mbnz] = nb_vertices;
					vertex[nb_vertices].nx = 0.0;
					vertex[nb_vertices].ny = 0.0;
					vertex[nb_vertices].nz = 0.0;
					coef = (mbk-f1) / (f2-f1);
					vertex[nb_vertices].x = x;
					vertex[nb_vertices].y = y;
					vertex[nb_vertices].z = z + deltaz*coef;
					nb_vertices++;
				} 	
				x += deltax;
			}
			y += deltay;
		}
		z += deltaz;
	}

	// Cálculo de las caras y de las normales en los vértices
	z = mbz1;
	for (k=0; k<mbnz-1; k++) {
		y = mby1;
		for (j=0; j<mbny-1; j++) {
			x = mbx1;
			for (i=0; i<mbnx-1; i++) {
				// Mira a que cubo corresponde 
				index  = ((f(i  ,j  ,k  ) >= mbk)?0x01:0x00);
				index |= ((f(i+1,j  ,k  ) >= mbk)?0x02:0x00);
				index |= ((f(i  ,j+1,k  ) >= mbk)?0x04:0x00);
				index |= ((f(i+1,j+1,k  ) >= mbk)?0x08:0x00);
				index |= ((f(i  ,j  ,k+1) >= mbk)?0x10:0x00);
				index |= ((f(i+1,j  ,k+1) >= mbk)?0x20:0x00);
				index |= ((f(i  ,j+1,k+1) >= mbk)?0x40:0x00);
				index |= ((f(i+1,j+1,k+1) >= mbk)?0x80:0x00);
				index *= 12;

				for (l=0; l<4; l++) {
					if (triangle[index+l*3] != triangle[index+l*3+1]) {
						// Creación de una nueva cara
						eindex = triangle[index+l*3]*4;
						v1 = face[nb_faces].v1 = vertices_grid[i+edge[eindex+1]+(j+edge[eindex+2])*mbnx+(k+edge[eindex+3])*mbnx_x_mbny+edge[eindex]*mbnx_x_mbny_x_mbnz];
						eindex = triangle[index+l*3+1]*4;
						v2 = face[nb_faces].v2 = vertices_grid[i+edge[eindex+1]+(j+edge[eindex+2])*mbnx+(k+edge[eindex+3])*mbnx_x_mbny+edge[eindex]*mbnx_x_mbny_x_mbnz];
						eindex = triangle[index+l*3+2]*4;
						v3 = face[nb_faces].v3 = vertices_grid[i+edge[eindex+1]+(j+edge[eindex+2])*mbnx+(k+edge[eindex+3])*mbnx_x_mbny+edge[eindex]*mbnx_x_mbny_x_mbnz];

						// Actualización de las normales de los vértices que pertenecen a la nueva cara
						ax = vertex[v2].x - vertex[v1].x;
						ay = vertex[v2].y - vertex[v1].y;
						az = vertex[v2].z - vertex[v1].z;
						bx = vertex[v3].x - vertex[v1].x;
						by = vertex[v3].y - vertex[v1].y;
						bz = vertex[v3].z - vertex[v1].z;
						nx = ay*bz - az*by;
						ny = az*bx - ax*bz;
						nz = ax*by - ay*bx;
						n = sqrt(nx*nx+ny*ny+nz*nz);
						if (n != 0.0) {
							n = 1.0/n;
							nx *= n; ny *= n; nz *= n;
						}
						vertex[v1].nx += nx; vertex[v1].ny += ny; vertex[v1].nz += nz;
						vertex[v2].nx += nx; vertex[v2].ny += ny; vertex[v2].nz += nz;
						vertex[v3].nx += nx; vertex[v3].ny += ny; vertex[v3].nz += nz;
						nb_faces++;
					}
				}
				x += deltax;
			}
			y += deltay;
		}
		z += deltaz;
	}

	// Normalización de las normales
	for (i=0; i<nb_vertices; i++) {
		n = sqrt(vertex[i].nx*vertex[i].nx + vertex[i].ny*vertex[i].ny + vertex[i].nz*vertex[i].nz );
		if (n != 0.0) {
			n = 1.0/n;
			vertex[i].nx *= n; vertex[i].ny *= n; vertex[i].nz *= n;
		}
	}
}


// Cada vez que OpenGL no tiene eventos que manejar (está ocioso) se manda llamar esta función
void idle(void)
{
	// Para cada partícula (esqueleto) actualizar su posición
	// En este caso sólo se suma 0.1 en X
	for(int p=0;p<num_parts;p++) {
	    tx[p]+=0.1;
	}

	// Se manda llamar el algoritmo de Marching Cubos para recalcular la superficie
	marching_cubes();
	// Se dibuja de nuevo
	glutPostRedisplay();
}

// Para rotar la escena completa al arrastrar el mouse
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;
        
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
}

// Para rotar la escena completa al arrastrar el mouse
void mouseMotion(int x, int y)
{
    if (mouseDown)
    {
        yrot = x - xdiff;
        xrot = y + ydiff;
        
        glutPostRedisplay();
    }
}

// Function to read a shader file.
char* readShader(char* aShaderFile)
{
   FILE* filePointer = fopen(aShaderFile, "rb");	
   char* content = NULL;
   long numVal = 0;

   fseek(filePointer, 0L, SEEK_END);
   numVal = ftell(filePointer);
   fseek(filePointer, 0L, SEEK_SET);
   content = (char*) malloc((numVal+1) * sizeof(char)); 
   fread(content, 1, numVal, filePointer);
   content[numVal] = '\0';
   fclose(filePointer);
   return content;
}

// Function to initialize shaders.
void setShaders(char* vertexShaderFile, char* fragmentShaderFile)  
{
   char* vertexShader = readShader(vertexShaderFile);
   char* fragmentShader = readShader(fragmentShaderFile);

   programHandle = glCreateProgram();
   vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
   fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

   glShaderSource(vertexShaderHandle, 1, (const char**) &vertexShader, NULL);
   glShaderSource(fragmentShaderHandle, 1, (const char**) &fragmentShader, NULL);

   glCompileShader(vertexShaderHandle);
   glCompileShader(fragmentShaderHandle);

   glAttachShader(programHandle, vertexShaderHandle);
   glAttachShader(programHandle, fragmentShaderHandle);

   glLinkProgram(programHandle);
   glUseProgram(programHandle);
}

// Initialization routine.
void setup(void)
{    
   //glClearColor (1.0, 1.0, 1.0, 1.0);	
   glClearColor (0.0, 0.0, 0.0, 1.0);
   //glEnable(GL_DEPTH_TEST); // Enable depth testing.

   //Turn on Alpha channel
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // Turn on OpenGL lighting.
   glEnable(GL_LIGHTING); 

   // Automatically resize all normals to unit length.
   glEnable(GL_NORMALIZE); 

   // Light property vectors.
   float lightAmb[] = {0.0, 0.0, 0.0, 1.0 };
   float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 0.0 };
   float lightPos[] = {0.0, 10.0, 10.0, 0.0 };
   float globAmb[] = { 0.3, 0.3, 0.3, 1.0 };

   // Light properties.
   glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
   glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

   glEnable(GL_LIGHT0); // Enable particular light source.
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

	// Material property vectors.

   float matAmbAndDif[] = {1.0, 0.0, 0.0, 0.1};
   float matSpec[] = { 1.0, 1.0, 1.0, 0.1 };
   float matShine[] = { 50.0 };

   // Material properties.
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

   // Material property vectors.
   /*float frontMatAmbAndDif[] = {0.0, 1.0, 0.0, 0.0};
   float frontMatSpec[] = { 0.0, 1.0, 0.0, 0.0 };
   float frontMatShine[] = { 100.0 };
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, frontMatAmbAndDif);
   glMaterialfv(GL_FRONT, GL_SPECULAR, frontMatSpec);
   glMaterialfv(GL_FRONT, GL_SHININESS, frontMatShine);*/
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (262, 134);
	glutCreateWindow ("Superficies Implícitas 3D");

	setup();

	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
	
	// Inicializar Marching Cubes mandando las dimensiones del cubo, la cantidad de subdivisiones en X, Y, Z, y el equipotencial
	init_marching_cubes(-4.0,4.0,-4.0,4.0,-4.0,4.0,MB_DETAIL,MB_DETAIL,MB_DETAIL,2.0);
	marching_cubes();
	
	glewInit();
    setShaders("perPixelLightingSimple.vs", "perPixelLightingSimple.fs");

	glutMainLoop();
	return 1;
}
