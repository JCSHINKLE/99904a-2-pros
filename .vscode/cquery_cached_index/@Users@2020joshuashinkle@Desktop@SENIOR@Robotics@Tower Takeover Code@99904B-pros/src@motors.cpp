#include "main.h"
#ifndef global
#include "global.h"
#endif
#include "okapi/api.hpp"

pros::Controller weber(pros::E_CONTROLLER_MASTER);

pros::Motor driveRightFront(DRIVE_RIGHT_FRONT_PORT, pros::E_MOTOR_GEARSET_18, false);
pros::Motor driveRightBack(DRIVE_RIGHT_BACK_PORT, pros::E_MOTOR_GEARSET_18, false);
pros::Motor driveLeftFront(DRIVE_LEFT_FRONT_PORT, pros::E_MOTOR_GEARSET_18, true);
pros::Motor driveLeftBack(DRIVE_LEFT_BACK_PORT, pros::E_MOTOR_GEARSET_18, true);
