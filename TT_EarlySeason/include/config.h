vex::brain cortex;   
//this defines the brain - called the default constructor because it does not take in any arguements// 
//for c++, write your code in a condensed form rather than the long form//

vex::competition Competition; 
//default constructor//

vex::controller joystick (vex::controllerType::primary); 
//for controllers, you have to secify the type//  

vex::motor driveFL(vex::PORT1, false);
vex::motor driveFR(vex::PORT2, false);
vex::motor driveBL(vex::PORT3, false);
vex::motor driveBR(vex::PORT4, false);

void drive(int x, int y);
//If you press "alt" and then click the different lines you want to write in, you can write multiple things at once//