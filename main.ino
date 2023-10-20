#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

int i = 0;
void printSpeed(){
    lcd.home();
    lcd.print("Velocidade Atual");
    lcd.setCursor(0, 1);
    lcd.print(giti);
    i++;
}

void spinMotor(){
    //falta o motor
}

int measureTemperature(){
    
}

void setup(){
    lcd.init();
    lcd.setBacklight(HIGH);
}

loop(){
    delay(1000);
}