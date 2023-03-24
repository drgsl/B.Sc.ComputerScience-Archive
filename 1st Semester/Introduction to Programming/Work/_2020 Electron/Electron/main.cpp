#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <winbgim.h>
#include <string>
#include <iostream>

#define ZOOM 10

using namespace std;

FILE *fileNames = fopen("nameForFiles.txt", "r");
FILE *f;
char name[100];
int width = GetSystemMetrics(SM_CXSCREEN);
int height = GetSystemMetrics(SM_CYSCREEN);
int orientation = 0;

void getFile()
{
    fscanf(fileNames, "%s", name);
    f = fopen(name, "r");
}

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

struct ellips //arc
{
    point point1;
    int stangle = 0, endangle = 360;
    point radius;
};

struct arcs // circle
{
    point point1;
    int stangle = 270, endangle = 90;
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
} fig[15];


point translatePoint(point p, int id) //TRANSLATE
{
    p.x *= ZOOM;
    p.x += width/30;

    p.y *= ZOOM;
    p.y += height/15*(id+1);

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

    return p;
}

/*point translateRadius(point radius)
{
    radius.x *= 50;
    //radius.x /= 7;

    radius.y *= 50;
   // radius.y /= 7;
}*/
/*void drawType(figure fig[])
{
    switch(type)
    {
        case 'L':
            line(transP1.x,
                 transP1.y,
                 transP2.x,
                 transP2.y);
            break;
        case 'R':
            rectangle(transP1.x,
                  transP1.y,
                  transP2.x,
                  transP2.y);
            break;
        case 'A':
             arc(transP1.x,
                 transP1.y,
                 fig.A[index].stangle,
                 fig.A[index].endangle,
                 fig.A[index].radius*6.3);
        break;
        case 'E':
             ellipse(transP1.x,
                     transP1.y,
                     fig.E[index].stangle,
                     fig.E[index].endangle,
                     transRadiusPoint.x/12,
                     transRadiusPoint.y/12);
            break;
    }
}*/

void readFromFileAndShow(figure fig[],int id, char type, int index) //READ
{
    switch(type)
    {
    case 'L':
    {
        fscanf(f, "%f", &fig[id].L[index].point1.x);
        fscanf(f, "%f", &fig[id].L[index].point1.y);
        fscanf(f, "%f", &fig[id].L[index].point2.x);
        fscanf(f, "%f", &fig[id].L[index].point2.y);

        point transP1 = translatePoint(fig[id].L[index].point1, id);//redimensionare puncte
        point transP2 = translatePoint(fig[id].L[index].point2, id);

        line(transP1.x,
             transP1.y,
             transP2.x,
             transP2.y);
    }
    break;

    case 'R':
    {
        fscanf(f, "%f", &fig[id].R[index].leftUp.x);
        fscanf(f, "%f", &fig[id].R[index].leftUp.y);
        fscanf(f, "%f", &fig[id].R[index].rightDown.x);
        fscanf(f, "%f", &fig[id].R[index].rightDown.y);

        point transP1 = translatePoint(fig[id].R[index].leftUp, id);
        point transP2 = translatePoint(fig[id].R[index].rightDown, id);

    }
    break;

    case 'A':
    {
        fscanf(f, "%f", &fig[id].A[index].point1.x);
        fscanf(f, "%f", &fig[id].A[index].point1.y);
        fscanf(f, "%f", &fig[id].A[index].radius);

        point transP1 = translatePoint(fig[id].A[index].point1, id);
        float transRadius = width/68;

    }
    break;

    case 'E':
    {
        fscanf(f, "%f", &fig[id].E[index].point1.x);
        fscanf(f, "%f", &fig[id].E[index].point1.y);
        fscanf(f, "%f", &fig[id].E[index].radius.x);
        fscanf(f, "%f", &fig[id].E[index].radius.y);

        point transP1 = translatePoint(fig[id].E[index].point1, id);
        point transRadiusPoint = translatePoint(fig[id].E[index].radius, id);
        break;
    }
    }
}
int main()
{
    initwindow(width, height, "ELECTRON");
    for (int id = 0; id < 10; id++)
    {
        getFile();
        fgets(fig[id].name, 50, f);
        fscanf(f, "%d", &fig[id].connections);

        for(int k = 0; k < fig[id].connections; k++)
        {
            fscanf(f, "%f", &fig[id].connectPoint[k].x);
            fscanf(f, "%f", &fig[id].connectPoint[k].y);

            point transPoint = translatePoint(fig[id].connectPoint[k], id);
            //putpixel(fig[i].connectPoint[k].x, fig[i].connectPoint[k].y, WHITE);
        }

        fscanf(f, "%s", fig[id].description);

        int index = -1;
        char type, before;

        fscanf(f, "%c", &type);
        fscanf(f, "%c", &type);

        before = type;
        while (!feof(f))
        {
            /*if(!strchr("LREA",type))
            {
                fscanf(f, "%c", &type);
                continue;
            }*/

            if(type != before)
            {
                index = 0;
                before = type;
            }
            else
                index++;

            readFromFileAndShow(&fig[id], id, type, index);
            fscanf(f, "%c", &type);
            fscanf(f, "%c", &type);
        }
        fclose(f);
    }

    while(1)
    {

    }
    //movePiece(fig);

    //fclose(f);
    getch();
    closegraph();
    return 0;
}
