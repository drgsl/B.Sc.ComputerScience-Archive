#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <algorithm>
/*how to use:
r-click drag to generate julia sets
l-click (on release) to zoom in
m-click (on release) to zoom out
+ and - to change maxIter
/ and * to change radius
*/


//#define highprec

#ifdef highprec
  typedef double Float;
  #define glVertex2 glVertex2d
  #define glVertex3 glVertex3d
#else
  typedef float Float;
  #define glVertex2 glVertex2f
  #define glVertex3 glVertex3f
#endif

using namespace std;

//is the mouse pressed?
bool g_mPress, g_mainInvalid;

unsigned int g_width, g_height, g_iter;
Float g_radius, g_cR, g_cI, g_xCenter, g_xRange, g_yCenter, g_yRange;

void initFractal() {
  g_iter = 50;
  g_radius = 4;
  g_cR = 0;
  g_cI = 0;
  g_xCenter = 0;
  g_xRange  = 2;
  g_yCenter = 0;
  g_yRange  = 2;
}

void init(void) {
   glClearColor(0.0, 0.0, 0.0, 0.0);
   //   glShadeModel(GL_FLAT);
   g_mPress = false;
   initFractal();
   g_mainInvalid = true;
}

void displayAux();
void display1();


inline Float julia(Float x, Float y, Float cR, Float cI, unsigned int maxIter = 50, Float radius = 4) {
  Float x2, y2;
  unsigned int iter = maxIter;
  for(; iter > 0; --iter) {
    x2 = pow(x, 2);
    y2 = pow(y, 2);
    if(x2 + y2 > radius) break; //slightly simplified; the radius can be increased significantly
    y = 2.0 * x * y + cI;
    x = x2 - y2 + cR;
  }
  return(Float(iter) / Float(maxIter));
}
/* one way to do it
inline void setColor(Float pos) {
  pos = pow(pos, 2);//encourages the mid-range
  if(0 == pos) glColor3f(0, 0, 0);
  else
    //glColor3f(1 - pos * 2.0, 0.5 - 2.0 * abs(0.5 - pos), pos - 0.5);//little bleed-through
    glColor3f(1 - pos * 1.5, 0.5 - 2.0 * abs(0.5 - pos), pos - 0.4);//more bleed-through
}*/

inline void setColor(Float pos) {
  if(0 == pos) glColor3f(0, 0, 0);
  else {
    pos = pos * 255;
    pos -= floor(pos); //we now have cyclic colours
    glColor3f(1 - pos * 1.5, 0.5 - 2.0 * abs(0.5 - pos), pos - 0.4);//more bleed-through
  }
}


void display1() {
  Float xRatio = 2.0 / Float(g_width);
  Float yRatio = 2.0 / Float(g_height);
  Float col, zr, zi;
  if(g_mainInvalid == true) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for(Float ii = -1.0; ii <= 1.0; ii+= xRatio) {
      for(Float jj = -1.0; jj <= 1.0; jj+= yRatio) {
	zr = g_xCenter + g_xRange * ii;
	zi = g_yCenter + g_yRange * jj;
	col = julia(zr, zi, zr, zi, g_iter, g_radius);
	setColor(col);
	glVertex2(ii, jj);
      }
    }
    glEnd();
    g_mainInvalid = false;
  }
  displayAux();
  cout<<"Finished drawing"<<endl;
}

void displayAux() {
  Float xRatio = 2.0 / Float(g_width);
  Float yRatio = 2.0 / Float(g_height);
  Float col;
  //smaller drawing
  xRatio *= 4.0;
  yRatio *= 4.0;
  glBegin(GL_POINTS);
  for(Float ii = -1.0; ii <= 1.0; ii+= xRatio) {
    for(Float jj = -1.0; jj <= 1.0; jj+= yRatio) {
      col = julia(2.0 * ii, 2.0 * jj, g_cR, g_cI, g_iter, g_radius); //we don't zoom in the Julia fractals
      setColor(col);
      glVertex2(0.75 + ii / 4.0, 0.75 + jj / 4.0);
    }
  }
  glEnd();
}

void display() {
  display1();
  glFlush();
  //glutSwapBuffers();
}

void reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   g_width = w;
   g_height = h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-1.0, 1.0, (GLfloat)h/(GLfloat)w,
               (GLfloat)h/(GLfloat)w, -1.0, 1.0);
   else
      glOrtho((GLfloat)w/(GLfloat)h,
               (GLfloat)w/(GLfloat)h, -1.0, 1.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   g_mainInvalid = true;
}

void keys(unsigned char key, int x, int y) {
  if(27 == key) exit(0);

  if('r' == key) {//reset
    initFractal();
    g_mainInvalid = true;
    glutPostRedisplay();
  }

  if('-' == key) {
    --g_iter;
    if(g_iter < 1) g_iter = 1;
    g_mainInvalid = true;
    glutPostRedisplay();
    cout<<"Max iter = "<<g_iter<<endl;
  }
  if('+' == key) {
    ++g_iter;
    g_mainInvalid = true;
    glutPostRedisplay();
    cout<<"Max iter = "<<g_iter<<endl;
  }
  if('/' == key) {
    g_radius /= 1.1;
    //if(g_radius < 2) g_radius = 2;//should be 2, left for experimentation
    g_mainInvalid = true;
    glutPostRedisplay();
    cout<<"Max radius = "<<g_radius<<endl;
  }
  if('*' == key) {
    g_radius *= 1.1;
    g_mainInvalid = true;
    glutPostRedisplay();
    cout<<"Max radius = "<<g_radius<<endl;
  }
 
}

Float scale(int c, int length) {
  return(-1.0 + Float(c) * 2.0 / Float(length));
}

inline void setCoords(int x, int y) {
  Float dx, dy;
  dx = scale(x, g_width);
  dy = -scale(y, g_height);//screen pixel coords increase in y-value as height decreases. trig coords decrease in y-value as height decreases.
  g_cR = g_xCenter + dx * g_xRange;
  g_cI = g_yCenter + dy * g_yRange;
}

inline void zoom(int x, int y) {
  Float dx, dy;
  dx = scale(x, g_width);
  dy = -scale(y, g_height);
  g_xCenter = g_xCenter + dx * g_xRange;
  g_yCenter = g_yCenter + dy * g_yRange;
  g_xRange *= 0.5;
  g_yRange *= 0.5;
  cout<<"New fractal area on screen: ("<<g_xCenter - g_xRange<<", "<<g_yCenter - g_yRange<<")->("<<g_xCenter + g_xRange<<", "<<g_yCenter + g_yRange<<")"<<endl;
}

inline void zoomOut() {
  g_xRange *= 2;
  g_yRange *= 2;
  //reset to default fractal view after large-enough zoom-out
  if(g_xRange >= 2) {
    g_xRange = 2;
    g_xCenter = 0;
  }
  if(g_yRange >= 2) {
    g_yRange = 2;
    g_yCenter = 0;
  }
}

void idle() {
}

void mouse(int button, int state, int x, int y) {
  if(2 == button) {//r-button
    setCoords(x, y);
    cout<<"cR = "<<g_cR<<" cI = "<<g_cI<<endl;
    glutPostRedisplay();//invalidate the display, but not the main drawing. the auxiliary will be drawn on top.
    if(1 == state) {//up
      g_mPress = false; //we did release the button
    }
    else {//down
      g_mPress = true;
    }
  }
  else if((0 == button) && (1 == state)) { //l-button, upon release (since the release generally moves the pointer less)
    zoom(x, y);
    g_mainInvalid = true;
    glutPostRedisplay();
  }
  else if((1 == button) && (1 == state)) {//m-button
    zoomOut();
    g_mainInvalid = true;
    glutPostRedisplay();
  }
}

void mouseMove(int x, int y) {
  Float dx, dy;
  if(g_mPress) {
    setCoords(x, y);
    glutPostRedisplay();
    cout<<"cR = "<<g_cR<<" cI = "<<g_cI<<endl;
  }
}


int main(int argc, char** argv) {
  g_width = 300;
  g_height = 300;
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize (g_width, g_height);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keys);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMove);
  glutIdleFunc(idle);

  glutMainLoop();
  return 0;
}
