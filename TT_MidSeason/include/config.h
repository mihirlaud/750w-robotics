#ifndef CONFIG_H
#define CONFIG_H

#include "main.h"

const int FRONT_LEFT_DRIVE = 14;
const int FRONT_RIGHT_DRIVE = 18;
const int BACK_LEFT_DRIVE = 13;
const int BACK_RIGHT_DRIVE = 19;
const int TRAY = 17;
const int ARM = 4;
const int LEFT_ROLLER = 15;
const int RIGHT_ROLLER = 16;
const int IMU_PORT = 7;

const double TILTER_LIFT = 350;
const double LIFT_LOW = 410;
const double LIFT_MID = 500;

const double TILTER_MID = 700;
const double TILTER_FINAL = 820;
const double ONE_FOOT = 1250 / 2;
const double ONE_DEGREE = 1675 / 360;

extern okapi::Motor driveFL;
extern okapi::Motor driveFR;
extern okapi::Motor driveBL;
extern okapi::Motor driveBR;
extern okapi::Motor tray;
extern okapi::Motor arm;
extern okapi::Motor rollerL;
extern okapi::Motor rollerR;

extern okapi::Controller joystick;

extern okapi::ControllerButton l1;
extern okapi::ControllerButton l2;
extern okapi::ControllerButton r1;
extern okapi::ControllerButton shift;
extern okapi::ControllerButton x;
extern okapi::ControllerButton a;
extern okapi::ControllerButton y;
extern okapi::ControllerButton b;
extern okapi::ControllerButton left;
extern okapi::ControllerButton right;

extern pros::Imu imu;

extern std::shared_ptr<okapi::ChassisController> chassis;
extern std::shared_ptr<okapi::AsyncPositionController<double, double>> tilterFast;
extern std::shared_ptr<okapi::AsyncPositionController<double, double>> tilterSlow;

void tilter(double speed);
void lift(double speed);
void intake(double speed);
void reg_drive(double distance, double speed);
void reg_turn(double angle, double speed);
void pid_drive(double dist);
void pid_turn(double dist);
void imu_turn(double angle);
void pid_tray(double dist);

extern int auton_index;
void selector();
void deploy();
void auto_stack();
void testing();
void red_unprotected();
void red_protected();
void blue_unprotected();
void blue_protected();
void prog_skills();

void macro_stack();
extern int lift_stage;
void macro_lift();

#endif // CONFIG_H