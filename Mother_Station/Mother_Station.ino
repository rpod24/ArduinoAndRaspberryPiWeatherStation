/*
 * How to configure and pair two HC-05 Bluetooth Modules
 * by Dejan Nedelkovski, www.HowToMechatronics.com
 * 
 *                 == SLAVE CODE ==
 */
 
#include <Servo.h>
#define button 8
#include <DHT.h>;
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;
//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
Servo myServo;
int state = 20;
int buttonState = 0;
int i = 0;
int chk;
float hum;  //Stores humidity value
float temp;
String message;
String letter;
String SentMessage;
int T100;
int T10;
int T1;
int H100;
int H10;
int H1;
int rain = 0;
int P10;
int P1;
int P01;
int P001;
double P;
double pressure;

void setup() {
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  dht.begin();
  bmp.begin();
  pinMode(6, INPUT);
}
void loop() {
  if(digitalRead(8)==HIGH){
    rain = 1;
  }
  else{
    rain = 0;
  }
hum = dht.readHumidity();
temp= dht.readTemperature();
P = bmp.readPressure();

P = P*0.00029529983071445;
temp = (temp*9/5)+32;



int h = round(hum);
int t = round(temp);

//Temp

if(t>99){
  T100=t;
  T100 = T100/100;
  T100=T100-0.5;
  T100=round(T100);
}
else{
  T100=0;
}
if(t>9){
  T10=t;
  if(t>100){
    T10=T10-100;
  }
    T10=T10/10;
    T10=T10;
    T10=round(T10);
}
else{
  T10=0;
}
if(t>0){
  T1=t-(T100*100);
  T1=T1-(T10*10);
}
else{
  T1=0;
}

//Humidity

if(h>99){
  H100=h;
  H100 = H100/100;
  H100=H100-0.5;
  H100=round(H100);
}
else{
  H100=0;
}
if(h>9){
  H10=h;
  if(h>100){
    H10=H10-100;
  }
    H10=H10/10;
    H10=H10;
    H10=round(H10);
} 
else{
  H10=0;
}
if(h>0){
  H1=h-(H100*100);
  H1=H1-(H10*10);
}
else{
  H1=0;
}



//Barometric Pressure

//D1

P=P*100;
P=round(P);
P10=P;
P10 = P10/1000;
P10=P10;
P10=round(P10);

P1=P-(P10*1000);
P1 = P1/100;
P1=P1;
P1=round(P1);

P01=P-(P10*1000);
P01=P01-(P1*100);
P01 = P01/10;
P01=P01;
P01=round(P01);


P001=P-(P10*1000);
P001=P001-(P1*100);
P001 = P001-(P01*10);
P001=P001;
P001=round(P001);


Serial.write("t");//1
Serial.write(T100);//2
Serial.write(T10);//3
Serial.write(T1);//4
Serial.write("H");//5
Serial.write(H100);//6
Serial.write(H10);//7
Serial.write(H1);//8
Serial.write(P10);//9
Serial.write(P1);//10
Serial.write(P01);//11
Serial.write(P001);//12
Serial.write(rain);//13

delay(300000);
}
