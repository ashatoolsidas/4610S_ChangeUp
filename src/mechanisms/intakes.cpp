#include "mechanisms/intakes.hpp"
#include "globals.hpp"

// constructor
Intakes::Intakes() {}

// run intakes at certain speed
void Intakes::run( int speed ) {
  IntakeLeft.move_voltage( speed * 20 );
  IntakeRight.move_voltage( speed * 20 );
}

// stop intakes
void Intakes::stop() {
  IntakeLeft.set_brake_mode( pros::E_MOTOR_BRAKE_COAST );
  IntakeRight.set_brake_mode( pros::E_MOTOR_BRAKE_COAST );

  IntakeLeft.move_relative(0,0);
  IntakeRight.move_relative(0,0);
}

// user control code
void Intakes::teleOp( int speed ) {
  if( INTAKE_BTN ){
    run(speed);
  }else if( OUTTAKE_BTN )
    run(-speed);
  else
    stop();
}

Intakes intakes;
