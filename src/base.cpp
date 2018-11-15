#include "main.h"

static int maxBaseVelocity = 200;

Motor leftDrive (1, E_MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor leftDrive1 (2, E_MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor rightDrive (3, E_MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);
Motor rightDrive1 (4, E_MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

void driveOP()
{
  leftDrive.move(controller.get_analog(ANALOG_LEFT_Y));
  leftDrive1.move(controller.get_analog(ANALOG_LEFT_Y));
  rightDrive.move(controller.get_analog(ANALOG_RIGHT_Y));
  rightDrive1.move(controller.get_analog(ANALOG_RIGHT_Y));
}

void drive(int distance)
{
  leftDrive.move_relative(distance, maxBaseVelocity);
  leftDrive1.move_relative(distance, maxBaseVelocity);
  rightDrive.move_relative(distance, maxBaseVelocity);
  rightDrive1.move_relative(distance, maxBaseVelocity);

while(!((leftDrive.get_position() < distance+3) && (leftDrive.get_position() > distance-3)))
  {
    delay(2);
  }
}

void turn(int degrees)
{
  double degreesToEncoder = 3.6;
  int Target = degrees*degreesToEncoder;

  leftDrive.move_relative(Target, maxBaseVelocity);
  leftDrive1.move_relative(Target, maxBaseVelocity);
  rightDrive.move_relative(Target, -maxBaseVelocity);
  rightDrive1.move_relative(Target, -maxBaseVelocity);

while(!((leftDrive.get_position() < degrees+3) && (leftDrive.get_position() > degrees-3)))
  {
    delay(2);
  }
}
