#include <radar.h>

#ifdef __AVR__
    #include <SoftwareSerial.h>
    SoftwareSerial SSerial(2, 3); // RX, TX
    #define Serial1 SSerial
#endif

#define MESSAGE_HEAD 0x55
int data[14] = {0};
int i = 0;
int Msg;
int Situation_action;
int Fall_action;

radar RADAR;

void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("Readly");
}

void Bodysign_judgment(int ad1, int ad2, int ad3, int ad4, int ad5){
  float s;
  s = RADAR.Bodysign_val(ad1, ad2, ad3, ad4, ad5);
  if(s > 1.5 && s < 35){
    Serial.println("SOMEBODY STOP");
  }
  else if(s < 1.5){
    Serial.println("NOBODY");
  }
  else if(s > 35){
    Serial.println("SOMEBODY MOVE");
  }
}

void loop()
{
  Msg = Serial1.read();
  if(Msg == MESSAGE_HEAD){
    for(i = 0; i<14; i++){
      data[i] = Msg;                         
      Msg = Serial1.read();
      if (Msg == MESSAGE_HEAD){
        Situation_action = RADAR.Situation_judgment(data[5], data[6], data[7], data[8], data[9]);   //situation function
        if (Situation_action == 1){
          Serial.println("radar said nobody");
        }
        if (Situation_action == 2){
          Serial.println("radar said somebody move");
        }
        if (Situation_action == 3){
          Serial.println("radar said somebody stop");
        }
        if (Situation_action == 4){
          Serial.println("radar said no move");
        }
        if (Situation_action == 5){
          Serial.println("radar said somebody close");
        }
        if (Situation_action == 6){
          Serial.println("radar said somebody away");
        } 
               
//        Fall_action = RADAR.Fall_judgment(data[4], data[5], data[6], data[7]);    // Fall function
//        if (Fall_action == 1){
//          Serial.println("SUSPECTED FALL");
//        }
//        if (Fall_action == 2){
//          Serial.println("REAL FALL");
//        }
//        if (Fall_action == 3){
//          Serial.println("NO FALL");
//        }
//        if (Fall_action == 4){
//          Serial.println("NO WARNING");
//        }
//        if (Fall_action == 5){
//          Serial.println("FIRST WARNING");
//        }
//        if (Fall_action == 6){
//          Serial.println("SECOND WARNING");
//        }
//        if (Fall_action == 7){
//          Serial.println("THIRD WARNING");
//        }
//        if (Fall_action == 8){
//          Serial.println("FORTH WARNING");
//        }
        continue;
      }
      delay(25);
     }
   }
}