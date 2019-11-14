#include "main.h"
#ifndef global
#include "global.h"
#endif

void gyroadj(void* param)
{
 	gyroCurrent = gyro.get();
 	gyroLast = gyro.get();
  while (true)
	{
		gyroCurrent = gyro.get();
 		diff = gyroCurrent - gyroLast;
 	 	gyroLast = gyroCurrent;
    if (abs(diff) < 100)
		{
			gyroOutputReal = gyroOutputReal + diff + 0.0002;
      gyroOutput = std::nearbyint(gyroOutputReal);
    }
  pros::delay(1);
 	}
 }

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	okapi::ADIGyro gyro(GYRO_PORT, 1);
	pros::delay(1400);
  pros::lcd::initialize();
  pros::Task task_gyroadj(gyroadj);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
