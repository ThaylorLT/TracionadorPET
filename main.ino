#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

//Variaveis globais
//---- termistor ----//
const int pinoTermistor = A0;
const double r0 = 100000.0;
const double t0 = 25.0 + 273.0;
const double b = 3950.0;
const double rx = r0 * exp(-b/t0);
//---- circuito ----//
const double vcc = 5.0;
const double Rref = 20000.0;

int i = 0;
void printSpeed(){
    lcd.home();
    lcd.print("Velocidade Atual");
    lcd.setCursor(0, 1);
    lcd.print(i);
    i++;
}

void spinMotor(){
    //falta o motor
}

int measureTemperature(){
    int average = 0;
    for (int i=0; i<5; i++){
        average += analogRead(pinoTermistor);
        delay(10);
    }
    double vout = (vcc*average)/1024.0 * 5.0;
    double rt = (vcc*Rref)/vout - Rref;
    double temperature= b/ log(rt/rx);
}

void setup(){
    lcd.init();
    lcd.setBacklight(HIGH);
}

loop(){
    delay(1000);
}