const int numPins = 10;
int pins[] = {13,12,11,10,9,8,7,6,5,4};

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

while(!Serial.available());

byte num = Serial.read();
for(int i=0;i<numPins;i++){
  byte state = bitRead(num, i);
  //digitalWrite(pins[i], state);
  Serial.print(state);
  Serial.print(" " + i);
  Serial.print(" " + pins[i]);
}
Serial.println();
}
