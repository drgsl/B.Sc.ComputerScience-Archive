/**********************************
  
  The reader of this program should not limit
  himself/herself to the comments of this 
  program.

  If one wants to read more about the syntax and 
  the semantics of OpenGL functions used in this
  program, one should read the beginning of the
  paragraph 2.6 "Begin/End Paradigm", the 
  paragraph 2.6.1 "Begin and End Objects" from the 
  file glspec15.pdf at page 25/333 and the index
  from the end of that file. One could also
  read the references to the GLUT functions from
  the file glut-3.spec.pdf.
  


  H O W  T O  R E A D  T H I S  P R O G R A M ?
  
  Start from the function "main" and follow the 
  instruction flow, paying attention to the fact that
  this program belongs to the event-driven programming
  paradigm. So pay attention to what happens when 
  the user presses a key, moves the mouse or presses a
  mouse button. There are also some special events: the
  redrawing of the application window, etc.
  Identify what happens in the program when one of these
  events occurs.

  **********************************/




/**********************************

 If you want to use the GLUT utility toolkit 
 you must include the header file <GL/glut.h> .

 This header file will include automatically
 the header files needed in order to use 
 OpenGL library : <GL/gl.h> and <GL/glu.h> .
 You don't need to include these two header files
 in your program.

 The OpenGL library functions are prefixed by gl,
 those in GLU by glu and those in GLUT by glut

 In the following it is desirable that the 
 students will use this program like a framework
 (or like a "skeleton") for their future programs
 at Computer Graphics course.

 **********************************/


// Pay attention to the order of include-file directives !
// That's important, in order to avoid some compile-time errors.
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**********************************
  This include-file directive will be used only if
  you have installed OpenGL library as an Administrator
  i.e., you have the necessary rights to copy the files
  glut.h, glut32.lib, glut32.dll in the following locations:
  C:\Program Files\Microsoft SDKs\Windows\v7.0A\Include\gl\glut.h
  C:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib\glut32.lib
  C:\Windows\System32\glut32.dll
 **********************************/
// #include <GL/glut.h>

// Instead of previous include-file directive use this one.
#include <GL/freeglut.h>

// This variable stores the code of the last key
// of the computer keyboard pressed. This code
// will be used later in the program to select which 
// image to draw.
unsigned char prevKey;

void Display1() {
	// The geometry object in this case is a line segment.
	// In order to completely specify a line segment one
	// should specify two different points.

	// A point is specified completely by providing 
	// two (or three in 3D case) coordinates: for x, y 
	// (and z).
  glColor3f(0.2,0.15,0.88); // blue
  // A line segment is drawn between the points
  // specified by the vertices 
  glBegin(GL_LINES); // line drawing
    glVertex2i(1,1); // vertice coordinates
    glVertex2i(-1,-1);
  glEnd();

  glColor3f(1,0.1,0.1); // red
  // A line segment is drawn between the points
  // specified by the vertices 
  glBegin(GL_LINES);
    glVertex2i(-1,1);
    glVertex2i(1,-1);
  glEnd();

  // A line segment is drawn between the points
  // specified by the vertices 
  glBegin(GL_LINES);
    glVertex2d(-0.5,0);
    glVertex2d(0.5,0);
  glEnd();
}

void Display2() {
  glColor3f(1,0.1,0.1); // red
  // In this case, by using GL_LINES begin/end paradigm
  // several line segment are drawn, between the 1st and
  // the 2nd point, between the 3rd and the 4th, etc.  
  glBegin(GL_LINES); 
    glVertex2f(1.0,1.0); 
    glVertex2f(0.9,0.9); 
    glVertex2f(0.8,0.8); 
    glVertex2f(0.7,0.7); 
    glVertex2f(0.6,0.6); 
    glVertex2f(0.5,0.5); 
    glVertex2f(-0.5,-0.5); 
    glVertex2f(-1.0,-1.0);
  glEnd();
}

void Display3() {
  // The geometry object in this case is a point.

  // By using GL_POINTS begin/end paradigm 
  // it is possible to draw as many points as there
  // are specified between glBegin and glEnd.

  glColor3f(1,0.1,0.1); // red
  glBegin(GL_POINTS); 
  // add lines of code here
  glEnd();
}

void Display4() {
  // The geometry object in this case is a polygonal line.

  // By using GL_LINE_STRIP begin/end paradigm 
  // it is possible to draw a polygonal line having as many 
  // points as there are specified between glBegin and glEnd.

  glColor3f(1,0.1,0.1); // red
  glBegin(GL_LINE_STRIP); 
  // add lines of code here
  glEnd();
}

void Display5() {
  // The geometry object in this case is a closed polygonal line.

  // By using GL_LINE_LOOP begin/end paradigm 
  // it is possible to draw a closed polygonal line having as many 
  // points as there are specified between glBegin and glEnd.

  glColor3f(1,0.1,0.1); // red
  glBegin(GL_LINE_LOOP); 
  // add lines of code here
  glEnd();
}

void Display6() {
  // The geometry object in this case is a triangle.

  // By using GL_TRIANGLES begin/end paradigm 
  // it is possible to draw triangles having the vertices
  // (v0,v1,v2), (v3,v4,v5), ...
  // There should be specified at least 3 vertices between
  // glBegin and glEnd.

  glColor3f(1,0.1,0.1); // red
  glBegin(GL_TRIANGLES); 
  // add lines of code here
  glEnd();
}

void Display7() {
  // The geometry object in this case is a quadrilateral
  // (i.e., a polygon with 4 vertex).

  // By using GL_QUADS begin/end paradigm 
  // it is possible to draw quadrilaterals having the vertices
  // (v0,v1,v2,v3), (v4,v5,v6,v7), ...
  // There should be specified at least 4 vertices between
  // glBegin and glEnd.

  glColor3f(1,0.1,0.1); // red
  glBegin(GL_QUADS); 
  // add lines of code here
  glEnd();
}

void Display8() {
  // The geometry object in this case is a polygon.

  // By using GL_POLYGON begin/end paradigm 
  // it is possible to draw a polygon having as many vertices
  // as there are specified between glBegin and glEnd.
  // OpenGL guarantees that only convex polygons are
  // drawn correctly.

  glColor3f(1,0.1,0.1); // red
  glBegin(GL_POLYGON);
  // add lines of code here
  glEnd();
}

void Init(void) {
  // The function glClearColor specifies a clear value
  // for the color buffers in RGBA mode (i.e., its
  // color after its content was deleted by a 
  // glClear function call). The first three parameters
  // specifiy the amounts of Red, Green and Blue colors
  // and the last parameter (alpha) specifies the opacity:
  // 1 = full opacity, 0 = no opacity
  // The part of the OpenGL state modified by this call
  // remains as it is until a new call may changes it.
  // That's true for all OpenGL functions.
  glClearColor(1.0,1.0,1.0,1.0);

  // the name is self-explanatory
  glLineWidth(3);

  // the name is self-explanatory
  glPointSize(4);

  // The function glPolygonMode with the parameters
  // "GLenum face" and "GLenum mode" controls how 
  // a polygon is drawn.
  // The parameter "mode" can have the values 
  // GL_POINT (meaning that only the vertices of 
  // an object are drawn), GL_LINE (meaning that only 
  // the edges of an object are drawn) and GL_FILL 
  // (meaning that the polygon is uniformly colored).
  // The parameter "face" specifies how a face of an
  // object is oriented. It can have the values
  // GL_FRONT (meaning that the face is oriented forward),
  // GL_BACK (meaning that the face is oriented backward)
  // GL_FRONT_AND_BACK (the face is not oriented)
  glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
  printf("Call Display\n");

  // The buffer GL_COLOR_BUFFER_BIT is cleared
  glClear(GL_COLOR_BUFFER_BIT);

  switch(prevKey) {
  case '1':
    Display1();
    break;
  case '2':
    Display2();
    break;
  case '3':
    Display3();
    break;
  case '4':
    Display4();
    break;
  case '5':
    Display5();
    break;
  case '6':
    Display6();
    break;
  case '7':
    Display7();
    break;
  case '8':
    Display8();
    break;
  default:
    break;
  }

  // practically, this call forces the redrawing of 
  // the application window
  glFlush();
}

// The parameters w(idth) and h(eight) specify the new 
// dimensions of the application window
void Reshape(int w, int h) {
  printf("Call Reshape : width = %d, height = %d\n", w, h);

  // The function void glViewport (GLint x, GLint y,
  //                               GLsizei width, GLsizei height)
  // defines the viewport : a rectangular area inside the
  // application window used for displaying by OpenGL.
  // x, y are the coordinates of the left down corner and
  // width and height are expressed in pixels.
  // In this case the viewport has the same dimensions as
  // the application window.
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

// The key parameter indicates the key code and x, y
// the position of the mouse cursor
void KeyboardFunc(unsigned char key, int x, int y) {
  printf("You have pressed <%c>. The mouse has the position %d, %d.\n",
          key, x, y);
  // The value of variable key is stored in the 
  // variable prevKey and thus it will be used in the
  // Display function to select which images to display
  prevKey = key;
  if (key == 27) // escape
    exit(0);
  glutPostRedisplay();
}

// The values of the parameter button could be 
// GLUT_LEFT_BUTTON or GLUT_MIDDLE_BUTTON or GLUT_RIGHT_BUTTON.
// The parameter state indicates the state of the mouse
// button: GLUT_DOWN (the button is pressed) and GLUT_UP (the
// button is released).
// The parameters x and y specifies the coordinates of the
// mouse cursor.
void MouseFunc(int button, int state, int x, int y) {
  printf("Call MouseFunc : you have %s the %s button in the position %d %d\n",
    (state == GLUT_DOWN) ? "pressed" : "released",
    (button == GLUT_LEFT_BUTTON) ? 
    "left" : 
    ((button == GLUT_RIGHT_BUTTON) ? "right": "middle"),
    x, y);
}

int main(int argc, char** argv) {
  // The function glutInit initializes the OpenGL library.
  // The parameters argc and argv are those of the command
  // line and should not be modified before this function
  // call.
  // All the calls of other OpenGL functions should be
  // made after this function call.
  glutInit(&argc, argv);
   
  // The parameters of this function represent the
  // width and the height of the application window 
  // expressed in pixels. The default values are
  // 300, 300.
  glutInitWindowSize(300, 300);

  // The parameters of this function represent the 
  // coordinates of the left up corner of the application
  // window, expressed in pixels. The default values
  // are -1, -1.
  glutInitWindowPosition(100, 100);

  // This function specifies, by a bitwise OR, the set of buffers 
  // which could be used in the program. The buffers are
  // GLUT_SINGLE (one image buffer), GLUT_DOUBLE (2 image buffers),
  // GLUT_RGB or GLUT_RGBA (a RGB color buffer), etc. (see the
  // OpenGL specification for more information).
  // In this case it will be available one colored buffer.
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

  // This function creates a window having the name given
  // by the parameter and returns a window handle.
  glutCreateWindow (argv[0]);

  // This is a call to a user-defined function.
  // See above.
  Init();

  // In the following there are used some callback
  // functions. These functions are defined in the
  // program (see above) and registered in OpenGL
  // by using some GLUT functions. These callback
  // functions are called by the operating system
  // when a certain event appears (e.g., a key is
  // pressed when the application window has the
  // focus).

  // The function
  // void glutReshapeFunc (void (*Reshape)(int width, int height))
  // registers the callback function Reshape which is called
  // whenever the application window changes its shape.
  glutReshapeFunc(Reshape);
   
  // The function
  // void glutKeyboardFunc (void (*KeyboardFunc)(unsigned char,int,int))
  // registers the callback function KeyboardFunc which is called
  // whenever a key is pressed.
  glutKeyboardFunc(KeyboardFunc);
   
  // The function
  // void glutMouseFunc (void (*MouseFunc)(int,int,int,int))
  // registers the callback function MouseFunc which is called
  // whenever a mouse button is pressed or released.
  glutMouseFunc(MouseFunc);

  // The function
  // void glutDisplayFunc (void (*Display)(void))
  // registers the callback function Display which is called
  // whenever the application window needs to be redrawn:
  // at its initialization, when its dimensions change or
  // the function glutPostRedisplay is called.
  glutDisplayFunc(Display);
   
  // The function glutMainLoop launches the GLUT events processing
  // loop. This loop ends only when the application window is 
  // closed.
  // This function should be called only once in a program.
  // The callback functions must be registered prior to this call.
  // When the event loop is empty, the callback function IdleFunc
  // ( registered by calling the function
  //   void glutIdleFunc (void (*IdleFunc) (void))
  // ) is executed.
  glutMainLoop();

  return 0;
}
