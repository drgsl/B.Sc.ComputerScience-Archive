#include <iostream>
#include <graphics.h>
#include <winbgim.h>

#include <math.h>

/// SuperShapes 2D
/// http://paulbourke.net/geometry/supershape/
/// https://www.youtube.com/watch?v=ksRoh-10lak

int windowHeight = 800;
int windowWidth = 800;

int scale = 150;

float a =1;
float b =1;
float n1=1;
float n2=1;
float n3=1;
float m;

float index = 6;
float total;

float osc = 0;

float colorInd;

float supershape(float theta)
{
    float part1 = (1/a) * cos(m/4* theta);
    part1 = abs(part1);
    part1 = pow(part1, n2);

    float part2 = (1/b)*sin(m/4*theta);
    part2 = abs(part2);
    part2 = pow(part2, n3);

    float part3 = pow(part1 + part2, 1 / n1);

    return(1/part3);
}

void newIndexCheck()
{
    total = 3.14159265359 * 2;

    if(index==1)
        n1=n2=n3=1;
    if(index==2)
        n1=n2=n3=0.3;
    if(index==3)
    {
        //n1=40;
        //n2=n3=10;
        n1 = n2= n3 = 0.3;
        total = 12*3.14;
        m = m/2;
    }
    if(index==4)
    {
        n1 = 60;
        n2 = 55;
        n3 = 30;
    }
    if(index==5)
    {
        n1 = n2= n3 = 0.3;
        total = 12*3.14;
        m = m/10;
    }
    if(index == 6)
    {
        n1 = 0.1;
        n2 = n3 = 1.7;
    }
    if(index == 7)
    {
        n1 = 0.02;
        n2 = n3 = 1.7;
    }
}

void draw()
{
    m =sin(osc) * 6;
    osc += 0.005;

    newIndexCheck();

    cleardevice();
    setbkcolor(BLACK);

    float lastX;
    float lastY;

    for (float angle = 0; angle < total * 1; angle +=0.01)
    {
        float r = supershape(angle);
        float x = scale * r * cos(angle) + windowWidth/4;
        float y = scale * r * sin(angle) + windowHeight/4;

        setcolor(colorInd);
        //circle(x, y, 5);
        putpixel(x, y, colorInd);
        //if(lastX && lastY) line(lastX, lastY, x, y);
        lastX = x;
        lastY = y;
        colorInd +=0.1;
        if(colorInd >15)
            colorInd = 1;
        //delay(0.1);
    }
}

int main()
{
    do
    {
        std::cout <<"Enter Animation Index(from 1 to 7): ";
        std::cin>>index;
    }
    while(index > 7 || index < 1);

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    //initwindow(windowWidth,windowHeight);
    setlinestyle(SOLID_LINE,0, 5);
    //setvisualpage(0);
    while(true)
    {
        draw();
        swapbuffers();
    }
    getch();
    closegraph();
}
