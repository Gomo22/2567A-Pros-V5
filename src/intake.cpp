#include "main.h"

Motor intake(5, E_MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

static int maxIntakeVelocity = 200;

void suck(int rotations)
{
  intake.tare_position();
  intake.move_relative(rotations, maxIntakeVelocity);
}

int getIntakeMode()
{
  return intake.get_direction();
}

void intakeOP()
{
  if(controller.get_digital(DIGITAL_Y))
  {
  intake.move(maxIntakeVelocity);
  }
  else if(controller.get_digital(DIGITAL_A))
  {
  intake.move(-maxIntakeVelocity);
  }
  else
  {
    intake.move(0);
  }
}
