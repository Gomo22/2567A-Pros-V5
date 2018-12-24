#include "main.h"

Motor intake(15, E_MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

static int maxIntakeVelocity = 200;
static int midIntakeVelocity = 100;

void suck(int rotations)
{
  intake.move_relative(rotations, maxIntakeVelocity);
  intake.tare_position();
}

int getIntakeMode()
{
  return intake.get_direction();
}

void intakeOP()
{
  if(controller.get_digital(DIGITAL_R2))
  {
  intake.move(midIntakeVelocity);
  }
  else if(controller.get_digital(DIGITAL_R1))
  {
  intake.move(-midIntakeVelocity);
  }
  else
  {
    intake.move(0);
  }

}
