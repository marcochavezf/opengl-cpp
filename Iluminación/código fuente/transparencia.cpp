#include <windows.h>
#include <GL/glut.h>

void dibujarFiguras(){

    float mcolor[] = {1.0f, 0.0f, 0.0f,1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mcolor);
    glMateriali (GL_FRONT, GL_SHININESS, 128);
    glutSolidSphere(0.4,20,20);

    float mcolor2[] = {1.0f, 1.0f, 1.0f,0.3f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mcolor2);
    glMateriali (GL_FRONT, GL_SHININESS, 128);
    glutSolidSphere(0.8,20,20);
}

void myDisplay(){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

     dibujarFiguras();

     glFlush();
     glutSwapBuffers();
}

void init_light ()
{
  float global_ambient[] = {0.75f, 0.75f, 0.75f, 1.0f};
  glLightModelfv (GL_LIGHT_MODEL_AMBIENT, global_ambient);

  float light0_position[] = {100.0, 100.0, 100.0, 1.0};
  glLightfv (GL_LIGHT0, GL_POSITION, light0_position);

  float light0_ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};
  glLightfv (GL_LIGHT0, GL_AMBIENT, light0_ambient);

  float light0_diffuse[] = {0.90f, 0.90f, 1.0f, 1.0f};
  glLightfv (GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

  float light0_specular[] = {1.0f, 0.0f, 0.0f, 1.0f};
  glLightfv (GL_LIGHT0, GL_SPECULAR, light0_specular);

  glEnable (GL_LIGHT0);
  glEnable (GL_LIGHTING);

}

void initValores(){
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     init_light ();
}


main( ){
      glutInitDisplayMode (GLUT_STENCIL | GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
      glutInitWindowSize(500,500);
      glutInitWindowPosition(0,0);
      glutCreateWindow("Prueba Transparecia");
      glutDisplayFunc(myDisplay);
      initValores();
      glutMainLoop();
}
