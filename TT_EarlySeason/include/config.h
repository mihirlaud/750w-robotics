vex::brain Brain;
vex::competition Competition;
vex::controller Controller(vex::controllerType::primary);

vex::motor flywheel(vex::PORT1);
vex::pot potent(Brain.ThreeWirePort.A);
vex::gyro g(Brain.ThreeWirePort.B);