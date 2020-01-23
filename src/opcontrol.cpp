#include "main.h"
#ifndef global
#include "global.h"
#endif

void opcontrol()
{
	bool broke = false;
	bool reversed = false;
	bool tiltback = false;
	bool tiltfor = false;
	bool botLift = false;
	bool lowLift = false;
	bool medLift = false;
	double leftLiftpos;
	double rightLiftpos;
	double midLiftpos;
	double tiltpos;

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
		if (weber.get_digital(DIGITAL_RIGHT))
		{
			tiltback = true;
		}

		if (weber.get_digital(DIGITAL_LEFT))
		{
			tiltfor = true;
		}

		if(abs(weber.get_analog(ANALOG_RIGHT_X)) > 1)
		{
			tilter.move(weber.get_analog(ANALOG_RIGHT_X));
		}
		else if (tiltfor == true)
		{
			tilter.move_absolute(6500, 127);
			tiltpos = tilter.get_position();
			if (tiltpos < 6503 && tiltpos > 6497)
			{
				tiltfor = false;
			}
		}
		else if (tiltback == true)
		{
			tilter.move_absolute(0, 127);
			tiltpos = tilter.get_position();
			if (tiltpos < 3)
			{
				tiltback = false;
			}
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
			rightIntake.move_velocity(127);
			leftIntake.move_velocity(127);
			driveRight.move_velocity(-50);
			driveLeft.move_velocity(-50);
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
		if (weber.get_digital(DIGITAL_B))
		{
			botLift = true;
		}

		if (weber.get_digital(DIGITAL_L2))
		{
			lowLift = true;
		}

		if (weber.get_digital(DIGITAL_L1))
		{
			medLift = true;
		}

		if (abs(weber.get_analog(ANALOG_RIGHT_Y)) > 1)
		{
			botLift = false;
			lowLift = false;
			medLift = false;
			leftLift.move(weber.get_analog(ANALOG_RIGHT_Y));
			rightLift.move(weber.get_analog(ANALOG_RIGHT_Y));
			midLift.move(weber.get_analog(ANALOG_RIGHT_Y));
		}
		else if (botLift == true)
		{
			leftLift.move_absolute(300, 127);
			rightLift.move_absolute(300, 127);
			midLift.move_absolute(300, 127);
			leftLiftpos = leftLift.get_position();
			rightLiftpos = rightLift.get_position();
			midLiftpos = midLift.get_position();
			if ((leftLiftpos < 310 && leftLiftpos > 290) && (rightLiftpos < 310 && rightLiftpos > 290) && (midLiftpos < 310 && midLiftpos > 290))
			{
				botLift = false;
			}
		}
		else if (lowLift == true)
		{
			leftLift.move_absolute(2650, 127);
			rightLift.move_absolute(2650, 127);
			midLift.move_absolute(2650, 127);
			leftLiftpos = leftLift.get_position();
			rightLiftpos = rightLift.get_position();
			midLiftpos = midLift.get_position();
			if ((leftLiftpos < 2660 && leftLiftpos > 2640) && (rightLiftpos < 2660 && rightLiftpos > 2640) && (midLiftpos < 2660 && midLiftpos > 2640))
			{
				lowLift = false;
			}
		}
		else if (medLift == true)
		{
			leftLift.move_absolute(3450, 127);
			rightLift.move_absolute(3450, 127);
			midLift.move_absolute(3450, 127);
			leftLiftpos = leftLift.get_position();
			rightLiftpos = rightLift.get_position();
			midLiftpos = midLift.get_position();
			if ((leftLiftpos < 3460 && leftLiftpos > 3440) && (rightLiftpos < 3460 && rightLiftpos > 3440) && (midLiftpos < 3460 && midLiftpos > 3440))
			{
				medLift = false;
			}
		}
		else
		{
			leftLift.move_velocity(0);
			rightLift.move_velocity(0);
			midLift.move_velocity(0);

			leftLift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			rightLift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
			midLift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
		}

		// flipout
		if (weber.get_digital(DIGITAL_X))
		{
			flipOut();
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
		pros::lcd::print(6, "midLift %f", midLift.get_temperature() );
		pros::lcd::print(7, "drive %f %f", driveLeft.get_temperature(), driveRight.get_temperature());
		pros::delay(20);
	}
}
