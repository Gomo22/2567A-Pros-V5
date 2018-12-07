#include "main.h"

static int fastExpand = 100;
static int slowExpand = 50;
static int lowPost = 300;

Motor lift(4, E_MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

void resetLift()
{
  lift.tare_position();
}

void liftOP()
{
  if(controller.get_digital(DIGITAL_L1))
  {
  lift.move(fastExpand);
  }
  else if(controller.get_digital(DIGITAL_L2))
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
