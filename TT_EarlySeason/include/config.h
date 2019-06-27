vex::brain cortex;
vex::competition Competition;
vex::controller joystick(vex::controllerType::primary);

vex::motor driveFL(vex::PORT1, false);
vex::motor driveFR(vex::PORT2, false);
vex::motor driveBL(vex::PORT3, false);
vex::motor driveBR(vex::PORT4, false);

void drive(int x, int y);