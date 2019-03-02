#include "main.h"

Motor lift(4, MOTOR_GEARSET_18, 0,  MOTOR_ENCODER_DEGREES);

void liftOP()
{
  if(controller.get_digital(DIGITAL_L1))
  {
    lift.set_brake_mode(MOTOR_BRAKE_HOLD);
    lift.move_velocity(-150);
  }
  else if(controller.get_digital(DIGITAL_L2))
  {
    lift.set_brake_mode(MOTOR_BRAKE_COAST);
    lift.move_velocity(150);
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
