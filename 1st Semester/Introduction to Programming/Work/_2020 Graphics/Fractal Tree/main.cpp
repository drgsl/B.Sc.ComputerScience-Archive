#include <iostream>
#include <graphics.h>
#include <winbgim.h>

#include <math.h>

using namespace std;

#define width 1000
#define height 700

#define PI 3.14159265359

float angle = PI / 2;
float shrink = 0.5;

float transX;
float transY;

int colorInd;

void branch(float len)
{
    line(0 + transX, 0+transY, 0 + transX, -len);
    //translate(0, -len);
    transX += 0;
    transY += -len;
    if (len > 4)
    {
        setcolor(colorInd++);
        if(colorInd >= 15)
            colorInd = 1;
        //push();
        //rotate(angle);
        transX += angle;
        transY += angle;

        branch(len * shrink);

        transX += -angle;
        transY += -angle;
        //pop();
        //push();
        //rotate(-angle);
        transX += -angle;
        transY += -angle;

        branch(len * shrink);

        transX += angle;
        transY += angle;
        //pop();
    }
}

void draw()
{
    cleardevice();
    setbkcolor(BLACK);

    transX =width/2;
    transY =height/1.2;

    branch(100);
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    initwindow(width, height);

    //while(true)
    draw();

    getch();
    closegraph();
}

