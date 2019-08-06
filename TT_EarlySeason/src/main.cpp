/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\mihir                                            */
/*    Created:      Thu Jun 20 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Robot.h"
#include "config.h"
#include "auton_selector.h"

bool driveSlow = false;

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen

// A global instance of vex::competition


// define your global instances of motors and other devices here



/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

int auton_index = -1;
void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  AutonSelector selector(cortex);
  
  selector.addRedOption("GOAL SIDE", 0)
          .addRedOption("ALLIANCE TOWER SIDE", 1)
          .addBlueOption("GOAL SIDE", 2)
          .addBlueOption("ALLIANCE TOWER SIDE", 3);
  
  auton_index = selector.getCode();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  switch(auton_index) {
    case 0: //RED GOAL SIDE
      break;
    case 1: //RED TOWER SIDE
      break;
    case 2: //BLUE GOAL SIDE
      break;
    case 3: //BLUE TOWER SIDE
      break;
    default:
      break;
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol( void ) {
  // User control code here, inside the loop

  while (1) {

  if(joystick.ButtonX.pressing()){
    driveSlow = speedChange( driveSlow );
  }

    drive( joystick.Axis3.position(), joystick.Axis1.position() );

    if(joystick.ButtonR1.pressing()){
      rollerL.setVelocity(50, vex::percentUnits::pct);
      rollerR.setVelocity(-50, vex::percentUnits::pct);

      rollerL.spin(directionType::fwd);
      rollerR.spin(directionType::fwd);
    }
    else if(joystick.ButtonR2.pressing()){
      rollerL.setVelocity(-50, vex::percentUnits::pct);
      rollerR.setVelocity(50, vex::percentUnits::pct);

      rollerL.spin(directionType::fwd);
      rollerR.spin(directionType::fwd);
    }
    else{
      rollerL.stop(brakeType::hold);
      rollerR.stop(brakeType::hold);
    }  
    
    if(joystick.ButtonL1.pressing()){
      spine.setVelocity(20, vex::percentUnits::pct);

      spine.spin(directionType::fwd);
    }
    else if(joystick.ButtonL2.pressing()){
      spine.setVelocity(-20, vex::percentUnits::pct);

      spine.spin(directionType::fwd);
    }
    else{
      spine.stop(brakeType::hold);
    }

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
    //if(Controller.ButtonA.pressing()) {
    //  Brain.Screen.print("Hello");
    //}

    //flywheel.setVelocity(Controller.Axis1.value(), vex::percentUnits::pct);
    //if(potent.value(vex::percentUnits::pct) > 75)
    //  flywheel.stop();

    //Brain.Screen.print("%lf", g.value(vex::rotationUnits::deg));

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

void drive(int x, int y){
 
  if(driveSlow == false){
    driveFL.setVelocity(y + x, vex::percentUnits::pct);
    driveFR.setVelocity(y - x, vex::percentUnits::pct);
    driveBL.setVelocity(y + x, vex::percentUnits::pct);
    driveBR.setVelocity(y - x, vex::percentUnits::pct);

    driveFL.spin(directionType::fwd);
    driveFR.spin(directionType::fwd);
    driveBL.spin(directionType::fwd);
    driveBR.spin(directionType::fwd);
}

  else{
    driveFL.setVelocity((y + x)/3, vex::percentUnits::pct);
    driveFR.setVelocity((y - x)/3, vex::percentUnits::pct);
    driveBL.setVelocity((y + x)/3, vex::percentUnits::pct);
    driveBR.setVelocity((y - x)/3, vex::percentUnits::pct);

    driveFL.spin(directionType::fwd);
    driveFR.spin(directionType::fwd);
    driveBL.spin(directionType::fwd);
    driveBR.spin(directionType::fwd);
  }

}

bool speedChange(bool newSpeed){
  return !(newSpeed);
}

void drive_for(int dist) {
  driveFL.rotateFor(dist, rotationUnits::deg, 60, velocityUnits::pct, false);
  driveFR.rotateFor(dist, rotationUnits::deg, 60, velocityUnits::pct, false);
  driveBL.rotateFor(dist, rotationUnits::deg, 60, velocityUnits::pct, false);
  driveBR.rotateFor(dist, rotationUnits::deg, 60, velocityUnits::pct, true);
  task::sleep(250);
}

void cw_turn_for(int angle) {
  driveFL.rotateFor(angle, rotationUnits::deg, 60, velocityUnits::pct, false);
  driveFR.rotateFor(-angle, rotationUnits::deg, 60, velocityUnits::pct, false);
  driveBL.rotateFor(angle, rotationUnits::deg, 60, velocityUnits::pct, false);
  driveBR.rotateFor(-angle, rotationUnits::deg, 60, velocityUnits::pct, true);
  task::sleep(250);
}

void ccw_turn_for(int angle) {
  cw_turn_for(-angle);
}

void intake_in() {
  rollerL.setVelocity(50, vex::percentUnits::pct);
  rollerR.setVelocity(-50, vex::percentUnits::pct);
  
  rollerL.spin(directionType::fwd);
  rollerR.spin(directionType::fwd);
}

void intake_out() {
  rollerL.setVelocity(-50, vex::percentUnits::pct);
  rollerR.setVelocity(50, vex::percentUnits::pct);
  
  rollerL.spin(directionType::fwd);
  rollerR.spin(directionType::fwd);
}

void intake_stop() {  
  rollerL.stop(brakeType::hold);
  rollerR.stop(brakeType::hold);
}


void accumulator_to(int pos) {
  spine.rotateTo(pos, rotationUnits::deg, 50, velocityUnits::pct);
  task::sleep(250);
}

//
// Main will set up the competition functions and callbacks.
//
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