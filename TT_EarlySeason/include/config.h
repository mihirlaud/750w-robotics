//The encoder value needed for the robot to point turn one complete circle
#define FULL_CIRCLE 1100

//The encoder value needed for the robot to move forward or backward one complete tile
#define FULL_TILE 660

//The encoder position for the accumulator while stacking cubes
#define STACKING_POS -200

//The encoder position for the accumulator while intaking cubes
#define INTAKING_POS 300

//The encoder value for the lift to reach high towers
#define HIGH_POS 300

//The encoder value for the lift to reach mid towers
#define MID_POS 200

//The encoder value for the lift to reach low towers
#define LOW_POS 100

vex::brain cortex;   
//this defines the brain - called the default constructor because it does not take in any arguements// 
//for c++, write your code in a condensed form rather than the long form//

vex::competition Competition; 
//default constructor//

vex::controller joystick (vex::controllerType::primary); 
//for controllers, you have to specify the type//  

vex::motor driveFL(vex::PORT20, false);
vex::motor driveFR(vex::PORT3, false);
vex::motor driveBL(vex::PORT4, false);
vex::motor driveBR(vex::PORT5, false);
vex::motor intakeL(vex::PORT11, false);
vex::motor intakeR(vex::PORT3, false);
vex::motor liftL(vex::PORT2, false);
vex::motor liftR(vex::PORT10, false);

vex::pot potentiometerL(cortex.ThreeWirePort.A);
vex::pot potentiometerR(cortex.ThreeWirePort.B);

void drive(int x, int y);
void tower(int mode, int type);
void stack();

void drive_for(int dist, double speed);
void cw_turn_for(int angle, double speed);
void ccw_turn_for(int angle, double speed);
void intake_in(double speed);
void intake_out(double speed);
void intake_stop();
void accumulator_to(int pos, double speed);
void lift_reset(double speed);