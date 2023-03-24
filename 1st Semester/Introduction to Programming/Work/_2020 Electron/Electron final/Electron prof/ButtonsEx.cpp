#include <iostream>
#include <winbgim.h>
#include <graphics.h>

#define HOVER_COLOR RED

using namespace std;

int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

int midX = WIDTH /2;
int midY = HEIGHT /2;

struct point
{
    int x, y;
};
point Mouse;

struct button
{
    point point1;
    point point2;
};
button b[5];

void showTitle()
{
    char title[8][2]= {"E", "L", "E", "C", "T", "R", "O", "N"};

    settextstyle(8, HORIZ_DIR, 10);
    int width = textwidth("ELECTRON");
    int height = textheight("ELECTRON");

    moveto(midX - width/2, midY - 200);
    for(int i = 0; i < 8; i++)
    {
        outtext(title[i]);
        delay(200);
    }
}

void text(int i, int x1, int y1, int color)
{
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
    else
        drawBackButton(b[4].point1.x, b[4].point1.y);
}

void backButton()
{
    int x = WIDTH/12;
    int y = HEIGHT/10;
    drawBackButton(x,y);

    b[4].point1.x = x;
    b[4].point1.y = y;
    b[4].point2.x = x-40;
    b[4].point2.y = y+10;

    bool click = false;
    do
    {
        if(ismouseclick(WM_MOUSEMOVE))
        {
            //click = true;
            getmouseclick(WM_MOUSEMOVE,Mouse.x,Mouse.y);
            clearmouseclick(WM_MOUSEMOVE);

            if(Mouse.x <= b[4].point1.x && Mouse.x >= b[4].point2.x && Mouse.y <= b[4].point1.y && Mouse.y >= b[4].point2.y)
                hoverButton(b, 4, HOVER_COLOR);
            else
                hoverButton(b, 4, 15);

        }
    }
    while(!click);
}

void schemeleMele()
{
    cleardevice();
    bool BACK = false;
    settextstyle(8, HORIZ_DIR, 10);

    outtextxy(midX - WIDTH/3, midY - 100, "COMING");
    outtextxy(midX + WIDTH/20, midY + HEIGHT/15, "SOON.");
    backButton();
}

void info()
{
    cleardevice();
}

void creeaza()
{
    cleardevice();
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

/// ***************************************************

int main()
{

    initwindow(WIDTH, HEIGHT, "Electron");

    showTitle();
    showMenu();

    cout << endl;
    for(int i = 0; i<4; i++)
    {
        cout << b[i].point1.x << " ";
        cout << b[i].point1.y << " ";
        cout << b[i].point2.x << " ";
        cout << b[i].point2.y << endl;
    }

    bool exit = false;

    do
    {
        bool click = false;
        if(ismouseclick(WM_MOUSEMOVE) )
        {
            getmouseclick(WM_MOUSEMOVE,Mouse.x,Mouse.y);
            clearmouseclick(WM_MOUSEMOVE);
            cout << endl << "Mouse Hover " << Mouse.x << " " << Mouse.y << endl;

            for(int i = 0; i < 4 && !click; i++)
            {
                if(Mouse.x >= b[i].point1.x && Mouse.x <= b[i].point2.x && Mouse.y >= b[i].point1.y && Mouse.y <= b[i].point2.y)
                    hoverButton(b, i, HOVER_COLOR);
                else
                    hoverButton(b, i, 15); //15 means WHITE

                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    getmouseclick(WM_LBUTTONDOWN, Mouse.x, Mouse.y);
                    clearmouseclick(WM_LBUTTONDOWN);

                    if(Mouse.x >= b[i].point1.x && Mouse.x <= b[i].point2.x && Mouse.y >= b[i].point1.y && Mouse.y <= b[i].point2.y)
                    {
                        cout << endl << "Mouse Click " << Mouse.x << " " << Mouse.y << endl;
                        cout << b[i].point1.x << " " << b[i].point2.x << endl;
                        cout << b[i].point1.y << " " << b[i].point2.y << endl;
                        click = true;
                        cleardevice();
                        cout << "STOP " << i << endl;
                        if(i == 3)
                            exit = true;
                        else
                            pickButton(i);
                        cout << "**" << exit << endl;

                        cout << "i= " << i << " " << endl;
                    }
                }
            }
        }
    }
    while(!exit);

    getch();
    closegraph();
    return 0;
}























