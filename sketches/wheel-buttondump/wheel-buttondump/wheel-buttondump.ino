int analogPin=3;    //пин для подключения кнопок 
int data; 

void setup() 
{

} 

void loop() 
{ 
  data=analogRead(analogPin); //читаем значение нажатой кнопки 
   
  Serial.print(millis());
  Serial.print(" ");
  Serial.println(data);
    
}  
