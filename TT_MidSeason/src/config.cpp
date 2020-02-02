#include "main.h"

okapi::Motor driveFL(FRONT_LEFT_DRIVE, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor driveFR(FRONT_RIGHT_DRIVE, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor driveBL(BACK_LEFT_DRIVE, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor driveBR(BACK_RIGHT_DRIVE, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor tray(TRAY, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor arm(ARM, true, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor rollerL(LEFT_ROLLER, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor rollerR(RIGHT_ROLLER, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);

okapi::Controller joystick;

okapi::ControllerButton l1(okapi::ControllerDigital::L1);
okapi::ControllerButton l2(okapi::ControllerDigital::L2);
okapi::ControllerButton r1(okapi::ControllerDigital::R1);
okapi::ControllerButton shift(okapi::ControllerDigital::R2);
okapi::ControllerButton x(okapi::ControllerDigital::X);
okapi::ControllerButton a(okapi::ControllerDigital::A);
okapi::ControllerButton y(okapi::ControllerDigital::Y);
okapi::ControllerButton left(okapi::ControllerDigital::left);
okapi::ControllerButton right(okapi::ControllerDigital::right);

std::shared_ptr<okapi::ChassisController> chassis = okapi::ChassisControllerBuilder()
	.withMotors(okapi::MotorGroup({driveBL, driveFL}), okapi::MotorGroup({driveBR, driveFR}))
	.withDimensions(okapi::AbstractMotor::gearset::blue, {{3.25_in, 9.5_in}, 600})
	.withOdometry()
	.buildOdometry();

std::shared_ptr<okapi::AsyncPositionController<double, double>> tilterFast = okapi::AsyncPosControllerBuilder()
	.withMotor(okapi::Motor{tray})
	.withMaxVelocity(100)
	.build();

std::shared_ptr<okapi::AsyncPositionController<double, double>> tilterSlow = okapi::AsyncPosControllerBuilder()
	.withMotor(okapi::Motor{tray})
	.withMaxVelocity(40)
	.build();