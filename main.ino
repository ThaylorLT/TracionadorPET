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
    lcd.print(maxTemperatura);
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

int lerVelocidade(bool estado){
  int velMotor=map(analogRead(A1),0,1023,0,100);
  return velMotor;
}

int lerTemperatura(){
    float maxTemperatura=map(analogRead(A2),0,1023,0,250);
    return maxTemperatura;
}

void setup(){
    lcd.init();
    lcd.backlight();
    pinMode(pinRele,OUTPUT);
    pinMode(botaoLiga, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop(){
  bool estado = digitalRead(botaoLiga);
  while (!estado){
      float temperatura = calcTemperatura();
      int velocidadeMotor = lerVelocidade(estado);
      float maxTemperatura = lerTemperatura();
      mostrarLCD(temperatura, velocidadeMotor, maxTemperatura);
      delay(200);
    }
    float temperatura = calcTemperatura();
    int velocidadeMotor = lerVelocidade(estado);
    float maxTemperatura = lerTemperatura();
    limiteTemperatura(temperatura, maxTemperatura);
    mostrarLCD(temperatura, velocidadeMotor, maxTemperatura);
    delay(200);
}