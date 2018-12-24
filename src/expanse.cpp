#include "main.h"

static int fastExpand = 200;
static int slowExpand = 50;
static int lowPost = 300;

Motor lift(17, E_MOTOR_GEARSET_36, 0, MOTOR_ENCODER_DEGREES);

void resetLift()
{
  lift.tare_position();
}

int getLiftRPM()
{
  return lift.get_actual_velocity();
}

void liftOP()
{
  if(controller.get_digital(DIGITAL_X))
  {
  lift.move(fastExpand);
  }
  else if(controller.get_digital(DIGITAL_B))
  {
  lift.move(-fastExpand);
  }
  else
  {
    lift.move(0);
  }

}

void expand(bool up, int height)
{
  if(up)
  {
  resetLift();
  lift.move_relative(height, slowExpand);
  }
    else
    {
      resetLift();
      lift.move_relative(height, -slowExpand);
    }

}

void lowCap()
{
  resetLift();
  lift.move_relative(lowPost, slowExpand);
}
