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
const int pinRele=11;

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
    lcd.print((int)velocidadeMotor);
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

float lerPotenciometro(bool estado){
  if(estado){
    float velMotor=map(analogRead(A1),0,1023,0,100);
    return velMotor;
  } else {
    float maxTemperatura=map(analogRead(A2),0,1023,0,250);
    return maxTemperatura;
  }
  
}

int lerTemperatura(){
    float maxTemperatura=map(analogRead(A2),0,1023,0,250);
    return maxTemperatura;
}

void acionaMotor(float velocidadeMotor){

}

void desligaMotor(){

}

void setup(){
    lcd.init();
    lcd.backlight();
    pinMode(pinRele,OUTPUT);
    pinMode(botaoLiga, INPUT_PULLUP);

}

void loop(){
  bool estado = digitalRead(botaoLiga);
  if (!estado){
      float temperatura = calcTemperatura();
      float velocidadeMotor = lerPotenciometro(estado);
      if(motorLigado){
        desligaMotor();
      }
      mostrarLCD(temperatura, velocidadeMotor, maxTemperatura);
      delay(200);
    } else {
      float temperatura = calcTemperatura();
      int velocidadeMotor = lerPotenciometro(estado);
      float maxTemperatura = lerTemperatura();
      if(!motorLigado){
        acionaMotor(velocidadeMotor);
      }
      limiteTemperatura(temperatura, maxTemperatura);
      mostrarLCD(temperatura, velocidadeMotor, maxTemperatura);
      delay(200);
    }
    
}
