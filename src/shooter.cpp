#include "main.h"

Motor shooter(5, MOTOR_GEARSET_36 , 0, MOTOR_ENCODER_DEGREES);

void shooterPower(int power)
{
  shooter.move(power);
}

void shooterOP()
{
  if(controller.get_digital(DIGITAL_L1))
  {
  shooter.move(127);
  }
  else
  {
  shooter.move(0);
  }
}

void shoot()
{
  shooterPower(127);
  delay(850);
}
