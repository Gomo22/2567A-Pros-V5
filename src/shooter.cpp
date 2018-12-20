#include "main.h"
static int maxPower = 200;
static int pullback = 600;
static int setPullback = 0;
Motor puncher(6, E_MOTOR_GEARSET_18 , 0, MOTOR_ENCODER_DEGREES);

void untilAtPullback()
{
  while(!((puncher.get_position() < setPullback+3) && (puncher.get_position() > setPullback-3)))
    {
      delay(20);
    }
}

void resetPuncher()
{
  puncher.tare_position();
}

void puncherPower()
{
  resetPuncher();
  puncher.move_absolute(pullback, maxPower);
  setPullback = pullback;
}

void puncherOP()
{
  if(controller.get_digital(DIGITAL_UP))
  {
  puncher.move(maxPower);
  }
  else
  {
  puncher.move(0);
  }
}

int getPuncher()
{
  return puncher.get_position();
}

void shoot()
{
  puncherPower();
  untilAtPullback();
}

void shootAsync()
{
  puncherPower();
}
