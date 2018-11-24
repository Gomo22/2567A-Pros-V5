#include "main.h"
static int maxPower = 200;
static int pullback = 600;
Motor puncher(3, MOTOR_GEARSET_36 , 0, MOTOR_ENCODER_DEGREES);

void shooterPower()
{
  puncher.move_absolute(pullback, maxPower);
}

void shooterOP()
{
  if(controller.get_digital(DIGITAL_L1))
  {
  puncher.move(maxPower);
  }
  else
  {
  puncher.move(0);
  }
}

void shoot()
{
  puncher.tare_position();
  shooterPower();
}
