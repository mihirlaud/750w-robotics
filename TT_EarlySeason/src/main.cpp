//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
#include "vex.h"
#include "Robot.h"
#include "config.h"
#include "auton_selector.h"
#include <cmath>

using namespace vex;

bool height = false; //False = Low; True = Mid
bool slow = false; //False = Slow; True = Fast;

int auton_index = -1;
void pre_auton( void ) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  // AutonSelector selector(cortex);
  
  // selector.addRedOption("GOAL SIDE", 0)
  //         .addRedOption("ALLIANCE TOWER SIDE", 1)
  //         .addBlueOption("GOAL SIDE", 2)
  //         .addBlueOption("ALLIANCE TOWER SIDE", 3);
  
  // auton_index = selector.getCode();
  // spine.resetRotation();

  lift.resetRotation();
  tilter.resetRotation();
}

void drive_for(int dist, double speed=60) {
  driveFL.rotateFor(vex::directionType::fwd, dist, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveFR.rotateFor(vex::directionType::fwd, -dist, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBL.rotateFor(vex::directionType::fwd, dist, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBR.rotateFor(vex::directionType::fwd, -dist, rotationUnits::deg, speed, velocityUnits::pct, true);

  task::sleep(250);
}

void cw_turn_for(int angle, double speed=60) {
  driveFL.rotateFor(vex::directionType::fwd, angle, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveFR.rotateFor(vex::directionType::fwd, angle, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBL.rotateFor(vex::directionType::fwd, angle, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBR.rotateFor(vex::directionType::fwd, angle, rotationUnits::deg, speed, velocityUnits::pct, true);
  task::sleep(250);
}

void ccw_turn_for(int angle, double speed=60) {
  cw_turn_for(-angle, speed);
}

void intake_in(double speed=50) {
  rollerL.setVelocity(speed, vex::percentUnits::pct);
  rollerR.setVelocity(-speed, vex::percentUnits::pct);
  
  rollerL.spin(vex::directionType::fwd);
  rollerR.spin(vex::directionType::fwd);
}

void intake_out(double speed=50) {
  rollerL.setVelocity(-speed, vex::percentUnits::pct);
  rollerR.setVelocity(speed, vex::percentUnits::pct);
  
  rollerL.spin(vex::directionType::fwd);
  rollerR.spin(vex::directionType::fwd);
}

void intake_stop() {  
  rollerL.stop(vex::brakeType::hold);
  rollerR.stop(vex::brakeType::hold);
}

void accumulator_to(int pos, double speed) {
  tilter.rotateTo(pos, rotationUnits::deg, speed, velocityUnits::pct, true);
}

void autonomous( void ) {
  auton_index = 3;
  switch(auton_index) {
    case -1: //TESTING AUTON

      drive_for(.30 * FULL_TILE);
      intake_out();
      vex::task::sleep(800);
      intake_stop();

      break;
    case 0: //RED GOAL SIDE

      drive_for(0.30 * FULL_TILE, 70);
      accumulatorTo(INTAKING_POS);
      drive_for(0.20 * FULL_TILE);
      intake_in();
      drive_for(1.0 * FULL_TILE, 20);
      intake_stop();

      break;
    case 1: //RED TOWER SIDE
      intake_in(80);
      drive_for(1.65 * FULL_TILE, 50);
      intake_in(30);
      drive_for(-1.70 * FULL_TILE, 80);
      drive_for(0.730 * FULL_TILE, 80);
      cw_turn_for(0.360 * FULL_CIRCLE, 15);
      drive_for(0.530 * FULL_TILE, 40);
      intake_stop();
      task::sleep(150);
      intake_out(30);
      task::sleep(500);
      intake_stop();
      drive_for(0.150 * FULL_TILE, 10);
      tilter.spin(directionType::fwd, 100, velocityUnits::pct);
      task::sleep(750);
      tilter.stop(brakeType::hold);
      task::sleep(250);
      drive_for(0.150 * FULL_TILE, 20);
      intake_out(40);
      task::sleep(100);
      drive_for(-0.500 * FULL_TILE, 30);
      break;
    case 2: //BLUE GOAL SIDE
      break;
    case 3: //BLUE TOWER SIDE
      intake_in(70);
      drive_for(1.65 * FULL_TILE, 50);
      intake_stop();
      drive_for(-1.70 * FULL_TILE, 80);
      drive_for(0.730 * FULL_TILE, 80);
      ccw_turn_for(0.360 * FULL_CIRCLE, 15);
      drive_for(0.530 * FULL_TILE, 40);
      intake_stop();
      task::sleep(150);
      intake_out(30);
      task::sleep(500);
      intake_stop();
      tilter.spin(directionType::fwd, 100, velocityUnits::pct);
      task::sleep(1100);
      tilter.stop(brakeType::hold);
      task::sleep(250);
      drive_for(0.150 * FULL_TILE, 20);
      intake_out(40);
      task::sleep(100);
      drive_for(-0.500 * FULL_TILE, 30);
      break;
  }
}

void usercontrol( void ) {

  while (1) {

    drive( joystick.Axis3.position(), joystick.Axis1.position() );


    if(joystick.ButtonR1.pressing()){
      rollerL.setVelocity(100, vex::percentUnits::pct);
      rollerR.setVelocity(-100, vex::percentUnits::pct);

      rollerL.spin(vex::directionType::fwd);
      rollerR.spin(vex::directionType::fwd);
    }
    else if(joystick.ButtonR2.pressing()){
      rollerL.setVelocity(-100, vex::percentUnits::pct);
      rollerR.setVelocity(100, vex::percentUnits::pct);

      rollerL.spin(vex::directionType::fwd);
      rollerR.spin(vex::directionType::fwd);
    }
    else{
      rollerL.stop(vex::brakeType::hold);
      rollerR.stop(vex::brakeType::hold);
    }

    if(joystick.ButtonL2.pressing()) {
      tilter.spin(vex::directionType::fwd, 30, vex::percentUnits::pct);
    } 
    else if(joystick.ButtonL1.pressing()) {  
      tilter.spin(vex::directionType::fwd, -30, vex::percentUnits::pct);
    }
    else {
      tilter.stop(vex::brakeType::hold);
    }

    if(joystick.ButtonX.pressing()){
      lift.setVelocity(-40, vex::percentUnits::pct);

      lift.spin(vex::directionType::fwd);
    }
    else if(joystick.ButtonB.pressing()){
      lift.setVelocity(40, vex::percentUnits::pct);

      lift.spin(vex::directionType::fwd);
    }
    else{
      lift.stop(vex::brakeType::hold);
    }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

void drive(int x, int y) {

  if(!slow) {
    driveFL.setVelocity(y + x, vex::percentUnits::pct);
    driveFR.setVelocity(y - x, vex::percentUnits::pct);
    driveBL.setVelocity(y + x, vex::percentUnits::pct);
    driveBR.setVelocity(y - x, vex::percentUnits::pct);
  }
  else {
    driveFL.setVelocity((y + x)/2, vex::percentUnits::pct);
    driveFR.setVelocity((y - x)/2, vex::percentUnits::pct);
    driveBL.setVelocity((y + x)/2, vex::percentUnits::pct);
    driveBR.setVelocity((y - x)/2, vex::percentUnits::pct);
  }
 /*
    driveFL.setVelocity(100-(sqrt(10000-(pow(y+x,2)))), vex::percentUnits::pct);
    driveFR.setVelocity(100-(sqrt(10000-(pow(y+x,2)))), vex::percentUnits::pct);
    driveBL.setVelocity(100-(sqrt(10000-(pow(y+x,2)))), vex::percentUnits::pct);
    driveBR.setVelocity(100-(sqrt(10000-(pow(y+x,2)))), vex::percentUnits::pct);
*/
    driveFL.spin(directionType::fwd);
    driveFR.spin(directionType::fwd);
    driveBL.spin(directionType::fwd);
    driveBR.spin(directionType::fwd);
}

void score() {

double val = potLift.value(vex::rotationUnits::deg);

  if(height) {
      while( fabs( (MID_POS - val)) > .1 ){
        val = potLift.value(vex::rotationUnits::deg);

        double mid_error = MID_POS - val;

        double mid_kP = .100;

        lift.setVelocity(mid_error * mid_kP, vex::percentUnits::pct);
      }
        lift.stop(vex::brakeType::hold);

        intake_in();
        vex::task::sleep(800);
        intake_stop();

        liftReset(MID_POS, 50);
  }
    else {
      while( fabs( (LOW_POS - val)) > .1 ){
        val = potLift.value(vex::rotationUnits::deg);

        double low_error = LOW_POS - val;

        double low_kP = .100;

        lift.setVelocity(low_error * low_kP, vex::percentUnits::pct);
      }
        lift.stop(vex::brakeType::hold);

        intake_in();
        vex::task::sleep(800);
        intake_stop();

        liftReset(LOW_POS, 50);
    }
}

void descore() {

double val = potLift.value(vex::rotationUnits::deg);

  if(height) {
      while( fabs( (MID_POS - val)) > .1 ){
        val = potLift.value(vex::rotationUnits::deg);

        double mid_error = MID_POS - val;

        double mid_kP = .100;

        lift.setVelocity(mid_error * mid_kP, vex::percentUnits::pct);
      }
        lift.stop(vex::brakeType::hold);

        intake_out();
        vex::task::sleep(800);
        intake_stop();

        liftReset(MID_POS, 50);
  }
    else {
      while( fabs( (LOW_POS - val)) > .1 ){
        val = potLift.value(vex::rotationUnits::deg);

        double low_error = LOW_POS - val;

        double low_kP = .100;

        lift.setVelocity(low_error * low_kP, vex::percentUnits::pct);
      }
        lift.stop(vex::brakeType::hold);

        intake_out();
        vex::task::sleep(800);
        intake_stop();

        liftReset(LOW_POS, 50);
    }
}

void liftReset(int pos, double speed) {
  double val = potLift.value(vex::rotationUnits::deg);

  while(val > 10){
  lift.spin(vex::directionType::fwd);
  }
}

void heightChange() {
  
  height = !height;
  
  if(height)
    joystick.Screen.print("Mid");
  else
    joystick.Screen.print("Low");

}

void accumulatorTo(int pos){

double val = potLift.value(vex::rotationUnits::deg);

      while( fabs( (pos - val)) > .1 ){
        val = potTilter.value(vex::rotationUnits::deg);

        double tilter_error = pos - val;

        double tilter_kP = .100;

        tilter.setVelocity(tilter_error * tilter_kP, vex::percentUnits::pct);
      }
        tilter.stop(vex::brakeType::hold);

}

void stack() {  

  drive_for(0.93 * FULL_TILE);
  accumulatorTo(STACKING_POS);
  intake_out(20);
  task::sleep(800);
  drive_for(-1.0 * FULL_TILE, 20);
  accumulatorTo(INTAKING_POS);

}

void speedChange() {
  
  slow = !slow;

  if(slow)
    joystick.Screen.print("Slow");
  else
    joystick.Screen.print("Fast");
}


// Main will set up the competition functions and callbacks.
int main() {
    //Callback Macros
    //joystick.ButtonUp.pressed(stack);
    //joystick.ButtonX.pressed(heightChange);
    //joystick.ButtonL1.pressed(score);
    //joystick.ButtonL2.pressed(descore);
    joystick.ButtonUp.pressed(speedChange);

    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      cortex.Screen.printAt(1, 20, "rotation: %f degrees", potTilter.value(rotationUnits::deg));
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}



