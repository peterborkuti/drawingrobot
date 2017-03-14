// MultiStepper.pde
// -*- mode: C++ -*-
// Use MultiStepper class to manage multiple steppers and make them all move to
// the same position at the same time for linear 2d (or 3d) motion.

#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Servo.h>

// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
// LEFT motor pins: 2,3,4,5 => 2,4,3,5
// RIGHT motor pins: 8,9,10,11  //5,6,7,8 => 5,7,6,8; 9,10,11,12 => 9,11,10,12

AccelStepper sr(AccelStepper::FULL4WIRE, 2, 4, 3, 5);
AccelStepper sl(AccelStepper::FULL4WIRE, 9, 11, 10, 12);

/**
 * FULL4WIRE: one circle is 2048 steps
 * HALF4WIRE: one circle is 4096 steps
 */

MultiStepper s;
Servo servo;

float const wheel_dia=66.2; //      # mm (increase = spiral out)
float const wheel_base=112.43; //,    # mm (increase = spiral in)

//FULL4WIRE
float const steps_rev=2048; //,     # 512 for 64x gearbox, 128 for 16x gearbox

//HALF4WIRE
//float const steps_rev=4096;

float const oneStepLength = 2.0 * PI * wheel_dia / 2.0 / steps_rev;

float const quarter_base = wheel_base / 2.0;

float getLength(float degree) {
    float radian = 2.0 * PI * degree / 360.0;

    return radian * quarter_base;
}

int getStepsNeeded(float distance) {
    return (int)(distance / oneStepLength + 0.5);
}

void forward(float);
void backward(float);
void left(float);
void right(float);
void penup();
void pendown();
void goMotor(int lSteps, int rSteps);

void setup() {
  Serial.begin(9600);

  servo.attach(6);
  pendown();

  // Configure each stepper
  sl.setMaxSpeed(200);
  sr.setMaxSpeed(200);

  s.addStepper(sl);
  s.addStepper(sr);

  // Then give them to MultiStepper to manage
}

long pos[2] = {0, 0}; // Array of desired stepper positions

void loop() {
  //goMotor(4096, -4096);
  //forward(100);
  //backward(100);
  pendown();
  for (int i = 0; i < 4; i++) {
      //pendown();
      forward(100);
      //penup();
      left(90);
      //pendown();
  }
  delay(1000);
  /*
  penup();
  forward(50);
  left(90);
  forward(50);
  left(90);
  forward(50);
  left(90);
  forward(50);
  left(90);
  delay(1000);
  */
}

void penup() {
    servo.write(100);
    delay(100);
}

void pendown() {
    servo.write(150);
    delay(100);
}

void goMotor(int lSteps, int rSteps) {
    sl.setCurrentPosition(0);
    sr.setCurrentPosition(0);
    pos[0] = lSteps;
    pos[1] = rSteps;
    s.moveTo(pos);
    s.runSpeedToPosition();
    delay(500);
}


void forward(float distance){
  int steps = getStepsNeeded(distance);
  Serial.println(steps);
  goMotor(-steps, steps);
}


void backward(float distance){
  int steps = getStepsNeeded(distance);
  goMotor(steps, -steps);
}


void right(float degrees){
  float distance = getLength(degrees);
  int steps = getStepsNeeded(distance);
  goMotor(-steps, -steps);
}


void left(float degrees){
    float distance = getLength(degrees);
    int steps = getStepsNeeded(distance);
    goMotor(steps, steps);
}
