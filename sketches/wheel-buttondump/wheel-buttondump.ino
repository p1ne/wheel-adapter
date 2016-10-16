int analogPin=3;    //пин для подключения кнопок 
int data; 

void setup() 
{

} 

void loop() 
{ 
  data=analogRead(analogPin); //читаем значение нажатой кнопки 
   
  Serial.println(data);
    
}  
