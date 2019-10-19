#include <LiquidCrystal.h>
#include <dht.h>
dht DHT;
LiquidCrystal lcd(2,3,4,5,6,7);
int lm35pin = A0;
float lm35Value = 0;
int redlm35 = 13;
int greenlm35 = 12;
int mq135pin = A2;
int redmq135 = 9;
int greenmq135 = 8;  
int buzzer = 22;
int ldr = A1;
int redldr =  11;
int greenldr = 10;
int reddht11 = 25;
int greendht11 = 27;
int dht11pin = 24;
int btlm35 = 45;
int btldr = 47;
int btmq = 49;
int btdht = 51;


void lm35sense();
void ldrsense();
void mq135sense();
void dht11sense();
void beep();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
  pinMode(ldr,INPUT);
  pinMode(redlm35,OUTPUT);
  pinMode(greenlm35,OUTPUT);
  pinMode(redldr,OUTPUT);
  pinMode(greenldr,OUTPUT); 
  pinMode(redmq135,OUTPUT);
  pinMode(greenmq135,OUTPUT);
  pinMode(dht11pin,INPUT);
  pinMode(reddht11,OUTPUT);
  pinMode(greendht11,OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Press a button");
}

void loop() {
  // put your main code here, to run repeatedly:
  lm35sense();
  ldrsense();
  mq135sense();
  dht11sense();
}

void beep()
{
    digitalWrite(buzzer,HIGH); 
    delay(1000);
    digitalWrite(buzzer,LOW);
}

void lm35sense()
{
  lm35Value = analogRead(lm35pin); 
  float temp;
  temp = lm35Value * 0.488;  // (5/1024)*(1000/10)
  Serial.println((String)"Temp="+temp);
  if(digitalRead(btlm35)==HIGH)
  {
    lcd.clear();
    lcd.print((String)"Temperature="+(String)temp+(String)" Degree celsius");
    delay(1000);
    lcd.clear();
    lcd.print("press button");
    
  }
  if(temp>=40)
  {
    Serial.println("High Temperature");
    digitalWrite(greenlm35,LOW);
    digitalWrite(redlm35,HIGH);
    beep();
  }
  else
  {
    digitalWrite(greenlm35,HIGH);
    digitalWrite(redlm35,LOW);
  }
}

void ldrsense()
{
  float reading = analogRead(ldr);
  reading = constrain(reading,200,700);
  if(digitalRead(btldr) == HIGH)
  {
    if(reading>450){
    lcd.clear();
    lcd.print((String)"Light="+"Dark");
    delay(1000);
    lcd.clear();
    lcd.print("press button");
  }else{
    lcd.clear();
     lcd.print((String)"Light="+"Bright");
    delay(1000);
    lcd.clear();
    lcd.print("press button");
  }
  }
  if(reading<450)
  {
    Serial.println("Bright");
    digitalWrite(redldr,LOW);
    digitalWrite(greenldr,HIGH);
    
  } 
 
  else 
  {
    Serial.println("Low light");
    digitalWrite(redldr,HIGH);
    digitalWrite(greenldr,LOW);
    beep();
  }  
}

void mq135sense()
{
  float gas = analogRead(gas);
  gas = map(gas,50,200,400,600);
  Serial.println((String)"Gas="+gas);
  if(digitalRead(btmq) == HIGH)
  {
    lcd.clear();
    lcd.print((String)"AQI="+(String)gas);
    delay(1000);
    lcd.clear();
    lcd.print("press button");
  }
  if(gas<500)
  {
    digitalWrite(redmq135,LOW);
    digitalWrite(greenmq135,HIGH);
    Serial.println("AQI is good");
  }
  else if(gas>500)
  {
    digitalWrite(redmq135,HIGH);
    digitalWrite(greenmq135,LOW);
    Serial.println("AQI is bad");
    beep();
  }  
}

void dht11sense()
{
   int a = DHT.read11(dht11pin);
   Serial.println((String)"Humidity"+DHT.humidity);
   if(digitalRead(btdht) == HIGH)
  {
    lcd.clear();
    lcd.print((String)"Humidity="+DHT.humidity+(String)"RH");
    delay(1000);
    lcd.clear();
    lcd.print("press button");
  }
   if(DHT.humidity>90)
   {
      digitalWrite(reddht11,HIGH);
      digitalWrite(greendht11,LOW);
      Serial.print("High Humidity: ");
      beep();
   }
  else if(DHT.humidity<50)
  {
    digitalWrite(reddht11,HIGH);
    digitalWrite(greendht11,LOW);
    Serial.print("Low Humidity: ");
    beep();
   
  }
  else
  {
    digitalWrite(reddht11,LOW);
    digitalWrite(greendht11,HIGH);
  }
}
