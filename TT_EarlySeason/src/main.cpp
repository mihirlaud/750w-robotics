#include "vex.h"
#include "Robot.h"
#include "config.h"
#include "auton_selector.h"
#include <cmath>

bool slowDrive = false;

using namespace vex;

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

  liftL.resetRotation();
  liftR.resetRotation();
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
  intakeL.setVelocity(speed, vex::percentUnits::pct);
  intakeR.setVelocity(-speed, vex::percentUnits::pct);
  
  intakeL.spin(vex::directionType::fwd);
  intakeR.spin(vex::directionType::fwd);
}

void intake_out(double speed=50) {
  intakeL.setVelocity(-speed, vex::percentUnits::pct);
  intakeR.setVelocity(speed, vex::percentUnits::pct);
  
  intakeL.spin(vex::directionType::fwd);
  intakeR.spin(vex::directionType::fwd);
}

void intake_stop() {  
  intakeL.stop(vex::brakeType::hold);
  intakeR.stop(vex::brakeType::hold);
}

void accumulator_to(int pos, double speed=50) {
  driveFL.rotateFor(pos, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveFR.rotateFor(pos, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBL.rotateFor(-pos, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBR.rotateFor(-pos, rotationUnits::deg, speed, velocityUnits::pct, true);

  task::sleep(250);
}

void lift_to(int pos, double speed=50) {
  liftL.rotateTo(pos, rotationUnits::deg, speed, velocityUnits::pct, false);
  liftR.rotateTo(pos, rotationUnits::deg, speed, velocityUnits::pct, false);

  task::sleep(250);
}

void lift_reset(double speed=50) {
  liftL.rotateTo(0, rotationUnits::deg, speed, velocityUnits::pct, false);
  liftR.rotateTo(0, rotationUnits::deg, speed, velocityUnits::pct, true);

  task::sleep(250);
}

void autonomous( void ) {
  
  switch(auton_index) {
    case -1: //TESTING AUTON
      break;
    case 0: //RED GOAL SIDE

      drive_for(0.30 * FULL_TILE, 70);
      accumulator_to(INTAKING_POS);
      drive_for(0.20 * FULL_TILE);
      intake_in();
      drive_for(1.0 * FULL_TILE, 20);
      intake_stop();

      break;
    case 1: //RED TOWER SIDE
      break;
    case 2: //BLUE GOAL SIDE
      break;
    case 3: //BLUE TOWER SIDE
      break;
  }
}

void usercontrol( void ) {

  while (1) {

    if(joystick.ButtonA.pressing()){
      vex::task::sleep(100);

      slowDrive = !slowDrive;
    }

    if(joystick.ButtonL1.pressing()){
      vex::task::sleep(100);

      lift_to(LOW_POS);
      
      liftL.stop(vex::brakeType::hold);
      liftR.stop(vex::brakeType::hold);
    }

    if(joystick.ButtonL2.pressing()){
      vex::task::sleep(100);

      lift_to(MID_POS);

      liftL.stop(vex::brakeType::hold);
      liftR.stop(vex::brakeType::hold);
    }

    if(joystick.ButtonR1.pressing()){
      intakeL.setVelocity(70, vex::percentUnits::pct);
      intakeR.setVelocity(-70, vex::percentUnits::pct);

      intakeL.spin(vex::directionType::fwd);
      intakeR.spin(vex::directionType::fwd);
    }
    else if(joystick.ButtonR2.pressing()){
      intakeL.setVelocity(-70, vex::percentUnits::pct);
      intakeR.setVelocity(70, vex::percentUnits::pct);

      intakeL.spin(vex::directionType::fwd);
      intakeR.spin(vex::directionType::fwd);
    }
    else{
      intakeL.stop(vex::brakeType::hold);
      intakeR.stop(vex::brakeType::hold);
    }

    if(joystick.ButtonLeft.pressing()) {
      driveFL.spin(vex::directionType::fwd, 25, vex::percentUnits::pct);
      driveBL.spin(vex::directionType::fwd, 25, vex::percentUnits::pct);
      driveFR.spin(vex::directionType::rev, 25, vex::percentUnits::pct);
      driveBR.spin(vex::directionType::rev, 25, vex::percentUnits::pct);
    } 
    else if(joystick.ButtonRight.pressing()) {  
      driveFL.spin(vex::directionType::fwd, -25, vex::percentUnits::pct);
      driveBL.spin(vex::directionType::fwd, -25, vex::percentUnits::pct);
      driveFR.spin(vex::directionType::rev, -25, vex::percentUnits::pct);
      driveBR.spin(vex::directionType::rev, -25, vex::percentUnits::pct);
    }
    else if(slowDrive) {
      driveFL.spin(vex::directionType::fwd, (joystick.Axis3.position(vex::percentUnits::pct)  + joystick.Axis1.position(vex::percentUnits::pct))/3.0, vex::percentUnits::pct);
      driveBL.spin(vex::directionType::fwd, (-joystick.Axis3.position(vex::percentUnits::pct) - joystick.Axis1.position(vex::percentUnits::pct))/3.0, vex::percentUnits::pct);
      driveFR.spin(vex::directionType::rev, (joystick.Axis3.position(vex::percentUnits::pct)  - joystick.Axis1.position(vex::percentUnits::pct))/3.0, vex::percentUnits::pct);
      driveBR.spin(vex::directionType::rev, (-joystick.Axis3.position(vex::percentUnits::pct) + joystick.Axis1.position(vex::percentUnits::pct))/3.0, vex::percentUnits::pct);
    
      joystick.Screen.clearScreen();
      joystick.Screen.print("Slow");
    }
    else {
      driveFL.spin(vex::directionType::fwd, joystick.Axis3.position(vex::percentUnits::pct)  + joystick.Axis1.position(vex::percentUnits::pct), vex::percentUnits::pct);
      driveBL.spin(vex::directionType::fwd, -joystick.Axis3.position(vex::percentUnits::pct) - joystick.Axis1.position(vex::percentUnits::pct), vex::percentUnits::pct);
      driveFR.spin(vex::directionType::rev, joystick.Axis3.position(vex::percentUnits::pct)  - joystick.Axis1.position(vex::percentUnits::pct), vex::percentUnits::pct);
      driveBR.spin(vex::directionType::rev, -joystick.Axis3.position(vex::percentUnits::pct) + joystick.Axis1.position(vex::percentUnits::pct), vex::percentUnits::pct);      
    
      joystick.Screen.clearScreen();
      joystick.Screen.print("Fast");    
    }

    if(joystick.ButtonUp.pressing()){
      vex::task::sleep(100);

      stack();
    }

    if(joystick.ButtonX.pressing()){
      vex::task::sleep(100);
     
     lift_reset();
    }

    if(joystick.ButtonA.pressing()){
      liftL.setVelocity(25, vex::percentUnits::pct);
      liftR.setVelocity(25, vex::percentUnits::pct);

      liftL.spin(vex::directionType::fwd);
      liftR.spin(vex::directionType::fwd);
    }
    else if(joystick.ButtonY.pressing()){
      liftL.setVelocity(-25, vex::percentUnits::pct);
      liftR.setVelocity(-25, vex::percentUnits::pct);

      liftL.spin(vex::directionType::fwd);
      liftR.spin(vex::directionType::fwd);
    }
    else{
      liftL.stop(vex::brakeType::hold);
      liftR.stop(vex::brakeType::hold);
    }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

void stack() {  

  drive_for(0.93 * FULL_TILE);
  accumulator_to(STACKING_POS);
  intake_out(30);
  task::sleep(800);
  drive_for(-1.0 * FULL_TILE, 20);
  accumulator_to(INTAKING_POS);

}


// Main will set up the competition functions and callbacks.
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}