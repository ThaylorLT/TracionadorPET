#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int i = 0;
void printSpeed(){
    lcd.home();
    lcd.print("Velocidade Atual");
    lcd.setCursor(0, 1);
    lcd.print(i);
    i++;
}

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup(){
    lcd.init();
    lcd.setBacklight(HIGH);
}

loop(){
    printSpeed();
    delay(1000);
}