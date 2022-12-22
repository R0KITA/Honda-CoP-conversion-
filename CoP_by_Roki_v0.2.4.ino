// DECLARATION OF VARIABLES //
#include "func.h"
//

// INPUT- OUTPUTS //
int COIL1    = 9;
int COIL2    = 10;
int COIL3    = 11;
int COIL4    = 12;
int LED      = 13;
int COILTR   = A3;
int INJ   = A4;
//

//INITIAL SYSTEM GLOBAL//
int OFFRET    = 0;
int SYNCNT    = 0;
int NEXTCOIL  = 0; // 
int SYNCED    = 0;
int RUNNING   = 0;
int SPARKS    = 0;
int RPM       = 0;
int FIRE      = 0;
unsigned long LASTMILLIS = 0;
unsigned long COILDUR;
unsigned long SYNCDUR;
unsigned long prevTime;
//

// ** SETTINGS ** //
int FIRSTCOIL = 2;
int DWELL     = 1500; // INITIAL DWELL IN MICROSECONDS // 
//
int MAXDWELL  = 2750; // MAX DWELL IN MICROSECONDS FOR MAPPING WITH RPM //
int MINDWELL  = 2100; // MIN DWELL IN MICROSECONDS FOR MAPPING WITH RPM //
//
int MAXOFFRET = 0;  // MAX OFFSET RETARD MICROSECONDS FOR MAPPING WITH RPM //
int MINOFFRET = 0;    // MIN OFFSET RETARD IN MICROSECONDS FOR MAPPING WITH RPM //
//


void setup() {    
  Serial.begin(9600); 
  pinAsOutput(COIL1);
  pinAsOutput(COIL2);
  pinAsOutput(COIL3);
  pinAsOutput(COIL4);
  pinAsOutput(LED);
  //
  pinMode(COILTR, INPUT);
  pinMode(INJ, INPUT);
  //  
  // SYNCHING ///
  delay
  while (SYNCED < 1){

   while(digitalRead(INJ)>LOW){asm(" ");}
  
    NEXTCOIL = FIRSTCOIL;
    SYNCED++;
   }
  
  //if (SYNCED == 1){
    digitalHigh(LED);
    //COILDUR = pulseIn(COILTR, HIGH,500000);  
    //
    //OFFRET = map(RPM,0,10000,MAXOFFRET,MINOFFRET);
    
    //
  //}



}

// the loop routine runs over and over again forever:
void loop() {
  unsigned long currentTime=millis();
    
    if(digitalRead(INJ)==LOW){NEXTCOIL=FIRSTCOIL;}
      
      if(digitalRead(COILTR)<HIGH && FIRE == 0){
          switch(NEXTCOIL){
            case 1: digitalHigh(COIL1);
            case 2: digitalHigh(COIL2);
            case 3: digitalHigh(COIL3);
            case 4: digitalHigh(COIL4);}
            prevTime = currentTime;
          FIRE=1;}
          
          if(FIRE == 1 && currentTime-prevTime>DWELL){
            switch(NEXTCOIL){
              case 1: digitalHigh(COIL1);
                NEXTCOIL = 3;
                
              case 2: digitalHigh(COIL2);
                NEXTCOIL = 1;
                
              case 3: digitalHigh(COIL3);
                NEXTCOIL = 4;
                
              case 4: digitalHigh(COIL4);
                NEXTCOIL = 2;
             }
          SPARKS++;
          FIRE=0;
          }
          
    /*if(Serial.available()>0){
      static char message[6];
      static unsigned int message_pos = 0;
      char inByte =Serial.read();

      /*if(inByte != '\n'){
        message[message_pos]=inByte;
        message_pos++;
        }
        else{
          message[message_pos] ='\0';
          Serial.println(message);
          message_pos=0;}
        if(inByte == 'x'){
          inByte =Serial.read();
          message[message_pos]=inByte;
          message_pos++;
          }
          
          Serial.println(message);
          message_pos=0;
      }
    */
    if (RPM > 400 && RUNNING == 0){
      RUNNING = 1; 
    }

  // CALCULATES RPM //
  if (SPARKS >= 2) { 
     RPM = 30*1000/(millis() - LASTMILLIS)*SPARKS;
     LASTMILLIS = millis();
     SPARKS = 0;
     DWELL  = map(RPM,6000,10000,MAXDWELL,MINDWELL);
  }
  //

  // RPM IS LOWER OF 40 WILL DESYNCH //
  if (RPM < 400 && RUNNING == 1){
    SYNCED = 0;
    RUNNING = 0;
    digitalLow(LED);
  } 
  //

}
