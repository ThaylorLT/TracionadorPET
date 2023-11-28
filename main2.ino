#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variaveis globais para leitura do termistor//
const int pinTermistor = A0;
const float beta = 3950;
const float resistenciaNominal = 100000;
const float temperaturaNominal = 25 + 273;
const float rx = resistenciaNominal * exp(-beta/temperaturaNominal);
const float vcc = 5;
const resistenciaReferencia = 100000;
//--------------------------------------------//

float calcTemperatura(){
    //Código adaptado de "https://www.makerhero.com/blog/termistor-ntc-arduino/"//
    leitura = analogRead(pinTermistor);
    float v = (vcc*leitura)/1024;
    float r = (vcc*resistenciaReferencia)/v - resistenciaReferencia
    float temperatura = beta / log(r/rx);
    //Fim do código adaptado//
    return temperatura - 273;
}

void mostrarLCD(float temperatura, int velocidadeMotor){
    lcd.home();
    lcd.print("TM:");
    lcd.print(temperatura);
    lcd.print("/200C");
    lcd.print(" ");
    lcd.print("T:");
    lcd.setCursor(0, 1);
    lcd.print("Vel Motor:");
    lcd.print(velocidadeMotor);
    lcd.print("%");
}

void limiteTemperatura(float temperatura, float maxTemperatura){
    float minTemperatura= maxTemperatura - 1;
    if(temperatura > maxTemperatura){
        digitalWrite(12,LOW);
    } else if (temperatura < minTemperatura){
        digitalWrite(12,HIGH);
    } 
}

int lerVelocidade(){
    int velMotor=map(analogRead(A1),0,1023,0,100);
    return pot1
}

int lerTemperatura(){
    int temp=map(analogRead(A2),0,1023,200,250);
    return temp;
}

void setup(){
    lcd.init();
    lcd.backlight(1);
    pinMode(12,OUTPUT);
}

void loop(){


}
