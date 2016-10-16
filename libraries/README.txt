Taken from here: http://pccar.ru/showpost.php?p=366382&postcount=669

Для последних версий Arduino IDE начиная с версии 1.6.8 и выше написал библиотеку для управления медиа функциями планшета. Делюсь своим трудом с вами! Библиотека работает на Arduino: Micro, Leonardo и Due 

Установка:
1) Скачать и установить последнюю версию ArduinoIDE: https://www.arduino.cc/en/Main/Software

2) Скачать библиотеку Tablet: ссылка под описанием

3) Распаковать архив

4) Положить распакованную папку Tablet в папку libraried в директории Arduino:

5) Должно получиться так:
5.1) для 64 битных ОС C:\Program Files (x86)\Arduino\libraries\Tablet
5.2)для 32 битных ОС C:\Program Files\Arduino\libraries\Tablet

6) При написании скетчей не забудьте импортировать библиотеку Tablet (т.е. в начале скетча написать #include <Tablet.h>)

Список команд.

Tablet.clear(); //очистить команду
Tablet.vol_up(); //громкость больше
Tablet.vol_down(); //громкость меньше
Tablet.mute(); //убрать звук
Tablet.play(); //плей
Tablet.pause(); //пауза
Tablet.play_pause(); //плай пауза
Tablet.stop(); //стоп
Tablet.next(); //следующий
Tablet.previous(); //предыдущая
Tablet.forward(); //быстрая перемотка
Tablet.rewind(); //перемотка назад 
Tablet.power(); //уйти в сон
Tablet.home(); //домой
Tablet.search(); //поиск  


Пример программы:

#include <Tablet.h>

void setup(){

}
void loop(){
//например

Tablet.next();
Tablet.clear();
delay(5000);

//программа каждые 5 сек будет переключать трек.

}  
