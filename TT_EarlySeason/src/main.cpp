#include "vex.h"
#include "Robot.h"
#include "config.h"
#include "auton_selector.h"
#include <cmath>

int height = 0;

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
  intakeL.setVelocity(speed, vex::percentUnits::pct);
  intakeR.setVelocity(-speed, vex::percentUnits::pct);
  
  intakeL.spin(directionType::fwd);
  intakeR.spin(directionType::fwd);
}

void intake_out(double speed=50) {
  intakeL.setVelocity(-speed, vex::percentUnits::pct);
  intakeR.setVelocity(speed, vex::percentUnits::pct);
  
  intakeL.spin(directionType::fwd);
  intakeR.spin(directionType::fwd);
}

void intake_stop() {  
  intakeL.stop(brakeType::hold);
  intakeR.stop(brakeType::hold);
}

void accumulator_to(int pos, double speed=50) {
  driveFL.rotateFor(pos, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveFR.rotateFor(pos, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBL.rotateFor(-pos, rotationUnits::deg, speed, velocityUnits::pct, false);
  driveBR.rotateFor(-pos, rotationUnits::deg, speed, velocityUnits::pct, true);

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
    
    drive( joystick.Axis3.position(), joystick.Axis1.position() );

    if(joystick.ButtonL1.pressing()){
      vex::task::sleep(100);

      tower(height, 0);
    }

    if(joystick.ButtonL2.pressing()){
      vex::task::sleep(100);

      tower(height, 1);
    }

    if(joystick.ButtonR1.pressing()){
      intakeL.setVelocity(70, vex::percentUnits::pct);
      intakeR.setVelocity(-70, vex::percentUnits::pct);

      intakeL.spin(directionType::fwd);
      intakeR.spin(directionType::fwd);
    }
    else if(joystick.ButtonR2.pressing()){
      intakeL.setVelocity(-70, vex::percentUnits::pct);
      intakeR.setVelocity(70, vex::percentUnits::pct);

      intakeL.spin(directionType::fwd);
      intakeR.spin(directionType::fwd);
    }
    else{
      intakeL.stop(brakeType::hold);
      intakeR.stop(brakeType::hold);
    }

    if(joystick.ButtonUp.pressing()){ //DIRECTION NEEDS TESTING (Should be up to down)
      driveFL.setVelocity(75, vex::percentUnits::pct);
      driveFR.setVelocity(75, vex::percentUnits::pct);
      driveBL.setVelocity(-75, vex::percentUnits::pct);
      driveBR.setVelocity(-75, vex::percentUnits::pct);

      driveFL.spin(directionType::fwd);
      driveFR.spin(directionType::fwd);
      driveBL.spin(directionType::fwd);
      driveBR.spin(directionType::fwd);
    }

    if(joystick.ButtonRight.pressing()){ //DIRECTION NEEDS TESTING (Should be down to up)
      driveFL.setVelocity(-75, vex::percentUnits::pct);
      driveFR.setVelocity(-75, vex::percentUnits::pct);
      driveBL.setVelocity(75, vex::percentUnits::pct);
      driveBR.setVelocity(75, vex::percentUnits::pct);

      driveFL.spin(directionType::fwd);
      driveFR.spin(directionType::fwd);
      driveBL.spin(directionType::fwd);
      driveBR.spin(directionType::fwd);
    }

    if(joystick.ButtonLeft.pressing()){
      vex::task::sleep(100);

      stack();
    }

    if(joystick.ButtonX.pressing()){
      vex::task::sleep(100);
      height++;

      if(height == 3)
        height = 0;
    }

    if(joystick.ButtonA.pressing()){
      vex::task::sleep(100);
      height--;

      if(height == -1)
        height = 2;
    }

    if(joystick.ButtonY.pressing()){
      liftL.setVelocity(-25, vex::percentUnits::pct);
      liftR.setVelocity(-25, vex::percentUnits::pct);

      liftL.spin(directionType::fwd);
      liftR.spin(directionType::fwd);
    }
    else if(joystick.ButtonB.pressing()){
      liftL.setVelocity(25, vex::percentUnits::pct);
      liftR.setVelocity(25, vex::percentUnits::pct);

      liftL.spin(directionType::fwd);
      liftR.spin(directionType::fwd);
    }
    else{
      liftL.stop(brakeType::hold);
      liftR.stop(brakeType::hold);
    }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

void drive(int x, int y) {
    driveFL.setVelocity(100-(sqrt(10000-(pow(y+x,2)))), vex::percentUnits::pct);
    driveFR.setVelocity(100-(sqrt(10000-(pow(y-x,2)))), vex::percentUnits::pct);
    driveBL.setVelocity(100-(sqrt(10000-(pow(y+x,2)))), vex::percentUnits::pct);
    driveBR.setVelocity(100-(sqrt(10000-(pow(y-x,2)))), vex::percentUnits::pct);

    driveFL.spin(directionType::fwd);
    driveFR.spin(directionType::fwd);
    driveBL.spin(directionType::fwd);
    driveBR.spin(directionType::fwd);
}

void tower(int mode, int type) {

double valL = potentiometerL.value(vex::rotationUnits::deg);
double valR = potentiometerR.value(vex::rotationUnits::deg);
double valAvg = (valL + valR)/2.0;

  switch(mode) {
    case 0: {
      while( fabs( (LOW_POS - valAvg)) > .1 ){
        valL = potentiometerL.value(vex::rotationUnits::deg);
        valR = potentiometerR.value(vex::rotationUnits::deg);

        double low_errorL = LOW_POS - valL;
        double low_errorR = LOW_POS - valR;
        double low_errorAvg = (low_errorL + low_errorR)/2.0;

        double low_kP = .100;

        liftL.setVelocity(low_errorAvg * low_kP, vex::percentUnits::pct);
        liftR.setVelocity(low_errorAvg * low_kP, vex::percentUnits::pct);
      }      
        if(type == 0) {
          intake_in();
          vex::task::sleep(800);
          intake_stop();
        }
        if(type == 1) {
          intake_out();
          vex::task::sleep(800);
          intake_stop();
        }
        lift_reset();
      break;
    }
    case 1: {
      while( fabs( (MID_POS - valAvg)) > .1 ){
        valL = potentiometerL.value(vex::rotationUnits::deg);
        valR = potentiometerR.value(vex::rotationUnits::deg);

        double mid_errorL = MID_POS - valL;
        double mid_errorR = MID_POS - valR;
        double mid_errorAvg = (mid_errorL + mid_errorR)/2.0;

        double mid_kP = .100;

        liftL.setVelocity(mid_errorAvg * mid_kP, vex::percentUnits::pct);
        liftR.setVelocity(mid_errorAvg * mid_kP, vex::percentUnits::pct);
      }
        if(type == 0) {
          intake_in();
          vex::task::sleep(800);
          intake_stop();
        }
        if(type == 1) {
          intake_out();
          vex::task::sleep(800);
          intake_stop();
        }
        lift_reset();
      break;
    }
    case 2: {
      while( fabs( (HIGH_POS - valAvg)) > .1 ){
        valL = potentiometerL.value(vex::rotationUnits::deg);
        valR = potentiometerR.value(vex::rotationUnits::deg);

        double high_errorL = HIGH_POS - valL;
        double high_errorR = HIGH_POS - valR;
        double high_errorAvg = (high_errorL + high_errorR)/2.0;

        double high_kP = .100;

        liftL.setVelocity(high_errorAvg * high_kP, vex::percentUnits::pct);
        liftR.setVelocity(high_errorAvg * high_kP, vex::percentUnits::pct);
      }
        if(type == 0) {
          intake_in();
          vex::task::sleep(800);
          intake_stop();
        }
        if(type == 1) {
          intake_out();
          vex::task::sleep(800);
          intake_stop();
        }
        lift_reset();
      break;
    }
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
      if(height == 0)
        joystick.Screen.print("Low");
      else if(height == 1)
        joystick.Screen.print("Mid");
      else if(height == 2)
        joystick.Screen.print("High");
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}