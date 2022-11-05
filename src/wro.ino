#include <L298N.h>
#include <HCSR04.h>
#include <Servo.h>
#define I2C
#include <Pixy2I2C.h>
Pixy2I2C pixy;
int IN2 = 8 ;
int IN1 = 7 ;
int ENA = 6 ;
int Tr_ULL = 2 ;
int Echo_ULL = 3 ;
int Tr_ULR = 4 ;
int Echo_ULR = 5 ;
int K1 = 5 ;
int steer ;
unsigned long cMillis = 0 ;
unsigned long pMillis = 0 ;
const long interval_1 = 0;  
const long interval_2 = 0 ;
int DR = 0 ;
int DL = 0;
unsigned long error = 0 ;
int x_pos = 0 ;

UltraSonicDistanceSensor Right_Ultra(5, 4);
UltraSonicDistanceSensor Left_Ultra(3, 2);

L298N motor(ENA, IN1, IN2);
Servo myservo;

void setup() {
  pixy.init();
  Serial.begin(115200);
  Serial.print("Starting...\n");
  
  myservo.attach(9);
  myservo.write(90);
  delay ( 10000) ;
  
  motor.setSpeed(150);
  pMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int i;
  pixy.ccc.getBlocks();
  
  
  if (pixy.ccc.numBlocks)
  {
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      motor.forward();
      x_pos = pixy.ccc.blocks[i].m_x;
    }
  }
  else
  {
    motor.stop();
    }
  cMillis = millis();
  
  //160 miangin
  error = (x_pos - 220) / 2 ;
  steer = 90 + error ;
  myservo.write(steer);


  
  DR = Right_Ultra.measureDistanceCm();
  DL = Left_Ultra.measureDistanceCm();
  Serial.println(x_pos);
  //if(cMillis - pMillis >= 3000 && DL >= 200 ){
  //  myservo.write(45);
  //  delay(2500);
  //  pMillis = millis() ;
 // }
 // else{
 //         error = DR - 12 ;
 //         steer = K1 * error ;
 //         myservo.write(steer);
 // }
        
}
