#include "main.h"

void tilter(double speed) {
	tray.moveVelocity(speed * 1);
}

void lift(double speed) {
	arm.moveVelocity(speed * 1);
}

void intake(double speed) {
	rollerL.moveVelocity(speed * 2);
	rollerR.moveVelocity(speed * 2);
}

void macro_stack() {
	tilterFast->setTarget(TILTER_MID);
	tilterFast->waitUntilSettled();
	tilterSlow->setTarget(TILTER_FINAL);
	tilterSlow->waitUntilSettled();
}

int lift_stage = 0;
void macro_lift() {
	lift_stage++;
	if(lift_stage > 2) lift_stage = 0;
	switch(lift_stage) {
		case 0:
			arm.moveAbsolute(0, 100);
			//pros::delay(500);
			//tray.moveAbsolute(0, 100);
			break;
		case 1:
			//tray.moveAbsolute(TILTER_LIFT, 100);
			//pros::delay(250);
			arm.moveAbsolute(LIFT_LOW, 100);
			break;
		case 2:
			arm.moveAbsolute(LIFT_MID, 50);
			break;
	}
	
}