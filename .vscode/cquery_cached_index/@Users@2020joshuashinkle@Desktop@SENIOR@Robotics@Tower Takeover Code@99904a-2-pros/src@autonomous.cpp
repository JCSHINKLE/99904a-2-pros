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
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
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
    driveRightFront.move(-output);
    driveRightBack.move(-output);
    driveLeftFront.move(output);
    driveLeftBack.move(output);
    pros::delay(10);
    pros::lcd::print(0, "Gyro: %f\n", gyroOutput);
    pros::lcd::print(1, "Gyroadj : %f\n", gyroOutput / gyroCalibrationConst);
    pros::lcd::print(1, "Error : %f\n", abs(target) - abs(gyroOutput / gyroCalibrationConst));
    iterations = iterations + 10;
  }
  driveRightFront.move(0);
  driveRightBack.move(0);
  driveLeftFront.move(0);
  driveLeftBack.move(0);
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

  driveRightFront.tare_position();
  driveRightBack.tare_position();
  driveLeftFront.tare_position();
  driveLeftBack.tare_position();

  int iterations = 0;
  int timeout = 0;
  float leftMotorEncoderAverage;
  float rightMotorEncoderAverage;

  while(iterations < time)
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
    iterations = iterations + 10;
  }
  //pros::lcd::print(1, "PID : %f\n", motorEncoderAverage);
  std::cout << "Left Error: " << leftMotorEncoderAverage << std::endl;
  std::cout << "Right Error: " << rightMotorEncoderAverage << std::endl;
}

void red_front_auton()
{
  drivePIDTime(3000, 1700);
  pros::delay(400);
  drivePIDTime(-2250, 1500);
  turnPIDTime(1800, 1500, false);
  pros::delay(400);
  turnPIDTime(3100, 1000, false);
  pros::delay(300);
  drivePIDTime(900, 800, 900, -60, 1);
  drivePIDTime(900, 1500, 280, 10, 1);
  drivePIDTime(-1500, 1200);
  turnPIDTime(4550, 1000, false);
  //drivePID(1850, 1100);
  turnPIDTime(3550, 900, false);
  drivePIDTime(3500, 5000);
}
void red_back_auton() {
  //red back
  drivePIDTime(3100, 1700);
  pros::delay(400);
  drivePIDTime(-300, 500);
  turnPIDTime(-900, 1000, false);
  drivePIDTime(3000, 2500);

  turnPIDTime(-900, 800, false, 0.003);
  drivePIDTime(1600, 1700, 270);
  turnPIDTime(-1800, 1000, false);
  driveRightFront.move(10);
  driveRightBack.move(10);
  driveLeftFront.move(10);
  driveLeftBack.move(10);
  pros::delay(1500);
  driveRightFront.move(0);
  driveRightBack.move(0);
  driveLeftFront.move(0);
  driveLeftBack.move(0);

  turnPIDTime(190, 700, true, 0.003);
  pros::delay(400);
  turnPIDTime(-1100, 1000);
  drivePIDTime(2600, 2500);
}
void blue_front_auton() {
  //blue primary auton
  drivePIDTime(3000, 1700);
  pros::delay(400);
  drivePIDTime(-2300, 1500);
  turnPIDTime(0, 800, false, 0.003);
  pros::delay(400);
  turnPIDTime(600, 1000, false);
  pros::delay(300);
  drivePIDTime(1000, 800, 900, 10, 1);
  drivePIDTime(1000, 1500, 280, 10, 1);
  drivePIDTime(-1570, 1200);
  turnPIDTime(-900, 1000, false);
  //drivePID(1850, 1100);
  turnPIDTime(0, 900, false);
  drivePIDTime(3500, 5000);
}
void blue_back_auton() {
  //Blue back
  drivePIDTime(3100, 1700);
  pros::delay(400);
  drivePIDTime(-400, 500);
  turnPIDTime(900, 1000, false);
  drivePIDTime(3000, 2500);

  turnPIDTime(900, 800, false, 0.003);
  drivePIDTime(1600, 1700, 270);
  turnPIDTime(0, 1000, false);
  driveRightFront.move(10);
  driveRightBack.move(10);
  driveLeftFront.move(10);
  driveLeftBack.move(10);
  pros::delay(1500);
  driveRightFront.move(0);
  driveRightBack.move(0);
  driveLeftFront.move(0);
  driveLeftBack.move(0);

  turnPIDTime(-140, 700, true, 0.003);
  pros::delay(400);
  turnPIDTime(-1000, 1000);
  drivePIDTime(2600, 2500);


}
void red_front_nopark_auton() {
  drivePIDTime(3000, 1700);
  pros::delay(400);
  drivePIDTime(-2250, 1500);
  turnPIDTime(1800, 1500, false);
  pros::delay(400);
  turnPIDTime(2635, 1000, false);

  drivePIDTime(3500, 2100, false);
  drivePIDTime(-1700, 900);

  turnPIDTime(3620, 900, false);
  drivePIDTime(600, 700, 900, -60, 1);
  drivePIDTime(750, 900, 280, 10, 1);

  turnPIDTime(2340, 1200, false);
  pros::delay(400);

}
void blue_front_nopark_auton() {
  drivePIDTime(3000, 1700);
  pros::delay(400);
  drivePIDTime(-2370, 1500);
  turnPIDTime(0, 800, false, 0.003);
  pros::delay(400);
  drivePIDTime(-150, 500);
  turnPIDTime(920, 1000, false);

  drivePIDTime(3800, 2100, false);
  drivePIDTime(-1850, 900);

  turnPIDTime(0, 900, false);
  drivePIDTime(600, 700, 900, 10, 1);
  drivePIDTime(820, 900, 280, 10, 1);

  turnPIDTime(-520, 1200, false);
  pros::delay(400);

}
void red_front_mid_nopark_auton()
{

}
void prog_skills()
{

}

void test()
{
  drivePIDTime(1000, 1000);
  turnPIDTime(-900, 1000, false);
  //pros::lcd::print(2, "Gyro %f", gyroOutput );
}

void autonomous()
{
  switch(getAutonNumber())
  {
    case 0:
      red_front_auton();
      break;
    case 1:
      red_back_auton();
      break;
    case 2:
      blue_front_auton();
      break;
    case 3:
      blue_back_auton();
      break;
    case 4:
      red_front_nopark_auton();
      break;
    case 5:
      blue_front_nopark_auton();
      break;
    case 6:
      prog_skills();
      break;
    case 7:
      test();
      break;
  }
}
