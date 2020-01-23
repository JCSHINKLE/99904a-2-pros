#include "okapi/api.hpp"

extern pros:: Controller weber;

extern okapi::ADIGyro gyro;

extern pros::Motor driveRight;
extern pros::Motor driveLeft;
extern pros::Motor leftLift;
extern pros::Motor rightLift;
extern pros::Motor midLift;
extern pros::Motor rightIntake;
extern pros::Motor leftIntake;
extern pros::Motor tilter;

extern double gyroCurrent;
extern double gyroLast;
extern float gyroOutput;
extern float diff;
extern double gyroOutputReal;

extern int pinValues[4];

extern int getAutonNumber();
extern void flipOut();

//pin declaration
extern pros::ADIDigitalIn pin1;
extern pros::ADIDigitalIn pin2;
extern pros::ADIDigitalIn pin3;
extern pros::ADIDigitalIn pin4;
