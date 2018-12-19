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
// Controller controller(CONTROLLER_MASTER);

static lv_res_t btn_rel_gyro(lv_obj_t * btn)
{
	return LV_RES_OK;
}

static lv_res_t btn_rel_encoder(lv_obj_t * btn)
{
  getDistance();
  return LV_RES_OK;
}

void opcontrol() {
  char lblstring[30] = "";

  lv_obj_t * scr = lv_page_create(NULL,NULL);
  lv_scr_load(scr);

  lv_obj_t * labelgyro = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(labelgyro, "Gyro Value");
  // lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t * labelflywheel = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(labelflywheel, labelgyro, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_label_set_text(labelflywheel, "Flywheel Value");

  lv_obj_t * labelDrive = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(labelDrive, labelflywheel, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_label_set_text(labelDrive, "Left Distance");

  lv_obj_t * labelsonic = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(labelsonic, labelDrive, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_label_set_text(labelDrive, "USonic");

  lv_obj_t * labelintake = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(labelintake, labelsonic, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_label_set_text(labelintake, "Intake Mode");

  lv_obj_t * btngyro = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_align(btngyro, labelintake, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_btn_set_action(btngyro,LV_BTN_ACTION_CLICK, btn_rel_gyro);
  lv_obj_t * label = lv_label_create(btngyro, NULL);
  lv_label_set_text(label, "Reset\nGyro");

  lv_obj_t * btnencoder = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_align(btnencoder, btngyro, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, 0);
  lv_btn_set_action(btnencoder,LV_BTN_ACTION_CLICK, btn_rel_encoder);
  label = lv_label_create(btnencoder, NULL);
  lv_label_set_text(label, "Reset\nEncoder");
  while(true)
	{
    std::string charstring = "Gyro:";// + std::to_string(getGyro());
    strcpy(lblstring, charstring.c_str());
    lv_label_set_text(labelgyro, lblstring);
    charstring = "Flywheel:";// + std::to_string(getFlyspeed());
    strcpy(lblstring, charstring.c_str());
    lv_label_set_text(labelflywheel, lblstring);
    charstring = "FLeft:" + std::to_string(getDistance());
    strcpy(lblstring, charstring.c_str());
    lv_label_set_text(labelDrive, lblstring);
    charstring = "Sonic:";// + std::to_string(getUsonic());
    strcpy(lblstring, charstring.c_str());
    lv_label_set_text(labelsonic, lblstring);
    charstring = "Intake Mode:";// + std::to_string(getIntakeMode());
    strcpy(lblstring, charstring.c_str());
    lv_label_set_text(labelintake, lblstring);

		driveOP();
    puncherOP();
    intakeOP();
		delay(20);
	}
}
