/**
 * Put a pen into the robot and place it on a paper.
 * Robot will go forward 100 mm.
 *
 * Measure the line.
 *
 * If it is more than 100 mm, increase the wheel diameter.
 * If it is less than 100 mm, decrease the wheel diameter
 */

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

  robot.pendown();
  delay(1000);
  robot.forward(100);
  robot.penup();
}

void loop() {
}
