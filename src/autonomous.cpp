#include "main.h"
#ifndef global
#include "global.h"
#endif
#include "okapi/api.hpp"
#include "MiniPID.h"

using namespace okapi::literals;
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be sleftped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

/*void turnPID (double target)
{
  MiniPID pid = MiniPID(0.27, 0.000, 1.8);
  pid.setOutputLimits(-127, 127);
  pid.setMaxIOutput(30);
  pid.setSetpointRange(900);
  //int bias = std::nearbyint(0.059722*target);
  int bias = 0;
  float gyroCalibrationConst = 1;
  if(target < 0)
  {
    gyroCalibrationConst = 1.01;
  }
  else if (target > 0)
  {
    gyroCalibrationConst = 1.01;
  }
  //reset the gyro value
  gyroOutputReal = 0;
  int iterations = 0;
  int timeout = 0;
  while(iterations < 2000)
  {
    double output = pid.getOutput(gyroOutput/gyroCalibrationConst, target + bias);
    driveRightFront.move(-output);
    driveRightBack.move(-output);
    driveLeftFront.move(output);
    driveLeftBack.move(output);
    pros::delay(10);
    if(driveRightFront.get_actual_velocity() == 0 && iterations > 30)
    {
      timeout = timeout + 10;
      if(timeout >= 50)
      {
        break;
      }
     }
     pros::lcd::print(0, "Gyro: %f\n", gyroOutput);
     pros::lcd::print(1, "Gyroadj : %f\n", gyroOutput / gyroCalibrationConst);
     pros::lcd::print(1, "Error : %f\n", abs(target) - abs(gyroOutput / gyroCalibrationConst));
     iterations = iterations + 10;
  }
  driveRightFront.move(0);
  driveRightBack.move(0);
  driveLeftFront.move(0);
  driveLeftBack.move(0);
}*/

void turnPIDTime (double target, double time, bool reset = true, double i = 0)
{
  MiniPID pid = MiniPID(0.27, i, 1.8);
  pid.setOutputLimits(-127, 127);
  pid.setMaxIOutput(30);
  pid.setSetpointRange(900);
  //int bias = std::nearbyint(0.059722*target);
  int bias = 0;
  //bias was 38
  float gyroCalibrationConst = 1;
  if(target < 0)
  {
    gyroCalibrationConst = 1.066;
  }
  else if (target > 0)
  {
    gyroCalibrationConst = 1.061;
  }
  //reset the gyro value
  if(reset)
  {
    gyroOutputReal = 0;
  }
  int iterations = 0;
  int timeout = 0;
  while(iterations < time)
  {
    double output = pid.getOutput(gyroOutput/gyroCalibrationConst, target + bias);
    driveRight.move(-output);
    driveLeft.move(output);
    pros::delay(10);
    pros::lcd::print(0, "Gyro: %f\n", gyroOutput);
    pros::lcd::print(1, "Gyroadj : %f\n", gyroOutput / gyroCalibrationConst);
    pros::lcd::print(1, "Error : %f\n", abs(target) - abs(gyroOutput / gyroCalibrationConst));
    iterations = iterations + 10;
  }
  driveRight.move(0);
  driveLeft.move(0);
}

/*void drivePID (double target, double setPointRange = 900, double rightBias = 10, double sideBias = 1)
{
  int leftBias = 0;

  if (target < 0)
  {
     leftBias = leftBias * -1;
     rightBias = -10;
  }

  MiniPID leftPID = MiniPID(0.24, 0.000, 0.50);
  leftPID.setOutputLimits(-127, 127);
  leftPID.setMaxIOutput(30);
  leftPID.setSetpointRange(setPointRange);

  MiniPID rightPID = MiniPID(0.24, 0.000, 0.50);
  rightPID.setOutputLimits(-127, 127);
  rightPID.setMaxIOutput(30);
  rightPID.setSetpointRange(setPointRange);



//
  MiniPID leftPID = MiniPID(0.21, 0.000, 0.5);
  leftPID.setOutputLimits(-127, 127);
  leftPID.setMaxIOutput(30);
  leftPID.setSetpointRange(setPointRange);


  MiniPID rightPID = MiniPID(0.24, 0.000, 0.6);
  rightPID.setOutputLimits(-127, 127);
  rightPID.setMaxIOutput(30);
  rightPID.setSetpointRange(setPointRange);
//

  driveRightFront.tare_position();
  driveRightBack.tare_position();
  driveLeftFront.tare_position();
  driveLeftBack.tare_position();

  //double target = 900;
  int iterations = 0;
  int timeout = 0;
  float leftMotorEncoderAverage;
  float rightMotorEncoderAverage;

  while(iterations < 2500)
  {
    leftMotorEncoderAverage = (driveLeftFront.get_position());// + driveLeftBack.get_position()) / 2;
    rightMotorEncoderAverage = (driveRightFront.get_position());// + driveRightBack.get_position()) / 2;
    double leftOutput = leftPID.getOutput(leftMotorEncoderAverage, target + leftBias);
    double rightOutput = sideBias * rightPID.getOutput(rightMotorEncoderAverage, target + rightBias);
    driveRightFront.move(rightOutput);
    driveRightBack.move(rightOutput);
    driveLeftFront.move(leftOutput);
    driveLeftBack.move(leftOutput);
    pros::delay(10);
    if(driveRightFront.get_actual_velocity() == 0 && iterations > 30)
    {
      timeout = timeout + 10;
      if(timeout >= 50)
      {
        break;
      }
    }
    iterations = iterations + 10;
  }
  //pros::lcd::print(1, "PID : %f\n", motorEncoderAverage);
  std::cout << "Left Error: " << leftMotorEncoderAverage << std::endl;
  std::cout << "Right Error: " << rightMotorEncoderAverage << std::endl;
}*/

void drivePIDTime (double target, double time, double setPointRange = 900, double rightBias = 10, double sideBias = 1)
{
  int leftBias = 0;

  if (target < 0)
  {
    leftBias = leftBias * -1;
    rightBias = -10;
  }

  MiniPID leftPID = MiniPID(0.24, 0.000, 0.50);
  leftPID.setOutputLimits(-127, 127);
  leftPID.setMaxIOutput(30);
  leftPID.setSetpointRange(setPointRange);

  MiniPID rightPID = MiniPID(0.24, 0.000, 0.50);
  rightPID.setOutputLimits(-127, 127);
  rightPID.setMaxIOutput(30);
  rightPID.setSetpointRange(setPointRange);

  driveRight.tare_position();
  driveLeft.tare_position();

  int iterations = 0;
  int timeout = 0;
  float leftMotorEncoderAverage;
  float rightMotorEncoderAverage;

  while(iterations < time)
  {
    leftMotorEncoderAverage = (driveLeft.get_position());// + driveLeftBack.get_position()) / 2;
    rightMotorEncoderAverage = (driveRight.get_position());// + driveRightBack.get_position()) / 2;
    double leftOutput = leftPID.getOutput(leftMotorEncoderAverage, target + leftBias);
    double rightOutput = sideBias * rightPID.getOutput(rightMotorEncoderAverage, target + rightBias);
    driveRight.move(rightOutput);
    driveLeft.move(leftOutput);
    pros::delay(10);
    iterations = iterations + 10;
  }
  //pros::lcd::print(1, "PID : %f\n", motorEncoderAverage);
  std::cout << "Left Error: " << leftMotorEncoderAverage << std::endl;
  std::cout << "Right Error: " << rightMotorEncoderAverage << std::endl;
}

void flipOut ()
{
  tilter.tare_position();
	leftLift.tare_position();
	rightLift.tare_position();
	midLift.tare_position();

  driveRight.move(127);
  driveLeft.move(127);
  pros::delay(450);
  driveRight.move(-127);
  driveLeft.move(-127);
  pros::delay(300);
  rightIntake.move(127);
  leftIntake.move(127);
  pros::delay(100);
  driveRight.move(0);
  driveLeft.move(0);
  pros::delay(400);
  rightIntake.move(-127);
  leftIntake.move(-127);

  leftLift.move_absolute(510, 100);
  rightLift.move_absolute(510, 100);
  midLift.move_absolute(510, 100);
  pros::delay(700);
}

void stack ()
{
  rightIntake.move(127);
  leftIntake.move(127);
  pros::delay(60);
  rightIntake.move(0);
  leftIntake.move(0);

  leftLift.move_absolute(100, 100);
  rightLift.move_absolute(100, 100);
  midLift.move_absolute(100, 100);
  pros::delay(500);

  tilter.move_absolute(2000, 200);
  pros::delay(700);
  rightIntake.move(40);
  leftIntake.move(40);
  tilter.move_absolute(2500, 200);
  pros::delay(400);
  tilter.move_absolute(3100, 100);
  pros::delay(1000);

  rightIntake.move(75);
  leftIntake.move(75);
  drivePIDTime(-1000, 1000, 500);
}

void any_1()
{
  drivePIDTime(-1000, 1000);
  pros::delay(400);
  drivePIDTime(1000, 1000);
  flipOut();
}

void blue_front()
{
  flipOut();

  drivePIDTime(3000, 3100, 300);

  drivePIDTime(-1650, 1400);

  turnPIDTime(-1500, 900);

  driveRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  driveLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  leftLift.move_absolute(650, 100);
  rightLift.move_absolute(650, 100);
  midLift.move_absolute(650, 100);
  pros::delay(1000);

  drivePIDTime(650, 1000);

  stack();

  driveRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void red_front()
{
  flipOut();

  drivePIDTime(3000, 3100, 300);

  drivePIDTime(-1650, 1400);

  turnPIDTime(1500, 900);

  driveRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  driveLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  leftLift.move_absolute(650, 100);
  rightLift.move_absolute(650, 100);
  midLift.move_absolute(650, 100);
  pros::delay(1000);

  drivePIDTime(650, 1000);

  stack();

  driveRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void blue_back()
{
  flipOut();

  drivePIDTime(1300, 1100, 500);

  driveRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  driveLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  leftLift.move_absolute(3700, 100);
  rightLift.move_absolute(3700, 100);
  midLift.move_absolute(3700, 100);
  pros::delay(1000);

  drivePIDTime(550, 1200);

  leftLift.move(-70);
  rightLift.move(-70);
  midLift.move(-70);
  pros::delay(1800);
  leftLift.move(0);
  rightLift.move(0);
  midLift.move(0);

  leftLift.move_absolute(650, 100);
  rightLift.move_absolute(650, 100);
  midLift.move_absolute(650, 100);
  pros::delay(1000);

  driveRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  drivePIDTime(-1000, 1000);

  turnPIDTime(1000, 1000);

  drivePIDTime(1500, 1500);

  rightIntake.move(0);
  leftIntake.move(0);

  stack();
}

void red_back()
{
  flipOut();

  drivePIDTime(1300, 1100, 500);

  driveRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  driveLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  leftLift.move_absolute(3700, 100);
  rightLift.move_absolute(3700, 100);
  midLift.move_absolute(3700, 100);
  pros::delay(1000);

  drivePIDTime(550, 1200);

  leftLift.move(-70);
  rightLift.move(-70);
  midLift.move(-70);
  pros::delay(1800);
  leftLift.move(0);
  rightLift.move(0);
  midLift.move(0);

  leftLift.move_absolute(650, 100);
  rightLift.move_absolute(650, 100);
  midLift.move_absolute(650, 100);
  pros::delay(1000);

  driveRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  drivePIDTime(-1000, 1000);

  turnPIDTime(-1000, 1000);

  drivePIDTime(1500, 1500);

  rightIntake.move(0);
  leftIntake.move(0);

  stack();
}

void blue_front_nopark_auton()
{
  //
}

void red_front_mid_nopark_auton()
{
  //
}

void prog_skills()
{
  //
}

void no_auton()
{
  //
}

void autonomous()
{
  switch(getAutonNumber())
  {
    case 0:
      any_1();
      break;
    case 1:
      blue_front();
      break;
    case 2:
      red_front();
      break;
    case 3:
      blue_back();
      break;
    case 4:
      red_back();
      break;
    case 5:
      blue_front_nopark_auton();
      break;
    case 6:
      prog_skills();
      break;
    case 7:
      no_auton();
      break;
  }
}
