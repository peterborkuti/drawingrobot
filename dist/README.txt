There are two directories in the zip file.
These two directories should be copied to the "libraries" folder of your Arduino IDE installation.

For example on Windows, if you installed Arduino IDE into C:\Program Files(x86)\Arduino,
then find the "libraries" folder below this directory and copy the directories in this zip into
the "libraries" folder.

Usage:
Run Arduino IDE
Open the test file for the robot
File->Examples->drawingrobot->test01
Click on the Verify icon, it should build successfully

Connect the robot to your PC
Go to Tools
Select from Board: "Arduino nano"
Select from Processor: "Atmega 328"
Select the appropriate port (COM1 for example, it heavily depends on you PC)

Upload the test program with the Upload button

Setting Up the servo
check the penup and pendown functions in the test file:

------------------
void penup() {
    servo.write(100);
}

void pendown() {
    servo.write(150);
}
------------------

You probably have to set the numbers 100 and 150 appropriately to your setup (it depends on how you installed the servo motor).
When penup runs, the "arm" of the servo should point to upwards in order to push the pen up.
When pendown runs, the "arm" of the servo should point to vertically or downwards in order to release the pen down.
The servo.write() commands parameters should be between 0 and 180, this is the rotation degree. You may not use the
two limits (180 and 0) but you can choose values in between.

Setting up the motors
the RIGHT motor is on the robot's right, if you are looking at the same direction as the robot. The caster wheel is on the back of the robot.
FORWARD means in the opposite direction of the caster wheel, so the caster wheel is pulled by the robot when it moves forward.

Péter Borkuti
