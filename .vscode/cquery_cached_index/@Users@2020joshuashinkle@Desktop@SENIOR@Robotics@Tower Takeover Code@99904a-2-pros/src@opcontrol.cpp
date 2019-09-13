#include "main.h"
#ifndef global
#include "global.h"
#endif

void opcontrol()
{
	bool broke = false;
	while (true)
	{
		int turn = weber.get_analog(ANALOG_LEFT_X);
		int power = weber.get_analog(ANALOG_LEFT_Y);
		int left = power + turn;
		int right = power - turn;

		if (abs(turn) + abs(power) < 1 && !broke)
		{
			driveRightFront.move(0);
			driveRightBack.move(0);
			driveLeftFront.move(0);
			driveLeftBack.move(0);
			driveRightFront.move_velocity(0);
			driveRightBack.move_velocity(0);
			driveLeftFront.move_velocity(0);
			driveLeftBack.move_velocity(0);
			driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			broke = true;
		}
		else
		{
			driveRightFront.move(right);
			driveRightBack.move(right);
			driveLeftFront.move(left);
			driveLeftBack.move(left);
			broke = false;
		}
		switch(getAutonNumber())
		{
		  case 0:
		    pros::lcd::print(0, "Auton: RED FRONT PARK");
				break;
		  case 1:
		    pros::lcd::print(0, "Auton: RED BACK MID PARK");
				break;
		  case 2:
		    pros::lcd::print(0, "Auton: BLUE FRONT PARK");
				break;
		  case 3:
		    pros::lcd::print(0, "Auton: BLUE BACK MID PARK");
				break;
		  case 4:
		    pros::lcd::print(0, "Auton: RED FRONT NOPARK");
				break;
			case 5:
				pros::lcd::print(0, "Auton: BLUE FRONT NOPARK");
				break;
			case 6:
				pros::lcd::print(0, "Auton: PROG SKILLS 1");
				break;
			case 7:
				pros::lcd::print(0, "Test");
				break;
		}
		pros::lcd::print(2, "Gyro %f", gyroOutput );
		pros::lcd::print(3, "Gyroadj %f", gyroOutput / 1.061 );
		pros::lcd::print(4, "Gyroraw %f", gyro.get() );
		pros::delay(20);
	}
}
