#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <winbgim.h>

#define HEIGHT 600
#define WIDTH 600
#define ZOOM 50


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

int orientation = 0;

point translatePoint(point p)
{
    if(orientation == 1)
    {
        p.x = -p.x;
        swap(p.x, p.y);
    }
    else if(orientation == 2)
    {
        p.x = -p.x;
    }
    else if(orientation == 3)
    {
        swap(p.x, p.y);
    }

    p.x *= ZOOM;
    p.x += WIDTH/2;

    p.y *= ZOOM;
    p.y += HEIGHT/2;

    return p;
}

FILE *f = fopen("servomot.txt", "r");

void allocate(char type, figure &fig, int index)
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
        fscanf(f, "%f", &fig.A[index].stangle);
        fscanf(f, "%f", &fig.A[index].endangle);
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
        fscanf(f, "%f", &fig.E[index].stangle);
        fscanf(f, "%f", &fig.E[index].endangle);
        fscanf(f, "%f", &fig.E[index].radius.x);
        fscanf(f, "%f", &fig.E[index].radius.y);

        point transP1 = translatePoint(fig.E[index].point1);
        point transRadius = translatePoint(fig.E[index].radius);

        ellipse(transP1.x,
                transP1.y,
                fig.E[index].stangle,
                fig.E[index].endangle,
                transRadius.x/4,
                transRadius.y/4);
    }
    break;
    }
}

void drawPiece(figure fig, point coord, int orientation)
{
    setcolor(RED);
    for(int i = 0; i< 20; i++)
    {
        point transP1 = translatePoint(fig.L[i].point1);
        point transP2 = translatePoint(fig.L[i].point2);
        line(transP1.x,transP1.y,transP2.x,transP2.y);
    }
        for(int i = 0; i< 20; i++)
    {
        point transLeftUp = translatePoint(fig.R[i].leftUp);
        point transRightDown = translatePoint(fig.R[i].rightDown);
        rectangle(transLeftUp.x,transLeftUp.y,transRightDown.x,transRightDown.y);
    }
            for(int i = 0; i< 1; i++)
    {
        point transPoint1 = translatePoint(fig.E[i].point1);
        point transRadius;
        transRadius.x = fig.E[i].radius.x * ZOOM;
        transRadius.y = fig.E[i].radius.y * ZOOM;
        ellipse(transPoint1.x,
                transPoint1.y,
                fig.E[i].stangle,
                fig.E[i].endangle,
                transRadius.x,
                transRadius.y);
    }
}
figure fig;

int main()
{
    initwindow(HEIGHT, WIDTH, "ELECTRON",200,70);

    fscanf(f, "%s", fig.name);
    fscanf(f, "%d", &fig.connections);

    for(int i = 0; i < fig.connections; i++)
    {
        fscanf(f, "%f", &fig.connectPoint[i].x);
        fscanf(f, "%f", &fig.connectPoint[i].y);

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
        if(!strchr("LREA",type))
        {
            fscanf(f, "%c", &type);
            continue;
        }
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
    point test;
    test.x = 0;
    test.y = 0;
    drawPiece(fig, test,0);
    getch();
    closegraph();
    fclose(f);
    return 0;
}
