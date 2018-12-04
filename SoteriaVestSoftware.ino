/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Simple Accelerometer Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/
 
#include <Wire.h>
#include "MPU6050.h"
 
#define Sensor1 A0
#define Sensor2 A1
#define Sensor3 A2
#define Sensor4 A3
#define Sensor5 A4
#define Sensor6 A5
#define Int1 13
#define Int2 12
#define Int3 11
#define Int4 10
#define Int5 9
#define Int6 8
 
//initializing variables
MPU6050 mpu;
String inString = "";
float sumAccel = 0;
int count = 0;
int switchCount = 0;
float totalDeltaT = 0;
int intCount = 0;
 
void setup()
{
  //begin serial communication
  Serial.begin(38400);
 
  //check if MPU 6050 initialized
  //Serial.println("Initialize MPU6050");
 
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  /*pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);*/
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  /*pinMode(13, INPUT);
  pinMode(13, INPUT);
  pinMode(13, INPUT);
  pinMode(13, INPUT);*/
 
  if(digitalRead(Int1) == 0 && digitalRead(Int2) == 0)
    {
      if(intCount == 0)
      {
        Serial.println("\tSensor1:");
        digitalWrite(A0, LOW);
        digitalWrite(A1, HIGH);
        intCount = 1;
      }
      else if(intCount == 1)
      {
        Serial.println("\tSensor2:");
        digitalWrite(A0, LOW);
        digitalWrite(A1, HIGH);
        intCount = 0;
      }
    }
    else if(digitalRead(Int1) == 0 && digitalRead(Int2) == 1)
    {
      Serial.println("\tSensor1:");
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
    }
    else if(digitalRead(Int1) == 1 && digitalRead(Int2) == 0)
    {
      Serial.println("\tSensor2:");
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
    }
 
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
 
  checkSettings();
 
  Serial.print("Time,");
  Serial.println("Impulse: ");
}
 
void checkSettings()
{
  //checks if the MPU 6050 is active and checks the clock sourse
  /*Serial.println();
 
  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
 
  Serial.print(" * Clock Source:          ");
  /*switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset");
    break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference");
    break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference");
    break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference");
    break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference");
    break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference");
    break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator");
    break;
  }*/
 
  //sets the range of the accelerometer
  //Serial.print(" * Accelerometer:         ");
  mpu.setRange(MPU6050_RANGE_16G);
  /*switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  */
 
  //print the default offset
/* Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());*/
 
  //Serial.println();
}
 
void loop()
{
  //intialize variables for calculations
  float mass, accel, avgAccel, Force, Impulse;
  float startTime, start, finish, deltaT;
  float accel1, accel2, accel3, accel4, accel5, ratio;
 
  //Serial.println(accel);
 
  //sets the data to vector type and intializes it to the data from the MPU6050 sensor
 Vector rawAccel = mpu.readRawAccel();
 Vector normAccel = mpu.readNormalizeAccel();
 
  /* //Print raw and normalized data
  Serial.print(" Xraw = ");
  Serial.print(rawAccel.XAxis*-1);
  Serial.print(" Yraw = ");
  Serial.print(rawAccel.YAxis*-1);
  Serial.print(" Zraw = ");
  Serial.println(rawAccel.ZAxis*-1);
  Serial.print(" Xnorm = ");
  Serial.print(normAccel.XAxis*-1);
  Serial.print(" Ynorm = ");
  Serial.print(normAccel.YAxis*-1);
  Serial.print(" Znorm = ");
  Serial.println(normAccel.ZAxis*-1);
  Serial.println(millis());*/
 
  //Gets input from serial monitor
  /*while (Serial.available() > 0)
  {
    Serial.print("Enter the mass of the object in kg");
    int inChar = Serial.read();
    i (isDigit(inChar)) {
     // convert the incoming byte to a char and add it to the string:
     inString += (char)inChar;
    }    // if you get a newline, print the string, then the string's value:
    i (inChar == '\n') {
     Serial.print("Value:");
     Serial.println(inString.toInt());
     Serial.print("String: ");
      Serial.println(inString);
      mass = inString.toInt();
      // clear the string for new input:
      inString = "";
    }
  }*/
 
  mass  = 1.8;
 
  //checks if the data is above a set threshold
  if(normAccel.XAxis > 15 || normAccel.XAxis < -15 || normAccel.YAxis < -15 || normAccel.YAxis > 15 || normAccel.ZAxis < -15 || normAccel.ZAxis > 15)
  {
    //stores the time of the first of an instance of Impulse
    if(count == 0)
    {
      startTime = millis();
    }
    //beginning time for the delta time
    start = millis();
 
    //acceleration calculations
    accel = sqrt(sq(normAccel.XAxis)+sq(normAccel.YAxis)+sq(normAccel.ZAxis));
    sumAccel = sumAccel + accel;
 
    //finishing time for the delta time
    finish = millis();
 
    //change in time
    deltaT = finish-start;
    totalDeltaT = totalDeltaT + deltaT;
 
    //total count of how many accelerations taken
    ++count;
  }
 
  //stores the last 5 acceleration measured and makes a ratio of them
  switch(switchCount)
  {
    case 0:
      accel1 = sqrt(sq(normAccel.XAxis)+sq(normAccel.YAxis)+sq(normAccel.ZAxis));
      ratio = (5*accel1)/(accel5+accel4+accel3+accel2+accel1);
      break;
    case 1:
      accel2 = sqrt(sq(normAccel.XAxis)+sq(normAccel.YAxis)+sq(normAccel.ZAxis));
      ratio = (5*accel2)/(accel5+accel4+accel3+accel2+accel1);
      break;
    case 2:
      accel3 = sqrt(sq(normAccel.XAxis)+sq(normAccel.YAxis)+sq(normAccel.ZAxis));
      ratio = (5*accel3)/(accel5+accel4+accel3+accel2+accel1);
      break;
    case 3:
      accel4 = sqrt(sq(normAccel.XAxis)+sq(normAccel.YAxis)+sq(normAccel.ZAxis));
      ratio = (5*accel4)/(accel5+accel4+accel3+accel2+accel1);
      break;
    case 4:
      accel5 = sqrt(sq(normAccel.XAxis)+sq(normAccel.YAxis)+sq(normAccel.ZAxis));
      ratio = (5*accel5)/(accel5+accel4+accel3+accel2+accel1);
      break;
    default:
      switchCount = 0;
      break;
  }
 
  //add count anytime data taken
  ++switchCount;
 
  if(digitalRead(Int1) == 0 && digitalRead(Int2) == 0)
    {
      if(intCount == 0)
      {
        Serial.println("\tSensor1:");
        digitalWrite(A0, LOW);
        digitalWrite(A1, HIGH);
       
        intCount = 1;
        count = 0;
        totalDeltaT = 0;
        sumAccel = 0;
      }
      else if(intCount == 1)
      {
        Serial.println("\tSensor2:");
        digitalWrite(A0, LOW);
        digitalWrite(A1, HIGH);
       
        intCount = 0;
        count = 0;
        totalDeltaT = 0;
        sumAccel = 0;
      }
    }
    else if(digitalRead(Int1) == 0 && digitalRead(Int2) == 1)
    {
      Serial.println("\tSensor1:");
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
 
      count = 0;
      totalDeltaT = 0;
      sumAccel = 0;
    }
    else if(digitalRead(Int1) == 1 && digitalRead(Int2) == 0)
    {
      Serial.println("\tSensor2:");
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
 
      count = 0;
      totalDeltaT = 0;
      sumAccel = 0;
    }
         
  if(count > 0)
  {
    avgAccel = sumAccel/count;
 
    //average force
    Force = mass * avgAccel;
    Impulse = Force * totalDeltaT;
   
    //Serial.print(millis());
    //Serial.println(",");
    Serial.println(Impulse);
    if (Impulse > 100) {
      Serial.println("SEEK MEDICAL ASSISTANCE!");
    }
  }
 
 
  //checks if no longer taking data above threshold and
  if(startTime+(count*25) < millis() && (ratio > 0.5 || ratio < 1.5))
  {
    count = 0;
    totalDeltaT = 0;
    sumAccel = 0;
  }
}
