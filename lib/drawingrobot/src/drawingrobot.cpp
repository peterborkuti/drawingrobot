#include "drawingrobot.h"

DrawingRobot::DrawingRobot(
    const uint8_t pinm11, const uint8_t pinm12, const uint8_t pinm13, const uint8_t pinm14,
    const uint8_t pinm21, const uint8_t pinm22, const uint8_t pinm23, const uint8_t pinm24,
    const float _wheel_dia, const float _wheel_base, const float maxSpeed):
        sr(AccelStepper::FULL4WIRE, pinm11, pinm13, pinm12, pinm14),
        sl(AccelStepper::FULL4WIRE, pinm21, pinm23, pinm22, pinm24),
        s()
         {
    pos[0] = 0;
    pos[1] = 0;

    // Configure each stepper
    sl.setMaxSpeed(maxSpeed);
    sr.setMaxSpeed(maxSpeed);
    //Serial.println("D");

    s.addStepper(sl);
    s.addStepper(sr);
    //Serial.println("E");

    //FULL4WIRE
    steps_rev = 2048; //,     # 512 for 64x gearbox, 128 for 16x gearbox

    //HALF4WIRE
    //float const steps_rev=4096;

    setCarParams(_wheel_dia, _wheel_base);
}

float DrawingRobot::degreesToRadians(const float degrees) const {
    return degrees * PI / 180.0;
}

float DrawingRobot::getArcLength(const float degrees, const float radius) const {
    return radius * degreesToRadians(degrees);
}

int DrawingRobot::getSteps(const float distance, const float stepLength) const {
    return (int)(distance / stepLength + 0.5);
}

void DrawingRobot::goMotor(const int lSteps, const int rSteps) {
    sl.setCurrentPosition(0);
    sr.setCurrentPosition(0);
    pos[0] = lSteps;
    pos[1] = rSteps;
    s.moveTo(pos);
    s.runSpeedToPosition();
    delay(500);
}

void DrawingRobot::forward(const float distance){
  int steps = getSteps(distance, oneStepLength);
  Serial.println(steps);
  goMotor(-steps, steps);
}

void DrawingRobot::backward(const float distance){
  int steps = getSteps(distance, oneStepLength);
  goMotor(steps, -steps);
}

void DrawingRobot::right(const float degrees){
  float distance = getArcLength(degrees, half_base);
  int steps = getSteps(distance, oneStepLength);
  goMotor(-steps, -steps);
}

void DrawingRobot::left(const float degrees){
    float distance = getArcLength(degrees, half_base);
    int steps = getSteps(distance, oneStepLength);
    goMotor(steps, steps);
}

void DrawingRobot::rightarc(const float degrees, const float radius) {
    float outerArcLength = getArcLength(degrees, radius + half_base);
    float innerArcLength = getArcLength(degrees, radius - half_base);

    int lsteps = getSteps(outerArcLength, oneStepLength);
    int rsteps = getSteps(innerArcLength, oneStepLength);

    //both motors go forward
    goMotor(-lsteps, rsteps);
}

void DrawingRobot::leftarc(const float degrees, const float radius) {
    float outerArcLength = getArcLength(degrees, radius + half_base);
    float innerArcLength = getArcLength(degrees, radius - half_base);

    int rsteps = getSteps(outerArcLength, oneStepLength);
    int lsteps = getSteps(innerArcLength, oneStepLength);

    //both motors go forward
    goMotor(-lsteps, rsteps);
}

float DrawingRobot::getWheelDia() const {
    return wheel_dia;
}

float DrawingRobot::getWheelBase() const {
    return wheel_base;
}

void DrawingRobot::setCarParams(const float _wheel_dia, const float _wheel_base) {
    wheel_dia = _wheel_dia;
    wheel_base = _wheel_base;

    oneStepLength = PI * wheel_dia / steps_rev;

    half_base = wheel_base / 2.0;
}
