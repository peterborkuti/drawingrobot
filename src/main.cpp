// MultiStepper.pde
// -*- mode: C++ -*-
// Use MultiStepper class to manage multiple steppers and make them all move to
// the same position at the same time for linear 2d (or 3d) motion.

#include <Arduino.h>
#include <drawingrobot.h>

// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
// LEFT motor pins: 2,3,4,5 => 2,4,3,5
// RIGHT motor pins: 8,9,10,11  //5,6,7,8 => 5,7,6,8; 9,10,11,12 => 9,11,10,12

DrawingRobot robot(2,3,4,5,9,10,11,12,6,66.2, 112.43, 200);
//AccelStepper sr(AccelStepper::FULL4WIRE, 2, 4, 3, 5);
//AccelStepper sl(AccelStepper::FULL4WIRE, 9, 11, 10, 12);


void setup() {
  Serial.begin(9600);
}

void loop() {
  robot.pendown();
  for (int i = 0; i < 4; i++) {
      robot.forward(100);
      robot.right(90);
  }
  delay(1000);
}
