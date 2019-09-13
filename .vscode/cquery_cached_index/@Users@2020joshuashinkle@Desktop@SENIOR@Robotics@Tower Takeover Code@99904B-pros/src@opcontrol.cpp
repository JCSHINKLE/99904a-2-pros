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
		if (weber.get_analog(ANALOG_RIGHT_X) > 2)
		{
			turn = turn + 11;
		}
		else if (weber.get_analog(ANALOG_RIGHT_X) < -1)
		{
			turn = turn - 11;
		}
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
		pros::delay(20);
	}
}
