#include "main.h"
//defines motors
Motor adjuster(3, MOTOR_GEARSET_18, 0,  MOTOR_ENCODER_DEGREES);

bool adjPos;
void adjusterOP()
{
  adjuster.set_brake_mode(MOTOR_BRAKE_HOLD);
  if(controller.get_digital(DIGITAL_L2))
  {
    if(adjPos)
    {
      adjuster.move_velocity(200);
      delay(300);
      adjuster.move_velocity(0);
    }
    else
    {
      adjuster.move_velocity(-200);
      delay(300);
      adjuster.move_velocity(0);
    }
    adjPos = !adjPos;
  }
}

void doubleShot()
{
  if(controller.get_digital(DIGITAL_A))
  {
    if(adjPos)
    {
      shoot();
      suck(1300);
      delay(100);
      adjuster.move_velocity(200);
      delay(300);
      adjuster.move_velocity(0);
      delay(175);
      shoot();
    }
    else
    {
      shoot();
      suck(700);
      adjuster.move_velocity(-200);
      delay(300);
      adjuster.move_velocity(0);
      shoot();
    }
    adjPos = !adjPos;
  }
}
void adjust(bool high)
{
  adjuster.set_brake_mode(MOTOR_BRAKE_HOLD);
  if(high)
  {
    adjuster.move_velocity(-200);
    delay(500);
    adjuster.move_velocity(0);
  }
  else
  {
    adjuster.move_velocity(200);
    delay(500);
    adjuster.move_velocity(0);
  }
}
