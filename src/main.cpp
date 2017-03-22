// MultiStepper.pde
// -*- mode: C++ -*-
// Use MultiStepper class to manage multiple steppers and make them all move to
// the same position at the same time for linear 2d (or 3d) motion.

#include <drawingrobot.h>
#include <Servo.h>
#include <TM1638.h>

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
  module.setDisplayToString("Hello");
}


DrawingRobot robot(
    2, 3, 4, 5,
    9,10,11,12,
    66.2, 112.43, 200.0);

void penup() {
    servo.write(100);
}

void pendown() {
    servo.write(150);
}

byte pos = 0;
void loop() {
  byte keys = module.getButtons();
  module.setLEDs(keys);

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
