#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

#include <graphics.h>
#include <winbgim.h>

using namespace std;

struct punct
{
    float x;
    float y;
};

struct linie
{
    punct punct1;
    punct punct2;
};

struct rect
{
    punct stangaSus;
    punct dreaptaJos;
};


struct desenPiesa
{
    char nume[100];

    int nrPuncteLegatura;
    punct puncteLegatura[50];

    char descriere[500];
    linie linii[50];
    rect dreptunghiuri[50];
};

#define WIDTH 600
#define HEIGHT 600

int zoom = 50;

int orientation =3 ;

punct translatePoint(punct point)
{
    if(orientation == 1)
    {
        point.x = -point.x;
        swap(point.x, point.y);
    }
    else if(orientation == 2)
    {
        point.x = -point.x;
    }
    else if(orientation == 3)
    {
        swap(point.x, point.y);
    }

    point.x *= zoom;
    point.x += WIDTH/2;

    point.y *= zoom;
    point.y += HEIGHT/2;

    return point;
}


int main()
{
    initwindow(WIDTH,HEIGHT);
    FILE *fptr = fopen("dioda.txt", "r");

    desenPiesa piesa1;

    fscanf(fptr,"%s", &piesa1.nume);
    fscanf(fptr,"%d", &piesa1.nrPuncteLegatura);

    for(int i= 0; i< piesa1.nrPuncteLegatura; i++)
    {
        fscanf(fptr,"%f", &piesa1.puncteLegatura[i].x);
        fscanf(fptr,"%f", &piesa1.puncteLegatura[i].y);

        punct transPoint = translatePoint(piesa1.puncteLegatura[i]);

        putpixel(piesa1.puncteLegatura[i].x, piesa1.puncteLegatura[i].y, WHITE);
    }

    fscanf(fptr,"%s", &piesa1.descriere);


    int Lind =0;
    int Rind = 0;

    while(!feof(fptr))
    {
        char tip;
        fscanf(fptr,"%c", &tip);

        if(tip == 'L')
        {
            fscanf(fptr,"%f", &piesa1.linii[Lind].punct1.x);
            fscanf(fptr,"%f", &piesa1.linii[Lind].punct1.y);
            fscanf(fptr,"%f", &piesa1.linii[Lind].punct2.x);
            fscanf(fptr,"%f", &piesa1.linii[Lind].punct2.y);

            punct transPunct1 = translatePoint(piesa1.linii[Lind].punct1);
            punct transPunct2 = translatePoint(piesa1.linii[Lind].punct2);

            line(transPunct1.x,
                 transPunct1.y,
                 transPunct2.x,
                 transPunct2.y);

            Lind++;
        }
        if(tip == 'R')
        {
            fscanf(fptr,"%f", &piesa1.dreptunghiuri[Rind].stangaSus.x);
            fscanf(fptr,"%f", &piesa1.dreptunghiuri[Rind].stangaSus.y);
            fscanf(fptr,"%f", &piesa1.dreptunghiuri[Rind].dreaptaJos.x);
            fscanf(fptr,"%f", &piesa1.dreptunghiuri[Rind].dreaptaJos.y);

            punct transStangaSus = translatePoint(piesa1.dreptunghiuri[Rind].stangaSus);
            punct transDreaptaJos = translatePoint(piesa1.dreptunghiuri[Rind].dreaptaJos);

            rectangle(transStangaSus.x,
                      transStangaSus.y,
                      transDreaptaJos.x,
                      transDreaptaJos.y);
            Rind++;
        }
    }
    getch();
    closegraph();
    return 0;
}
