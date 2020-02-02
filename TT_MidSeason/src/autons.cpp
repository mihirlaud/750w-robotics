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


void reg_drive(double distance, double speed) {
	chassis->setMaxVelocity(speed * 6);
	chassis->moveRaw(distance);
	chassis->waitUntilSettled();
	chassis->setMaxVelocity(600);
}


void reg_turn(double angle, double speed) {
	chassis->setMaxVelocity(speed * 6);
	chassis->turnRaw(angle);
	chassis->waitUntilSettled();
	chassis->setMaxVelocity(600);
}

void pid_drive(double dist) {
	driveFL.tarePosition();
	driveFR.tarePosition();
	driveBL.tarePosition();
	driveBR.tarePosition();
	
	double TARGET = driveFL.getPosition() + dist;
	double HALFWAY = driveFL.getPosition() + dist / 4;
	
	double currentValue = driveFL.getPosition();
	double currentError = TARGET - currentValue;
	double previousError = 0;
	double difference = driveFL.getPosition() - driveFR.getPosition();
	
	bool accel = true;
	
	double kP  =  2.000;
	double kI  =  0.000;
	double kD  = 10.000;
	double kDr =  0.000;
	
	double maxRate = 90;
	
	while(fabs(currentError) > 20) {
		
		if(dist > 0 && currentValue > HALFWAY)
			accel = false;
		else if(dist < 0 && currentValue < HALFWAY)
			accel = false;
		
		double p  = kP * currentError;
		double i  = kI;
		double d  = kD * (currentError - previousError);
		
		double dr = kDr * difference;
		
		double command = p + i + d;
		
		if(fabs(command) > maxRate) {
			if(command > 0)
				command = maxRate;
			else
				command = -maxRate;
		}
		
		driveFL.moveVelocity(command - dr);
		driveFR.moveVelocity(command + dr);
		driveBL.moveVelocity(command - dr);
		driveBR.moveVelocity(command + dr);
		
		pros::delay(20);
		
		if(accel) {
			if(maxRate < 120)
			maxRate += 10;
		}
		
		currentValue = driveFL.getPosition();
		previousError = currentError;
		currentError = TARGET - currentValue;
	
	}
	
	driveFL.moveVelocity(0);
	driveFR.moveVelocity(0);
	driveBL.moveVelocity(0);
	driveBR.moveVelocity(0);
}

void pid_turn(double angle) {
	driveFL.tarePosition();
	driveFR.tarePosition();
	driveBL.tarePosition();
	driveBR.tarePosition();
	
	double TARGET = driveFL.getPosition() + angle;
	double HALFWAY = driveFL.getPosition() + angle / 4;
	
	double currentValue = driveFL.getPosition();
	double currentError = TARGET - currentValue;
	double previousError = 0;
	double difference = driveFL.getPosition() - driveFR.getPosition();
	
	bool accel = true;
	
	double kP  =  1.000;
	double kI  =  0.000;
	double kD  =  5.000;
	double kDr =  0.000;
	
	double maxRate = 90;
	
	while(fabs(currentError) > 5) {
		if(angle > 0 && currentValue > HALFWAY)
			accel = false;
		else if(angle < 0 && currentValue < HALFWAY)
			accel = false;
		
		double p  = kP * currentError;
		double i  = kI;
		double d  = kD * (currentError - previousError);
		double dr = kDr * difference;
		
		double command = p + i + d;
		
		if(fabs(command) > maxRate) {
			if(command > 0)
			command = maxRate;
			else
			command = -maxRate;
		}
		
		driveFL.moveVelocity(command - dr);
		driveFR.moveVelocity(-(command + dr));
		driveBL.moveVelocity(command - dr);
		driveBR.moveVelocity(-(command + dr));
		
		pros::delay(20);
		
		if(accel) {
			if(maxRate < 120)
			maxRate += 10;
		}
		
		currentValue = driveFL.getPosition();
		previousError = currentError;
		currentError = TARGET - currentValue;
	
	}
	
	driveFL.moveVelocity(0);
	driveFR.moveVelocity(0);
	driveBL.moveVelocity(0);
	driveBR.moveVelocity(0);
}

int auton_index = -1;
void selector() {
	joystick.clear();
	joystick.setText(1, 0, "ONE POINT?");
	bool redraw = false;
	while(!a.changedToPressed()) {
		pros::delay(50);
		if(left.isPressed()) {
			auton_index--;
			redraw = true;
		} else if(right.isPressed()) {
			auton_index++;
			redraw = true;
		}
		
		if(auton_index < -1) {
			redraw = false;
			auton_index = -1;
			joystick.rumble(".");
		} else if(auton_index > 3) {
			redraw = false;
			auton_index = 3;
			joystick.rumble(".");
		}
		
		if(redraw) {
			joystick.clearLine(1);
			switch(auton_index) {
				case -1:
					joystick.setText(1, 0, "ONE POINT?");
					break;
				case 0:
					joystick.setText(1, 0, "RED UNPROT?");
					break;
				case 1:
					joystick.setText(1, 0, "RED PROT?");
					break;
				case 2:
					joystick.setText(1, 0, "BLUE UNPROT?");
					break;
				case 3:
					joystick.setText(1, 0, "BLUE PROT?");
					break;
			}
		}
	}
	joystick.clear();
	switch(auton_index) {
		case -1:
			joystick.setText(1, 0, "ONE POINT");
			break;
		case 0:
			joystick.setText(1, 0, "RED UNPROT");
			break;
		case 1:
			joystick.setText(1, 0, "RED PROT");
			break;
		case 2:
			joystick.setText(1, 0, "BLUE UNPROT");
			break;
		case 3:
			joystick.setText(1, 0, "BLUE PROT");
			break;
	}
	joystick.setText(2, 0, "SELECTED");
}

void testing() {
	intake(-100);
	pros::delay(500);
	intake(0);
	pros::delay(1000);
	pid_drive(3.00 * ONE_FOOT);
	intake(-100);
	
	pid_drive(-3.00 * ONE_FOOT);
}


void red_unprotected() {
	intake(-100);
	pros::delay(500);
	intake(0);
	//drive(-0.60 * ONE_FOOT, 30);
	intake(100);
	pid_drive(3.50 * ONE_FOOT);
	pros::delay(200);
	intake(0);
	pid_drive(-2.30 * ONE_FOOT);
	pid_turn(141.0 * ONE_DEGREE);
	pid_drive(1.6 * ONE_FOOT);

	intake(-50);
	pros::delay(300);
	intake(0);

	tilterFast->setTarget(TILTER_MID);
	tilterFast->waitUntilSettled();
	tilterSlow->setTarget(TILTER_FINAL);
	tilterSlow->waitUntilSettled();

	intake(-30);
	pros::delay(200);
	intake(0);
	pros::delay(200);
	reg_drive(-1.00 * ONE_FOOT, 50);
	intake(0);
	
}


void red_protected() {}


void blue_unprotected() {
	intake(-100);
	pros::delay(500);
	intake(0);
	//drive(-0.60 * ONE_FOOT, 30);
	intake(100);
	pid_drive(3.50 * ONE_FOOT);
	pros::delay(200);
	intake(0);
	pid_drive(-2.30 * ONE_FOOT);
	pid_turn(-141.0 * ONE_DEGREE);
	pid_drive(1.6 * ONE_FOOT);

	intake(-50);
	pros::delay(300);
	intake(0);

	tilterFast->setTarget(TILTER_MID);
	tilterFast->waitUntilSettled();
	tilterSlow->setTarget(TILTER_FINAL);
	tilterSlow->waitUntilSettled();

	intake(-30);
	pros::delay(200);
	intake(0);
	pros::delay(200);
	reg_drive(-1.00 * ONE_FOOT, 50);
	intake(0);
	
}

void blue_protected() {}