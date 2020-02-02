#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_global.h"
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_triport.h"

//The encoder value needed for the robot to point turn one complete circle
#define FULL_CIRCLE 1338

//The encoder value needed for the robot to move forward or backward one complete tile
#define FULL_TILE 745

//The encoder position for the accumulator while stacking cubes
#define STACKING_POS 505

//The encoder position for the accumulator while intaking cubes
#define INTAKING_POS 300

//The encoder value for the lift to reach mid towers
#define MID_POS 200

//The encoder value for the lift to reach low towers
#define LOW_POS 100

vex::brain cortex;   

vex::competition Competition; 

vex::controller joystick (vex::controllerType::primary);   

vex::motor driveFL(vex::PORT9, false);
vex::motor driveFR(vex::PORT8, false);
vex::motor driveBL(vex::PORT6, false);
vex::motor driveBR(vex::PORT7, false);
vex::motor rollerL(vex::PORT4, false);
vex::motor rollerR(vex::PORT2, false);
vex::motor lift(vex::PORT5, false);
vex::motor tilter(vex::PORT3, false);

vex::pot potLift(cortex.ThreeWirePort.A);
vex::pot potTilter(cortex.ThreeWirePort.B);

void drive(int x, int y);
void score();
void descore();
void liftReset(int pos, double speed);
void heightChange();
void accumulatorTo(int pos);
void stack();

void drive_for(int dist, double speed);
void cw_turn_for(int angle, double speed);
void ccw_turn_for(int angle, double speed);
void intake_in(double speed);
void intake_out(double speed);
void intake_stop();
void lift_reset(int pos, double speed);