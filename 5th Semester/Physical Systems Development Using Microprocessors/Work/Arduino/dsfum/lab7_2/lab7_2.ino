#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

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


struct Player {
  int x;
  int y;
};

struct Food {
  int x;
  int y;
};

Player p;
Food fs[3];

int score = 0;

int frameMillis = 100;

int startMillis = 0;

void setup() {
  randomSeed(analogRead(A5));
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);  // initialize the lcd

  lcd.createChar(0, stickman);  // load character to the LCD
  lcd.createChar(1, pacman);    // load character to the LCD
  lcd.createChar(2, empty);     // load character to the LCD



  p.x = 2;
  p.y = 1;

  for (int i = 0; i < 3; i++) {
    fs[i] = getRandomFoodPos(fs[i]);
  }
}

void loop() {
  lcd.clear();

  p = updatePlayerPosition(p);
  showPlayer(p.x, p.y);

  for (int i = 0; i < 3; i++) {
    showFood(fs[i].x, fs[i].y);
  }




  if (millis() - startMillis > 5000) {
    for (int i = 0; i < 3; i++) {
      fs[i] = getRandomFoodPos(fs[i]);
    }
    startMillis = millis();
  }

  showScore();

  delay(10);
}

void showScore(){
lcd.setCursor(15, 1);
lcd.print(score);
}

bool checkCollision(Player newP) {
  for (int i = 0; i < 3; i++) {
    if (collides(newP, fs[i])) {
      score += 1;
    }
  }
}

bool collides(Player p, Food f) {
  return ((p.x == f.x) && (p.y == f.y));
}

Food getRandomFoodPos(Food in) {
  Food f = in;
  f.x = random(0, 17);
  f.y = 0;
  return f;
}

void showFood(int x, int y) {
  lcd.setCursor(x, y);
  lcd.print(char(1));
}

Player updatePlayerPosition(Player in) {
  Player p = in;
  int input = analogRead(0);

  if (input < 60) {
    p.x += 1;
    delay(frameMillis);
  } else if (input < 200) {
    p.y = 0;
    showPlayer(p.x, p.y);
    checkCollision(p);
    delay(500);
    p.y = 1;
    showPlayer(p.x, p.y);
  } else if (input < 600) {
    p.x -= 1;
    delay(frameMillis);
  }
  return p;
}

void showPlayer(int x, int y) {
  lcd.setCursor(x, y);
  lcd.print(char(0));
}