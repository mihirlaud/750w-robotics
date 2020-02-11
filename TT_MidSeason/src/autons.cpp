#include "main.h"

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
	
	double maxRate = 120;
	
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
			if(maxRate < 180)
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
			if(maxRate < 130)
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

void imu_turn(double angle) {
	driveFL.tarePosition();
	driveFR.tarePosition();
	driveBL.tarePosition();
	driveBR.tarePosition();
	
	double TARGET = imu.get_rotation() + angle;
	double HALFWAY = imu.get_rotation() + angle / 4;
	
	double currentValue = driveFL.getPosition();
	double currentError = TARGET - currentValue;
	double previousError = 0;
	
	bool accel = true;
	
	double kP  =  1.000;
	double kI  =  0.000;
	double kD  =  5.000;
	
	double maxRate = 90;
	
	while(fabs(currentError) > 5) {
		if(angle > 0 && currentValue > HALFWAY)
			accel = false;
		else if(angle < 0 && currentValue < HALFWAY)
			accel = false;
		
		double p  = kP * currentError;
		double i  = kI;
		double d  = kD * (currentError - previousError);
		
		double command = p + i + d;
		
		if(fabs(command) > maxRate) {
			if(command > 0)
				command = maxRate;
			else
				command = -maxRate;
		}
		
		driveFL.moveVelocity(command);
		driveFR.moveVelocity(-command);
		driveBL.moveVelocity(command);
		driveBR.moveVelocity(-command);
		
		pros::delay(20);
		
		if(accel) {
			if(maxRate < 120)
			maxRate += 10;
		}
		
		currentValue = imu.get_rotation();
		previousError = currentError;
		currentError = TARGET - currentValue;
	
	}
	
	driveFL.moveVelocity(0);
	driveFR.moveVelocity(0);
	driveBL.moveVelocity(0);
	driveBR.moveVelocity(0);
}

void pid_tray(double dist) {
	tray.tarePosition();
	
	double TARGET = tray.getPosition() + dist;
	
	double currentValue = tray.getPosition();
	double currentError = TARGET - currentValue;
	double previousError = 0;
	
	double kP  =  1.000;
	double kI  =  0.000;
	double kD  =  5.000;
	
	double maxRate = 200;
	
	while(fabs(currentError) > 5) {
		
		double p  = kP * currentError;
		double i  = kI;
		double d  = kD * (currentError - previousError);
		
		double command = p + i + d;
		
		if(fabs(command) > maxRate) {
			if(command > 0)
				command = maxRate;
			else
				command = -maxRate;
		}
		
		tray.moveVelocity(command);
		
		pros::delay(20);
		
		currentValue = tray.getPosition();
		previousError = currentError;
		currentError = TARGET - currentValue;
	
	}
	
	tray.moveVelocity(0);
}

int auton_index = 2;
void selector() {
	joystick.clear();
	pros::delay(51);
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
			auton_index = 3;
		} else if(auton_index > 3) {
			redraw = false;
			auton_index = -1;
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
	joystick.rumble(".");
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

void deploy() {
	intake(-100);
	pros::delay(900);
	intake(0);
	reg_drive(-0.30 * ONE_FOOT, 100);
}

void auto_stack() {
	
//	intake(-50);
//	pros::delay(400);
//	intake(0);

	pid_tray(TILTER_FINAL);
	pros::delay(100);
	intake(-30);
	pros::delay(200);
	
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
	deploy();
	lift(-100);
	intake(100);
	pid_drive(4.00 * ONE_FOOT);
	pros::delay(400);
	intake(0);
	pid_drive(-2.80 * ONE_FOOT);
	pid_turn(141.0 * ONE_DEGREE);
	pid_drive(1.40 * ONE_FOOT);

	auto_stack();
	
	pros::delay(200);
	reg_drive(-1.00 * ONE_FOOT, 80);
	intake(0);
	
}


void red_protected() {
	deploy();
	lift(-100);
	intake(100);
	pid_drive(1.60 * ONE_FOOT);
	pros::delay(500);
	pid_turn(-100.0 * ONE_DEGREE);
	pid_drive(1.80 * ONE_FOOT);
	pros::delay(400);
	pid_turn(-60.0 * ONE_DEGREE);
	pid_drive(1.4 * ONE_FOOT);

	auto_stack();
	
	pros::delay(200);
	reg_drive(-1.00 * ONE_FOOT, 50);
	intake(0);
	
}


void blue_unprotected() {
	deploy();
	lift(-100);
	intake(100);
	pid_drive(4.00 * ONE_FOOT);
	pros::delay(400);
	intake(0);
	pid_drive(-2.80 * ONE_FOOT);
	pid_turn(-147.0 * ONE_DEGREE);
	pid_drive(1.40 * ONE_FOOT);

	auto_stack();
	
	pros::delay(200);
	reg_drive(-1.00 * ONE_FOOT, 80);
	intake(0);
	
}

void blue_protected() {
	deploy();
	intake(100);
	pid_drive(1.20 * ONE_FOOT);
	pros::delay(250);
	pid_turn(90.0 * ONE_DEGREE);
	pid_drive(2.00 * ONE_FOOT);
	pros::delay(250);
	pid_turn(45.0 * ONE_DEGREE);
	pid_drive(1.6 * ONE_FOOT);

	auto_stack();
	
	pros::delay(200);
	reg_drive(-1.00 * ONE_FOOT, 50);
	intake(0);
}

void prog_skills() {
	//deploy
	deploy();
	
	//intake preload + line of 4 + auton line cube
	lift(-100);
	intake(100);
	pid_drive(4.60 * ONE_FOOT);
	pros::delay(400);
	intake(0);
	
	//drive back line up with goal zone
	pid_drive(-3.40 * ONE_FOOT);
	pid_turn(141.0 * ONE_DEGREE);
	pid_drive(1.40 * ONE_FOOT);

	//stack 6
	auto_stack();
	pros::delay(200);
	
	//line up with auton line tower
	pid_drive(-2.80 * ONE_FOOT);
	intake(0);
	pid_turn(-141.0 * ONE_DEGREE);
	
	//intake tower cube + score
	intake(100);
	pid_drive(2.40 * ONE_FOOT);
	pros::delay(150);
	intake(0);
	pid_drive(-0.40 * ONE_FOOT);
	tray.moveAbsolute(TILTER_LIFT, 100);
	arm.moveAbsolute(LIFT_LOW, 50);
	pid_drive(0.40 * ONE_FOOT);
	intake(-50);
	pros::delay(1000);
	intake(0);
	
	//reset and line up with red side tower
	arm.moveAbsolute(0, 50);
	tray.moveAbsolute(0, 100);
	pid_drive(-3.40 * ONE_FOOT);
	pid_turn(-90 * ONE_DEGREE);
	
	//intake tower cube + score
	intake(100);
	pid_drive(2.40 * ONE_FOOT);
	pros::delay(150);
	intake(0);
	pid_drive(-0.40 * ONE_FOOT);
	tray.moveAbsolute(TILTER_LIFT, 100);
	arm.moveAbsolute(LIFT_MID, 50);
	pid_drive(0.40 * ONE_FOOT);
	intake(-50);
	pros::delay(1000);
	intake(0);
	
	//reset and line up with line of 3
	arm.moveAbsolute(0, 50);
	tray.moveAbsolute(0, 100);
	pid_drive(-1.40 * ONE_FOOT);
	pid_turn(90 * ONE_DEGREE);
	
	//intake cube + line up with alliance tower
	intake(100);
	pid_drive(1.20 * ONE_FOOT);
	pros::delay(250);
	intake(0);
	pid_drive(-0.20 * ONE_FOOT);
	pid_turn(90 * ONE_DEGREE);
	
	//score alliance tower
	pid_drive(3.60 * ONE_FOOT);
	tray.moveAbsolute(TILTER_LIFT, 100);
	arm.moveAbsolute(LIFT_MID, 50);
	pid_drive(0.40 * ONE_FOOT);
	intake(-50);
	pros::delay(1000);
	intake(0);
	pid_drive(-0.40 * ONE_FOOT);
}