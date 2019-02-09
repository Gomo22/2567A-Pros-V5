#include "main.h"

static int fastExpand = 200;
static int slowExpand = 50;
static int lowPost = 300;

Motor lift(1, E_MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

void resetLift()
{
  lift.tare_position();
}

int getLiftRPM()
{
  return lift.get_voltage();
}

int getCurrentDraw()
{
  return lift.get_current_draw();
}

int getTemp()
{
  return lift.get_temperature();
}

void liftOP()
{
  lift.set_current_limit(1550);
  if(controller.get_digital(DIGITAL_R1))
  {
  lift.move(fastExpand);
  }
  else if(controller.get_digital(DIGITAL_R2))
  {
  lift.move(-fastExpand);
  }
  else
  {
    lift.move(0);
  }

}

void liftre(int distance)
{
  while(lift.get_position()< distance )
  {
    lift.move_velocity(200);
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
