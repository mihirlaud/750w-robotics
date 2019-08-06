vex::brain cortex;   
//this defines the brain - called the default constructor because it does not take in any arguements// 
//for c++, write your code in a condensed form rather than the long form//

vex::competition Competition; 
//default constructor//

vex::controller joystick (vex::controllerType::primary); 
//for controllers, you have to secify the type//  

vex::motor driveFL(vex::PORT20, false);
vex::motor driveFR(vex::PORT7, false);
vex::motor driveBL(vex::PORT19, false);
vex::motor driveBR(vex::PORT9, false);
vex::motor rollerL(vex::PORT11, false);
vex::motor rollerR(vex::PORT3, false);
vex::motor spine(vex::PORT2, false);

void drive(int x, int y);
bool speedChange(bool newSpeed);
//If you press "alt" and then click the different lines you want to write in, you can write multiple things at once//