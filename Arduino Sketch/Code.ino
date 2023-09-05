#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int analogInPin = A0;
int sensorValue = 0;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;  
int pos = 20;
const int trigPin = 5;
const int echoPin = 6;

long duration;
float distance;

int i = 0;

void setup() {
  Serial.begin(9600); //Initializing the Serial Port to Baud rate 9600
  mlx.begin();
  //initialize lcd screen
  lcd.init();
  // turn on the backlight
  lcd.backlight();
  // declare pin  to be an output:
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  //Serial.begin(9600);
  //-----------------
  myservo.attach(11);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  myservo.write(pos);
}

// the loop routine runs over and over again forever:
void loop() {
  //Reading the data from the sensor and printing it on Serial terminal
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  Serial.print("Temperature:");
  lcd.setCursor(0,1);
  Serial.print(mlx.readObjectTempC());
  lcd.print(mlx.readObjectTempC() - 10);
  Serial.print(" C");
  lcd.print(" C");

  Serial.println();
  delay(2000);
  //-------------------
  sensorValue = analogRead(analogInPin);
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\n");
  delay(2);
  if(( sensorValue<340)){
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    delay(100);
    }
  else if((sensorValue>=340)&&(sensorValue<420)){
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4, LOW);
    delay(100);
    }
  else if((sensorValue>=420)){
    digitalWrite(2,HIGH);//green
    digitalWrite(3,LOW);//blue
    digitalWrite(4,LOW);//red
   delay(100);
    } 
   // Serial.begin(9600);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = 0.034*(duration/2);
  Serial.println(distance);
  if (distance < 15)
  {
    //-------------
    myservo.write(pos+100);
    lcd.clear();
    //delay(500);
    i = i + 1;
  }
  else 
  {
      myservo.write(pos);
      if (i == 1) {
        i = 0;
        lcd.clear();
      }
  }
}