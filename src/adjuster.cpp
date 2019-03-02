#include "main.h"
//defines motors
Motor adjuster(3, MOTOR_GEARSET_36, 0,  MOTOR_ENCODER_DEGREES);

void adjusterOP()
{
  adjuster.set_brake_mode(MOTOR_BRAKE_HOLD);
  if(controller2.get_digital(DIGITAL_R1))
  {
  adjuster.move(127);
  }
  else if(controller2.get_digital(DIGITAL_R2))
  {
    adjuster.move(-127);
  }
    else
    {
      adjuster.move(0);
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
