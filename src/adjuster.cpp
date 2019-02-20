#include "main.h"
//defines motors
Motor adjuster(11, MOTOR_GEARSET_18, 0,  MOTOR_ENCODER_DEGREES);

bool adjusterPos;
void adjusterOP()
{
  adjuster.set_brake_mode(MOTOR_BRAKE_HOLD); 
  if(controller.get_digital(DIGITAL_L2))
  {
    if(adjusterPos)
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
    adjusterPos = !adjusterPos;
  }
}
void adjust(bool high)
{
  adjuster.set_brake_mode(MOTOR_BRAKE_HOLD);
  if(high)
  {
    adjuster.move_velocity(-200);
    delay(300);
    adjuster.move_velocity(0);
  }
  else
  {
    adjuster.move_velocity(200);
    delay(300);
    adjuster.move_velocity(0);
  }
}
