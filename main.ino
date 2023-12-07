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
const float resistenciaReferencia = 100000;
//--------------------------------------------//
const int nSamples=128;

float calcTemperatura(){
  //Código adaptado de "https://www.makerhero.com/blog/termistor-ntc-arduino/"//  
  unsigned long long int soma = 0;
  for (int i = 0; i < nSamples; i++) {
    soma += analogRead(pinTermistor);
  }
  double v = (vcc*soma)/(nSamples*1024.0);
  double r = (vcc*resistenciaReferencia)/v - resistenciaReferencia;
  double temperatura = beta / log(r/rx);
  //Fim do código adaptado//
  return (temperatura - 273.0);
}

void mostrarLCD(float temperatura, int velocidadeMotor){
    lcd.home();
    lcd.print("TMP:");
    lcd.print((int)temperatura);
    lcd.print("/250C");
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

int lerVelocidade(bool estado){
  if(estado){
    int velMotor=map(analogRead(A1),0,1023,0,100);
    return velMotor;
  } else {
    int temp=map(analogRead(A2),0,1023,200,250);
    return temp;
  }
}

int lerTemperatura(){
    
}

void setup(){
    lcd.init();
    lcd.backlight();
    pinMode(12,OUTPUT);
    Serial.begin(9600);
}

void loop(){
  float temperatura= calcTemperatura();
  mostrarLCD(temperatura,0);
  delay(1000);

}
