bool blink = true;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Enter data:");

  if (blink) {
    if ((millis()/1000) % 2 == 0)
    {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  while (!Serial.available());     //wait for data available
  String inString = Serial.readString();  //read until timeout
  inString.trim();                        // remove any \r \n whitespace at the end of the String
  if (inString == "1")
  {
    blink = false;
    Serial.println("Pornit");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if (inString == "2")
  {
    blink = false;
    Serial.println("Oprit");
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (inString == "3")
  {
    Serial.println("Blink");
    blink = !blink;
  }
}
