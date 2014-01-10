/**
 * @file 		DFRduino.cpp
 * @author		Will Price
 * @date		09/01/2014
 * @see			DFRduino.h, for method documentation
 *
 *
 */

#include "Arduino.h"
#include "DFRduino.h"

#include <Servo.h>

DFRduino::DFRduino(void) {
        initMotors();
        initSensors();
}

void DFRduino::initMotors(void) {
        pinMode(LEFT_MOTOR_DIRECTION_CONTROL, OUTPUT);
        pinMode(LEFT_MOTOR_SPEED_CONTROL, OUTPUT);
        pinMode(RIGHT_MOTOR_DIRECTION_CONTROL, OUTPUT);
        pinMode(RIGHT_MOTOR_SPEED_CONTROL, OUTPUT);
}

void DFRduino::initSensors(void) {
        pinMode(DISTANCE_SENSOR_INPUT_PIN, INPUT);
}

void DFRduino::setDirection(char direction) {
        switch(direction) {
                case ('f'):
                        setMotors(100, 100);
                        break;
                case ('b'):
                        setMotors(-100, -100);
                        break;
                case ('r'):
                        setMotors(100, -100);
                        break;
                case ('l'):
                        setMotors(-100, 100);
                        break;
        }
}

int DFRduino::scaleSpeedToRangeOfInt(int speed) {
        return map(speed, 0, 100, 0, 255);
}

void DFRduino::setMotors(int left, int right) {
        right = scaleSpeedToRangeOfInt(right);
        left  = scaleSpeedToRangeOfInt(left);

        if (left < 0) {
                digitalWrite(LEFT_MOTOR_DIRECTION_CONTROL, HIGH);
                analogWrite(LEFT_MOTOR_SPEED_CONTROL, -left);
        } else {
                digitalWrite(LEFT_MOTOR_DIRECTION_CONTROL, LOW);
                analogWrite(LEFT_MOTOR_SPEED_CONTROL, left);
        }

        if (right < 0) {
                digitalWrite(RIGHT_MOTOR_DIRECTION_CONTROL, HIGH);
                analogWrite(RIGHT_MOTOR_SPEED_CONTROL, -right);
        } else {
                digitalWrite(RIGHT_MOTOR_DIRECTION_CONTROL, LOW);
                analogWrite(RIGHT_MOTOR_SPEED_CONTROL, right);
        }
}

int DFRduino::readDistanceInCentimeters() {
       /** Max distance detectable is 150cm 
        *       
        *  Min distance detectable is 20cm
        * */
       int distance = 1;
       for (int i = 0; i < 10; i++) {
               distance += 4800/(analogRead(DISTANCE_SENSOR_INPUT_PIN) - 20);
               delayMicroseconds(2);
       }
       distance /= 10;

       if (distance > 150 || distance < 0)
               return 150;
       return distance;
}

void DFRduino::setHorizontalHeadPosition(int angle) {
		// Refactoring the attach out doesn't work
        horizontalServo.attach(HORIZONTAL_SERVO_PIN);
        horizontalServo.write(angle);
}

void DFRduino::setVerticalHeadPosition(int angle) {
        if (angle >= 165) {
                error("Too high an angle");
                return;
        }
        // Refactoring the attach out doesn't work
        verticalServo.attach(VERTICAL_SERVO_PIN);
        verticalServo.write(angle);
}

void DFRduino::error(char *error_message) {
        Serial.print("ERROR: ");
        Serial.print(error_message);
        Serial.print('\n');
}

