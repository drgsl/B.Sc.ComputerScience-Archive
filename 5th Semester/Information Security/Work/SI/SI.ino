#include"melodii.c"
#include <SoftwareSerial.h>
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

SoftwareSerial Bluetooth(10, 11);
int BluetoothData;
int melodie = 1;

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  Bluetooth.println("Introduceti un numar de la 1 la 5 pentru a selecta o melodie");

  
  int* melody=&melody_Ode_of_Joy[0];
  int* durations=&noteDurations_Ode_of_Joy[0];
  Serial.print(ARRAY_SIZE(melody));
  Serial.print("\t");
  //for (int thisNote = 0; thisNote < (sizeof(melody) / sizeof(int)) ; thisNote++)
  for (int thisNote = 0; thisNote < ARRAY_SIZE(melody) ; thisNote++)
  {
    Serial.print(*(melody+thisNote));
    Serial.print("\t");
  }

  Serial.print(*(melody+0));
  Serial.print("\t");
  Serial.print(*(melody+1));
  Serial.print("\t");
  Serial.print(*(melody+2));
  Serial.print("\t");
  
}

int to_int(int data)
{
  if(data=='1') return 1;
  if(data=='2') return 2;
  if(data=='3') return 3;
  if(data=='4') return 4;
  if(data=='5') return 5;
}

void raiseTempo(float *tempo)
{
  if(*tempo>0.5)
    *tempo=*tempo-(float)0.05;
}

void lowerTempo(float *tempo)
{
    if(*tempo<1.5)
    *tempo=*tempo+(float)0.1;
}

void restoreTempo(float *tempo)
{
  *tempo=1;
}

void loop() {
  //int* melody=&melody_Ode_of_Joy[0];
  //int* durations=&noteDurations_Ode_of_Joy[0];

  
  if (melodie == 1)
  {
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < (sizeof(melody_Ode_of_Joy) / sizeof(int)) ; thisNote++) {
    //int thisNote;
  //while(thisNote++){
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

      if (Bluetooth.available()){
          BluetoothData=Bluetooth.read();
          if(BluetoothData >= '1' && BluetoothData <= '5')
          {
            restoreTempo(&tempo_Ode_of_Joy);
            melodie=to_int(BluetoothData);
            break;
          }
          else if(BluetoothData == '+')
          {
            raiseTempo(&tempo_Ode_of_Joy);
          }
          else if(BluetoothData == '-')
          {
            lowerTempo(&tempo_Ode_of_Joy);
          }
          else if(BluetoothData == '=')
          {
            restoreTempo(&tempo_Ode_of_Joy);
          }
      }
      int noteDuration = 1000 * tempo_Ode_of_Joy / noteDurations_Ode_of_Joy[thisNote];
      tone(8, melody_Ode_of_Joy[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      double pauseBetweenNotes = (double)noteDuration * 1.30 * tempo_Ode_of_Joy;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(8);
    }
  }
  else if (melodie == 2) //pirates
  {
    for (int thisNote = 0; thisNote < (sizeof(melody_Pirates) / sizeof(int)) ; thisNote++) 
    {
      if (Bluetooth.available()){
          BluetoothData=Bluetooth.read();
          if(BluetoothData >= '1' && BluetoothData <= '5')
          {
            restoreTempo(&tempo_Pirates);
            melodie=to_int(BluetoothData);
            break;
          }
          else if(BluetoothData == '+')
          {
            raiseTempo(&tempo_Pirates);
          }
          else if(BluetoothData == '-')
          {
            lowerTempo(&tempo_Pirates);
          }
          else if(BluetoothData == '=')
          {
            restoreTempo(&tempo_Pirates);
          }
      }
      int noteDuration = 1000 * tempo_Pirates / noteDurations_Pirates[thisNote];
      tone(8, melody_Pirates[thisNote], noteDuration);

      double pauseBetweenNotes = (double)noteDuration * 1.2 * tempo_Pirates;
      delay(pauseBetweenNotes);
      noTone(8);
    }
  }
  else if (melodie==3) //Crazy frog
  {
    for (int thisNote = 0; thisNote < (sizeof(melody_Crazy_Frog) / sizeof(int)) ; thisNote++) 
    {
      if (Bluetooth.available()){
          BluetoothData=Bluetooth.read();
          if(BluetoothData >= '1' && BluetoothData <= '5')
          {
            restoreTempo(&tempo_Crazy_Frog);
            melodie=to_int(BluetoothData);
            break;
          }
          else if(BluetoothData == '+')
          {
            raiseTempo(&tempo_Crazy_Frog);
          }
          else if(BluetoothData == '-')
          {
            lowerTempo(&tempo_Crazy_Frog);
          }
          else if(BluetoothData == '=')
          {
            restoreTempo(&tempo_Crazy_Frog);
          }
      }
      int noteDuration = 1000.0 * tempo_Crazy_Frog / noteDurations_Crazy_Frog[thisNote] ;
      tone(8, melody_Crazy_Frog[thisNote], noteDuration);

      double pauseBetweenNotes = (double)noteDuration * 1.5 * tempo_Crazy_Frog;
      delay(pauseBetweenNotes);
      noTone(8);
    }
  }
  else if (melodie==4) //Mario
  {
    for (int thisNote = 0; thisNote < (sizeof(melody_Mario) / sizeof(int)) ; thisNote++) 
    {
      if (Bluetooth.available()){
          BluetoothData=Bluetooth.read();
          if(BluetoothData >= '1' && BluetoothData <= '5')
          {
            restoreTempo(&tempo_Mario);
            melodie=to_int(BluetoothData);
            break;
          }
          else if(BluetoothData == '+')
          {
            raiseTempo(&tempo_Mario);
          }
          else if(BluetoothData == '-')
          {
            lowerTempo(&tempo_Mario);
          }
          else if(BluetoothData == '=')
          {
            restoreTempo(&tempo_Mario);
          }
      }
      int noteDuration = 1000 * tempo_Mario / noteDurations_Mario[thisNote];
      tone(8, melody_Mario[thisNote], noteDuration);

      double pauseBetweenNotes = (double)noteDuration * 1.6 * tempo_Mario;
      delay(pauseBetweenNotes);
      noTone(8);
    }
  }
  else if (melodie==5) //Titanic
  {
    for (int thisNote = 0; thisNote < (sizeof(melody_Titanic) / sizeof(int)) ; thisNote++) 
    {
      if (Bluetooth.available()){
          BluetoothData=Bluetooth.read();
          if(BluetoothData >= '1' && BluetoothData <= '5')
          {
            restoreTempo(&tempo_Titanic);
            melodie=to_int(BluetoothData);
            break;
          }
          else if(BluetoothData == '+')
          {
            raiseTempo(&tempo_Titanic);
          }
          else if(BluetoothData == '-')
          {
            lowerTempo(&tempo_Titanic);
          }
          else if(BluetoothData == '=')
          {
            restoreTempo(&tempo_Titanic);
          }
      }
      int noteDuration = 1000 * tempo_Titanic / noteDurations_Titanic[thisNote];
      tone(8, melody_Titanic[thisNote], noteDuration);

      double pauseBetweenNotes = (double)noteDuration * 1.5 * tempo_Titanic;
      delay(pauseBetweenNotes);
      noTone(8);
    }
  }
}
