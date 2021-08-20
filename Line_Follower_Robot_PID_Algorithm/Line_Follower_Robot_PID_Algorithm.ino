int sensor_Average ;
int sensor_sum;
int Position;
int last_position;
long sensors[]={0,0,0,0,0,0};
byte sensorPins[]={A0,A1,A2,A3,A4,A5};
byte num_of_sensors=6;
int  set_point=2500;

double Kp= 0.09; //edit 
double Ki=0;  //edit
double Kd=0.01; //edit 
int lnv =30; 

int proportional;
int integral;
int derivative;
int last_proportional;
int error_value;

int right_speed;
int left_speed;
int max_speed=255;  
 
byte motor1A=8; 
byte motor1B=7;
byte motor_Right=6;
byte motor2A=4;
byte motor2B=3;
byte motor_Left=5;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(motor1A,OUTPUT);
    pinMode(motor1B,OUTPUT);
    pinMode(motor2A,OUTPUT);
    pinMode(motor2B,OUTPUT);
}

void loop() {
sensor_read();
pid_calc();
calc_turn();
motor_drive(right_speed,left_speed);
}
void sensor_read(){
  sensor_Average=0;
  sensor_sum=0;
  for(byte c=0;c<num_of_sensors;c++){
       sensors[c]=digitalRead(sensorPins[c]);
      sensor_Average =sensor_Average + sensors[c]*c*1000; //Calculating weighted mean
      sensor_sum += int(sensors[c]);      // Calculating sum of sensor Reading
  }
  
}
void pid_calc(){
  Position= int(sensor_Average/sensor_sum);
  if(Position==-1)
  Position=last_position;
  proportional=Position-set_point;
  integral=integral+proportional;
  derivative=proportional-proportional;
  last_proportional=proportional;
  error_value=int(proportional*Kp+integral*Ki+derivative*Kd);

  if(Position!=1)
  last_position=Position;
  
}
void calc_turn(){
    Serial.print(error_value);
    Serial.print("  ");

    right_speed=max_speed+error_value;
    left_speed=max_speed-error_value;
}
void motor_drive(int right_speed,int left_speed){
  
  if(right_speed<=lnv){
    right_speed=left_speed;
    digitalWrite(motor1A,0);
    digitalWrite(motor1B,1);
  }
  else{
    digitalWrite(motor1A,1);
        digitalWrite(motor1B,0);
  }

  if(left_speed<=lnv)
    {
      left_speed=right_speed;
      digitalWrite(motor2A,0);
      digitalWrite(motor2B,1);
      }else
      {
       digitalWrite(motor2A,1);
        digitalWrite(motor2B,0);
        }
//    if(right_speed<(-1)*max_speed)
//      left_speed = left_speed*.7;
//
//    if(left_speed<(-1)*max_speed)
//      right_speed = right_speed*.7;
      if(right_speed>max_speed)
        right_speed=max_speed;
      if(left_speed>max_speed)
        left_speed=max_speed;

    analogWrite(motor_Right,right_speed);
    analogWrite(motor_Left,left_speed);
  Serial.print(right_speed);
  Serial.print("  ");
  Serial.print(left_speed);
  Serial.println();
}
