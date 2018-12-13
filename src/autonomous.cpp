#include "main.h"

void blueBackCaps()
{

  //drives to cap and flips it
  suck(800); //run suck before drive to have it run while drive
  drive(40);
  //reverse and turn to next cap
  drive(-24);
  turn(45);
  //drives to cap and flips it
  suck(800);
  drive(24);
}

void autonomous()
{
  LV_IMG_DECLARE(drow);
  lv_obj_t * imgDrow = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(imgDrow, &drow);

}
