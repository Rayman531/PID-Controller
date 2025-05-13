// PID Controller code 
#include <Wire.h>
#include <Servo.h>



//Inputs/outputs
int Analog_in = A0;
Servo myservo;  



//Variables/
int Read = 0;
float distance = 0.0;
float elapsedTime, time, timePrev;        
float distance_previous_error, distance_error;
int period = 50; 



//PID constants
float kp=20; 
float ki=0.4;
float kd=2900; 
float distance_middle = 5;         
float PID_p, PID_i, PID_d, PID_total;




void setup() {
   Serial.begin(9600);  
  myservo.attach(9);  
  myservo.write(125); 
  pinMode(Analog_in,INPUT);  
  time = millis();

}

void loop() {
   if (millis() > time+period)
  {
    time = millis();    
    distance = get_dist(100);   
    distance_error = distance_middle - distance;   
    PID_p = kp * distance_error;
    float dist_diference = distance_error - distance_previous_error;     
    PID_d = kd*((distance_error - distance_previous_error)/period);
      
    if(-3 < distance_error && distance_error < 3)
    {
      PID_i = PID_i + (ki * distance_error);
    }
    else
    {
      PID_i = 0;
    }
  
    PID_total = PID_p + PID_i + PID_d;  
    PID_total = map(PID_total, -150, 150, 0, 150);
  
    if(PID_total < 20){PID_total = 20;}
    if(PID_total > 160) {PID_total = 160; } 
  
    myservo.write(PID_total+30);  
    distance_previous_error = distance_error;
  }
  

}

float get_dist(int n)
{
  long sum=0;
  for(int i=0;i<n;i++)
  {
    sum=sum+analogRead(Analog_in);
  }  
  float adc=sum/n;
  //float volts = analogRead(adc)*0.0048828125;  // value from sensor * (5/1024)
  //float volts = sum*0.003222656;  // value from sensor * (3.3/1024) EXTERNAL analog refference

  float distance_cm = 17569.7 * pow(adc, -1.2062);
  //float distance_cm = 13*pow(volts, -1); 
  return(distance_cm);
}