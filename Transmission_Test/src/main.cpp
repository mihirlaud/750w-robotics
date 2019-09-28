/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\mihir                                            */
/*    Created:      Tue Aug 20 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_controller.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/v5_apitypes.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here
vex::controller joystick(vex::controllerType::primary);

vex::motor transmissionFL(vex::PORT4);
vex::motor transmissionBL(vex::PORT2);
vex::motor transmissionFR(vex::PORT5);
vex::motor transmissionBR(vex::PORT3);

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
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
 
    if(joystick.ButtonDown.pressing()) {
      transmissionFL.spin(vex::directionType::fwd, 25, vex::percentUnits::pct);
      transmissionBL.spin(vex::directionType::fwd, 25, vex::percentUnits::pct);
      transmissionFR.spin(vex::directionType::rev, 25, vex::percentUnits::pct);  
      transmissionBR.spin(vex::directionType::rev, 25, vex::percentUnits::pct);  
    } else if(joystick.ButtonUp.pressing()) {  
      transmissionFL.spin(vex::directionType::fwd, -25, vex::percentUnits::pct);
      transmissionBL.spin(vex::directionType::fwd, -25, vex::percentUnits::pct);
      transmissionFR.spin(vex::directionType::rev, -25, vex::percentUnits::pct);
      transmissionBR.spin(vex::directionType::rev, -25, vex::percentUnits::pct);
    } else {
      transmissionFL.spin(vex::directionType::fwd, joystick.Axis3.position(vex::percentUnits::pct)  + joystick.Axis1.position(vex::percentUnits::pct), vex::percentUnits::pct);
      transmissionBL.spin(vex::directionType::fwd, -joystick.Axis3.position(vex::percentUnits::pct) - joystick.Axis1.position(vex::percentUnits::pct), vex::percentUnits::pct);
      transmissionFR.spin(vex::directionType::rev, joystick.Axis3.position(vex::percentUnits::pct)  - joystick.Axis1.position(vex::percentUnits::pct), vex::percentUnits::pct);
      transmissionBR.spin(vex::directionType::rev, -joystick.Axis3.position(vex::percentUnits::pct) + joystick.Axis1.position(vex::percentUnits::pct), vex::percentUnits::pct);
    }

    /*
    if(joystick.ButtonA.pressing()) {         //Same direction, positive 
      transmissionFL.spin(vex::directionType::fwd, +100, vex::percentUnits::pct);
      transmissionBL.spin(vex::directionType::fwd, +100, vex::percentUnits::pct);
      transmissionFR.spin(vex::directionType::rev, +100, vex::percentUnits::pct);
      transmissionBR.spin(vex::directionType::rev, +100, vex::percentUnits::pct);
    } else if(joystick.ButtonB.pressing()) {  //Same direction, negative
      transmissionFL.spin(vex::directionType::fwd, -100, vex::percentUnits::pct);
      transmissionBL.spin(vex::directionType::fwd, -100, vex::percentUnits::pct);
      transmissionFR.spin(vex::directionType::rev, -100, vex::percentUnits::pct);
      transmissionBR.spin(vex::directionType::rev, -100, vex::percentUnits::pct);
    } else if(joystick.ButtonX.pressing()) {  //Left positive, right negative
      transmissionFL.spin(vex::directionType::fwd, -100, vex::percentUnits::pct);
      transmissionBL.spin(vex::directionType::fwd, +100, vex::percentUnits::pct);
      transmissionFR.spin(vex::directionType::rev, -100, vex::percentUnits::pct);
      transmissionBR.spin(vex::directionType::rev, +100, vex::percentUnits::pct);
    } else if(joystick.ButtonY.pressing()) {  //Left negative, right positive
      transmissionFL.spin(vex::directionType::fwd, +100, vex::percentUnits::pct);
      transmissionBL.spin(vex::directionType::fwd, -100, vex::percentUnits::pct);
      transmissionFR.spin(vex::directionType::rev, +100, vex::percentUnits::pct);
      transmissionBR.spin(vex::directionType::rev, -100, vex::percentUnits::pct);
    } else {                                  //Stop
      transmissionFL.stop(vex::brakeType::brake);
      transmissionBL.stop(vex::brakeType::brake);
      transmissionFR.stop(vex::brakeType::brake);
      transmissionBR.stop(vex::brakeType::brake);
    }
    */

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
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
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}