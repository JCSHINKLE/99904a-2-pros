#include "main.h"
#ifndef global
#include "global.h"
#endif

void opcontrol()
{
	bool broke = false;
	//driveRight.set_voltage_limit(12000);
  //driveLeft.set_voltage_limit(12000);
	//rightIntake.set_voltage_limit(12000);
  //leftIntake.set_voltage_limit(12000);
	bool reversed = false;
	while (true)
	{
		//drive control
		int turn = weber.get_analog(ANALOG_LEFT_X);
		int power = weber.get_analog(ANALOG_LEFT_Y);
		int left;
		int right;
		if (reversed == true)
		{
			left = power - turn;
			right = power + turn;
		}
		else
		{
			left = power + turn;
			right = power - turn;
		}

		if (weber.get_digital_new_press(DIGITAL_Y))
		{
			reversed = !reversed;
		}

		if (abs(turn) + abs(power) < 1 && !broke)
		{
			driveRight.move(0);
			driveLeft.move(0);
			driveRight.move_velocity(0);
			driveLeft.move_velocity(0);
			driveRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			driveLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			broke = true;
		}
		else if (reversed == false)
		{
			driveRight.move(right);
			driveLeft.move(left);
			broke = false;
		}
		else if (reversed == true)
		{
			driveRight.move(-right);
			driveLeft.move(-left);
			broke = false;
		}

		// tilter
		if(abs(weber.get_analog(ANALOG_RIGHT_X)) > 1)
		{
			tilter.move(weber.get_analog(ANALOG_RIGHT_X));
		}
		else
		{
			tilter.move_velocity(0);
			tilter.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
		}


		// cube intake
		if (weber.get_digital(DIGITAL_R2))
		{
			rightIntake.move_velocity(100);
			leftIntake.move_velocity(100);
		}
		else if (weber.get_digital(DIGITAL_R1))
		{
			rightIntake.move_velocity(-100);
			leftIntake.move_velocity(-100);
		}
		else if (weber.get_digital(DIGITAL_A))
		{
			leftIntake.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			rightIntake.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			rightIntake.move_velocity(35);
			leftIntake.move_velocity(35);
			driveRight.move_velocity(-10);
			driveLeft.move_velocity(-10);
			leftIntake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			rightIntake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}
		else
		{
			leftIntake.move_velocity(0);
			rightIntake.move_velocity(0);

			leftIntake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			rightIntake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}


		// lift
		if(abs(weber.get_analog(ANALOG_RIGHT_Y)) > 1)
		{
			leftLift.move(weber.get_analog(ANALOG_RIGHT_Y));
			rightLift.move(weber.get_analog(ANALOG_RIGHT_Y));
		}
		else
		{
			leftLift.move_velocity(0);
			rightLift.move_velocity(0);

			leftLift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			rightLift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
		}

		switch(getAutonNumber())
		{
		  case 0:
		    pros::lcd::print(0, "Auton: ANYWHERE 1");
				break;
		  case 1:
		    pros::lcd::print(0, "Auton: BLUE FRONT");
				break;
		  case 2:
		    pros::lcd::print(0, "Auton: RED FRONT");
				break;
		  case 3:
		    pros::lcd::print(0, "Auton: BLUE BACK");
				break;
		  case 4:
		    pros::lcd::print(0, "Auton: RED BACK");
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
		pros::lcd::print(2, "rightIntake %f", rightIntake.get_temperature() );
		pros::lcd::print(3, "leftIntake %f", leftIntake.get_temperature() );
		pros::lcd::print(4, "leftLift %f", leftLift.get_temperature() );
		pros::lcd::print(5, "rightLift %f", rightLift.get_temperature() );
		pros::lcd::print(6, "driveRight %f", driveRight.get_temperature() );
		pros::lcd::print(7, "driveLeft %f", driveLeft.get_temperature() );
		pros::delay(20);
	}
}
