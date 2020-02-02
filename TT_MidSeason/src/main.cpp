#include "main.h"

void initialize() {
	//pros::lcd::initialize();

	tray.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	arm.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	rollerL.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	rollerR.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

	tray.tarePosition();
	arm.tarePosition();
	
	selector();
}

void autonomous() {
	switch(auton_index) {
		case -1:
			testing();
			break;
		case 0:
			red_unprotected();
			break;
		case 1:
			red_protected();
			break;
		case 2:
			blue_unprotected();
			break;
		case 3:
			blue_protected();
			break;
	}
}


void macro(/*int stage*/) {

	if(fabs(TILTER_LIFT - tray.getPosition() > 50)) {
		tray.moveAbsolute(TILTER_LIFT, 100);
	}
	else {
		tray.moveAbsolute(0, 100);
	}

	// switch(stage) {
	// 	case 0:
	// 		arm.moveAbsolute(LIFT_LOW, 100);
	// 		count++;
	// 		break;
	// 	case 1:
	// 		arm.moveAbsolute(LIFT_MID, 100);
	// 		count++;
	// 		break;
	// 	case 2:
	// 		arm.moveAbsolute(-6, 100);
	// 		// tray.moveAbsolute(0, 100);
	// 		count = 0;
	// 		break;
	// }
}

void opcontrol() {
	
	bool l1_RELEASED, l2_RELEASED;
	int count = 0;
	while(true) {
		pros::lcd::clear_line(1);
		pros::lcd::set_text(1, std::to_string(tray.getPosition()));
		pros::lcd::clear_line(2);
		pros::lcd::set_text(2, std::to_string(arm.getPosition()));

		chassis->getModel()->arcade(
			joystick.getAnalog(okapi::ControllerAnalog::leftY),
			joystick.getAnalog(okapi::ControllerAnalog::rightX)
		);

		l1_RELEASED = l1.changedToReleased();
		l2_RELEASED = l2.changedToReleased();

		if(l1.isPressed() && l2.isPressed() && !(shift.isPressed())) {
			tilter(60);
		}
		else if(l2.isPressed() && !(shift.isPressed())) {
			tilter(100);
		}
		else if(l1.isPressed() && !(shift.isPressed())) {
			tilter(-100);
		}
		if(l1_RELEASED || l2_RELEASED) {
			if(tray.getPosition() < 0) {
				tray.tarePosition();
			}

			tilter(0);
		}


		if(l2.isPressed() && shift.isPressed()) {
			lift(100);
		}
		else if(l1.isPressed() && shift.isPressed()) {
			lift(-100);
		}
		if(l1_RELEASED || l2_RELEASED) {
			lift(0);
		}


		if(r1.isPressed() && shift.isPressed()) {
			intake(-70);
		}
		else if(r1.isPressed()) {
			intake(100);
		}
		else if(x.isPressed()) {
			intake(-100);
		}
		else if(y.isPressed()) {
			intake(-30);
		}
		else {
			intake(0);
		}


		if(a.changedToPressed()) {
			if(tray.getPosition() < 0) {
				tray.tarePosition();
			}

			macro(/*count*/);
		}


		pros::delay(20);
	}
}


void disabled() {}


void competition_initialize() {}
