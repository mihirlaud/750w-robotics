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

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  g.startCalibration(1000);
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

    drive( joystick.Axis1.position(), joystick.Axis3.position() );
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
    if(Controller.ButtonA.pressing()) {
      Brain.Screen.print("Hello");
    }

    flywheel.setVelocity(Controller.Axis1.value(), vex::percentUnits::pct);
    if(potent.value(vex::percentUnits::pct) > 75)
      flywheel.stop();

    //Brain.Screen.print("%lf", g.value(vex::rotationUnits::deg));

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

void drive(int x, int y){
  driveFL.setVelocity(y + x, vex::percentUnits::pct);
  driveFR.setVelocity(y - x, vex::percentUnits::pct);
  driveBL.setVelocity(y + x, vex::percentUnits::pct);
  driveBR.setVelocity(y - x, vex::percentUnits::pct);
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