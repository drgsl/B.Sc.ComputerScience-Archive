#include <time.h>
#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <string.h>

#define PIECE_COLOR 15
#define HOVER_COLOR 13
#define NODE_COLOR YELLOW
#define TEXT_COLOR YELLOW
#define MAX1 50
#define MAX2 40
#define FUNDAL 0

using namespace std;

int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

int midX = WIDTH /2;
int midY = HEIGHT /2;

unsigned nrPieseMeniu = 13;
unsigned nrPiesaAleasa;
unsigned nrLegaturi;
unsigned nrPiese;
int order, n;
int frecvPieseMeniu[13];
float zoom = 7.0;

struct point
{
    float x, y;
};
point Mouse;

struct descriere
{
    char comanda[MAX1];
    unsigned nComenzi;
    float x1[MAX1], y1[MAX1], x2[MAX1], y2[MAX1];
};

struct piesa
{
    unsigned id;
    int frecv;
    char nume[MAX1];
    char continut[MAX1];
    int x,y;
    unsigned orientare;
    unsigned nrLegaturi;
    point pLeg[MAX1];
    descriere descr;
};
piesa Meniu[MAX1];
piesa Piesa[MAX2];

struct node
{
    point connectPoint[MAX1];
};
node stringNode[MAX1];

struct legatura
{
    int nod1, nod2; // cele doua noduri ce se leaga
    int punct1, punct2; // punctele de legatura de la cele doua noduri
    int tipLegatura; // nu am folosit, dar va trebui folosit
};
legatura stringConnection[MAX2];
legatura Legatura[MAX2];

struct button
{
    char name[50];
    point point1;
    point point2;
};
button b[5];
button scheme[100];

void initializeaza(piesa& P)
{
    char numeFisier[MAX1], s[MAX1];
    P.orientare = 0;

    strcpy(numeFisier, P.nume);
    strcat(numeFisier, ".ps");
    FILE* f = fopen(numeFisier, "r");

    fscanf(f, "%s", &P.nume);
    fscanf(f, "%d", &P.nrLegaturi);

    for (unsigned i = 1; i <= P.nrLegaturi; i++)
        fscanf(f, "%f%f", &P.pLeg[i].x, &P.pLeg[i].y);

    fscanf(f, "%s", &P.continut);
    cout << "\n Numele este: -> " << P.continut;
    fscanf(f, "%d\n", &P.descr.nComenzi);

    for (unsigned i = 1; i <= P.descr.nComenzi; i++)
    {
        fscanf(f, "%c%f%f", &P.descr.comanda[i],
               &P.descr.x1[i], &P.descr.y1[i]);
        fscanf(f, "%f%f\n", &P.descr.x2[i], &P.descr.y2[i]);
    }
    fclose(f);

}

void roteste (float x, float y, float & xnou, float & ynou)
{
    xnou = y;
    ynou = -x;
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

void deseneazaPuncteDeLegatura(piesa P, node &Node)
{
     int xNode, yNode;
    setcolor(NODE_COLOR);
    for(int i = 1; i <= P.nrLegaturi; i++) ///Save the connected points
    {
        Node.connectPoint[i].x = P.x + zoom*P.pLeg[i].x;
        Node.connectPoint[i].y= P.y + zoom*P.pLeg[i].y;

        xNode = Node.connectPoint[i].x;
        yNode = Node.connectPoint[i].y;
        putpixel(xNode, yNode, RED);

        fillellipse(xNode, yNode, zoom/2, zoom/2);
    }
}

/*void drawNode(piece& Piece, node& Node, unsigned id)
{
    int xNode, yNode;
    setcolor(14);
    for(int i = 1; i <= Piece.connections; i++)
    {
        Node.connectPoint[i].x = Piece.x + zoom*Piece.connectP[i].x;
        Node.connectPoint[i].y= Piece.y + zoom*Piece.connectP[i].y;

        xNode = Node.connectPoint[i].x ;
        yNode = Node.connectPoint[i].y;

        fillellipse(xNode, yNode, 2, 2 );
    }
}*/

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

void deseneaza(piesa P, int culoare, int call, int nrRepetitiiPiesa = 0)
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
    if(call)
            rotestePuncteDeLegatura(P);
        //deseneazaPuncteDeLegatura(P, *stringNode);
    /*setcolor(15);
    settextstyle(11,HORIZ_DIR,1);
    //cout << nrRepetitiiPiesa << endl;

    point textOffset;
    textOffset.x = -zoom *7;
    textOffset.y = zoom *2;

    char numeCuInd[50];
    char numBuff[10];

    sprintf (numBuff, "%d", nrRepetitiiPiesa);
    strcpy(numeCuInd, P.nume);
    strcat(numeCuInd, " - ");
    strcat(numeCuInd, numBuff);

    if(strcmp(P.nume, "-"))
        outtextxy(P.x + textOffset.x*1.1, P.y + textOffset.y*2, P.nume);

    if(nrRepetitiiPiesa != -1)
        outtextxy(P.x + textOffset.x, P.y - textOffset.y*3, numeCuInd);
    else
        outtextxy(P.x + textOffset.x, P.y - textOffset.y*3, P.nume);*/
}

void amplaseaza(piesa& P, unsigned x, unsigned y, unsigned orient, int call, int color, int nrRepetitiiPiesa = 0 ){
    P.x=x;
    P.y=y;
    P.orientare=orient;
    cout << "----- " << P.x << " " << P.y << endl;
    deseneazaPuncteDeLegatura(P,*stringNode);
    deseneaza(P, color, call, nrRepetitiiPiesa);
}

void roteste(piesa& P)
{
    deseneaza(P,FUNDAL,0);
    P.orientare=(P.orientare+1) % 4;
    deseneaza(P, WHITE,0);
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
    do
    {
        //New Frame Event Update
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Mouse.x=mousex();
            Mouse.y=mousey();
            for (i=1; i<=nrPiese; i++)
            {
                //Mouse Click Event
                //if(Mouse.x >= WIDTH - 50 && Mouse.y >= HEIGHT - 50) updateZoom(4);

                if (abs(vectorPiese[i].x - Mouse.x)<=50
                        && abs(vectorPiese[i].y - Mouse.y)<=50)
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
        if(i == 12)
            amplaseaza(Meniu[i],lat*i-lat/3,25,0,1,PIECE_COLOR);
        else if(i > 9 && i < 13)
                amplaseaza(Meniu[i],lat*i*1.1-lat*1.3,25,0,0,PIECE_COLOR);
              else
                amplaseaza(Meniu[i],lat*i-lat/2.5,25,0,0,PIECE_COLOR);
    }
}

unsigned alegeOPiesaDinMeniu(piesa Meniu[MAX2],unsigned nrPieseMeniu)
{
    unsigned nrPiesaAleasa=0;
    nrPiesaAleasa=alegePiesa(Meniu,nrPieseMeniu);
    frecvPieseMeniu[nrPiesaAleasa]++;
    // printf("%d, ",nrPiesaAleasa);
    return nrPiesaAleasa;
}

void punePiesa(piesa& P,int nrRepetitiiPiesa = 0)
{
    bool click=false;
    do
    {
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            roteste(P);
            rotestePuncteDeLegatura(P);
            Beep(1500, 100);
        }
        else if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Mouse.x=mousex();
            Mouse.y=mousey();
            // printf("%d, %d\n",Mouse.x,Mouse.y);
            amplaseaza(P,Mouse.x,Mouse.y,P.orientare, nrRepetitiiPiesa,PIECE_COLOR);
            //cout<<nrRepetitiiPiesa<<endl;
            click=true;
        }
    }
    while (!click);
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
    int i;
    // aleg un punct de legatura (p1) de la nodul 1 (idNod1)
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            Beep(2000,100);
            clearmouseclick(WM_LBUTTONDOWN);
            Mouse.x=mousex();
            Mouse.y=mousey();
            for (i=1; i<=nrPiese; i++)
                if (abs(Piesa[i].pLeg[1].x * zoom + Piesa[i].x - Mouse.x)<=5
                        && abs(Piesa[i].pLeg[1].y * zoom + Piesa[i].y - Mouse.y)<=5)
                {
                    idNod1=i;
                    p1=1;
                    click=true;
                }
                else if (abs(Piesa[i].pLeg[2].x * zoom + Piesa[i].x - Mouse.x)<=5
                         && abs(Piesa[i].pLeg[2].y * zoom + Piesa[i].y - Mouse.y)<=5)
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
    Mouse.x=mousex();
    Mouse.y=mousey();
    do
    {
        drawLine(x1,y1,Mouse.x,Mouse.y, 15-FUNDAL);
        delay(50);
        drawLine(x1,y1,Mouse.x,Mouse.y,FUNDAL);
        Mouse.x=mousex();
        Mouse.y=mousey();
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            Beep(1200,100);
            clearmouseclick(WM_LBUTTONDOWN);
            Mouse.x=mousex();
            Mouse.y=mousey();
            for (i=1; i<=nrPiese; i++)
                if (abs(Piesa[i].pLeg[1].x * zoom + Piesa[i].x - Mouse.x)<=5
                        && abs(Piesa[i].pLeg[1].y * zoom + Piesa[i].y - Mouse.y)<=5)
                {
                    idNod2=i;
                    p2=1;
                    click=true;
                }
                else if (abs(Piesa[i].pLeg[2].x * zoom + Piesa[i].x - Mouse.x)<=5
                         && abs(Piesa[i].pLeg[2].y * zoom + Piesa[i].y - Mouse.y)<=5)
                {
                    idNod2=i;
                    p2=2;
                    click=true;
                }
        }
    }
    while (!click);
    drawLine(x1,y1,Mouse.x,Mouse.y, 15-FUNDAL);
}

void Update()
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
                amplaseaza(Piesa[i], Piesa[i].x, Piesa[i].y, Piesa[i].orientare, BLACK, Piesa[i].frecv);
            }
            zoom +=1;
            ///Redraw bigger Pieces
            for(int i = 0; i<=nrPiese; i++)
            {
                amplaseaza(Piesa[i], Piesa[i].x, Piesa[i].y, Piesa[i].orientare, WHITE,Piesa[i].frecv);
            }
        }
        ///Zoom Out
        if(ismouseclick(WM_LBUTTONDBLCLK) && !click)
        {
            clearmouseclick(WM_LBUTTONDBLCLK);
            ///Hide Old pieces
            for(int i = 0; i<=nrPiese; i++)
            {
                amplaseaza(Piesa[i], Piesa[i].x, Piesa[i].y, Piesa[i].orientare, BLACK, Piesa[i].frecv);
            }
            zoom -=1;
            ///Redraw bigger Pieces
            for(int i = 0; i<=nrPiese; i++)
            {
                amplaseaza(Piesa[i], Piesa[i].x, Piesa[i].y, Piesa[i].orientare, WHITE,Piesa[i].frecv);
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
                        cout<<"Conectat in p1";
                        idNod2=i;
                        p2=1;
                        click=true;
                        break;
                    }
                    else if (abs(Piesa[i].pLeg[2].x * zoom + Piesa[i].x - xMouse)<=clickZone
                         && abs(Piesa[i].pLeg[2].y * zoom + Piesa[i].y - yMouse)<=clickZone)
                    {
                        cout<<"Conectat in p2";
                        idNod2=i;
                        p2=2;
                        click=true;
                        break;
                    }
                    else
                    {
                        cout<<"Nod Nou";
                        nrPiese++;
                        Meniu[12].frecv++;
                        Piesa[nrPiese]=Meniu[12]; // NOD
                        int nrRepetitiiPiesa = Piesa[nrPiese].frecv; //frecvPieseMeniu[nrPiesaAleasa];
                        amplaseaza(Piesa[nrPiese],xMouse,yMouse,0, nrRepetitiiPiesa, PIECE_COLOR);
                        deseneazaPuncteDeLegatura(Piesa[nrPiese], *stringNode);
                        click=true;
                        //frecvPieseMeniu[nrPiesaAleasa]++;
                        break;
                    }
                }
            }
        }
        while (!click);
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
        deseneaza(PiesaAux, 0, nrRepetitiiPiesa);
        punePiesa(Piesa[nrPiesaAleasa], nrRepetitiiPiesa); ///Loop
        Beep(1900,100);
        deseneazaPuncteDeLegatura(Piesa[nrPiese], *stringNode);
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


///--------------------- Graphics -----------------------
void showTitle(int call) ///here, call is for the moment when is called this function
                         ///if call = 0 -> the title have a delay between letters
                         ///else  -> the title  have not a delay, is for when you return to menu
{
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 10);
    if(call == 0)
    {
        char title[8][2]= {"E", "L", "E", "C", "T", "R", "O", "N"};
        int width = textwidth("ELECTRON");
        int height = textheight("ELECTRON");

        moveto(midX - width/2, midY - 200);
        for(int i = 0; i < 8; i++)
        {
            outtext(title[i]);
            delay(200);
        }
    }
    else
    {
        int width = textwidth("ELECTRON");
        int height = textheight("ELECTRON");

        moveto(midX - width/2, midY - 200);
        outtext("ELECTRON");
    }
}

void text(int i, int x1, int y1, int color)
{
    //setactivepage(0);
    settextstyle(8, HORIZ_DIR, 4);
    switch(i)
    {
    case 0:
        outtextxy(x1 + 20, y1 + 20, "SCHEMELE");
        outtextxy(x1 + 60, y1 + 50, "MELE");
        break;
    case 1:
        outtextxy(x1 + 60, y1 + 35, "INFO");
        break;
    case 2:
        outtextxy(x1 + 30, y1 + 35, "CREEAZA");
        break;
    case 3:
        outtextxy(x1 + 35, y1 + 35, "IESIRE");
        break;
    }
}

button showMenu()
{
    //setactivepage(0);
    setcolor(WHITE);
    int x1, y1;
    int x2, y2;
    x1 = midX - 450;
    y1 = midY + 50;
    y2 = y1 + 100;

    for (int i = 0; i < 4; i++)
    {

        x2 = x1 + 200;
        cout << x1 << " " << y1 << endl << x2 << " " << y2 << endl;
        b[i].point1.x = x1;
        b[i].point1.y = y1;
        b[i].point2.x = x2;
        b[i].point2.y = y2;

        rectangle(x1, y1, x2, y2);
        text(i, x1, y1, 15);
        x1 = x2 + 50;
        delay(100);
    }
    return *b;
}

void drawBackButton(int x, int y)
{
    line(x, y, x-40, y);
    line(x-40, y, x-40, y+10);
    line(x-40, y+10, x-75, y-15);
    line(x, y, x, y-30);
    line(x, y-30, x-40, y-30);
    line(x-40, y-30, x-40, y-40);
    line(x-40, y-40, x-75, y-15);
}

void hoverButton(button b[], int indice, int color)
{
    setcolor(color);
    if(indice < 4)
    {
        rectangle(b[indice].point1.x, b[indice].point1.y, b[indice].point2.x, b[indice].point2.y);
        text(indice, b[indice].point1.x, b[indice].point1.y, RED);
    }
    else ///button 5 (b[4]) is for the back button
        drawBackButton(b[4].point1.x, b[4].point1.y);
}

///-------------------- Buttons -------------------
void backButton(button b[], int call)
{
    int x1, y1;
    if(!call)
    {
        x1 = WIDTH/12;
        y1 = HEIGHT/10;

        b[4].point1.x = x1;
        b[4].point1.y = y1;
        b[4].point2.x = x1-75;
        b[4].point2.y = y1-40;
    }
    else
    {
        x1 = WIDTH/12;
        y1 = HEIGHT-HEIGHT/10;

        b[4].point1.x = x1;
        b[4].point1.y = y1;
        b[4].point2.x = x1-75;
        b[4].point2.y = y1-40;
    }


    bool click = false;
    while(!click)
    {
        putpixel(x1,y1,4);
        if(ismouseclick(WM_MOUSEMOVE))
        {
            Mouse.x = mousex();
            Mouse.y = mousey();
            clearmouseclick(WM_MOUSEMOVE);

            if(Mouse.x <= b[4].point1.x && Mouse.x >= b[4].point2.x && Mouse.y <= b[4].point1.y && Mouse.y >= b[4].point2.y)
                hoverButton(b, 4, HOVER_COLOR);
            else
                hoverButton(b, 4, 15);
        }
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            Mouse.x = mousex();
            Mouse.y = mousey();
            clearmouseclick(WM_LBUTTONDOWN);

            if(Mouse.x <= b[4].point1.x && Mouse.x >= b[4].point2.x && Mouse.y <= b[4].point1.y && Mouse.y >= b[4].point2.y)
            {
                click = true;

                cleardevice();
                showTitle(1);
                showMenu();
            }

        }
    }
}

void schemeleMele() ///here i want to make also some buttons to get the saved circuits
{
    point leftUp, rightDown;

    settextstyle(8, HORIZ_DIR, 5);
    int width = textwidth("SCHEMELE MELE");
    outtextxy(midX-width/2, 30, "SCHEMELE MELE");

    setcolor(YELLOW);
    leftUp.x = WIDTH/8;
    rightDown.x = leftUp.x + WIDTH/8;
    leftUp.y = HEIGHT/4;
    rightDown.y = 5*HEIGHT/16;

    FILE *nameOfCircuits = fopen("nameOfCircuits.txt", "r");
    cout << "Schemele mele:";
    int i = 0;
    while(!feof(nameOfCircuits))
    {
        fgets(scheme[i].name, 100, nameOfCircuits);
        cout << scheme[i].name<<"ncuidbbc";

        if(i % 3 == 0 && i!=0)
         {
            leftUp.y = rightDown.y + 2*HEIGHT/16;
            rightDown.y = leftUp.y + HEIGHT/16;
            leftUp.x = WIDTH/8;
            rightDown.x = leftUp.x + WIDTH/8;
         }
        scheme[i].point1.x = leftUp.x;
        scheme[i].point1.y = leftUp.y;
        scheme[i].point2.x = rightDown.x;
        scheme[i].point2.y = rightDown.y;

        cout << scheme[i].point1.x << " " <<  scheme[i].point1.y << " " << scheme[i].point2.x << " " << scheme[i].point2.y << endl;

        rectangle(leftUp.x, leftUp.y, rightDown.x, rightDown.y);
        settextstyle(9, HORIZ_DIR, 1);
        outtextxy( leftUp.x + ((rightDown.x - leftUp.x)/2 - textwidth(scheme[i].name)/2), leftUp.y + ((rightDown.y - leftUp.y)/2 - textheight(scheme[i].name)/2), scheme[i].name);

        leftUp.x = rightDown.x + 1.5*WIDTH/8;
        rightDown.x = leftUp.x + WIDTH/8;
        i++;
    }
    fclose(nameOfCircuits);

    bool click = false;
    while(!click)
        for(int i = 0; i < 1 ; i++)
           if(ismouseclick(WM_LBUTTONDOWN))
            {
                Mouse.x = mousex();
                Mouse.y = mousey();
                clearmouseclick(WM_LBUTTONDOWN);

                if(Mouse.x >= scheme[i].point1.x && Mouse.x <= scheme[i].point2.x && Mouse.y >= scheme[i].point1.y && Mouse.y >= scheme[i].point2.y);
                      {
                          click = true;
                          cout << "*//*/*/" << scheme[i].name << endl;
                          cleardevice();
                          rectangle(WIDTH/11, HEIGHT/16, 15*WIDTH/16, 14*HEIGHT/16);
                          char nume[50] = "circuit1.jpg";
                          readimagefile(nume, WIDTH/11, HEIGHT/16, 15*WIDTH/16, 14*HEIGHT/16);
                        }
            }

    backButton(b, 0);


}

void info()
{
    setcolor(14);
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);

    moveto(midX/4,midY/4); outtext("Echipa noastra");

    setcolor(13);
    settextstyle(SCRIPT_FONT, HORIZ_DIR, 5);
    moveto(midX/2, midY/2); outtext("Elena Ginghina");
    moveto(midX/2, 1.5*midY/2); outtext("Dragos Bobu");

    backButton(b, 1);

}

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

void saveAsImg() /// here i want to save the circuit and also you can introduce the name of your circuit
{
    setcolor(TEXT_COLOR);
    char nameImg[50];
    char key[2];
    moveto(10, 55);

    do{
        sprintf(key, "%c", getch());
        strcat(nameImg, key);
        outtext(key);
    }while(key[0] != '.');
    strcat(nameImg, "jpg");

    FILE *nameOfCircuits = fopen("nameOfCircuits.txt", "a");
    fprintf(nameOfCircuits, "%s%c", nameImg, '\n');
    fclose(nameOfCircuits);

    writeimagefile(nameImg, 0, 50);
}

void creeaza()
{
    nrPiese = 0;
    nrPiesaAleasa = 0;
    setcolor(15);

    deseneazaMeniul(Meniu,nrPieseMeniu);
    do
    {

        Update();
        for(int i = 0; i<=nrPiese; i++)
        {
            amplaseaza(Piesa[i], Piesa[i].x, Piesa[i].y, Piesa[i].orientare, 1, -1, WHITE);
        }
    }
    while (nrPiesaAleasa!=nrPieseMeniu);
    saveAsImg(); /// give a name to circuit and save it as a .jpg format
    backButton(b, 1);

}

bool pickButton(int index)
{
    switch(index)
    {
    case 0:
        schemeleMele();
        break;
    case 1:
        info();
        break;
    case 2:
        creeaza();
        break;
    }
}



/// -------------------- Main ------------------------
int main()
{
    initwindow(WIDTH, HEIGHT, "Electron");

    showTitle(0);
    showMenu();

    bool exit = false;
    ///--------- LOOP FOR MOUSE MOVE AND ACT
    while(!exit)
    {
        if(ismouseclick(WM_MOUSEMOVE) )
        {
            Mouse.x = mousex();
            Mouse.y = mousey();
            clearmouseclick(WM_MOUSEMOVE);
            cout << endl << "Mouse Hover " << Mouse.x << " " << Mouse.y << endl;
            int i;
            for(i = 0; i < 4; i++)
            {
                if(Mouse.x >= b[i].point1.x && Mouse.x <= b[i].point2.x && Mouse.y >= b[i].point1.y && Mouse.y <= b[i].point2.y)
                {
                    hoverButton(b, i, HOVER_COLOR);
                    break;
                }
                else
                    hoverButton(b, i, 15); //15 means WHITE
            }
            cout << "i= " << i << endl;
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                Mouse.x = mousex();
                Mouse.y = mousey();
                clearmouseclick(WM_LBUTTONDOWN);

                if(Mouse.x >= b[i].point1.x && Mouse.x <= b[i].point2.x && Mouse.y >= b[i].point1.y && Mouse.y <= b[i].point2.y)
                {
                    cout << endl << "Mouse Click " << Mouse.x << " " << Mouse.y << endl;
                    cout << b[i].point1.x << " " << b[i].point2.x << endl;
                    cout << b[i].point1.y << " " << b[i].point2.y << endl;

                    //click = true;
                    cleardevice();

                    cout << "STOP " << i << endl;
                    if(i == 3)
                        exit = true;
                    else
                        pickButton(i);
                }

            }
        }
    }
    savePiecesInFile();
    closegraph();
    return 0;
}
