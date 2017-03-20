#include <drawingrobot.h>
#include <Servo.h>

Servo servo;

char command = 'N';
float param = 0.0;

void setup() {
  Serial.begin(9600);
  servo.attach(6);
}

DrawingRobot robot(
    2, 3, 4, 5,
    9,10,11,12,
    66.2, 112.43, 200.0);

/**
 * commands:
 * s : servo
 * s,100 : set the servo to 100 degrees
 * l : left motor
 * l,-100 : left motor goes 100 steps backwards
 * r : right motor
 * r,57 : right motor goes forward 57 steppers
 * d : set wheel diameter
 * d,66.4 : sets the wheel diameter to 66.4 mm
 * b : sets the wheel base in millimeters
 * b,114.4 : sets the wheel base to 114.4 mm
 *
 * The commands without comma and parameter writes the actual value to the console
 *
 */
void readCommand() {
    command = 'N';

    String s = Serial.readStringUntil('\n');
    if (s.length() > 0) {
        command = s.charAt(0);
    }

    param = 0.0;

    if (s.length() > 2) {
        s = s.substring(2);
        param = atof(s.c_str());
    }
}

void control() {
    switch (command) {
    case 'N' :
            Serial.println("Valid commands are s,l,r,d and b.");
            break;
    case 's' :
            Serial.println(servo.read());
            if (param > 0) {
                servo.write(param);
            }
            break;
    case 'l' :
            //the left motor go "opposite" like the right, because they are
            //attached to the robot base flipped
            robot.goMotor(-param, 0);
            break;
    case 'r' :
            robot.goMotor(0, param);
            break;
    case 'd' :
            Serial.println(robot.getWheelDia());
            if (param > 0) {
                robot.setCarParams(param, robot.getWheelBase());
            }
            break;
    case 'b' :
            Serial.println(robot.getWheelBase());
            if (param > 0) {
                robot.setCarParams(robot.getWheelDia(), param);
            }
            break;
    }
}

void loop() {
  if (Serial.available() > 0) {
      readCommand();
      control();
  }
}
