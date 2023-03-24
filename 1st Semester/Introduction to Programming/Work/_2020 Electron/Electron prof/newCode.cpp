#include <stdio.h>
#include <string.h>
#include <winbgim.h>
#include <iostream>

#define MAX1 20
#define MAX2 40
#define FUNDAL 0

using namespace std;

float zoom=8.0;

struct descriere
{
    char comanda[MAX1];
    unsigned nComenzi;
    float x1[MAX1], y1[MAX1], x2[MAX1], y2[MAX1];
};

struct punctLegatura
{
    float x, y;
};

void roteste (float x, float y, float & xnou, float & ynou)
{
    xnou = y;
    ynou = -x;
}

struct piesa
{
    unsigned id;
    char nume[MAX1];
    int x,y;
    unsigned orientare;
    char continut[MAX2];
    unsigned nrLegaturi;
    punctLegatura pLeg[MAX1];
    descriere descr;
};

struct legatura
{
    unsigned bloc1, bloc2;
    unsigned varianta;
};

void initializeaza(piesa &P)
{
    P.orientare=0;
    char numeFisier[MAX1],s[MAX1];
    strcpy(numeFisier,P.nume);
    strcat(numeFisier,".ps");
    FILE* f=fopen(numeFisier,"rt");
    fscanf(f,"%s",s);
    /*printf("%s\n",s);*/
    fscanf(f,"%d",&P.nrLegaturi);
    /*printf("%d\n",P.nrLegaturi); */
    for (unsigned i=1; i<=P.nrLegaturi; i++)
    {
        fscanf(f,"%f%f",&P.pLeg[i].x,&P.pLeg[i].y);
        /* printf("%f %f\n",P.pLeg[i].x,P.pLeg[i].y); */
    }
    fscanf(f,"%s",s);
    /* printf("%s\n",s); */
    fscanf(f,"%d\n",&P.descr.nComenzi);
    /* printf("%d comenzi\n",P.descr.nComenzi); */
    for (unsigned i=1; i<=P.descr.nComenzi; i++)
    {
        fscanf(f,"%c%f%f",&P.descr.comanda[i],&P.descr.x1[i],&P.descr.y1[i]);
        fscanf(f,"%f%f\n",&P.descr.x2[i],&P.descr.y2[i]);
        /* printf("%c %f %f %f %f\n",P.descr.comanda[i],P.descr.x1[i],P.descr.y1[i],P.descr.x2[i],P.descr.y2[i]); */
    }
    fclose(f);
}

void myLine(piesa P, unsigned i)
{
    float x_1,y_1,x_2,y_2;
    float x1,y1,x2,y2;
    x1=P.descr.x1[i];
    y1=P.descr.y1[i];
    x2=P.descr.x2[i];
    y2=P.descr.y2[i];
    switch (P.orientare)
    {
    case 0:
        x_1=x1;
        y_1=y1;
        x_2=x2;
        y_2=y2;
        break;
    case 1:
        roteste(x1,y1,x_1,y_1);
        roteste(x2,y2,x_2,y_2);
        break;
    case 2:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        x_1=x1;
        y_1=y1;
        roteste(x2,y2,x_2,y_2);
        roteste(x_2,y_2,x2,y2);
        x_2=x2;
        y_2=y2;
        break;
    case 3:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        roteste(x1,y1,x_1,y_1);
        roteste(x2,y2,x_2,y_2);
        roteste(x_2,y_2,x2,y2);
        roteste(x2,y2,x_2,y_2);
        break;
    }
    line(P.x+zoom*x_1,P.y+zoom*y_1,P.x+zoom*x_2,P.y+zoom*y_2);
}

void myRectangle(piesa P, unsigned i)
{
    float x_1,y_1,x_2,y_2;
    float x1,y1,x2,y2;
    x1=P.descr.x1[i];
    y1=P.descr.y1[i];
    x2=P.descr.x2[i];
    y2=P.descr.y2[i];
    switch (P.orientare)
    {
    case 0:
        x_1=x1;
        y_1=y1;
        x_2=x2;
        y_2=y2;
        break;
    case 1:
        roteste(x1,y1,x_1,y_1);
        roteste(x2,y2,x_2,y_2);
        break;
    case 2:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        x_1=x1;
        y_1=y1;
        roteste(x2,y2,x_2,y_2);
        roteste(x_2,y_2,x2,y2);
        x_2=x2;
        y_2=y2;
        break;
    case 3:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        roteste(x1,y1,x_1,y_1);
        roteste(x2,y2,x_2,y_2);
        roteste(x_2,y_2,x2,y2);
        roteste(x2,y2,x_2,y_2);
        break;
    }
    rectangle(P.x+zoom*x_1,P.y+zoom*y_1,P.x+zoom*x_2,P.y+zoom*y_2);
}

void myEllipse(piesa P, unsigned i)
{
    float x_1,y_1,x_2,y_2;
    float x1,y1,x2,y2;
    x1=P.descr.x1[i];
    y1=P.descr.y1[i];
    x2=P.descr.x2[i];
    y2=P.descr.y2[i];
    switch (P.orientare)
    {
    case 0:
        x_1=x1;
        y_1=y1;
        x_2=x2;
        y_2=y2;
        break;
    case 1:
        roteste(x1,y1,x_1,y_1);
        x_2=y2;
        y_2=x2;
        break;
    case 2:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        x_1=x1;
        y_1=y1;
        x_2=x2;
        y_2=y2;
        break;
    case 3:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        roteste(x1,y1,x_1,y_1);
        x_2=y2;
        y_2=x2;
        break;
    }
    ellipse(P.x+x_1*zoom,P.y+y_1*zoom,0,360,x_2*zoom,y_2*zoom);
}

void myArc(piesa P, unsigned i)
{
    float x1,y1,x2;
    float x_1,y_1;
    x1=P.descr.x1[i];
    y1=P.descr.y1[i];
    x2=P.descr.x2[i]; /* y2=P.descr.y2[i]; */
    switch (P.orientare)
    {
    case 0:
        arc(P.x+x1*zoom,P.y+y1*zoom,-90,90,x2*zoom);
        break;
    case 1:
        roteste(x1,y1,x_1,y_1);
        arc(P.x+x_1*zoom,P.y+y_1*zoom,0,180,x2*zoom);
        break;
    case 2:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        arc(P.x+x1*zoom,P.y+y1*zoom,90,270,x2*zoom);
        break;
    case 3:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        roteste(x1,y1,x_1,y_1);
        arc(P.x+x_1*zoom,P.y+y_1*zoom,-180,0,x2*zoom);
        break;
    }
}

void deseneaza(piesa P, int culoare)
{
    setcolor(culoare);
    for (unsigned i=1; i<=P.descr.nComenzi; i++)
        switch(P.descr.comanda[i])
        {
        case 'L':
            myLine(P,i);
            break;
        case 'R':
            myRectangle(P,i);
            break;
        case 'O':
            myEllipse(P,i);
            break;
        case 'A':
            myArc(P,i);
            break;
        }
}

void amplaseaza(piesa& P, unsigned x, unsigned y, unsigned orient)
{
    P.x=x;
    P.y=y;
    P.orientare=orient;
    deseneaza(P, 12);
}

void roteste(piesa& P)
{
    deseneaza(P,FUNDAL);
    P.orientare=(P.orientare+1) % 4;
    deseneaza(P, 15);

}

unsigned alegePiesa(piesa vectorPiese[MAX2], unsigned nrPiese)
{
    bool click=false;
    unsigned i, nrPiesaAleasa=0;
    int xMouse,yMouse;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            cout << xMouse << " ** ";
            yMouse=mousey();
            cout << yMouse << endl;
            for (i=1; i<=nrPiese; i++)
                if (abs(vectorPiese[i].x - xMouse)<=10
                        && abs(vectorPiese[i].y - yMouse)<=10)
                {
                    nrPiesaAleasa=i;
                    click=true;
                }
        }
    while (!click);
    return nrPiesaAleasa;
}


void deseneazaMeniul(piesa Meniu[MAX2],unsigned int nrPieseMeniu)
{
    setcolor(WHITE);
    rectangle(0,0,getmaxx(),getmaxy());
    strcpy(Meniu[1].nume,"DIODA");
    strcpy(Meniu[2].nume,"ZENNER");
    strcpy(Meniu[3].nume,"TRANZNPN");
    strcpy(Meniu[4].nume,"TRANZPNP");
    strcpy(Meniu[5].nume,"CONDENS");
    strcpy(Meniu[6].nume,"REZIST");
    strcpy(Meniu[7].nume,"BATERIE");
    strcpy(Meniu[8].nume,"POLARIZ");
    strcpy(Meniu[9].nume,"SINU");
    strcpy(Meniu[10].nume,"SERVOMOT");
    strcpy(Meniu[11].nume,"AMPLOP");
    strcpy(Meniu[12].nume,"STOP");
    rectangle(0,0,getmaxx(),60);
    int lat=getmaxx()/nrPieseMeniu;
    printf("%d\n", lat);
    for (unsigned i=1; i<=nrPieseMeniu; i++)
    {
        initializeaza(Meniu[i]);
        printf("%d %f\n", i, lat*i-lat/1.6);
        amplaseaza(Meniu[i],lat*i-lat/1.6,30,0);
    }
}

unsigned alegeOPiesaDinMeniu(piesa Meniu[MAX2],unsigned nrPieseMeniu)
{
    unsigned nrPiesaAleasa=0;
    nrPiesaAleasa=alegePiesa(Meniu,nrPieseMeniu);
    // printf("%d, ",nrPiesaAleasa);
    return nrPiesaAleasa;
}

void punePiesa(piesa& P){
    bool click=false;
    int xMouse,yMouse;
    int orient = 0;
    while(!ismouseclick(WM_LBUTTONDOWN)) ///**Orientare doar in meniu**
        if(ismouseclick(WM_RBUTTONDOWN))
         {
            orient++;
            clearmouseclick(WM_RBUTTONDOWN);
            roteste(P);
            if(orient > 4)
                orient = 0;
         }

   do{
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex(); yMouse=mousey();
            printf("%d, %d\n",xMouse,yMouse);
            amplaseaza(P,xMouse,yMouse,orient);
            click=true;
        }
    }while (!click);

}
int main()
{
    initwindow(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),"Electron");
    piesa Meniu[MAX1];
    unsigned nrPieseMeniu=12;

    piesa Piesa[MAX2];
    unsigned nrPiese=0;

    legatura Legatura[MAX2];
    unsigned nrLegaturi=0;

    unsigned nrPiesaAleasa;
    deseneazaMeniul(Meniu,nrPieseMeniu);
    do
    {
        nrPiesaAleasa=alegeOPiesaDinMeniu(Meniu,nrPieseMeniu);
        // printf("Am ales piesa %u\n",nrPiesaAleasa);
        if (nrPiesaAleasa!=nrPieseMeniu)
        {
            nrPiese++;
            Piesa[nrPiese]=Meniu[nrPiesaAleasa];
            punePiesa(Piesa[nrPiese]);
        }
    }
    while (nrPiesaAleasa!=nrPieseMeniu);
  //  getch();
    closegraph();
    return 0;
}
