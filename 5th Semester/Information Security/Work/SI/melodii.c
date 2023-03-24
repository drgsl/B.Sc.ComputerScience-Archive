#include"pitches.h"
//"HE IS A PIRATE" Theme song of Pirates of caribbean
static int melody_Pirates[] = {
NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4,
NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_D4, 0,
		NOTE_A3, NOTE_C4, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_E4, NOTE_F4,
		NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4,
		NOTE_D4, 0, 0, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4,
		NOTE_G4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4,
		NOTE_A4, NOTE_D4, 0, NOTE_D4, NOTE_E3, NOTE_F4, NOTE_F4, NOTE_G4,
		NOTE_A4,
		NOTE_D4, 0, NOTE_D4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_D4 };

static int noteDurations_Pirates[] = { 4, 8, 4, 8, 4, 8, 8, 8, 8, 4, 8, 4, 8, 4, 8, 8,
		8, 8, 4, 8, 4, 8, 4, 8, 8, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 8,
		4, 8, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 8, 4, 4, 8, 8, 8, 8, 4, 4, 8,
		8, 4, 4, 8, 8, 4, 4, 8, 8, 8, 4, 8, 8, 8, 4, 4, 4, 8, 4, 8, 8, 8, 4, 4,
		8, 8 };

//static float tempo_Pirates = 2.5;
static float tempo_Pirates = 1;

//##############**"Crazy Frog" song of Crazy frog album**##############//
static int melody_Crazy_Frog[] = {
  NOTE_D4, 0, NOTE_F4, NOTE_D4, 0, NOTE_D4, NOTE_G4, NOTE_D4, NOTE_C4,
  NOTE_D4, 0, NOTE_A4, NOTE_D4, 0, NOTE_D4, NOTE_AS4, NOTE_A4, NOTE_F4,
  NOTE_D4, NOTE_A4, NOTE_D5, NOTE_D4, NOTE_C4, 0, NOTE_C4, NOTE_A3, NOTE_E4, NOTE_D4,
  0,NOTE_D4,NOTE_D4
};
static int noteDurations_Crazy_Frog[] = {
  8, 8, 6, 16, 16, 16, 8, 8, 8,
  8, 8, 6, 16, 16, 16, 8, 8, 8,
  8, 8, 8, 16, 16, 16, 16, 8, 8, 2,
  8,4,4
};

//static float tempo_Crazy_Frog=4;
static float tempo_Crazy_Frog=1;
//###########End of Crazy Frog#############//



//##############**"Mario underworld" **##############//
static int melody_Mario[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,NOTE_AS3, NOTE_AS4, 0, 0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4, 0,0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,NOTE_DS3, NOTE_DS4, 0, 0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4, NOTE_DS4, NOTE_GS3, NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,  NOTE_AS3, NOTE_A3, NOTE_GS3,0, 0, 0
};
static int noteDurations_Mario[] = {
 12, 12, 12, 12,12, 12, 6,3,
 12, 12, 12, 12, 12, 12, 6, 3,
 12, 12, 12, 12, 12, 12, 6,
 3, 12, 12, 12, 12,
 12, 12, 6, 6, 18, 18, 18,
 6, 6, 6, 6,6, 6,
 18, 18, 18, 18, 18, 18, 10, 10, 10,
 10, 10, 10, 3, 3, 3
};

//static float tempo_Mario=4;
static float tempo_Mario=1;
//###########End of Mario underworld#############//


//##############**"Titanic" **##############//
static int melody_Titanic[] = {
NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4,
NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_F5,
NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4,
NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_B3, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_B3, NOTE_E4,
NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4


};
static int noteDurations_Titanic[] = {
8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,4,4,8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,8,8,1,
8,8,8,8,4,4,4,8,4,4,8,8,8,8,4,8,8,4,8,4,8,8,4,8,4,1



};
//static int tempo_Titanic=4;
static float tempo_Titanic=1;
//###########End of Titanic#############//


//ode of joy
#define D0 -1
#define D1 262
#define D2 293
#define D3 329
#define D4 349
#define D5 392
#define D6 440
#define D7 494

#define M1 523
#define M2 586
#define M3 658
#define M4 697
#define M5 783
#define M6 879
#define M7 987

#define H1 1045
#define H2 1171
#define H3 1316
#define H4 1393
#define H5 1563
#define H6 1755
#define H7 1971
//All D adjustable frequenc2
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SI4TEENTH 0.625
//List all the time
static int melody_Ode_of_Joy[]=        //According to the numbered list each frequenc2
{
  M3,M3,M4,M5,
  M5,M4,M3,M2,
  M1,M1,M2,M3,
  M3,M2,M2,
  M3,M3,M4,M5,
  M5,M4,M3,M2,
  M1,M1,M2,M3,
  M2,M1,M1,
  M2,M2,M3,M1,
  M2,M3,M4,M3,M1,
  M2,M3,M4,M3,M2,
  M1,M2,D5,D0,
  M3,M3,M4,M5,
  M5,M4,M3,M4,M2,
  M1,M1,M2,M3,
  M2,M1,M1
};
static int noteDurations_Ode_of_Joy[]=       //According to the numbered list each time
{
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  2,8,8,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  2,8 ,8,
  4,4,4,4,
  4,8,8,4,4,
  4,8,8,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,8,8,
  4,4,4,4,
  2,4,4,
};
//static float tempo_Ode_of_Joy=1.50; //1/2
static float tempo_Ode_of_Joy=1;
