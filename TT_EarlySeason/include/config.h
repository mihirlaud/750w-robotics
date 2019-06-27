vex::brain cortex;   
//this defines the brain - called the default constructor because it does not take in any arguements// 
//for c++, write your code in a condensed form rather than the long form//

vex::competition Competition; 
//default constructor//

vex::controller joystick (vex::controllerType::primary); 
//for controllers, you have to secify the type//  

vex::motor drive_motor_1 (vex::PORT1);
vex::motor drive_motor_2 (vex::PORT2);
vex::motor drive_motor_3 (vex::PORT3);
vex::motor drive_motor_4 (vex::PORT4);  

void drive(int x, int y);
//If you press "alt" and then click the different lines you want to write in, you can write multiple things at once//