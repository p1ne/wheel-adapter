#include <Arduino.h>

// Tablet library taken from here http://pccar.ru/showpost.php?p=366382&postcount=669

#include "Tablet.h"

int analogPin=3;    //пин для подключения кнопок 
int data; 
unsigned long flag = 0; 
unsigned long eventTime = 0; 
unsigned long pauseMillis = 0; 

#define NOBUTTON 256
#define PLAY 432
#define NEXT 652
#define PREV 538
#define VOLUP 772
#define VOLDOWN 896

#define TOLERANCE 10

boolean between(int value, int a, int b)
{
  if ( (value > a) && (value < b) ) return 1;
  else return 0;
}

boolean tolerance(int value, int expected)
{
  if ((value >= expected - TOLERANCE) && (value <= expected + TOLERANCE)) return 1;
  else return 0;
}

void setup() 
{
} 

void loop() 
{ 
  data=analogRead(analogPin); //читаем значение нажатой кнопки 
   


  if((tolerance(data, 256) || tolerance(data, 0)) && flag == 0) // все кнопки отпущены 
   { 
    eventTime=millis(); 
   } 
   
//********************** Громкость ************************************ 
  if(between(millis()-eventTime, 10, 499) && tolerance(data, VOLUP) && flag == 0) // короткое нажатие кнопки от 10 до 499 миллисекунд (изменяется здесь millis()-eventTime>10 && millis()-eventTime<499) 
   {  
    Tablet.vol_up(); 
    flag = 5; 
    delay(10); 
    Tablet.clear(); 
   } 

  if(millis()-eventTime>500 && tolerance(data, VOLUP) && flag == 5 || tolerance(data, VOLUP) && flag == 3) // удержание кнопки от 500 до ? миллисекунд (изменяется здесь millis()-eventTime>500) 
   {  
    Tablet.vol_up(); // действие после удержание кнопки, Увеличить громкость каждые 0,1 секунды 
    flag = 3; 
    Tablet.clear(); 
    delay(100); 
   } 

  if(between(millis()-eventTime, 10, 499) && tolerance(data, VOLDOWN) && flag == 0) // короткое нажатие кнопки от 10 до 499 миллисекунд (изменяется здесь millis()-eventTime>10 && millis()-eventTime<499) 
   {  
    Tablet.vol_down(); 
    flag = 6; 
    delay(10); 
    Tablet.clear(); 
   } 

  if(millis()-eventTime>500 && tolerance(data, VOLDOWN) && flag == 6 || tolerance(data, VOLDOWN) && flag == 3) // удержание кнопки от 500 до ? миллисекунд (изменяется здесь millis()-eventTime>500) 
   {  
    Tablet.vol_down(); // действие после удержание кнопки, Уменьшить громкость каждые 0,1 секунды 
    flag = 3; 
    Tablet.clear(); 
    delay(100); 
   } 
    
//********************** AltTab + Play/pause ************************************     

if(between(millis()-eventTime, 10, 499) && tolerance(data, PLAY)) // короткое нажатие кнопки от 10 до 499 миллисекунд (изменяется здесь millis()-eventTime>10 && millis()-eventTime<499) 
   {  
    flag = 1; 
   } 

   if(tolerance(data, NOBUTTON) && flag == 1 && pauseMillis == 0) // действие после короткого нажатия кнопки, Alt+Tab 
   { 
    Tablet.play_pause(); 
    flag = 0; 
    delay(10); 
    Tablet.clear(); 
   } 
//********************** Next и Fast Forward ************************************     
     
  if(between(millis()-eventTime, 10, 499) && tolerance(data, NEXT)) // короткое нажатие кнопки от 10 до 499 миллисекунд (изменяется здесь millis()-eventTime>10 && millis()-eventTime<499) 
   {  
    flag = 2; 
   } 
    
  if(tolerance(data, NOBUTTON) && flag == 2) // действие после короткого нажатия кнопки, Next 
   { 
    Tablet.next(); 
    flag = 0; 
    delay(10); 
    Tablet.clear(); 
   } 

  if(millis()-eventTime>500 && tolerance(data, NEXT) && flag == 2 || tolerance(data, NEXT) && flag == 3) // удержание кнопки от 500 до ? миллисекунд (изменяется здесь millis()-eventTime>500) 
   {  
    Tablet.forward(); // действие после удержание кнопки, Fast Forward 
    flag = 3; 
    Tablet.clear(); 
    delay(100); 
   } 
//********************** Previous и Rewind ************************************     
     
  if(between(millis()-eventTime, 10, 499) && tolerance(data, PREV)) // короткое нажатие кнопки от 10 до 499 миллисекунд (изменяется здесь millis()-eventTime>10 && millis()-eventTime<499) 
   {  
    flag = 4; 
   } 
    
  if(tolerance(data, NOBUTTON) && flag == 4) // действие после короткого нажатия кнопки, Previous 
   { 
    Tablet.previous(); 
    flag = 0; 
    delay(10); 
    Tablet.clear(); 
   } 

  if(millis()-eventTime>500 && tolerance(data, PREV) && flag == 4 || tolerance(data, PREV) && flag == 3) // удержание кнопки от 500 до ? миллисекунд (изменяется здесь millis()-eventTime>500) 
   {  
    Tablet.rewind(); // действие после удержание кнопки, Rewind 
    flag = 3; 
    Tablet.clear(); 
    delay(100); 
   } 
    
  if(tolerance(data, NOBUTTON) && flag == 3 || tolerance(data, NOBUTTON) && flag == 5 || tolerance(data, NOBUTTON) && flag == 6) // действие после отпускания кнопки 
   { 
    flag = 0; 
   }    
}  
