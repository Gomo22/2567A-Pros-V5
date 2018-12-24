#include "main.h"
/*
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}
**/
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
/*
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}
*/
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

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

 static lv_res_t btn_rel_redFront(lv_obj_t * btn)
 {
 	resetPuncher();
 	return LV_RES_OK;
 }

 static lv_res_t btn_rel_blueFront(lv_obj_t * btn)
 {
   blueBackCaps();
   return LV_RES_OK;
 }

void competition_initialize() {

  lv_obj_t * scr = lv_page_create(NULL,NULL);
  lv_scr_load(scr);

  lv_obj_t * btnredFront = lv_btn_create(lv_scr_act(), NULL);
  lv_btn_set_action(btnredFront,LV_BTN_ACTION_CLICK, btn_rel_redFront);
  lv_obj_t * label = lv_label_create(btnredFront, NULL);
  lv_label_set_text(label, "Red\nFront");

  lv_obj_t * btnBlueFront = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_align(btnBlueFront, btnredFront, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, 0);
  lv_btn_set_action(btnBlueFront,LV_BTN_ACTION_CLICK, btn_rel_blueFront);
  label = lv_label_create(btnBlueFront, NULL);
  lv_label_set_text(label, "Blue\nFront");

}
