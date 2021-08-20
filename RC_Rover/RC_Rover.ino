#include <SoftwareSerial.h>
#include <L298N.h>

#define EN_A 10
#define IN3 9
#define IN4 8

#define EN_B 11
#define IN1 6
#define IN2 5

#define NORMAL_SPEED 150
#define HIGH_SPEED 255

L298N left_motor(EN_A, IN3, IN4), right_motor(EN_B, IN1, IN2);

SoftwareSerial mySerial(3, 2); // RX, TX

int speedX = NORMAL_SPEED;
char x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  left_motor.setSpeed(speedX);
  right_motor.setSpeed(speedX);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySerial.available()){
    char a;
    a = mySerial.read();
    Serial.print(a);
    Command(a);
    if(a == 'n'){delay(100); Serial.println(x); Command(x);}
  }
}

void Command(char a){
  switch(a){
      case 'a' : right_motor.forward();
                 left_motor.stop();
                 x = 'a';
                 break;
      case 'd' : right_motor.stop();
                 left_motor.forward();
                 x = 'd';
                 break;
      case 'w' : right_motor.forward();
                 left_motor.forward();
                 x = 'w';
                 break;
      case 's' : right_motor.backward();
                 left_motor.backward();
                 x = 's';
                 break;
      case 'c' : right_motor.backward();
                 left_motor.forward();
                 x = 'c';
                 break;
      case 'z' : right_motor.forward();
                 left_motor.backward();
                 x = 'z';
                 break;
      case 'x' : right_motor.stop();
                 left_motor.stop();
                 x = 'x';
                 break;
      case 'n' : if(speedX == NORMAL_SPEED) speedX = HIGH_SPEED;
                 else speedX = NORMAL_SPEED;
                 left_motor.setSpeed(speedX);
                 right_motor.setSpeed(speedX);
                 break;
    }
}
