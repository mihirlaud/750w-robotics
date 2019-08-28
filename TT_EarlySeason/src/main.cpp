/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\mihir                                            */
/*    Created:      Thu Jun 20 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/gcc/include/stdio.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_brain.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_controller.h"
#include "vex.h"
#include "Robot.h"
#include "config.h"
#include "auton_selector.h"
#include<cmath>

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

int auton_index = 1;
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

void drive_for(int dist, double speed=60) {
  driveFL.rotateFor(directionType::fwd, dist, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveFR.rotateFor(directionType::fwd, -dist, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBL.rotateFor(directionType::fwd, dist, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBR.rotateFor(directionType::fwd, -dist, rotationUnits::deg, speed, velocityUnits::pct, true);
  task::sleep(250);
}

void cw_turn_for(int angle, double speed=60) {
  driveFL.rotateFor(directionType::fwd, angle, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveFR.rotateFor(directionType::fwd, angle, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBL.rotateFor(directionType::fwd, angle, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBR.rotateFor(directionType::fwd, angle, rotationUnits::deg, speed, velocityUnits::pct, true);
  task::sleep(250);
}

void ccw_turn_for(int angle, double speed=60) {
  cw_turn_for(-angle, speed);
}

void intake_in(double speed=50) {
  rollerL.setVelocity(speed, vex::percentUnits::pct);
  rollerR.setVelocity(-speed, vex::percentUnits::pct);
  
  rollerL.spin(directionType::fwd);
  rollerR.spin(directionType::fwd);
}

void intake_out(double speed=50) {
  rollerL.setVelocity(-speed, vex::percentUnits::pct);
  rollerR.setVelocity(speed, vex::percentUnits::pct);
  
  rollerL.spin(directionType::fwd);
  rollerR.spin(directionType::fwd);
}

void intake_stop() {  
  rollerL.stop(brakeType::hold);
  rollerR.stop(brakeType::hold);
}


void accumulator_to(int pos, double speed=50) {
  spine.rotateTo(pos, rotationUnits::deg, speed, velocityUnits::pct, true);
  task::sleep(250);
}

void autonomous( void ) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  switch(auton_index) {
    case -1:
      cw_turn_for(FULL_CIRCLE);
      break;
    case 0: //RED GOAL SIDE
      break;
    case 1: //RED TOWER SIDE
    /*
      //Go forward until the accumulator can be deployed
      drive_for(0.30 * FULL_TILE, 70);
      //Deploy accumulator
      accumulator_to(STACKING_POS);
      //Return accumulator to intaking position
      accumulator_to(INTAKING_POS);
      //Drive forward so that bot is closer to cubes
      drive_for(0.20 * FULL_TILE);
      //Begin intaking
      intake_in();
      //Drive forward to intake cubes
      drive_for(1.0 * FULL_TILE, 20);
      //Stop intake
      intake_stop();
      //Drive backwards to be closer to goal
      drive_for(-1.0 * FULL_TILE);
      //Turn to align with goal
      cw_turn_for(0.36 * FULL_CIRCLE);
      //Drive up to goal
      drive_for(0.93 * FULL_TILE);
      //Ready accumulator for stacking
      accumulator_to(STACKING_POS);
      //Stack cubes into goal
      intake_out();
      //Delay for a short while so that cubes can stack
      task::sleep(800);
      //Drive backwards so that cubes count as scored
      drive_for(-1.0 * FULL_TILE, 20);
      */

//Tanav's scuffed auton RED
      drive_for(.3 * FULL_TILE);
      intake_out();
      task::sleep(800);
      drive_for(-1.0 * FULL_TILE, 20);
      intake_stop();

      break;
    case 2: //BLUE GOAL SIDE
      break;
    case 3: //BLUE TOWER SIDE
    /*
      //Go forward until the accumulator can be deployed
      drive_for(0.30 * FULL_TILE, 70);
      //Deploy accumulator
      accumulator_to(STACKING_POS);
      //Return accumulator to intaking position
      accumulator_to(INTAKING_POS);
      //Drive forward so that bot is closer to cubes
      drive_for(0.20 * FULL_TILE);
      //Begin intaking
      intake_in();
      //Drive forward to intake cubes
      drive_for(1.0 * FULL_TILE, 20);
      //Stop intake
      intake_stop();
      //Drive backwards to be closer to goal
      drive_for(-1.0 * FULL_TILE);
      //Turn to align with goal
      ccw_turn_for(0.36 * FULL_CIRCLE);
      //Drive up to goal
      drive_for(0.93 * FULL_TILE);
      //Ready accumulator for stacking
      accumulator_to(STACKING_POS);
      //Stack cubes into goal
      intake_out();
      //Delay for a short while so that cubes can stack
      task::sleep(800);
      //Drive backwards so that cubes count as scored
      drive_for(-1.0 * FULL_TILE, 20);
      */

//Tanav's scuffed auton BLUE
      drive_for(.3 * FULL_TILE);
      intake_out();
      task::sleep(800);
      drive_for(-1.0 * FULL_TILE, 20);
      intake_stop();



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

    if(joystick.ButtonA.pressing()){
      vex::task::sleep(100);
      driveSlow = !driveSlow;
    }
    
    drive( joystick.Axis3.position(), joystick.Axis1.position() );

    if(joystick.ButtonR1.pressing()){
      rollerL.setVelocity(70, vex::percentUnits::pct);
      rollerR.setVelocity(-70, vex::percentUnits::pct);

      rollerL.spin(directionType::fwd);
      rollerR.spin(directionType::fwd);
    }
    else if(joystick.ButtonR2.pressing()){
      rollerL.setVelocity(-70, vex::percentUnits::pct);
      rollerR.setVelocity(70, vex::percentUnits::pct);

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
 
  if(!driveSlow){
    driveFL.setVelocity(100-(sqrt(10000-(pow(y+x,2)))), vex::percentUnits::pct);
    driveFR.setVelocity(100-(sqrt(10000-(pow(y-x,2)))), vex::percentUnits::pct);
    driveBL.setVelocity(100-(sqrt(10000-(pow(y+x,2)))), vex::percentUnits::pct);
    driveBR.setVelocity(100-(sqrt(10000-(pow(y-x,2)))), vex::percentUnits::pct);

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
      if(driveSlow)
        joystick.Screen.print("Slow");
      else
        joystick.Screen.print("Fast");
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}