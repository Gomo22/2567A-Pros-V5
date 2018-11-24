#include "main.h"

Motor intake(4, E_MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

static int maxIntakeVelocity = 200;

void suck(int rotations)
{
  intake.tare_position();
  intake.move_relative(rotations, maxIntakeVelocity);
}

void intakeOP()
{
  if(controller.get_digital(DIGITAL_R1))
  {
  intake.move(maxIntakeVelocity);
  }
  else if(controller.get_digital(DIGITAL_R2))
  {
  intake.move(-maxIntakeVelocity);
  }
  else
  {
    intake.move(0);
  }
}
