#include "main.h"
#ifndef global
#include "global.h"
#endif
#include "okapi/api.hpp"

pros::Controller weber(pros::E_CONTROLLER_MASTER);

okapi::ADIGyro gyro(GYRO_PORT);

pros::Motor driveRight(DRIVE_RIGHT_PORT, pros::E_MOTOR_GEARSET_18, true);
pros::Motor driveLeft(DRIVE_LEFT_PORT, pros::E_MOTOR_GEARSET_18, false);

pros::Motor leftLift(LEFT_LIFT_PORT, pros::E_MOTOR_GEARSET_36, true);
pros::Motor rightLift(RIGHT_LIFT_PORT, pros::E_MOTOR_GEARSET_36, false);

pros::Motor tilter(TILTER_PORT, pros::E_MOTOR_GEARSET_36, true);

pros::Motor rightIntake(RIGHT_INTAKE_PORT, pros::E_MOTOR_GEARSET_36, false);
pros::Motor leftIntake(LEFT_INTAKE_PORT, pros::E_MOTOR_GEARSET_36, true);


double gyroCurrent = 0;
double gyroLast = 0;
double difference;
float gyroOutput = 0;
float diff = 0;
double gyroOutputReal = 0;

int pinValues[4] = {0, 0, 0, 0};

int getAutonNumber()
{
  pinValues[0] = pin1.get_value();
  pinValues[1] = pin2.get_value();
  pinValues[2] = pin3.get_value();
  pinValues[3] = pin4.get_value();

  int value = pinValues[0] + (pinValues[1] * 2) + (pinValues[2] * 4) + (pinValues[3] * 8);

  return value;
}

//pin declaration
pros::ADIDigitalIn pin1(1);
pros::ADIDigitalIn pin2(2);
pros::ADIDigitalIn pin3(3);
pros::ADIDigitalIn pin4(4);
