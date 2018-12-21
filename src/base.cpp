#include "main.h"

static int maxBaseVelocity = 200;
static int medBaseVelocity = 150;
static int halfMaxBaseVelocity = 100;
static int slowBaseVelocity = 50;
static int brakeBaseVelocity = -20;
//DEFINING MOTORS
Motor leftDrive(1, MOTOR_GEARSET_18, 0,  MOTOR_ENCODER_DEGREES);
Motor leftDrive1(2, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

Motor rightDrive(3, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);
Motor rightDrive1(4, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

void drivePID(int inches)
{
  int speed;
  double kd = 0; //2x kp
  double kp = .1;
  int error;
  int derivative;
  int prevError;
  int distance = inches*(360/14.125);
  while(leftDrive.get_position() > distance + 5 || leftDrive.get_position() < distance - 5)
    {
  error = distance - leftDrive.get_position();
  speed = error * kp;
  derivative = prevError - error;
  prevError = error;
  speed = (error*kp) + (derivative*kd);
  //sets clamp for over wind up
  if(speed > 200)
  speed = maxBaseVelocity;
  if(speed < -200)
  speed = -maxBaseVelocity;
  left(speed);
  right(speed);
    }
}


void turnPID(int deg)
{

  int speed;
  // both should be higher
  double kd = 0; //2x kp
  double kp = .1;
  int error;
  int derivative;
  int prevError;
  int degrees;
  int target = deg*2.5;
while(leftDrive.get_position() > target + 5 || leftDrive.get_position() < target - 5)
  {
  error = target - ((rightDrive.get_position() - leftDrive.get_position())/2);
  speed = error * kp;
  derivative = prevError - error;
  prevError = error;
  speed = (error*kp) + (derivative*kd);
  left(-speed);
  right(speed);
  }
}

void left(int vel){
  leftDrive.move(vel);
  leftDrive1.move(vel);
}

void right(int vel){
  rightDrive.move(vel);
  rightDrive1.move(vel);
}

void driveOP()
{
  leftDrive.move(controller.get_analog(ANALOG_LEFT_Y));
  leftDrive1.move(controller.get_analog(ANALOG_LEFT_Y));
  rightDrive.move(controller.get_analog(ANALOG_RIGHT_Y));
  rightDrive1.move(controller.get_analog(ANALOG_RIGHT_Y));
}

int getBatteryLevel()
{
  return battery::get_capacity();
}

int getDistance()
{
  return leftDrive.get_position();
}

void resetDrive()
{

  leftDrive.tare_position();
  leftDrive1.tare_position();
  rightDrive.tare_position();
  rightDrive1.tare_position();
}

//drive
void drive(int inches)
{
  resetDrive();
    int distance = inches*(360/14.125);
    if(distance > 0)
    {
      leftDrive.move_velocity(medBaseVelocity);
      leftDrive1.move_velocity(medBaseVelocity);
      rightDrive.move_velocity(medBaseVelocity);
      rightDrive1.move_velocity(medBaseVelocity);

      while(leftDrive.get_position() < distance-200)
      {
        delay(2);
      }
      leftDrive.move_velocity(slowBaseVelocity);
      leftDrive1.move_velocity(slowBaseVelocity);
      rightDrive.move_velocity(slowBaseVelocity);
      rightDrive1.move_velocity(slowBaseVelocity);


      while(leftDrive.get_position() < distance)
      {
        delay(2);
      }

      leftDrive.move_velocity(brakeBaseVelocity);
      leftDrive1.move_velocity(brakeBaseVelocity);
      rightDrive.move_velocity(brakeBaseVelocity);
      rightDrive1.move_velocity(brakeBaseVelocity);

      delay(10);

      leftDrive.move_velocity(0);
      leftDrive1.move_velocity(0);
      rightDrive.move_velocity(0);
      rightDrive1.move_velocity(0);
    }

    if(distance < 0)
    {
      leftDrive.move_velocity(-medBaseVelocity);
      leftDrive1.move_velocity(-medBaseVelocity);
      rightDrive.move_velocity(-medBaseVelocity);
      rightDrive1.move_velocity(-medBaseVelocity);

      while(leftDrive.get_position() > distance+200)
      {
        delay(2);
      }
      leftDrive.move_velocity(-slowBaseVelocity);
      leftDrive1.move_velocity(-slowBaseVelocity);
      rightDrive.move_velocity(-slowBaseVelocity);
      rightDrive1.move_velocity(-slowBaseVelocity);


      while(leftDrive.get_position() > distance)
      {
        delay(2);
      }

      leftDrive.move_velocity(-brakeBaseVelocity);
      leftDrive1.move_velocity(-brakeBaseVelocity);
      rightDrive.move_velocity(-brakeBaseVelocity);
      rightDrive1.move_velocity(-brakeBaseVelocity);

      delay(10);

      leftDrive.move_velocity(0);
      leftDrive1.move_velocity(0);
      rightDrive.move_velocity(0);
      rightDrive1.move_velocity(0);
    }
}

void driveMax(int inches)
{
  resetDrive();
  int distance = inches*(360/14.125);
  if(distance > 0)
  {
    leftDrive.move_velocity(maxBaseVelocity);
    leftDrive1.move_velocity(maxBaseVelocity);
    rightDrive.move_velocity(maxBaseVelocity);
    rightDrive1.move_velocity(maxBaseVelocity);

    while(leftDrive.get_position() < distance)
    {
      delay(2);
    }

    leftDrive.move_velocity(brakeBaseVelocity);
    leftDrive1.move_velocity(brakeBaseVelocity);
    rightDrive.move_velocity(brakeBaseVelocity);
    rightDrive1.move_velocity(brakeBaseVelocity);

    delay(10);

    leftDrive.move_velocity(0);
    leftDrive1.move_velocity(0);
    rightDrive.move_velocity(0);
    rightDrive1.move_velocity(0);
  }
  if(distance < 0)
  {
    leftDrive.move_velocity(-maxBaseVelocity);
    leftDrive1.move_velocity(-maxBaseVelocity);
    rightDrive.move_velocity(-maxBaseVelocity);
    rightDrive1.move_velocity(-maxBaseVelocity);

    while(leftDrive.get_position() > distance)
    {
      delay(2);
    }

    leftDrive.move_velocity(-brakeBaseVelocity);
    leftDrive1.move_velocity(-brakeBaseVelocity);
    rightDrive.move_velocity(-brakeBaseVelocity);
    rightDrive1.move_velocity(-brakeBaseVelocity);

    delay(10);

    leftDrive.move_velocity(0);
    leftDrive1.move_velocity(0);
    rightDrive.move_velocity(0);
    rightDrive1.move_velocity(0);
  }
}

void turn(int degrees)
{
  resetDrive();
  int target = degrees*2.5;

  /*  leftDrive.move_relative(target, slowBaseVelocity);
    leftDrive1.move_relative(target, slowBaseVelocity);
    rightDrive.move_relative(-target, slowBaseVelocity);
    rightDrive1.move_relative(-target, slowBaseVelocity);*/
    if(target > 0)
    {
      leftDrive.move_velocity(medBaseVelocity);
      leftDrive1.move_velocity(medBaseVelocity);
      rightDrive.move_velocity(-medBaseVelocity);
      rightDrive1.move_velocity(-medBaseVelocity);

      while(leftDrive.get_position() < target-300)
      {
        delay(2);
      }
      leftDrive.move_velocity(slowBaseVelocity);
      leftDrive1.move_velocity(slowBaseVelocity);
      rightDrive.move_velocity(-slowBaseVelocity);
      rightDrive1.move_velocity(-slowBaseVelocity);


      while(leftDrive.get_position() < target)
      {
        delay(2);
      }

      leftDrive.move_velocity(brakeBaseVelocity);
      leftDrive1.move_velocity(brakeBaseVelocity);
      rightDrive.move_velocity(-brakeBaseVelocity);
      rightDrive1.move_velocity(-brakeBaseVelocity);

      delay(10);

      leftDrive.move_velocity(0);
      leftDrive1.move_velocity(0);
      rightDrive.move_velocity(0);
      rightDrive1.move_velocity(0);
    }

    if(target < 0)
    {
      leftDrive.move_velocity(-medBaseVelocity);
      leftDrive1.move_velocity(-medBaseVelocity);
      rightDrive.move_velocity(medBaseVelocity);
      rightDrive1.move_velocity(medBaseVelocity);

      while(leftDrive.get_position() > target+300)
      {
        delay(2);
      }
      leftDrive.move_velocity(-slowBaseVelocity);
      leftDrive1.move_velocity(-slowBaseVelocity);
      rightDrive.move_velocity(slowBaseVelocity);
      rightDrive1.move_velocity(slowBaseVelocity);


      while(leftDrive.get_position() > target)
      {
        delay(2);
      }

      leftDrive.move_velocity(-brakeBaseVelocity);
      leftDrive1.move_velocity(-brakeBaseVelocity);
      rightDrive.move_velocity(brakeBaseVelocity);
      rightDrive1.move_velocity(brakeBaseVelocity);

      delay(10);

      leftDrive.move_velocity(0);
      leftDrive1.move_velocity(0);
      rightDrive.move_velocity(0);
      rightDrive1.move_velocity(0);
    }
  }
