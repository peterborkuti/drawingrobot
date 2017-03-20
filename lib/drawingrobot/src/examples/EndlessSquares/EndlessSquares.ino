#include <drawingrobot.h>
#include <Servo.h>

Servo servo;

DrawingRobot robot(
    2, 3, 4, 5,
    9,10,11,12,
    66.22, 133.0, 200.0);

void pendown() {
    servo.write(100);
}

void penup() {
    servo.write(150);
}

void setup() {
  Serial.begin(9600);
  servo.attach(6);

  pendown();
}

void loop() {
    robot.forward(50);
    robot.left(90);
}
