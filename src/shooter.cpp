#include "main.h"
static int maxPower = 200;
static int pullback = 600;
Motor shooter(3, MOTOR_GEARSET_36 , 0, MOTOR_ENCODER_DEGREES);

void shooterPower()
{
  shooter.move_absolute(pullback, maxPower);
}

void shooterOP()
{
  if(controller.get_digital(DIGITAL_L1))
  {
  shooter.move(maxPower);
  }
  else
  {
  shooter.move(0);
  }
}

void shoot()
{
  shooterPower();
}
