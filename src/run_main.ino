#include <L298N.h>
#include <HCSR04.h>
#include <Servo.h>
int IN2 = 8 ;
int IN1 = 7 ;
int ENA = 6 ;
int Tr_ULL = 3 ;
int Echo_ULL = 2 ;
int Tr_ULR = 5 ;
int Echo_ULR = 4 ;
int K1 = 9 ;
int steer ;
unsigned long cMillis = 0 ;
unsigned long pMillis = 0 ;
const long interval_1 = 0;  
const long interval_2 = 0 ;
unsigned long DR = 0 ;
unsigned long DL = 0;
unsigned long error = 0 ;

UltraSonicDistanceSensor Right_Ultra(3, 2);
UltraSonicDistanceSensor Left_Ultra(5, 4);

L298N motor(ENA, IN1, IN2);
Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  delay ( 10000) ;
  
  myservo.write(90);
  motor.setSpeed(100);
}

void loop() {
  cMillis = millis ();
  motor.forward();
  myservo.write(150);
}
