#include <stdio.h>
#include <string.h>
#include <winbgim.h>
#include <iostream>
#include <time.h>

#define MAX1 50
#define MAX2 40
#define FUNDAL 0

#define WIDTH 1000
#define HEIGHT 600

using namespace std;

float zoom=10.0;

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
    int frecv;
};

struct legatura
{
    int nod1, nod2; // cele doua noduri ce se leaga
    int punct1, punct2; // punctele de legatura de la cele doua noduri
    int tipLegatura; // nu am folosit, dar va trebui folosit

    punctLegatura p1, p2;
};

void initializeaza(piesa& P)
{
    P.orientare=0;
    char numeFisier[MAX1],s[MAX1];
    strcpy(numeFisier,P.nume);
    strcat(numeFisier,".ps");
    FILE* f=fopen(numeFisier,"rt");
    fscanf(f,"%s",&P.nume);
    /*printf("%s\n",P.nume);*/
    fscanf(f,"%d",&P.nrLegaturi);
    /*printf("%d\n",P.nrLegaturi); */
    for (unsigned i=1; i<=P.nrLegaturi; i++)
    {
        fscanf(f,"%f%f",&P.pLeg[i].x,&P.pLeg[i].y);
        /* printf("%f %f\n",P.pLeg[i].x,P.pLeg[i].y); */
    }
    fscanf(f,"%s",&P.continut);
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

void rotestePuncteDeLegatura(piesa &P)
{
    float x_1,y_1,x_2,y_2;
    float x1,y1,x2,y2;
    x1=P.pLeg[1].x;
    y1=P.pLeg[1].y;
    x2=P.pLeg[2].x;
    y2=P.pLeg[2].y;

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
    P.pLeg[1].x = x_1;
    P.pLeg[1].y = y_1;
    P.pLeg[2].x = x_2;
    P.pLeg[2].y = y_2;
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

void deseneazaPuncteDeLegatura(piesa P)
{
    circle(P.x + P.pLeg[1].x * zoom,P.y + P.pLeg[1].y * zoom,zoom/1.5f);
    circle(P.x + P.pLeg[2].x * zoom,P.y + P.pLeg[2].y * zoom,zoom/1.5f);
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

void deseneaza(piesa P, int culoare, int nrRepetitiiPiesa = 0)
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

    rotestePuncteDeLegatura(P);
    ///NEW
    //deseneazaPuncteDeLegatura(P);

    punctLegatura textOffset;
    textOffset.x = -zoom *3;
    textOffset.y = zoom *3;

    char numeCuInd[50];
    char numBuff[10];

    sprintf (numBuff, "%d", nrRepetitiiPiesa);
    strcpy(numeCuInd, P.nume);
    strcat(numeCuInd, " - ");
    strcat(numeCuInd, numBuff);

    if(strcmp(P.continut, "-"))
        outtextxy(P.x + textOffset.x, P.y + textOffset.y, P.continut);

    if(nrRepetitiiPiesa != -1)
        outtextxy(P.x + textOffset.x, P.y - textOffset.y * 1.5f, numeCuInd);
    else
        outtextxy(P.x + textOffset.x, P.y - textOffset.y * 1.5f, P.nume);

}

void amplaseaza(piesa& P, unsigned x, unsigned y, unsigned orient, int nrRepetitiiPiesa = 0, int color = WHITE)
{
    P.x=x;
    P.y=y;
    P.orientare=orient;
    deseneaza(P, color, nrRepetitiiPiesa);
    deseneazaPuncteDeLegatura(P); ///NEW

}

void roteste(piesa& P)
{
    deseneaza(P,FUNDAL);
    P.orientare=(P.orientare+1) % 4;
    deseneaza(P, WHITE);
}



void updateZoom(int increment)
{
    zoom +=increment;
    cleardevice();
    // Redraw canvas
    //deseneazaMeniul(Meniu,nrPieseMeniu);
}

unsigned alegePiesa(piesa vectorPiese[MAX2], unsigned nrPiese)
{
    bool click=false;
    unsigned i, nrPiesaAleasa=0;
    int xMouse,yMouse;
    do
    {
        //New Frame Event Update
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            for (i=1; i<=nrPiese; i++)
            {
                //Mouse Click Event
                //if(xMouse >= WIDTH - 50 && yMouse >= HEIGHT - 50) updateZoom(4);

                if (abs(vectorPiese[i].x - xMouse)<=10
                        && abs(vectorPiese[i].y - yMouse)<=10)
                {
                    nrPiesaAleasa=i;
                    click=true;
                }
            }
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
    strcpy(Meniu[12].nume,"NOD");
    strcpy(Meniu[13].nume,"STOP");
    rectangle(0,0,getmaxx(),50);
    int lat=getmaxx()/nrPieseMeniu;
    for (unsigned i=1; i<=nrPieseMeniu; i++)
    {
        initializeaza(Meniu[i]);
        amplaseaza(Meniu[i],lat*i-lat/2,25,0);
    }
}

piesa Meniu[MAX1];
unsigned nrPieseMeniu=13;
//int frecvPieseMeniu[13];

unsigned alegeOPiesaDinMeniu(piesa Meniu[MAX2],unsigned nrPieseMeniu)
{
    unsigned nrPiesaAleasa=0;
    nrPiesaAleasa=alegePiesa(Meniu,nrPieseMeniu);
    //frecvPieseMeniu[nrPiesaAleasa]++;
    //Meniu[nrPiesaAleasa].frecv++;
    //cout<<nrPiesaAleasa;
    // printf("%d, ",nrPiesaAleasa);
    return nrPiesaAleasa;
}

void punePiesa(piesa& P,int nrRepetitiiPiesa = 0)
{
    bool click=false;
    int xMouse,yMouse;
    do
    {
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            roteste(P);
            rotestePuncteDeLegatura(P); /// NEW
            Beep(1500, 100);
        }
        else if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            // printf("%d, %d\n",xMouse,yMouse);
            amplaseaza(P,xMouse,yMouse,P.orientare, nrRepetitiiPiesa);
            //cout<<nrRepetitiiPiesa<<endl;
            click=true;
        }
    }
    while (!click);
}

piesa Piesa[MAX2];
unsigned nrPiese=0;
unsigned nrPiesaAleasa;

legatura Legatura[MAX2];
unsigned nrLegaturi=0;

void savePiecesInFile()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%d%b%y - %H;%M;%S", &tstruct);

    strcat(buf, ".txt");
    cout<<buf;
    FILE *fptr = fopen(buf,"w");
    for(int i = 1; i<=nrPiese; i++)
    {
        //fprintf(fptr,"%d\n",Piesa[i].id);
        fprintf(fptr,"%s\n",Piesa[i].nume);
        fprintf(fptr,"%d %d\n",Piesa[i].x, Piesa[i].y);
        fprintf(fptr,"%d\n",Piesa[i].orientare);
        fprintf(fptr,"%s\n",Piesa[i].continut);
        //NrLegaturi
        fprintf(fptr,"%u\n",Piesa[i].nrLegaturi);
        for(int j = 1; j<= Piesa[i].nrLegaturi; j++)
        {
            fprintf(fptr,"%f %f\n",Piesa[i].pLeg[j].x, Piesa[i].pLeg[j].y);
        }
        //Descriere
        fprintf(fptr,"%u\n",Piesa[i].descr.nComenzi);

        for(int j = 1; j<= Piesa[i].descr.nComenzi; j++)
        {
            fprintf(fptr,"%c\n",Piesa[i].descr.comanda[j]);
            fprintf(fptr,"%f %f %f %f\n",Piesa[i].descr.x1[j], Piesa[i].descr.y1[j],Piesa[i].descr.x2[j], Piesa[i].descr.y2[j]);

        }

        fprintf(fptr,"%d\n",Piesa[i].frecv);
        fprintf(fptr, "\n");
    }
    fclose(fptr);
}


void drawLine(int x1, int y1, int x2, int y2, int cul)
{
    setcolor(cul);
    line(x1,y1,(x1+x2)/2,y1);
    line((x1+x2)/2,y1,(x1+x2)/2,y2);
    line((x1+x2)/2,y2,x2,y2);
}

void deseneazaLegatura(int &idNod1, int &p1, int &idNod2, int &p2)
{
    bool click=false;
    int i, xMouse,yMouse;
    // aleg un punct de legatura (p1) de la nodul 1 (idNod1)
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            Beep(2000,100);
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            for (i=1; i<=nrPiese; i++)
                if (abs(Piesa[i].pLeg[1].x * zoom + Piesa[i].x - xMouse)<=5
                        && abs(Piesa[i].pLeg[1].y * zoom + Piesa[i].y - yMouse)<=5)
                {
                    idNod1=i;
                    p1=1;
                    click=true;
                }
                else if (abs(Piesa[i].pLeg[2].x * zoom + Piesa[i].x - xMouse)<=5
                         && abs(Piesa[i].pLeg[2].y * zoom + Piesa[i].y - yMouse)<=5)
                {
                    idNod1=i;
                    p1=2;
                    click=true;
                }
        }
    }
    while (!click);
    // aleg un punct de legatura (p2) de la nodul 2 (idNod2)
    // pana aleg, desenez mereu o linie
    click=false;
    int x1,y1,x2,y2;
    x1=Piesa[idNod1].pLeg[p1].x*zoom + Piesa[idNod1].x;
    y1=Piesa[idNod1].pLeg[p1].y*zoom + Piesa[idNod1].y;
    xMouse=mousex();
    yMouse=mousey();
    do
    {
        drawLine(x1,y1,xMouse,yMouse, 15-FUNDAL);
        delay(50);
        drawLine(x1,y1,xMouse,yMouse,FUNDAL);
        xMouse=mousex();
        yMouse=mousey();
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            Beep(1200,100);
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            for (i=1; i<=nrPiese; i++)
                if (abs(Piesa[i].pLeg[1].x * zoom + Piesa[i].x - xMouse)<=5
                        && abs(Piesa[i].pLeg[1].y * zoom + Piesa[i].y - yMouse)<=5)
                {
                    idNod2=i;
                    p2=1;
                    click=true;
                }
                else if (abs(Piesa[i].pLeg[2].x * zoom + Piesa[i].x - xMouse)<=5
                         && abs(Piesa[i].pLeg[2].y * zoom + Piesa[i].y - yMouse)<=5)
                {
                    idNod2=i;
                    p2=2;
                    click=true;
                }
        }
    }
    while (!click);
    drawLine(x1,y1,xMouse,yMouse, 15-FUNDAL);
}

void checkForUpdates()
{
    ///init Legaturi
    nrLegaturi ++;
    int idNod1, idNod2, p1, p2;
    int clickZone = 15;

    ///Init Piesa Noua
    nrPiesaAleasa=0;

    ///Init Move Piece
    piesa PiesaAux;

    bool NewPieceLoop = false;
    bool NewConnectionLoop = false;
    bool MovePieceLoop = false;

    ///MAIN LOOP
    bool click=false;
    int i, xMouse,yMouse;
    // aleg un punct de legatura (p1) de la nodul 1 (idNod1)
    do
    {
        ///Left Mouse Clicked Event
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            ///New Connection point checker
            for (i=1; i<=nrPiese; i++)
                if (abs(Piesa[i].pLeg[1].x * zoom + Piesa[i].x - xMouse)<=clickZone
                        && abs(Piesa[i].pLeg[1].y * zoom + Piesa[i].y - yMouse)<=clickZone)
                {
                    Beep(2000,100);
                    idNod1=i;
                    p1=1;
                    click=true;
                    NewConnectionLoop = true;
                }
                else if (abs(Piesa[i].pLeg[2].x * zoom + Piesa[i].x - xMouse)<=clickZone
                         && abs(Piesa[i].pLeg[2].y * zoom + Piesa[i].y - yMouse)<=clickZone)
                {
                    Beep(2000,100);
                    idNod1=i;
                    p1=2;
                    click=true;
                    NewConnectionLoop = true;
                }
            ///New Piece From Menu Checker
            for (i=1; i<=nrPieseMeniu; i++)
                if (abs(Meniu[i].x - xMouse)<=clickZone
                        && abs(Meniu[i].y - yMouse)<=clickZone)
                {
                    Beep(1000,100);
                    nrPiesaAleasa=i;
                    click=true;
                    //frecvPieseMeniu[nrPiesaAleasa]++;
                    Meniu[nrPiesaAleasa].frecv++;
                    NewPieceLoop = true;
                }
        }

        ///Right Mouse Clicked Event
        if(ismouseclick(WM_RBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_RBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            ///New Piece From Editor Checker
            for (i=1; i<=nrPiese; i++)
                if (abs(Piesa[i].x - xMouse)<=clickZone
                        && abs(Piesa[i].y - yMouse)<=clickZone)
                {
                    Beep(1600,100);
                    PiesaAux = Piesa[i];
                    nrPiesaAleasa=i;
                    click=true;
                    MovePieceLoop = true;
                }
        }


        ///Zoom in
        if(ismouseclick(WM_RBUTTONDBLCLK) && !click)
        {
            clearmouseclick(WM_RBUTTONDBLCLK);
            ///Hide Old pieces
            for(int i = 0; i<=nrPiese; i++)
            {
                amplaseaza(Piesa[i], Piesa[i].x, Piesa[i].y, Piesa[i].orientare,Piesa[i].frecv, BLACK);
            }
            zoom +=1;
            ///Redraw bigger Pieces
            for(int i = 0; i<=nrPiese; i++)
            {
                amplaseaza(Piesa[i], Piesa[i].x, Piesa[i].y, Piesa[i].orientare,Piesa[i].frecv, WHITE);
            }
        }
        ///Zoom Out
        if(ismouseclick(WM_LBUTTONDBLCLK) && !click)
        {
            clearmouseclick(WM_LBUTTONDBLCLK);
            ///Hide Old pieces
            for(int i = 0; i<=nrPiese; i++)
            {
                amplaseaza(Piesa[i], Piesa[i].x, Piesa[i].y, Piesa[i].orientare,Piesa[i].frecv, BLACK);
            }
            zoom -=1;
            ///Redraw bigger Pieces
            for(int i = 0; i<=nrPiese; i++)
            {
                amplaseaza(Piesa[i], Piesa[i].x, Piesa[i].y, Piesa[i].orientare,Piesa[i].frecv, WHITE);
            }
        }
    }
    while (!click);

    ///Start Checking for 2nd Connection Point
    //aleg un punct de legatura (p2) de la nodul 2 (idNod2) pana aleg, desenez mereu o linie
    click=false;
    xMouse=mousex();
    yMouse=mousey();
    ///Second Loop - Connections
    if(NewConnectionLoop)
    {
        int x1,y1,x2,y2;
        x1=Piesa[idNod1].pLeg[p1].x*zoom + Piesa[idNod1].x;
        y1=Piesa[idNod1].pLeg[p1].y*zoom + Piesa[idNod1].y;
        do
        {
            drawLine(x1,y1,xMouse,yMouse, 15-FUNDAL);
            delay(50);
            drawLine(x1,y1,xMouse,yMouse,FUNDAL);
            xMouse=mousex();
            yMouse=mousey();
            if(ismouseclick(WM_LBUTTONDOWN) && !click)
            {
                Beep(2300,100);
                clearmouseclick(WM_LBUTTONDOWN);
                xMouse=mousex();
                yMouse=mousey();
                ///Actual Checking for 2nd Connection Point
                for (i=1; i<=nrPiese; i++)
                {
                    if (abs(Piesa[i].pLeg[1].x * zoom + Piesa[i].x - xMouse)<=clickZone
                            && abs(Piesa[i].pLeg[1].y * zoom + Piesa[i].y - yMouse)<=clickZone)
                    {
                        //cout<<"Conectat in p1";
                        idNod2=i;
                        p2=1;
                        click=true;
                        punctNou.x = Piesa[i].pLeg[1].x * zoom + Piesa[i].x;
                        break;
                    }
                    else if (abs(Piesa[i].pLeg[2].x * zoom + Piesa[i].x - xMouse)<=clickZone
                             && abs(Piesa[i].pLeg[2].y * zoom + Piesa[i].y - yMouse)<=clickZone)
                    {
                        //cout<<"Conectat in p2";
                        idNod2=i;
                        p2=2;
                        click=true;
                        break;
                    }
                    else
                    {
                        //cout<<"Nod Nou";
                        nrPiese++;
                        Meniu[12].frecv++;
                        Piesa[nrPiese]=Meniu[12]; // NOD
                        int nrRepetitiiPiesa = Piesa[nrPiese].frecv; //frecvPieseMeniu[nrPiesaAleasa];
                        amplaseaza(Piesa[nrPiese],xMouse,yMouse,0, nrRepetitiiPiesa);
                        deseneazaPuncteDeLegatura(Piesa[nrPiese]);
                        click=true;
                        //frecvPieseMeniu[nrPiesaAleasa]++;
                        break;
                    }
                }
            }
        }
        while (!click);
        Legatura[nrLegaturi].p1.x = x1;
        Legatura[nrLegaturi].p1.y = y1;
        Legatura[nrLegaturi].p2.x = xMouse;
        Legatura[nrLegaturi].p2.y = yMouse;

        drawLine(x1,y1,xMouse,yMouse, (rand()%14)+1 );//15-FUNDAL);
        //drawLine(x1,y1,xMouse,yMouse, 15-FUNDAL);
        NewConnectionLoop = false;
    }

    ///Second Loop - New Piece
    if(NewPieceLoop)
    {
        if (nrPiesaAleasa!=nrPieseMeniu)
        {
            nrPiese++;
            Piesa[nrPiese]=Meniu[nrPiesaAleasa];
            int nrRepetitiiPiesa = Piesa[nrPiese].frecv; //frecvPieseMeniu[nrPiesaAleasa];
            punePiesa(Piesa[nrPiese], nrRepetitiiPiesa); ///Loop
            Beep(1300,100);
            //deseneazaPuncteDeLegatura(Piesa[nrPiese]);
        }
        NewPieceLoop = false;
    }

    ///Second Loop - Move a piece
    if(MovePieceLoop)
    {
        //nrPiese++;
        Piesa[nrPiesaAleasa]=PiesaAux;
        int nrRepetitiiPiesa = Piesa[nrPiesaAleasa].frecv; //frecvPieseMeniu[nrPiesaAleasa];
        deseneaza(PiesaAux, BLACK, nrRepetitiiPiesa);
        punePiesa(Piesa[nrPiesaAleasa], nrRepetitiiPiesa); ///Loop
        /*
                for(int i = 0; i<nrLegaturi; i++)
                {
                    cout<<Legatura[i].p1.x << " " << Legatura[i].p1.y<<endl;
                    cout<<Legatura[i].p2.x << " " << Legatura[i].p2.y<<endl;
                    cout<<endl;
                }
        */
        Beep(1900,100);
        deseneazaPuncteDeLegatura(Piesa[nrPiese]);
        MovePieceLoop = false;
    }

    ///Ending Legaturi
    Legatura[nrLegaturi].nod1=idNod1;
    Legatura[nrLegaturi].nod2=idNod2;
    Legatura[nrLegaturi].punct1=p1;
    Legatura[nrLegaturi].punct2=p2;

    ///Ending piesa noua
    // printf("%d, ",nrPiesaAleasa);
}

int main()
{
    initwindow(WIDTH,HEIGHT,"Electron");
    srand(time(NULL));

    deseneazaMeniul(Meniu,nrPieseMeniu);
    nrLegaturi=0;

    //int ind = 0;
    do
    {
        checkForUpdates();
        ///Redraw everything to prevent user from clearing the pieces
        for(int i = 0; i<=nrPiese; i++)
        {
            amplaseaza(Piesa[i], Piesa[i].x, Piesa[i].y, Piesa[i].orientare,Piesa[i].frecv, WHITE);
        }
    }
    while (nrPiesaAleasa!=nrPieseMeniu);
    savePiecesInFile();
    // getch();
    closegraph();
    return 0;
}
