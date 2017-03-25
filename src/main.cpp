// MultiStepper.pde
// -*- mode: C++ -*-
// Use MultiStepper class to manage multiple steppers and make them all move to
// the same position at the same time for linear 2d (or 3d) motion.

#include <drawingrobot.h>
#include <Servo.h>
#include <TM1638.h>
#include <stdio.h>

// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
// LEFT motor pins: 2,3,4,5 => 2,4,3,5
// RIGHT motor pins: 8,9,10,11  //5,6,7,8 => 5,7,6,8; 9,10,11,12 => 9,11,10,12

//AccelStepper sr(AccelStepper::FULL4WIRE, 2, 4, 3, 5);
//AccelStepper sl(AccelStepper::FULL4WIRE, 9, 11, 10, 12);

Servo servo;
TM1638 module(8,7,13); //data(dont use pin13 on nano), clock, strobe

void penup();

void setup() {
  Serial.begin(9600);
  servo.attach(6);
  penup();
  module.setupDisplay(true, 0);
  module.setDisplayToString("Hello");
}

double wheelDiameter = 66.2;
double wheelBase = 132.5;
float speed = 200;


DrawingRobot robot(
    2, 3, 4, 5,
    9,10,11,12,
    wheelDiameter, wheelBase, speed);

void penup() {
    servo.write(100);
}

void pendown() {
    servo.write(150);
}


/**
 * Menu:
 * S1: Menu
 * S2: "enter"
 * S3: +/-
 *
 * S4-S8: increase/decrease (according to S2) the given digit
 */

byte getKey() {
    byte keys = 0;
    while (keys == 0) {keys = module.getButtons();};
    while (module.getButtons() != 0);
    delay(100);
    module.setLEDs(keys);
    return keys;
}

char menuChars[] = {'D', 'B', 'E'};
byte menuState = 0;
int sign = 1;

void refreshDisplay() {
    module.setupDisplay(true, 0);
    module.clearDisplay();
    char menuChar = menuChars[menuState];
    char signChar = (sign == 1) ? '+' : '-';
    robot.setCarParams(wheelDiameter, wheelBase);
    double number = (menuState == 0) ? wheelDiameter : wheelBase;
    char buffer [20];
    sprintf(buffer, "%c%c  %04d", menuChar, signChar, (int)(number * 10.0d));
    Serial.println(buffer);
    module.setDisplayToString(buffer, 2); //2: decimal point
}

void draw() {
    robot.rightarc(360, 50);
};



void menu() {
    byte key = getKey();
    switch (key) {
    case 1:
        menuState++;
        if (menuState > 2) menuState = 0;
        break;
    case 4:
        sign = -sign; // -1, +1
        break;
    case 2:
        if (menuState == 2) {
            module.clearDisplay();
            module.setDisplayToString("dRA");
            draw();
        }
        break;
    case 128:
        if (menuState == 0) {
            wheelDiameter += sign/10.0;
        }
        if (menuState == 1) {
            wheelBase += sign/10.0;
        };
        break;
    case 64:
        if (menuState == 0) {
            wheelDiameter += sign;
        }
        if (menuState == 1) {
            wheelBase += sign;
        };
        break;
    case 32:
        if (menuState == 0) {
            wheelDiameter += 10.0*sign;
        }
        if (menuState == 1) {
            wheelBase += 10.0*sign;
        };
        break;

    }
    refreshDisplay();
}


void loop() {
    menu();
    Serial.print(millis());
    Serial.print("state:");
    Serial.println(menuState);
  //byte keys = module.getButtons();
  //module.setLEDs(((keys & 0xF0) << 8) | (keys & 0xF));
/*
  Serial.println("1");
  robot.left(90);
  delay(1000);
  penup();
  delay(1000);
  pendown();

  Serial.println("2");
  */
}
