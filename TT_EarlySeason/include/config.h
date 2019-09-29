#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_global.h"

//The encoder value needed for the robot to point turn one complete circle
#define FULL_CIRCLE 1100

//The encoder value needed for the robot to move forward or backward one complete tile
#define FULL_TILE 660

//The encoder position for the accumulator while stacking cubes
#define STACKING_POS -200

//The encoder position for the accumulator while intaking cubes
#define INTAKING_POS 300

//The encoder value for the lift to reach mid towers
#define MID_POS 200

//The encoder value for the lift to reach low towers
#define LOW_POS 100

vex::brain cortex;   

vex::competition Competition; 

vex::controller joystick (vex::controllerType::primary);   

vex::motor driveFL(vex::PORT15, false);
vex::motor driveBL(vex::PORT16, false);
vex::motor driveFR(vex::PORT2, false);
vex::motor driveBR(vex::PORT8, false);

vex::motor intakeL(vex::PORT4, false);
vex::motor intakeR(vex::PORT3, false);
vex::motor liftL(vex::PORT20, false);
vex::motor liftR(vex::PORT10, false);

void stack();

void drive_for(int dist, double speed);
void cw_turn_for(int angle, double speed);
void ccw_turn_for(int angle, double speed);
void intake_in(double speed);
void intake_out(double speed);
void intake_stop();
void accumulator_to(int pos, double speed);
void lift_to(int pos, double speed);
void lift_reset(double speed);