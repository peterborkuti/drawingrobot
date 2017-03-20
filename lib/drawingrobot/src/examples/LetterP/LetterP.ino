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
  delay(1000);
  robot.forward(150);
  robot.right(90);
  robot.rightarc(180, 30);
  penup();
}

void loop() {
}
