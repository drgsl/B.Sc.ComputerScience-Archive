#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
//            lcd(RS,  E, d4, d5, d6, d7)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Creat a set of new characters

uint8_t bell[8] = { 0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4 };
uint8_t note[8] = { 0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0 };
uint8_t clock[8] = { 0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0 };
uint8_t heart[8] = { 0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0 };
uint8_t duck[8] = { 0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0 };
uint8_t check[8] = { 0x0, 0x1, 0x3, 0x16, 0x1c, 0x8, 0x0 };
uint8_t cross[8] = { 0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0 };
uint8_t retarrow[8] = { 0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4 };


byte stickman[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b11111,
  0b00100,
  0b00100,
  0b01010,
  0b10001
};

byte pacman[8] = {
  0b00000,
  0b01100,
  0b01110,
  0b00111,
  0b00111,
  0b01110,
  0b01100,
  0b00000
};

byte empty[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

int sensorValue;
int aux;

String giveDirection(int sensorValue) {
  if (sensorValue < 50) return "RIGHT";
  if (sensorValue > 50 && sensorValue < 195) return "UP";
  if (sensorValue > 195 && sensorValue < 380) return "DOWN";
  if (sensorValue > 380 && sensorValue < 440) return "LEFT";
  if (sensorValue > 440 && sensorValue < 790) Serial.println("SELECT");
};

int PLAYER_POSITION_Y = 1;
int PACMAN_POSITION_X = 15;

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);  // initialize the lcd

  lcd.createChar(0, stickman);  // load character to the LCD
  lcd.createChar(1, pacman);    // load character to the LCD
  lcd.createChar(2, empty);     // load character to the LCD

  lcd.home();  // go home
}
int gameOver = 0;
void loop() {
  if (gameOver == 0) {
    lcd.setCursor(PACMAN_POSITION_X + 1, 1);
    lcd.print(char(2));
    lcd.setCursor(PACMAN_POSITION_X, 1);
    lcd.print(char(1));
    delay(200);
    lcd.setCursor(3, PLAYER_POSITION_Y);
    lcd.print(char(0));
    delay(200);
    PACMAN_POSITION_X--;
    if (PACMAN_POSITION_X == -1) {
      PACMAN_POSITION_X = 15;
      lcd.setCursor(0, 1);
      lcd.print(char(2));
    }
    sensorValue = analogRead(A0);
    if (sensorValue < 50) {
      PLAYER_POSITION_Y = 0;
      lcd.setCursor(3, 1);
      lcd.print(char(2));
      aux = PACMAN_POSITION_X;
    }

    if (PACMAN_POSITION_X == aux - 3) {
      PLAYER_POSITION_Y = 1;
      lcd.setCursor(3, 0);
      lcd.print(char(2));
    }

    delay(200);
    if (PACMAN_POSITION_X == 3 && PLAYER_POSITION_Y == 1)
      gameOver = 1;
  } else {
    lcd.clear();
    lcd.print("GameOver");
  }
}