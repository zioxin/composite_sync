#include <WiFi.h>

volatile int count = 0;
//unsigned long lastEntry, lastDisplay;
int frequency, tst;
const int PWMChannel =0;
const int resolution = 10;
int freq=15735;//63.55us period
int dutyCycle =948;
#define INPUTPIN 33
#define PWMPin  32

portMUX_TYPE synch = portMUX_INITIALIZER_UNLOCKED;


void IRAM_ATTR isr()
{
  if(count==6)
  {   
    ledcSetup(PWMChannel, 31440, resolution);
    ledcAttachPin(PWMPin, PWMChannel);
    timerSetDivider(0,31470);
    ledcWrite(PWMChannel, 72);
  }
  if(count==12)
  {    
    ledcWrite(PWMChannel, 952);    
  }
  if(count==18)
  {    
    ledcSetup(PWMChannel, 15720, resolution);
    ledcAttachPin(PWMPin, PWMChannel);   
    ledcWrite(PWMChannel, 948);//4.7us
  }  
  
  if(count==262)// && phase==0)
  {
    count=0;
    ledcSetup(PWMChannel, 31470, resolution);
    ledcAttachPin(PWMPin, PWMChannel);
    ledcWrite(PWMChannel, 952);
  }
  count++;
}


void setup() {
WiFi.mode(WIFI_OFF);

  pinMode(INPUTPIN, INPUT_PULLUP);
  pinMode(PWMPin,OUTPUT);
  ledcSetup(PWMChannel, 31470, resolution);
  ledcAttachPin(PWMPin, PWMChannel);
  ledcWrite(PWMChannel, 952);
   
  attachInterrupt(INPUTPIN, isr, FALLING  );

}

void loop() {

  
  
}
