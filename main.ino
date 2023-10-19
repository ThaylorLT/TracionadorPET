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
    
    servo.write(0); // move MG996R's shaft to angle 0°
  delay(1000); // wait for one second
  servo.write(45); // move MG996R's shaft to angle 45°
  delay(1000); // wait for one second 
  servo.write(90); // move MG996R's shaft to angle 90°
  delay(1000); // wait for one second
  servo.write(135); // move MG996R's shaft to angle 135°
  delay(1000); // wait for one second
  servo.write(180); // move MG996R's shaft to angle 180°
  delay(1000); // wait for one second
}


void setup(){
    servo.attach(6);
    lcd.init();
    lcd.setBacklight(HIGH);
}

loop(){
    //printSpeed();
    spinMotor();
    delay(1000);
}