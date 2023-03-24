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
  With respect to the include-file directives, see the 
  example program from homework 1; in the following it
  was made the assumption that you are using GLUT locally,
  in your project and you didn't install it as an
  Administrator
  **********************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <cmath>

// the size of the window measured in pixels
#define dim 300

unsigned char prevKey;


void RenderString(float x, float y, void *font, const char* string, float r, float g, float b)
{  
  char *c;

  glColor3f(r,g,b); 
  glRasterPos2f(x, y);

  glutBitmapString(font, (unsigned char*)string);
}

// the graph of the Conchoid of Nicomedes
void Display1() {
   double xmax, ymax, xmin, ymin;
   double a = 1, b = 2;
   double pi = 4 * atan(1.0);
   double ratia = 0.05;
   double t;

   /**********************************
      Maximum/minimum values of x and y are computed.
      These values will be further used in scaling the
      original graph of the curve. 
      These values are stored in the variables
      xmax, ymax, xmin, ymin: e.g., xmax is initialized
      with a value smaller than any of possible values
      of x; if in doubt or you cannot estimate it, use 
      DBL_MIN instead (or DBL_MAX for minimum values).
      These DBL_* constants are found in <float.h> which
      need to be included.
      E.g., xmax is initialized with a - b - 1 because
      x(t) = a +/- b * cos(t) and for t in (-pi/2, pi/2),
      cos(t) is in (0, 1), so b * cos(t) is in (0, b),
      so +/- b * cos(t) is in (-b, b), so x(t) is in
      (a-b, a+b) and one can safely choose a-b-1 because
      a-b-1 < a-b. 
      For y(t) we see that in its expression appears
      tan(t) which varies in (-inf,+inf) when t
      varies in (-pi/2, pi/2).
     **********************************/
   xmax = a - b - 1; 
   xmin = a + b + 1;
   ymax = ymin = 0;
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = a + b * cos(t);
      xmax = (xmax < x1) ? x1 : xmax;
      xmin = (xmin > x1) ? x1 : xmin;

      x2 = a - b * cos(t);
      xmax = (xmax < x2) ? x2 : xmax;
      xmin = (xmin > x2) ? x2 : xmin;

      y1 = a * tan(t) + b * sin(t);
      ymax = (ymax < y1) ? y1 : ymax;
      ymin = (ymin > y1) ? y1 : ymin;

      y2 = a * tan(t) - b * sin(t);
      ymax = (ymax < y2) ? y2 : ymax;
      ymin = (ymin > y2) ? y2 : ymin;
   }

   /**********************************
      At this line, we have found that the graph of the Conchoid
      is included in the rectangle having the edges x = xmin,
      x = xmax, y = ymin and y = ymax. 
      We would like that the rectangle should be symmetric with
      respect to the Ox and Oy axes.
      We store in xmax and ymax the maximum of absolute values
      max(|xmax|,|xmin|) and max(|ymax|,|ymin|).
      Now we know that the graph of the Conchoid is included in
      the rectangle [-xmax, xmax] x [-ymax, ymax].
     **********************************/

   xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
   ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

   /**********************************
      At this line, we can perform the scaling. All the points
      scaled are visible (i.e., in the rectangle [-1,1]x[-1,1]).
      Because we have -xmax <= x <= xmax we get
      -1 <= x / xmax <= 1. Idem for y.
      In order to correctly display the graph of the Conchoid,
      one should use the exact same points that were used in
      the computation of the scaling factor.
     **********************************/

   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP); 
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();

   glBegin(GL_LINE_STRIP); 
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x2,y2);
   }
   glEnd();
}

// The graph of the function 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
   double pi = 4 * atan(1.0);
   double xmax = 8 * pi;
   double ymax = exp(1.1);
   double ratia = 0.05;


   /**********************************
      For this example, the computation of the scaling factors
      is not needed. Because x is in the interval [0, 8pi]
      the scaling factor for x is 8pi because x/(8pi) is in
      [0,1]. In the case of the exponential function we know
      that if x is [0,8pi] then sin x is in [-1,1] so
      e^(-sin x) is in [1/e, e] and thus it is safe to use 
      e^(1.1) as a scaling factor.
     **********************************/
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP); 
   for (double x = 0; x < xmax; x += ratia) {
      double x1, y1;
      x1 = x / xmax;
      y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();
}

void Display3(){
   /**********************************
      f(x) =   1, if x = 0
               d(x) / x, if 0 < x <= 100

      d(x) = the distance from x to the nearest integer.
     **********************************/

   double xmax = 15;
   double ymax = 1;
   double ratia = 0.05;

   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP);
   for (double x = 0; x <= xmax; x += ratia) {
      double x1, y1;
      x1 = x / xmax;
      if (x == 0) {
         y1 = 1;
      } else {
         double d = x - floor(x);
         if (d > 0.5) {
            d = ceil(x) - x;
         }
         y1 = d / x;
      }
      ymax = (ymax < y1) ? y1 : ymax;
      glVertex2f(x1,y1);
   }
   glEnd();
}

void Display4(){
      /**********************************
       * The trisectrix of Longchamps:
       * x = a / (4 * cos^2(t) - 3 )
       * y = a * tan(t) / (4 * cos^2(t) - 3 )
       * t in [-pi/2, pi/2] \ { +- pi/6 }
       * 
       * 
     **********************************/

   double pi = 4 * atan(1.0);
   double a = 0.2;
   double xmax = 1;
   double ymax = 1;
   double ratia = 0.005;

   // Remembering each x, y pair
   // in order to draw the lines separately 
   double xList[1000];
   double yList[1000];
   int k = 0;

   glColor3f(0.1,0.1,0.1); // negru
   glBegin(GL_LINE_STRIP);
   for (double t = - pi/2 + ratia; t < -pi / 6; t += ratia) {
      double x1, y1;
      x1 = a / (4 * cos(t) * cos(t) - 3);
      y1 = a * tan(t) / (4 * cos(t) * cos(t) - 3);
      // xmax = (xmax < x1) ? x1 : xmax;
      // ymax = (ymax < y1) ? y1 : ymax;

      // x1 /= xmax;
      // y1 /= ymax;

      xList[k] = x1;
      yList[k] = y1;
      ++k;

      glVertex2f(x1,y1);

   }
   glEnd();

      glColor3f(1, 0.1, 0.1); //rosu
    glBegin(GL_TRIANGLES);
    //triunghiurile din jmt de sus
    for (int i = 1; i < k / 4; i += 2) {

        glVertex2f(-1, 1);
        glVertex2f(xList[i], yList[i]);
        glVertex2f(xList[i + 1], yList[i + 1]);
    }
    //jmt de jos
    for (int i = 3 * k / 4; i < k - 1; i += 2) {

        glVertex2f(-1, 1);
        glVertex2f(xList[i], yList[i]);
        glVertex2f(xList[i + 1], yList[i + 1]);
    }
    glEnd();

   RenderString(-1, -0.7, GLUT_BITMAP_TIMES_ROMAN_24, "The trisectrix of Longchamps", 0, 0, 1.0);
   RenderString(-0.9, -0.9, GLUT_BITMAP_TIMES_ROMAN_24, "a = 0.2;", 0, 0, 1.0);

}

void Display5(){
         /**********************************
       * The cycloid
       * 
       * x = a * t - b * sin(t)
       * y = a - b * cos(t)
       * for any t in R
     **********************************/

   double pi = 4 * atan(1.0);
   double a = 0.1;
   double b = 0.2;
   double xmax = 1;
   double ymax = 1;
   double ratia = 0.05;


   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP);
   for (double t = - 4 * pi; t < 4 * pi; t += ratia) {
      double x1, y1;
      x1 = a * t - b * sin(t);
      y1 = a - b * cos(t);
      xmax = (xmax < x1) ? x1 : xmax;
      ymax = (ymax < y1) ? y1 : ymax;

      x1 /= xmax;
      y1 /= ymax;

      glVertex2f(x1,y1);
   }
   glEnd();

   RenderString(-0.9, 0.9, GLUT_BITMAP_TIMES_ROMAN_24, "The cycloid", 0, 0, 1.0);
   RenderString(-0.9, 0.7, GLUT_BITMAP_TIMES_ROMAN_24, "a = 0.1;", 0, 0, 1.0);
   RenderString(-0.9, 0.5, GLUT_BITMAP_TIMES_ROMAN_24, "b = 0.2;", 0, 0, 1.0);


}

void Display6(){
            /**********************************
       * The Lemniscate of Bernoulli
       * 
       * (r, t) - polar coodrinates
       * where t in [a, b]
       * where r = f(t)
       * 
       * polar coordinates to cartesian:
       * x = r * cos(t)
       * y = r * sin(t)
       * 
       * f(t) = +-a * sqrt(2 * cos(2t))
       * where t in [-pi/4, pi/4]
     **********************************/

   double pi = 4 * atan(1.0);
   double a = 0.4;
   double xmax = 1;
   double ymax = 1;
   double ratia = 0.05;


   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP);
   for (double t = - pi / 4; t < pi / 4; t += ratia) {
      double x1, y1;
      double r = a * sqrt(2 * cos(2 * t));
      x1 = r * cos(t);
      y1 = r * sin(t);
      xmax = (xmax < x1) ? x1 : xmax;
      ymax = (ymax < y1) ? y1 : ymax;

      x1 /= xmax;
      y1 /= ymax;

      glVertex2f(x1,y1);
   }
   glEnd();
   
   glBegin(GL_LINE_STRIP);
   for (double t = - pi / 4; t < pi / 4; t += ratia) {
      double x1, y1;
      double r = -a * sqrt(2 * cos(2 * t));
      x1 = r * cos(t);
      y1 = r * sin(t);
      xmax = (xmax < x1) ? x1 : xmax;
      ymax = (ymax < y1) ? y1 : ymax;

      x1 /= xmax;
      y1 /= ymax;

      glVertex2f(x1,y1);
   }
   glEnd();


   RenderString(-0.9, 0.9, GLUT_BITMAP_TIMES_ROMAN_24, "Lemniscate of Bernoulli", 0, 0, 1.0);
   RenderString(-0.9, 0.7, GLUT_BITMAP_TIMES_ROMAN_24, "a = 0.4", 0, 0, 1.0);
}

void Display7(){
   /**********************************
       * The Logarithmic Spiral
       * 
       * (r, t) - polar coodrinates
       * where t in [a, b]
       * where r = f(t)
       * 
       * polar coordinates to cartesian:
       * x = r * cos(t)
       * y = r * sin(t)
       * 
       * f(t) = a * e ^ (1+t)
       * where t in [0, infinty]
     **********************************/
    
   double pi = 4 * atan(1.0);
   double a = 0.02;
   double xmax = 1;
   double ymax = 1;
   double ratia = 0.05;


   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP);

   for (double t = 0; t < 100; t += ratia) {
      double x1, y1;
      double r = a * exp(1 + t);
      x1 = r * cos(t);
      y1 = r * sin(t);
      xmax = (xmax < x1) ? x1 : xmax;
      ymax = (ymax < y1) ? y1 : ymax;

      x1 /= xmax;
      y1 /= ymax;

      glVertex2f(x1,y1);
   }
   glEnd();

   RenderString(-0.9, 0.9, GLUT_BITMAP_TIMES_ROMAN_24, "The logarithmic spiral", 0, 0, 1.0);
   RenderString(-0.9, 0.7, GLUT_BITMAP_TIMES_ROMAN_24, "a = 0.02", 0, 0, 1.0);
}


void Init(void) {

   glClearColor(1.0,1.0,1.0,1.0);

   glLineWidth(1);

//   glPointSize(4); 7, 8

   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
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
   default:
      break;
   }

   glFlush();
}

void Reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
   prevKey = key;
   if (key == 27) // escape
      exit(0);
   glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

   glutInit(&argc, argv);
   
   glutInitWindowSize(dim, dim);

   glutInitWindowPosition(100, 100);

   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

   glutCreateWindow (argv[0]);

   Init();

   glutReshapeFunc(Reshape);
   
   glutKeyboardFunc(KeyboardFunc);
   
   glutMouseFunc(MouseFunc);

   glutDisplayFunc(Display);
   
   glutMainLoop();

   return 0;
}
