#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Servo.h>
#include <drawingrobot.h>

#include <Arduino.h>

DrawingRobot::DrawingRobot(
    const uint8_t pinm11, const uint8_t pinm12, const uint8_t pinm13, const uint8_t pinm14,
    const uint8_t pinm21, const uint8_t pinm22, const uint8_t pinm23, const uint8_t pinm24,
    const uint8_t pinservo, const float _wheel_dia, const float _wheel_base, const float maxSpeed):
        sr(AccelStepper::FULL4WIRE, pinm11, pinm13, pinm12, pinm14),
        sl(AccelStepper::FULL4WIRE, pinm21, pinm23, pinm22, pinm24) {

    servo.attach(pinservo);

    penup();
    pendown();

    // Configure each stepper
    sl.setMaxSpeed(maxSpeed);
    sr.setMaxSpeed(maxSpeed);

    s.addStepper(sl);
    s.addStepper(sr);

    wheel_base = _wheel_base;
    wheel_dia = _wheel_dia;

    //FULL4WIRE
    steps_rev=2048; //,     # 512 for 64x gearbox, 128 for 16x gearbox

    //HALF4WIRE
    //float const steps_rev=4096;

    oneStepLength = 2.0 * PI * wheel_dia / 2.0 / steps_rev;

    quarter_base = wheel_base / 2.0;
}

float DrawingRobot::getLength(float degree) {
    float radian = 2.0 * PI * degree / 360.0;

    return radian * quarter_base;
}

int DrawingRobot::getStepsNeeded(float distance) {
    return (int)(distance / oneStepLength + 0.5);
}

void DrawingRobot::penup() {
    servo.write(100);
    delay(100);
}

void DrawingRobot::pendown() {
    servo.write(150);
    delay(100);
}

void DrawingRobot::goMotor(int lSteps, int rSteps) {
    sl.setCurrentPosition(0);
    sr.setCurrentPosition(0);
    pos[0] = lSteps;
    pos[1] = rSteps;
    s.moveTo(pos);
    s.runSpeedToPosition();
    delay(500);
}

void DrawingRobot::forward(const float distance){
  int steps = getStepsNeeded(distance);
  Serial.println(steps);
  goMotor(-steps, steps);
}

void DrawingRobot::backward(const float distance){
  int steps = getStepsNeeded(distance);
  goMotor(steps, -steps);
}

void DrawingRobot::right(const float degrees){
  float distance = getLength(degrees);
  int steps = getStepsNeeded(distance);
  goMotor(-steps, -steps);
}

void DrawingRobot::left(const float degrees){
    float distance = getLength(degrees);
    int steps = getStepsNeeded(distance);
    goMotor(steps, steps);
}
