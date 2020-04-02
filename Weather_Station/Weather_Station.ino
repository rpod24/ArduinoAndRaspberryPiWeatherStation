//Made by Ryan O'Donnell
 #include <LiquidCrystal.h>
#include <DHT.h>;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
#define ledPin 9

#include <SPI.h>
#include <SD.h>

File myFile;
File myFile2;
File myFile3;

#define DHTPIN 7
#define DHTTYPE DHT22   // DHT 22 Sensor
DHT dht(DHTPIN, DHTTYPE);
int state = 0;//A load of variables
int temp;
int t;
int t100;
int t10;
int t1;
int h;
int h100;
int h10;
int h1;
int b10;
int b1;
int b01;
int b001;
double p;
boolean rain;
int cycle = 0;
int timeSinceRecived = 0;
int prevstate;
int Interior = 0;
int Exterior = 1;
int GasSensor = 2;
int totalModes = 2;
int mode=Exterior;
int IntHum = 0;
int IntTemp = 0;
int timePressing=0;
int screen;
boolean receiving;
boolean finishedOneCycle = false;
void setup() {//Setup method
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  lcd.begin(16, 2);
  dht.begin();

  if (!SD.begin(10)) {//looks for sd card
    while (1);
  }
}
void loop() {
    if(digitalRead(6)==HIGH){
      timePressing=0;
      if(mode < totalModes-1){
        mode++;
      }
      else{
        mode=0;
      }
      delay(2000);
    }
    IntHum = dht.readHumidity();
    IntTemp= dht.readTemperature();
    IntTemp = (IntTemp*9/5)+32;
    prevstate = state;
 if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
    timeSinceRecived=0;
    if(state==116){
      cycle=1;
    }
    receiving = true;
 }
 if(state==prevstate){
  timeSinceRecived++;
 }
  if(cycle==2){
    t100=state;
  }
  if(cycle==3){
    t10=state;
  }
  if(cycle==4){
    t1=state;
  }
  if(cycle==6){
    h100=state;
  }
  if(cycle==7){
    h10=state;
  }
  if(cycle==8){
    h1=state;
  }
  if(cycle==9){
    b10=state;
  }
  if(cycle==10){
    b1=state;
  }
  if(cycle==11){
    b01=state;
  }
  if(cycle==12){
    b001=state;
  }
  if(cycle==13){
    if(state == 1){
      rain = true;
    }
    else{
      rain = false;
    }
  }
 if(cycle>0){
  cycle++;
 }
 // Controlling the LED
  if(timeSinceRecived>1000){
    lcd.setCursor(0, 0);
    lcd.print("Not Receiving");
    lcd.setCursor(0, 1);
    lcd.print("                     ");
    receiving = false;
  }
  else{
  if(cycle >= 13){
    cycle = 0;
    String text = "Temp: ";
    t=(t100*100)+(t10*10)+t1;
    text = "Humitidy: ";
    h=(h100*100)+(h10*10)+h1;
    text = "Pressure: ";
    p=(b10*1000)+(b1*100)+(b01*10)+b001;
    p = p/100;
    if(rain){
    }
  else{
  }
  
    myFile = SD.open("Temp.txt", FILE_WRITE);
    if (myFile) {
    myFile.println(t);
    // close the file:
    myFile.close();
  }

    myFile2 = SD.open("Humidity.txt", FILE_WRITE);
    if (myFile2) {
    myFile2.println(h);
    // close the file:
    myFile2.close();
  }
  myFile3 = SD.open("Times.txt", FILE_WRITE);
    if (myFile3) {
    myFile3.println(millis());
    // close the file:
    myFile3.close();
  }

  finishedOneCycle = true;
  }
  if(screen == 3){
  lcd.setCursor(0, 0);
  lcd.print("                 ");
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  if(mode == Interior){
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  }
 }
    if(mode == Exterior){
      lcd.setCursor(13,0);
      lcd.print("Out");
      showOutside();
    }
    else if(mode == Interior){
      ShowInside();
      lcd.setCursor(13,0);
      lcd.print(" In");
    }
  }
 delay(2500);
if(receiving && finishedOneCycle){
  Serial.println("I");
  Serial.println("");
  Serial.println(t);
  Serial.println("NV");
  Serial.println(h); 
  Serial.println("NV");
  Serial.println(rain);
  Serial.println("NV");
  Serial.println(p);
}
 if(screen<4){
    screen++;
 }
 else{
  screen = 1;
  if(mode == Exterior){
  lcd.setCursor(0, 0);
  lcd.print("                 ");
  lcd.setCursor(0, 1);
  lcd.print("                 ");
 }
 lcd.setCursor(0, 0);
 lcd.print("Temp: ");
 }
}














void showOutside(){
  if(screen<3){
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    if(t100!=0){
      lcd.setCursor(5, 0);
      lcd.print(t);
    }
    else if(t10!=0){
      lcd.setCursor(6, 0);
      lcd.print(t);
    }
    else{
      lcd.setCursor(7, 0);
      lcd.print(t);

    }
    lcd.setCursor(8, 0);
    lcd.print("F    ");
    lcd.setCursor(0, 1);
    lcd.print("Humidity:" );
    if(h<100){
      lcd.setCursor(10, 1);
      lcd.print(h);
    }
    else if(h<10){
      lcd.setCursor(9, 1);
      lcd.print(h);
    }
    else{
      lcd.setCursor(8, 1);
      lcd.print(h);
    }
    lcd.setCursor(12, 1);
    lcd.print("%      ");
}
else{
  lcd.setCursor(0,0);
  if(rain){
  lcd.print("It is raining!");
  }
  else{
  lcd.print("It isn't raining");
  }
  lcd.setCursor(0,1);
  lcd.print("Pressure: ");
  lcd.setCursor(10,1);
  lcd.print(p);
  lcd.setCursor(15,1);
  lcd.print('"');
}
}

void ShowInside(){
  lcd.print("Temp: ");
  if(IntTemp>=100){
    lcd.setCursor(5, 0);
    lcd.print(IntTemp);
  }
  else if(IntTemp>=10){
    lcd.setCursor(6, 0);
    lcd.print(IntTemp);
  }
  else{
    lcd.setCursor(7, 0);
    lcd.print(IntTemp);
  }

    lcd.setCursor(8, 0);
    lcd.print("F     ");
    lcd.setCursor(0, 1);
  
    lcd.print("Humidity: " );
    if(IntHum<100){
      lcd.setCursor(10, 1);
      lcd.print(IntHum);
    }
    else if(IntHum<10){
      lcd.setCursor(9, 1);
      lcd.print(IntHum);
    }
    else{
      lcd.setCursor(8, 1);
      lcd.print(IntHum);
    }
    lcd.setCursor(12, 1);
    lcd.print("%     ");
}
