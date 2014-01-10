/**
 * @file		DFRduino.h
 * @author		Will Price
 * @date		09/01/2014
 * @see 		DFRduino.cpp for implementation
 *
 * DFRduino is an Arduino class that encapsulates the behaviour of
 * the DFRduino robot, it provides methods to set motor speed or
 * direction and read the distance from it's IR sensor. The ability
 * to move the servo motors is also implemented in the set*HeadPosition
 * methods.
 *
 * \see http://www.dfrobot.com/wiki/index.php/DFRduino_Romeo-All_in_one_Controller_V1.1(SKU:DFR0004),
 * for documentation on the controller
 */

#ifndef DFRduino_h
#define DFRduino_h

#include "Arduino.h"
#include <Servo.h>

#define LEFT_MOTOR_SPEED_CONTROL          5
#define RIGHT_MOTOR_SPEED_CONTROL         6
#define LEFT_MOTOR_DIRECTION_CONTROL      4
#define RIGHT_MOTOR_DIRECTION_CONTROL     7

#define DISTANCE_SENSOR_INPUT_PIN         A5

#define HORIZONTAL_SERVO_PIN              13
#define VERTICAL_SERVO_PIN                12
class DFRduino {
public:
	/**
	 * Set up the sensors and motors.
	 */
	DFRduino();

	/**
	 * Sets the direction of the robot at 100% speed:
	 * \param direction takes ones of the following:
	 * 'f': Forward,
	 * 'b': Backward,
	 * 'r': Right,
	 * 'l': Left
	 */
	void setDirection(char direction);

	/** Set the motors as a percentage of their max speed.
	 * Anything lower than 30 doesn't do anything.
	 * \param left Percentage that the left motor is on (-100,100)
	 * \param right Percentage that the right motor is on (-100,100)
	 */
	void setMotors(int left, int right);

	/** Sets the horizontal position of the head.
	 * \param angle: (0,180) degrees
	 *
	 * Positions: (from the robot's perspective)
	 * 90: Central
	 * 0: Left
	 * 180: Right
	 */
	void setHorizontalHeadPosition(int angle);

	/** Sets the vertical position of the head.
	 * \param angle: (0,180) degrees
	 *
	 * Positions:
	 * 160: As downards as it can go
	 * 130: Central
	 * 0: Pointing upwards and backwards
	 *
	 */
	void setVerticalHeadPosition(int angle);

	/** Reads the input from the IR sensor and calculates
	 * the distance to the object the IR light bounces off
	 * \returns Distance in cm (int).
	 */
	int readDistanceInCentimeters();

private:
	/** Sets the motor pins as outputs.
	 */
	void initMotors();

	/** Sets the IR pin as an input.
	 *
	 */
	void initSensors();
        
	/** Sets up a serial port at 9600 baud and prints out the error
	 * message over the serial port prefixing it with "ERROR: "
	 */
	void error(char *error_message);

	/** We have to scale the percentage to between 0 and 2^{sizeof(int)}
	 * in setMotors. This method performs that function
	 */
	int scaleSpeedToRangeOfInt(int speed);
	Servo horizontalServo;
	Servo verticalServo;
};

#endif
