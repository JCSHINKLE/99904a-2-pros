#include "main.h"
#ifndef global
#include "global.h"
#endif

void opcontrol()
{
	// drive control
	bool broke = false;
	driveRightFront.set_voltage_limit(12000);
  driveRightBack.set_voltage_limit(12000);
  driveLeftFront.set_voltage_limit(12000);
  driveLeftBack.set_voltage_limit(12000);
	rightIntake.set_voltage_limit(12000);
  leftIntake.set_voltage_limit(12000);
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
			driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
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

		// cube intake
		if (weber.get_digital(DIGITAL_R1))
		{
			rightIntake.move_velocity(200);
			leftIntake.move_velocity(200);
		}
		else if (weber.get_digital(DIGITAL_R2))
		{
			rightIntake.move_velocity(-200);
			leftIntake.move_velocity(-200);
		}
		else
		{
			rightIntake.move_velocity(0);
			leftIntake.move_velocity(0);

			rightIntake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			leftIntake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}

		// lift
		if(abs(weber.get_analog(ANALOG_RIGHT_Y)) > 1)
		{
			topLift.move(weber.get_analog(ANALOG_RIGHT_Y));
			bottomLift.move(weber.get_analog(ANALOG_RIGHT_Y));
		}
		else
		{
			// cube fast outake
			if (weber.get_digital(DIGITAL_A))
			{
				topLift.move_velocity(100);
				bottomLift.move_velocity(100);
				rightIntake.move_velocity(-150);
				leftIntake.move_velocity(-150);
			}
			else
			{
				topLift.move(0);
				bottomLift.move(0);

				topLift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
				bottomLift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			}
		}

		switch(getAutonNumber())
		{
		  case 0:
		    pros::lcd::print(0, "Auton: ANYWHERE 1");
				break;
		  case 1:
		    pros::lcd::print(0, "Auton: BLUE FRONT 4");
				break;
		  case 2:
		    pros::lcd::print(0, "Auton: RED FRONT 4");
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
				pros::lcd::print(0, "Auton: NONE");
				break;
		}
		pros::lcd::print(1, "Gyro %f", gyroOutput );
		//pros::lcd::print(2, "Gyroadj %f", gyroOutput / 1.061 );
		//pros::lcd::print(3, "Gyroraw %f", gyro.get() );
		pros::lcd::print(2, "rightIntake Temp %f", rightIntake.get_temperature() );
		pros::lcd::print(3, "leftIntake Temp %f", leftIntake.get_temperature() );
		pros::lcd::print(4, "topLift Temp %f", topLift.get_temperature() );
		pros::lcd::print(5, "bottomLift Temp %f", bottomLift.get_temperature() );
		pros::lcd::print(6, "IN LOVING MEMORY OF:" );
		pros::lcd::print(7, "GABRIEL BLYE AND HUMZA" );
		pros::delay(20);
	}
}
