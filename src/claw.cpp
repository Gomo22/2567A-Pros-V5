#include "main.h"

Motor rotater (10, E_MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES);

static int ClawSpeed = 100;
static int RotateSpeed = 100;

void rotate()
{
  rotater.move_relative(400, RotateSpeed);
  rotater.tare_position();
}

void rotateOP()
{
  rotater.set_voltage_limit(10500);
  rotater.set_current_limit(1000);
  if(controller.get_digital(DIGITAL_L2))
  {
  rotater.move(RotateSpeed);
  }
  else if(controller.get_digital(DIGITAL_L1))
  {
  rotater.move(-RotateSpeed);
  }
  else
  {
    rotater.move(0);
  }

}
