#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>

#include "GL/freeglut.h"
#include "GL/gl.h"

// the size of the window measured in pixels
#define dim 300
// the maximum number of iterations for the Julia-Fatou set membership testing 
#define NRITER_JF 5000
// the maximum value of M for the Julia-Fatou set membership testing 
#define MODMAX_JF 10000000
// increments used in CJuliaFatou
#define RX_JF 0.01
#define RY_JF 0.01

unsigned char prevKey;

class CComplex {
public:
  CComplex() : re(0.0), im(0.0) {}
  CComplex(double re1, double im1) : re(re1 * 1.0), im(im1 * 1.0) {}
  CComplex(const CComplex &c) : re(c.re), im(c.im) {}
	~CComplex() {}

  CComplex &operator=(const CComplex &c) 
  {
    re = c.re;
    im = c.im;
    return *this;
  }

  double getRe() {return re;}
  void setRe(double re1) {re = re1;}
  
  double getIm() {return im;}
  void setIm(double im1) {im = im1;}

  double getModul() {return sqrt(re * re + im * im);}

  int operator==(CComplex &c1)
  {
    return ((re == c1.re) && (im == c1.im));
  }

  CComplex pow2() 
  {
    CComplex rez;
    rez.re = powl(re * 1.0, 2) - powl(im * 1.0, 2);
    rez.im = 2.0 * re * im;
    return rez;
  }

	friend CComplex operator+(const CComplex &c1, const CComplex &c2);
	friend CComplex operator*(CComplex &c1, CComplex &c2);

	void print(FILE *f) 
	{
		fprintf(f, "%.20f%+.20f i", re, im);
	}

private:
  double re, im;
};

CComplex operator+(const CComplex &c1, const CComplex &c2) 
{
	CComplex rez(c1.re + c2.re, c1.im + c2.im);
	return rez;
}

CComplex operator*(CComplex &c1, CComplex &c2) 
{
	CComplex rez(c1.re * c2.re - c1.im * c2.im,
                c1.re * c2.im + c1.im * c2.re);
	return rez;
}

class CJuliaFatou {
public:
  CJuliaFatou()
  {
    // m.c is initialized by default with 0+0i

    m.nriter = NRITER_JF;
    m.modmax = MODMAX_JF;
  }
  
  CJuliaFatou(CComplex &c)
  {
    m.c = c;
    m.nriter = NRITER_JF;
    m.modmax = MODMAX_JF;
  }
  
  ~CJuliaFatou() {}

  void setmodmax(double v) {assert(v <= MODMAX_JF); m.modmax = v;}
  double getmodmax() {return m.modmax;}

  void setnriter(int v) {assert(v <= NRITER_JF); m.nriter = v;}
  int getnriter() {return m.nriter;}

  // it tests if x belongs to the Julia-Fatou set Jc
  // it returns 0 if yes, -1 for finite convergence, +1 for infinite convergence
  int isIn(CComplex &x)
  {
    int rez = 0;
    // an array for storing the values for computing z_n+1 = z_n * z_n + c
    CComplex z0,z1;

    z0 = x;
    for (int i = 1; i < m.nriter; i++)
    {
      z1 = z0 * z0 + m.c;
      if (z1 == z0) 
      {
        // x does not belong to the J-F set because the 
        // iterative process converges finitely
        rez = -1;
        break;
      }
      else if (z1.getModul() > m.modmax)
      {
        // x does not belong to the J-F set because the 
        // iterative process converges infinitely
        rez = 1;
        break;
      }
      z0 = z1;
    }

    return rez;
  }

  // it displays a J-F set
  void display(double xmin, double ymin, double xmax, double ymax)
  {
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_POINTS); 
    for(double x = xmin; x <= xmax; x+=RX_JF)
      for(double y = ymin; y <= ymax; y+=RY_JF) 
      {
        CComplex z(x, y);
        int r = isIn(z);
        if (r == 0) 
        {
          glVertex3d(x,y,0);
        }
        else if (r == -1)
        {
        }
        else if (r == 1)
        {
        }
      }
    fprintf(stdout, "STOP\n");
    glEnd();

    glPopMatrix();
  }

private:
  struct SDate {
    CComplex c;
    // number of iterations
    int nriter;
    // the maximum value of M
    double modmax;
  } m;
};

// Julia-Fatou set for z0 = 0 and c = -0.12375+0.056805i
void Display1() {
  CComplex c(-0.12375, 0.056805);
  CJuliaFatou cjf(c);

  glColor3f(1.0, 0.1, 0.1);
  cjf.setnriter(30);
  cjf.display(-0.8, -0.4, 0.8, 0.4);
}

// Julia-Fatou set for z0 = 0 and c = -0.012+0.74i
void Display2() {
  CComplex c(-0.012, 0.74);
  CJuliaFatou cjf(c);

  glColor3f(1.0, 0.1, 0.1);
  cjf.setnriter(30);
  cjf.display(-1, -1, 1, 1);
}

void Display9() {

  CComplex c(-0.8, 0.1561);
  CJuliaFatou cjf(c);

  glColor3f(1.0, 0.1, 0.1);
  cjf.setnriter(30);
  cjf.display(-1, -1, 1, 1);
}

void Init(void) {

   glClearColor(1.0,1.0,1.0,1.0);

   glLineWidth(1);

   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
  switch(prevKey) {
  case '1':
    glClear(GL_COLOR_BUFFER_BIT);
    Display1();
    break;
  case '2':
    glClear(GL_COLOR_BUFFER_BIT);
    Display2();
    break;
  case '3':
    glClear(GL_COLOR_BUFFER_BIT);
    // Display3();
    break;
  case '4':
    glClear(GL_COLOR_BUFFER_BIT);
    // Display4();
    break;
  case '5':
    glClear(GL_COLOR_BUFFER_BIT);
    // Display5();
    break;
  case '6':
    glClear(GL_COLOR_BUFFER_BIT);
    // Display6();
    break;
  case '7':
    glClear(GL_COLOR_BUFFER_BIT);
    // Display7();
    break;
  case '8':
    glClear(GL_COLOR_BUFFER_BIT);
    // Display8();
    break;
  case '9':
    glClear(GL_COLOR_BUFFER_BIT);
    Display9();
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
   if (key == 27)
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


