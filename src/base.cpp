#include "main.h"

static int maxBaseVelocity = 200;
static int midBasesVelocity = 100;
static int lowBaseVelocity = 50;
static int setdistance = 0;
static int setTarget = 0;

Motor leftDrive (1, E_MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor rightDrive (3, E_MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

void untilAtDistance()
{
  while(!((leftDrive.get_position() < setdistance+3) && (leftDrive.get_position() > setdistance-3)))
    {
      delay(20);
    }
}

void untilAtTarget()
{
  while(!((leftDrive.get_position() < setTarget+3) && (leftDrive.get_position() > setTarget-3)))
    {
      delay(20);
    }
}

void driveOP()
{
  leftDrive.move(controller.get_analog(ANALOG_LEFT_Y));
  rightDrive.move(controller.get_analog(ANALOG_RIGHT_Y));
}

void driveAsync(int distance) // will not block program (multi tasking)
{
  float inches = (360/14.20)*distance;
  leftDrive.move_relative(inches, midBasesVelocity);
  rightDrive.move_relative(inches, midBasesVelocity);
  setdistance = inches;
}


void drive(int distance) // will block drive(no multi tasking )
{
  driveAsync(distance);
  untilAtDistance();
}


void turnAsync(int degrees)
{
  double degreesToEncoder = 5.5;
  int Target = degrees*degreesToEncoder;

  leftDrive.move_relative(Target, lowBaseVelocity);
  rightDrive.move_relative(-Target, lowBaseVelocity);
  setTarget = degrees;
}

void turn(int degrees)
{
turnAsync(degrees);
untilAtTarget();
}
