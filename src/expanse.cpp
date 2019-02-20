#include "main.h"

Motor lift(11, MOTOR_GEARSET_18, 0,  MOTOR_ENCODER_DEGREES);

void liftOP()
{
  lift.set_brake_mode(MOTOR_BRAKE_HOLD);
  if(controller.get_digital(DIGITAL_X))
  {
    lift.move_velocity(100);
  }
  else if(controller.get_digital(DIGITAL_Y))
  {
    lift.move_velocity(-100);
  }
  else
  {
    lift.move_velocity(0);
  }
}

void swing(int pos)
{
  lift.set_brake_mode(MOTOR_BRAKE_HOLD);
  pos *= 5;
  lift.move_absolute(pos, 100);
}
