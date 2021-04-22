#include "main.h"
#include "mechanisms/belt.hpp"
#include "mechanisms/drivetrain.hpp"
#include "mechanisms/intakes.hpp"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

 void opcontrol() {
	 while(true) {
    // std::cout<<Bumper1.get_value()<<"\t"<<Bumper2.get_value()<<std::endl;
     if( Control.get_digital(DIGITAL_Y))
      belt.deploy();
    if( Control.get_digital(DIGITAL_LEFT))
      belt.shoot();
      // std::cout << "line:" << Line.get_value() << "\tright:" << RightOdom.get_value()
      // << "\tback:" << BackOdom.get_value() << std::endl;
     // printCoords();
     drivetrain.teleOp( 1, 0.1 );
  	 intakes.teleOp( 600 );
  	 belt.teleOp( 600 );

     pros::delay(10);
	 }
 }
