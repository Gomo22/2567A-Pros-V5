#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
Controller controller(CONTROLLER_MASTER);
Controller controller2(CONTROLLER_PARTNER);

static lv_res_t btn_rel_puncher(lv_obj_t * btn)
{
	resetPuncher();
	return LV_RES_OK;
}

static lv_res_t btn_rel_encoder(lv_obj_t * btn)
{
  resetDrive();
  return LV_RES_OK;
}

void opcontrol() {
  char lblstring[30] = "";

  lv_obj_t * scr = lv_page_create(NULL,NULL);
  lv_scr_load(scr);

  lv_obj_t * labelbattery = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(labelbattery, "Battery Level");
  // lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t * labelpuncher = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(labelpuncher, labelbattery, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_label_set_text(labelpuncher, "Puncher Distance");

  lv_obj_t * labelDrive = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(labelDrive, labelpuncher, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_label_set_text(labelDrive, "Left Distance");

  lv_obj_t * labellift = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(labellift, labelDrive, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_label_set_text(labelDrive, "Lift RPM");

  lv_obj_t * btnpuncher = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_align(btnpuncher, labellift, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_btn_set_action(btnpuncher,LV_BTN_ACTION_CLICK, btn_rel_puncher);
  lv_obj_t * label = lv_label_create(btnpuncher, NULL);
  lv_label_set_text(label, "Reset\nPuncher");

  lv_obj_t * btnencoder = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_align(btnencoder, btnpuncher, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, 0);
  lv_btn_set_action(btnencoder,LV_BTN_ACTION_CLICK, btn_rel_encoder);
  label = lv_label_create(btnencoder, NULL);
  lv_label_set_text(label, "Reset\nDrive");
  while(true)
	{
    std::string charstring = "Battery Level:" + std::to_string(getBatteryLevel());
    strcpy(lblstring, charstring.c_str());
    lv_label_set_text(labelbattery, lblstring);
    charstring = "Puncher: " + std::to_string(getPuncher());
    strcpy(lblstring, charstring.c_str());
    lv_label_set_text(labelpuncher, lblstring);
    charstring = "FLeft: " + std::to_string(getDistance());
    strcpy(lblstring, charstring.c_str());
    lv_label_set_text(labelDrive, lblstring);
    charstring = "LiftRPM: " + std::to_string(getLiftRPM());
    strcpy(lblstring, charstring.c_str());
    lv_label_set_text(labellift, lblstring);

		if(controller.get_digital(DIGITAL_LEFT) && !competition::is_connected())
		autonomous();
		driveOP();
    puncherOP();
    intakeOP();
		liftOP();
		rotateOP();
		printf("%d\n", autonFar.get_value());
		delay(20);
	}
}
