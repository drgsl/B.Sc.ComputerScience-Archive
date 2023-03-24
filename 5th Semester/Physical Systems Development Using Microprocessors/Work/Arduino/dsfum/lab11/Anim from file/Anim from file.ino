#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include "SdFat.h"
#include <string.h>
SdFat sd;


struct Circle {
  int x;
  int y;
  int r;
  int col;
};

Circle circle1;


MCUFRIEND_kbv tft;
#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F



void setup() {

  Serial.begin(9600);

  if (!sd.begin(10)) {  //make sure sd card was found
    while (true)
      ;
  }
  functie();

  circle1.x = 100;
  circle1.y = 100;
  circle1.r = 10;
  circle1.col = GREENYELLOW;

  // put your setup code here, to run once:
  uint16_t ID = tft.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9486;  // write-only shield
  tft.begin(ID);
  tft.setRotation(0);  //PORTRAIT
  tft.fillScreen(BLACK);
  showCircle(circle1);

  functie();
}

void comm(char* comanda, int x, int y) {
  if (strcmp(comanda, "goTo") == 0)
    goTo(circle1, x, y);
  else
    moveTo(circle1, x, y);
}




void loop() {
  // put your main code here, to run repeatedly:
  //   goTo (circle1, 50, 60);
  //   delay(10000);
  // goTo (circle1, 70, 80);
  //   delay(1000);
  // goTo (circle1, 90, 100);
  //   delay(10000);

  // moveTo(circle1, 200, 200);
  // moveTo(circle1, 100, 100);
}

void functie() {
  SdFile file;
  if (!sd.exists("file.txt")) return;
  if (file.open("file.txt", O_RDONLY)) {
    char continut[500] = " ";
    file.read(continut, 500);
    char sep[] = " \n";
    char* p = strtok(continut, sep);
    char comanda[7];
    int i = 0, x, y;
    while (p != NULL) {
      if (i % 3 == 0) strcpy(comanda, p);
      if (i % 3 == 1) x = atoi(p);
      if (i % 3 == 2) y = atoi(p);
      if (i % 3 == 2) {
        comm(comanda, x, y);
        comanda[0] = '\n';
      }
      i++;
      p = strtok(NULL, sep);
    }
  }
}


Circle goTo(Circle& circle, int x, int y) {
    tft.fillCircle(circle.x, circle.y, circle1.r, BLACK);
  circle.x = x;
  circle.y = y;

  showCircle(circle);
  return circle;
}

Circle moveTo(Circle& circle, int x, int y) {
  int steps = 20;
  int xDist = x - circle.x;
  int yDist = y - circle.y;

  for (int i = 0; i < steps; i++) {
    goTo(circle, circle.x + xDist / steps, circle.y + yDist / steps);
    Serial.println(xDist / steps);
    Serial.println(yDist / steps);
    delay(100);
  }
}

Circle showCircle(Circle circle) {
  tft.fillCircle(circle.x, circle.y, circle1.r, circle1.col);
}