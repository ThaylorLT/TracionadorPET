#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo motor;
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
const int pinRele=9;
const int pinLigar=7;
const int pinConfig=6;
const int pinMotor=5;
int velocidadeMotor=0;
float maxTemperatura=0;

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

void mostrarLCD(float temperatura, int velocidadeMotor, float maxTemperatura){
    lcd.home();
    lcd.print("TMP:");
    lcd.print((int)temperatura);
    lcd.print("/");
    lcd.print((int)maxTemperatura);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Vel Motor:");
    lcd.print(velocidadeMotor);
    lcd.print("%");
}

void limiteTemperatura(float temperatura, float maxTemperatura){
    float minTemperatura= maxTemperatura - 1;
    if(temperatura > maxTemperatura){
        digitalWrite(pinRele,LOW);
    } else if (temperatura < minTemperatura){
        digitalWrite(pinRele,HIGH);
    } 
}

float lerMotor(){
    float velMotor=analogRead(A1);
    return velMotor;
}

int lerTemperatura(){
    float maxTemperatura=map(analogRead(A1),0,1023,0,210);
    return maxTemperatura;
}

void acionaMotor(float velocidadeMotor){
  motor.write(velocidadeMotor);
}

void desligaMotor(){
  motor.write(90);

}

void setup(){
    lcd.init();
    lcd.backlight();
    motor.attach(pinMotor);
    pinMode(pinRele,OUTPUT);
    pinMode(pinLigar, INPUT);
    pinMode(pinConfig, INPUT);

}

void loop(){
    bool estadoConfig=digitalRead(pinConfig);
    bool estadoLigar=digitalRead(pinLigar);
    float temperatura=calcTemperatura();
    desligaMotor();
    if(!estadoLigar){
      digitalWrite(pinRele,LOW);
      if(estadoConfig){
        velocidadeMotor=lerMotor();
      } else {
        maxTemperatura=lerTemperatura();
      }
      mostrarLCD(temperatura, velocidadeMotor, maxTemperatura);
    } else {
      limiteTemperatura(temperatura, maxTemperatura);
      acionaMotor(velocidadeMotor);
      mostrarLCD(temperatura, velocidadeMotor, maxTemperatura);
    }
   lcd.home();
}
