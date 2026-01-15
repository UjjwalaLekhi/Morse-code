#include<Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define dotp 27
#define dashp 26
#define vt 25
volatile long lastSignalTime;
volatile int rear=0,i=0,j=0,b=0;
char temp[100];
volatile char a[100];
int lcdCol = 0; 
int lcdRow = 0;


 const char *morse_code[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
  };

  const char letters[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'
  };

void enqueue(char b)
{
  a[rear]= b;

  rear=(rear+1)%100;
}
void dotfunc(){
   lastSignalTime = millis();
  if(digitalRead(vt)==HIGH)
  enqueue('.');

}

void dashfunc(){
   lastSignalTime = millis();
  if(digitalRead(vt)==HIGH)
  enqueue('-');
}

void setup() {
 pinMode(dotp,INPUT);
 pinMode(2,OUTPUT);
 pinMode(dashp,INPUT);
  pinMode(vt,INPUT_PULLUP);
 Serial.begin(9600);
 attachInterrupt(digitalPinToInterrupt(dotp), dotfunc,FALLING);
 attachInterrupt(digitalPinToInterrupt(dashp), dashfunc,FALLING);
lcd.init(); // Initialize the LCD
lcd.backlight(); // Turn on the backlight
lcd.setCursor(0, 0);

}

void loop() {

  if (millis() - lastSignalTime > 3000 && lastSignalTime != 0) {
  enqueue(' '); 
  //Serial.print("sopace");
  lastSignalTime=millis();
}
   
  while(i!=rear)
  {
    if (a[i] == ' ')
    {
      temp[j] = '\0';
      Serial.println(temp);
      if (j > 0) {
            for (int k  = 0; k < 26; k++) {
              if (strcmp(temp, morse_code[k]) == 0) {
                Serial.print(letters[k]);
               lcd.print(letters[k]);
               lcdCol++;

if (lcdCol >= 16) {       // move to next line
  lcdCol = 0;
  lcdRow++;
  if (lcdRow >= 2) {      // if both lines are full
    lcd.clear();          // clear the screen
    lcdRow = 0;
  }
  lcd.setCursor(lcdCol, lcdRow);
} else {
  lcd.setCursor(lcdCol, lcdRow);
}
                break;
              }
            }
      }
      j=0;
    }
    else
    temp[j++]=a[i];
    a[i]=0;
    i=((i+1)%100);
  }
}
