#include <SPI.h>
#include "SdFat.h"
 
#define chipSelect 10 // pinul la care este conectat cardul (xx = 4 pe shieldul Ethernet, xx = 10 pentru ecrane)
 
SdFat sd;
 
void setup() {
  Serial.begin(9600);
 
  // Pornim cardul; daca nu merge, se pot folosi viteze mai mici de 50Mhz
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    sd.initErrorHalt(); // afiseaza pe portul serial posibilele motive ale erorii
  }
  else 
  {
    Serial.println("Card ready");  
  }

  afisareDirector("/");
}
void loop() {}



void afisareDirector(char cale[]){
  SdFile dir;
  SdFile file;
  if (!dir.open(cale)){
    Serial.print("Eroare deschidere director: ");
    Serial.println(cale);
  }
  else
  {
    while (file.openNext(&dir, O_RDONLY)) {
        if (!file.isHidden()) {
 
          // afisarea tipului (fisier / director):
          Serial.print((file.isDir() ? "d " : "f "));
 
          // afisarea numelui:
          char nume[100];
          file.getName(nume, 100);
          Serial.print(nume);
 
          // afisam dimensiunea:
          if (!file.isDir()) {
            Serial.print('(');
            Serial.print(file.fileSize());
            Serial.print(')');
          }
 
          // alte functii interesante pentru lucrul cu fisiere, gasiti aici: 
          // https://profs.info.uaic.ro/~vcosmin/pagini/resurse_arduino/ImagineCardSD/extras/html/class_file.html
 
          Serial.println();
        }
        file.close();
      }
  }
}


// dp portul serial o cale catre director + fisier

// de la director cauta recursiv fisierul

// gasit fisier->

// selectat cuvant cu lungimea cea mai mare

// serial print



