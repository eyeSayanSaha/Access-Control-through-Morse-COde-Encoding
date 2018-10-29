#include <Wire.h> 

//Here the transmit is being taken as a means of on off button with the button doing the input part.
int led = 8;
int button = 5;
int  star = 10;
const int trigger = 2;
const int echo = 3;
int go = 0;
int len =0;
String fin = "";
String morse_array[50];
int test = 0;
int m_inc = 0;
char m_in[5];
String translated ="";
int buttonState = 0; 
String morsecode[] ={
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
    "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
    "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
    "-.--", "--..", " " };
String alphabets [] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
"q", "r", "s", "t", "u", "v", "w", "x", "y", "z", " "};

void setup() {
  // put your setup code here, to run once:
    pinMode(echo, INPUT);
    pinMode(trigger, OUTPUT);
    pinMode(led, OUTPUT);
    pinMode(button, INPUT);
    pinMode(star, INPUT);
    Serial.begin(9600);
}
unsigned long ultraSound()
{
    // Establish variables for duration of the ping, 
    // The distance result in inches and centimeters:
    long duration, inches, cm;

    
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
  
    duration = pulseIn(echo, HIGH);

    // convert the time into a distance
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);

  
    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    return cm;
    delay(50);
}

void loop() {
  // put your main code here, to run repeatedly:
    int x=0;
    x = ultraSound();
    if(cm<55)
    {
      if  (digitalRead(star)==LOW)
      { 
         delay (300);
         if  (digitalRead(star)==HIGH)
         convert();
      else
        while (digitalRead(star)==LOW)
        check_button();
      }
    }
    delay(250);
}


long microsecondsToInches(long microseconds)
{
    return microseconds/74/2;                                  //Formula given on the internet.
}


long microsecondsToCentimeters(long microseconds)
{
    return microseconds/29/2;                                  //Formula given on the internet.
}


void check_button(){
if (digitalRead(button)==LOW)
 {
 delay (300);
  if(digitalRead(button)==HIGH)
    {
      m_in[m_inc] = '.';
      m_inc++;
      test = 1;
    }
  else 
    {
       m_in[m_inc] = '-';
      m_inc++;
    test = 2;
    delay(400);
    }
 }
}
void convert(){
  for (int i = 0; i<5; i++)
    {
    translated += m_in[i];
    }
    translated.trim();
     Serial.print(translated);
     translated = findMorse(translated);
     Serial.print(translated);
     fin += translated;
    translated = "";
    for (int i = 0; i<5; i++)
    {
    m_in[i] = ' ';
    }
    m_inc=0;
}
String findMorse(String s){
  int v = 26;
  for (int x = 0; x<26;x++)
  {
    if (morsecode[x].equals(s))
      v = x;
  }
      
  return alphabets[v];
}
