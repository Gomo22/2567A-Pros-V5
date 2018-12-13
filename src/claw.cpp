#include "main.h"

static int hardHold = 200;
static int softHold = 50;
static int noHold = 0;
Motor claw (7, E_MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

void clawOP()
{
  if(controller.get_digital(DIGITAL_R1))
  {
  claw.move(hardHold);
  }
    else if(controller.get_digital(DIGITAL_R2))
  {
  claw.move(-hardHold);
  }
  else
  {
    claw.move(noHold);
  }
  if(controller.get_digital(DIGITAL_R2) == 0  && controller.get_digital(DIGITAL_R1) == 0)
  {
  claw.set_brake_mode(MOTOR_BRAKE_HOLD);
  }
  else
  {
    claw.set_brake_mode(MOTOR_BRAKE_COAST);
  }
}

void grab ()
{

}

void grabHold()
{

}

void distanceValues(void)
{
    /*Create a Label on the currently active screen*/
    lv_obj_t * label1 =  lv_label_create(lv_scr_act(), NULL);

    /*Modify the Label's text*/
    lv_label_set_text(label1, "rightDrive:");

    /* Align the Label to the center
     * NULL means align on parent (which is the screen now)
     * 0, 0 at the end means an x, y offset after alignment*/
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
}
