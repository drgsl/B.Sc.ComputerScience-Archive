#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <winbgim.h>

#define HEIGHT 600
#define WIDTH 600
#define ZOOM 100


using namespace std;

struct point
{
    float x;
    float y;
};

struct lines
{
    point point1;
    point point2;
};

struct rect
{
    point leftUp;
    point rightDown;
};

struct ellips
{
    point point1;
    float stangle, endangle;
    point radius;
};

struct arcs
{
    point point1;
    float stangle, endangle;
    float radius;

};

struct figure
{
    char name[50];
    int connections;
    point connectPoint[50];
    char description[50];
    lines L[20];
    rect R[20];
    ellips E[20];
    arcs A[20];
};

point translatePoint(point p)
{
    p.x *= ZOOM;
    p.x += WIDTH/2;

    p.y *= ZOOM;
    p.y += HEIGHT/2;

    return p;
}

FILE *f = fopen("C:\\Users\\Elena\\Desktop\\Electron\\piese\\REZIST.txt", "r");

void allocate(char type, figure fig, int index)
{
    switch(type)
    {
    case 'L':
    {
        fscanf(f, "%f", &fig.L[index].point1.x);
        fscanf(f, "%f", &fig.L[index].point1.y);
        fscanf(f, "%f", &fig.L[index].point2.x);
        fscanf(f, "%f", &fig.L[index].point2.y);

        point transP1 = translatePoint(fig.L[index].point1);//redimensionare puncte
        point transP2 = translatePoint(fig.L[index].point2);

        line(transP1.x,
             transP1.y,
             transP2.x,
             transP2.y);
    }
     break;
    case 'R':
    {
        fscanf(f, "%f", &fig.R[index].leftUp.x);
        fscanf(f, "%f", &fig.R[index].leftUp.y);
        fscanf(f, "%f", &fig.R[index].rightDown.x);
        fscanf(f, "%f", &fig.R[index].rightDown.y);

        point transP1 = translatePoint(fig.R[index].leftUp);
        point transP2 = translatePoint(fig.R[index].rightDown);

        rectangle(transP1.x,
                  transP1.y,
                  transP2.x,
                  transP2.y);
    }
    break;
   case 'A':
    {
        fscanf(f, "%f", &fig.A[index].point1.x);
        fscanf(f, "%f", &fig.A[index].point1.y);
        fscanf(f, "%d", &fig.A[index].stangle);
        fscanf(f, "%d", &fig.A[index].endangle);
        fscanf(f, "%f", &fig.A[index].radius);

        point transP1 = translatePoint(fig.A[index].point1);

        arc(transP1.x,
            transP1.y,
            fig.A[index].stangle,
            fig.A[index].endangle,
            fig.A[index].radius);
    }
    break;
    case 'E':
    {
        fscanf(f, "%f", &fig.E[index].point1.x);
        fscanf(f, "%f", &fig.E[index].point1.y);
        fscanf(f, "%d", &fig.E[index].stangle);
        fscanf(f, "%d", &fig.E[index].endangle);
        fscanf(f, "%f", &fig.E[index].radius.x);
        fscanf(f, "%f", &fig.E[index].radius.y);

        point transP1 = translatePoint(fig.E[index].point1);
        point transRadius = translatePoint(fig.E[index].radius);

        ellipse(transP1.x,
                transP1.y,
                fig.E[index].stangle,
                fig.E[index].endangle,
                transRadius.x,
                transRadius.y);
    }
    break;
    }
}
int main()
{
    initwindow(HEIGHT, WIDTH, "ELECTRON",200,70);

    figure fig;

    fscanf(f, "%s", fig.name);
    fscanf(f, "%d", &fig.connections);

    for(int i = 0; i < fig.connections; i++)
    {
        fscanf(f, "%f", fig.connectPoint[i].x);
        fscanf(f, "%f", fig.connectPoint[i].y);

        point transPoint = translatePoint(fig.connectPoint[i]);
        putpixel(fig.connectPoint[i].x, fig.connectPoint[i].y, WHITE);
    }

    fscanf(f, "%s", fig.description);

    int index = -1;
    char type, before;
    fscanf(f, "%c", &type);
    before = type;
    while (!feof(f))
    {
        if(type != before)
        {
            index = 0;
            before = type;
        }
        else
            index++;
        allocate(type, fig, index);
        fscanf(f, "%c", &type);

    }

    getch();
    closegraph();
    fclose(f);
    return 0;
}
