#include "mechanisms/belt.hpp"
#include "mechanisms/drivetrain.hpp"
#include "globals.hpp"

// constructor
Belt::Belt() {}

// run the belt
// loc - manipulation of rollers
//     "top" - shoot
//     "back" - eject
//     "bottom" - outtake
//     "indexer" - index only
//     "sort" - auto sort
void Belt::run( std::string loc, int speed ) {
  if( loc.compare("top") == 0 ) {
    Indexer.move_velocity( speed/2 );
    Launcher.move_velocity( speed );
  }else if( loc.compare("back") == 0 ) {
    Indexer.move_velocity( speed );
    Launcher.move_velocity( -600 );
  }else if( loc.compare("bottom") == 0 ) {
    Indexer.move_velocity( -speed );
    Launcher.move_velocity( -speed );
    IntakeLeft.move_voltage(-speed*20);
    IntakeRight.move_voltage(-speed*20);
  }else if( loc.compare("indexer") == 0 ) {
    Indexer.move_velocity( speed );
  }else if( loc.compare("sort") == 0 ){ //autosorter
    if( Lidar.get() > 150) { //if no ball detected
      Indexer.move_velocity( 300 );
      Launcher.move_velocity( 600 );
    }else{ // if ball detected
      if( Opt.get_hue() > 100 && Opt.get_hue() < 320 ) { //blue ball
         Launcher.move_velocity( -600 );
         pros::delay(500);
         //wait until launcher reverses direction
         if(Launcher.get_actual_velocity() > 0)
           Indexer.move_velocity( 0 );
         else
           Indexer.move_velocity( 600 );
      }else{ //red ball
        Indexer.move_velocity( 600 );
        Launcher.move_velocity( 600 );
      }
    }
  }
}

// shooting function for auton
// timeout - whether to stop code after time runs out
void Belt::shoot( bool timeout ) {
  int count = 0;
  run("top", 600);
  // run until optical sees red ball or times out
  while( Opt.get_hue() < 300 && Opt.get_hue() > 40 && count < 100 ) {
    if( timeout )
      count++;
    pros::delay(10);
  }
  // run until optical no longer sees red ball or times out
  while( (Opt.get_hue() > 300 || Opt.get_hue() < 40) && count < 100 ) {
    if( timeout )
      count++;
    pros::delay(10);
  }
  // additional time to shoot
  pros::delay(200);
  stop();
}

// deploy macro
void Belt::deploy() {
  Indexer.move_velocity(-600);
  pros::delay(200);
  Launcher.move_velocity(600);
  pros::delay(300);
  stop();
}

// stop all belt motors
void Belt::stop() {
  Indexer.set_brake_mode( pros::E_MOTOR_BRAKE_BRAKE );
  Launcher.set_brake_mode( pros::E_MOTOR_BRAKE_BRAKE );

  Indexer.move_relative(0, 0);
  Launcher.move_relative(0, 0);
}

// user control code
void Belt::teleOp( int speed ) {
  // holding two buttons at the same time
  // will make intakes outtake as well
  if( EJECT_BTN && INDEXOUT_BTN ) {
    run("back", speed);
    IntakeLeft.move_voltage( -speed*20 );
    IntakeRight.move_voltage( -speed*20 );
  }else if( LAUNCH_BTN && INDEXOUT_BTN ) {
    run("top", speed);
    IntakeLeft.move_voltage( -speed*20 );
    IntakeRight.move_voltage( -speed*20 );
  }else if ( LAUNCH_BTN )
    run("top", speed);
  else if ( EJECT_BTN )
    run("back", speed);
  else if( INDEXOUT_BTN )
    run("bottom", speed);
  else
    stop();
}

Belt belt;
