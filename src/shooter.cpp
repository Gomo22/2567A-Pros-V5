#include "main.h"
static int maxPower = 100;
static int pullback = 352;
static int setPullback = 0;
Motor puncher(7, E_MOTOR_GEARSET_36 , 0, MOTOR_ENCODER_DEGREES);

void untilAtPullback()
{
  while(!((puncher.get_position() < setPullback+3) && (puncher.get_position() > setPullback-3)))
    {
      delay(20);
    }
}
void loadPuncher()
{
puncher.set_brake_mode(MOTOR_BRAKE_HOLD);
puncher.move_relative(232, maxPower);

}

void puncherPower()
{
  resetPuncher();
  puncher.set_brake_mode(MOTOR_BRAKE_HOLD);
  puncher.move_absolute(pullback, 200);
  setPullback = pullback;
}

void resetPuncher()
{
  puncher.tare_position();
}

int getPuncher()
{
  return puncher.get_position();
}

void puncherOP()
{
  if(controller2.get_digital(DIGITAL_L1))
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
  puncherPower();
  untilAtPullback();
}

void shootAsync()
{
  puncherPower();
}
