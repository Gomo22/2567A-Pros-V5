#include "main.h"

Motor Claw (18, E_MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES);


static int ClawSpeed = 100;
static int RotateSpeed = 200;


void grab()
{
 Claw.move(ClawSpeed);
delay(250);
}

void grabHold()
{
Claw.move(ClawSpeed);
delay(250);
Claw.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void release()
{
Claw.move(-ClawSpeed);
delay(250);
}

void clawOP()
  {

    if(controller.get_digital(DIGITAL_Y))
      {
        Claw.move(ClawSpeed);
      }
        else if(controller.get_digital(DIGITAL_A))
          {

            Claw.move(-ClawSpeed);
          }
            else
              {
                Claw.move(0);
              }
              if(controller.get_digital(DIGITAL_L1) == 0 && controller.get_digital(DIGITAL_L2) == 0)
              {

                Claw.set_brake_mode(MOTOR_BRAKE_HOLD);
              }
  }
