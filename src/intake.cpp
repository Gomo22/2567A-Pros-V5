#include "main.h"

Motor intake(15, E_MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

static int maxIntakeVelocity = 200;

void suck(int rotations)
{
  intake.move_relative(-rotations, maxIntakeVelocity);
  intake.tare_position();
}

int getIntakeMode()
{
  return intake.get_direction();
}

void intakeOP()
{
  if(controller2.get_digital(DIGITAL_R2))
  {
  intake.move(maxIntakeVelocity);
  }
  else if(controller2.get_digital(DIGITAL_R1))
  {
  intake.move(-30);
  }
  else
  {
    intake.move(0);
  }

}
