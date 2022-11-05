#include <L298N.h>
#include <HCSR04.h>
#include <Servo.h>
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

UltraSonicDistanceSensor Right_Ultra(5, 4);
UltraSonicDistanceSensor Left_Ultra(3, 2);

L298N motor(ENA, IN1, IN2);
Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  delay ( 10000) ;
  
  myservo.write(90);
  motor.setSpeed(150);
  pMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  cMillis = millis();
  motor.forward();
  DR = Right_Ultra.measureDistanceCm();
  DL = Left_Ultra.measureDistanceCm();
  Serial.println(DL);
  if(cMillis - pMillis >= 3000 && DL >= 200 ){
    myservo.write(45);
    delay(2500);
    pMillis = millis() ;
  }
  else{
          error = DR - 12 ;
          steer = K1 * error ;
          myservo.write(steer);
  }
        
}
