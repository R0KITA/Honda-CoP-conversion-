// DECLARATION OF VARIABLES //
//

// INPUT- OUTPUTS //
int VAR[5]   = {0,3,5,6,7};
int LED      = LED_BUILTIN;
int COILTR   = 8;
int INJ      = 12;

int ORDER[5]={0,3,1,4,2};
 //pin numbers for cyl none,1,2,3,4

//INITIAL SYSTEM GLOBAL//
int SYNCNT    = 0;
int NEXTCOIL  = 0;
int SYNCED    = 0;

int FIRSTCOIL = 2;

void setup() {    
  
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(LED, OUTPUT);
  //
  pinMode(COILTR, INPUT);
  pinMode(INJ, INPUT);
  //  
  
  // SYNCHING ///
  while (SYNCED < 1){
   //
    while(digitalRead(INJ)==LOW){/* NOTIN */}
    NEXTCOIL=FIRSTCOIL;
    SYNCED++;  
    }

  digitalHigh(LED);
}

// the loop routine runs over and over again forever:
void loop() {

  
  if (SYNCED == 1){
        while (digitalRead(COILTR) ==LOW){/* NOTIN */}
        FIRE_COIL(NEXTCOIL);
    }
}


  void FIRE_COIL(int a){
    digitalHigh(VAR[a]);
    
    while(COILTR != LOW ){/* NOTIN */}
      digitalLow(VAR[a]);
    
    NEXTCOIL=ORDER[a];
  }
