/**
 * DrawingRobot Control Class
 *
 * Peter Borkuti
 */

#ifndef DRAWINGROBOT_H
#define DRAWINGROBOT_H

#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

/**
 * DrawingRobot control class
 *
 */
class DrawingRobot {
private:
    AccelStepper sr;
    AccelStepper sl;
    MultiStepper s;

    long pos[2];
    float wheel_dia; //      # mm (increase = spiral out)
    float wheel_base; //    # mm (increase = spiral in)

    //FULL4WIRE
    float steps_rev; //     # 512 for 64x gearbox, 128 for 16x gearbox

    //HALF4WIRE
    //float const steps_rev=4096;

    float oneStepLength;

    float quarter_base;
    float getLength(float degree);
    int getStepsNeeded(float distance);

public:
    /**
     * pinm11..pinm14 : pins for the right motor
     * pinm21..pinm24 : pins for the left motor
     * wheel_dia: wheel diameter in millimeters
     * wheel_base: distance between the two wheels in millimeters
     * maxSpeed: maximum speed.
     */
    DrawingRobot(
        const uint8_t pinm11, const uint8_t pinm12, const uint8_t pinm13, const uint8_t pinm14,
        const uint8_t pinm21, const uint8_t pinm22, const uint8_t pinm23, const uint8_t pinm24,
        const float _wheel_dia, const float _wheel_base, const float maxSpeed);

    /**
    * make lsteps with left motor and rsteps with the right motor.
    * positiv steps mean forward, negative steps mean backward
    * It is only for testing, this is a "low-level" function.
    * @param lSteps steps for the left motor
    * @param rSteps steps for the right motor
    */
    void goMotor(int lSteps, int rSteps);
    /**
     * turns left in place with a given degrees
     * @param degrees degrees of turning, positive number
     */
    void left(const float degrees);
    /**
     * turns right in place with a given degrees
     * @param degrees degrees of turning, positive number
     */
    void right(const float degrees);
    /**
     * both motor goes forward with a given millimeter
     * @param mm millimeters to move
     */
    void forward(const float mm);
    /**
     * both motor goes backward with a given millimeter
     * @param mm millimeters to move
     */
    void backward(const float mm);
};

#endif
