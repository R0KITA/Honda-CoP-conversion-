/* COP CONVERSION CODE
 * BUILD AND DESIGNED FOR HONDA D/B-SERIES
 * 
 * DESIGN IDEA AND OG CODE amadeuscr
 * PROGRAMMING AND UPDATES Rokita_S
 * 
 * FOR MORE INFO CHECK OG THREAD
 * https://honda-tech.com/forums/engine-management-tuning-124/obd1-ecu-coil-plug-module-trojantuning-3275874/page5/
 * FOR CODE UPDATES CHECK MY GITHUB
 * https://github.com/R0KITA/Honda-CoP-conversion-
 */

//settings//
int FIRSTCOIL = 2; /*DEPENING ON WHICH INJECTOR IS USED FOR SYNC
                    *INJ1 = 2 
                    *INJ2 = 4 
                    *INJ3 = 1 
                    *INJ4 = 3
                    */
int DWELL     = 2500; // INITIAL DWELL IN MICROSECONDS //
int MAXDWELL  = 2500; // MAX DWELL IN MICROSECONDS FOR MAPPING WITH RPM //
int MINDWELL  = 1900; // MIN DWELL IN MICROSECONDS FOR MAPPING WITH RPM //

//settings//

int inj_flag;
int coil_flag;
int NEXTCOIL;
int RPM;
long CLK_DWELL = 65535-(DWELL*2); //math

unsigned long sparktim1 = 0;
unsigned long sparktim2 = 0;
  
void setup() {
  //Serial.begin(9600);
  //ATmega328 setup...
  TCCR1A = 0;                                 //DO NOT TOUCH
  TCCR1B = 0;                                 //DO NOT TOUCH
  TCCR1B |=(0<<CS10) | (1<<CS11) | (0<<CS12); //DO NOT TOUCH
  TIMSK1 |=(1<<TOIE1);                        //DO NOT TOUCH

  //PORT SETUP
  /*OUTPUT*/DDRB = B00011110; //p,p,p,D12,D11,D10,D9,p
  /*INPUT*/DDRD = B00000000; // PD3(A0)-INJ PD2(A1)-ICM

}

ISR(TIMER1_OVF_vect){
  if(coil_flag == 1)
  {
    PORTB &= !B00011110; 
    inj_flag=0;
    coil_flag=0;
  
  //Serial.println("SPARK"); //DONT USE... FOR EMULATOR PURPOSES ONLY
  
    
    /*RPM CALCULATOR
    sparktim1=sparktim2;
    sparktim2=millis();
    RPM=(1000/((sparktim2-sparktim1)*2))*60;
    */
    
    /*DWELL MAPPING TO RPM
    if(RPM>9000){DWELL=map(RPM, 9000, 12000, MAXDWELL, MINDWELL);}
    else{DWELL=MAXDWELL;}
    CLK_DWELL = 65535-(DWELL*2);
    */
  
    TCNT1=0;}
}

void loop() {
  
  /*if(Pin_input(2,LOW,inj_flag) == 1){
  NEXTCOIL=FIRSTCOIL;
    inj_flag=1;
  }*/

  if ((PIND >> 3 & B00001000 >> 3) == LOW && inj_flag == 0 ) {  
  NEXTCOIL=FIRSTCOIL;
    inj_flag=1;
  }

  
  
  //if(Pin_input(3,LOW,coil_flag) == 1){
  if ((PIND >> 2 & B00000100 >> 2) == LOW && coil_flag == 0) {
    switch(NEXTCOIL)
    {
      case 1: PORTB |= B00000010;
        NEXTCOIL=3;
        break;
      case 2: PORTB |= B00000100;
        NEXTCOIL=1;
        break;
      case 3: PORTB |= B00001000;
        NEXTCOIL=4;
        break;
      case 4: PORTB |= B00010000;
        NEXTCOIL=2;
        break;
    }
  TCNT1 = CLK_DWELL;
    coil_flag=1;
  }
  
}
