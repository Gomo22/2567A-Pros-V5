#include "main.h"
void distanceValues()
{
    /*Create a Label on the currently active screen*/
    lv_obj_t * label1 =  lv_label_create(lv_scr_act(), NULL);

    /*Modify the Label's text*/
    lv_label_set_text(label1, "rightDrive: rightDrive.get_position();");

    /* Align the Label to the center
     * NULL means align on parent (which is the screen now)
     * 0, 0 at the end means an x, y offset after alignment*/
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
}


bool shootLast = false;

//static lv_res_t btn_rel_gyro(lv_obj_t * btn)
//{
//	resetGyro();
//	return LV_RES_OK;
//}

static lv_res_t btn_rel_encoder(lv_obj_t * btn)
{
	resetDrive();
	return LV_RES_OK;
}

void opcontrol() {
  Task intakeTask(intakeTask_fn);
	char lblstring[30] = "";
	setDriveBrake(MOTOR_BRAKE_COAST);
	LV_IMG_DECLARE(sittingfox);

	lv_obj_t * scr = lv_page_create(NULL,NULL);
	lv_scr_load(scr);

	lv_obj_t * labelgyro = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(labelgyro, "Gyro Value");
	// lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);

	lv_obj_t * labelflywheel = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(labelflywheel, labelgyro, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
	lv_label_set_text(labelflywheel, "Flywheel Value");

	lv_obj_t * labelflip = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(labelflip, labelflywheel, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
	lv_label_set_text(labelflip, "Left Distance");

	lv_obj_t * labelsonic = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(labelsonic, labelflip, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
	lv_label_set_text(labelflip, "USonic");

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

//	lv_obj_t * img_src = lv_img_create(lv_scr_act(), NULL);
//	lv_img_set_src(img_src, sittingfox);

	master.print(0,0,"Lets do IT!");
	// master.rumble(". . -");

	while (true) {
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		drive(left,right);

		// left_mtr1.move(left);
		// left_mtr2.move(left);
		// right_mtr1.move(right);
		// right_mtr2.move(right);
		std::string charstring = "Gyro:" + std::to_string(getGyro());
		strcpy(lblstring, charstring.c_str());
		lv_label_set_text(labelgyro, lblstring);
		charstring = "Flywheel:" + std::to_string(getFlyspeed());
		strcpy(lblstring, charstring.c_str());
		lv_label_set_text(labelflywheel, lblstring);
		charstring = "FLeft:" + std::to_string(getDistance());
		strcpy(lblstring, charstring.c_str());
		lv_label_set_text(labelflip, lblstring);
		charstring = "Sonic:" + std::to_string(getUsonic());
		strcpy(lblstring, charstring.c_str());
		lv_label_set_text(labelsonic, lblstring);
		charstring = "Intake Mode:" + std::to_string(getIntakeMode());
		strcpy(lblstring, charstring.c_str());
		lv_label_set_text(labelintake, lblstring);

		// Set the flywheel speed
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
			setFlyspeed(200);
		}
		else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)){
			setFlyspeed(150);
		}
		else if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
			setFlyspeed(0);
		}

		// digital L1 Load ball
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
			loadBalls();
		}

		// digital L2 roller outwards
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
			flipCaps();
		}

		// digital R1 shoot ball
		if(master.get_digital(E_CONTROLLER_DIGITAL_R1) != shootLast){
			shootLast = master.get_digital(E_CONTROLLER_DIGITAL_R1);
			if(shootLast){
				shootBall();
			}
		}

		// digital R2 shut off intake
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
			setIntakeMode(0);
		}

		// digital R2 shut off intake
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)){
			unloadBalls();
		}

		delay(10);
	}
}
