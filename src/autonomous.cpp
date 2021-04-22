#include "main.h"
#include "mechanisms/belt.hpp"
#include "mechanisms/drivetrain.hpp"
#include "mechanisms/intakes.hpp"
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  double realign = 2.5;
  double normal = 1.8;
  double crazy = 1.3;
  belt.deploy();
  pros::delay(200);

  drivetrain.turn(0, {normal,0}); // turn to goal
  //first goal
  intakes.run(600); //intake

  drivetrain.forwards(1000, {0.01,0}); // drive to first ball

  drivetrain.turn(90, {normal,0}); // turn to goal

  belt.run("indexer", 50);
  //drivetrain.forwards(1000, {0.005,0}); // drive to corner goal 1
  drivetrain.bumper(1);
  drivetrain.turn(90, {normal,0});
  // belt.stop();
  // intakes.run(200); // to make sure u dont descore
  // belt.run("bottom", 600);
  // intakes.run(600);
  // pros::delay(200);
  // intakes.run(600);
  // belt.run("top",0);
  // Launcher.move_voltage(12000);
  // pros::delay(300);
  // belt.run("top", 600); // run launcher, shoot ball
  //
  // pros::delay(800);
  belt.shoot();
  belt.run("bottom");
  drivetrain.turn(75, {realign,0}); // realign
  drivetrain.forwards( -1100, {0.003 ,0} ); // back up from goal

  belt.stop();

  // belt.run("indexer", 200); // slow this down if it's pooping
  // intakes.stop();

  drivetrain.turn(45, {normal, 0}, "c", false); // turn to wall ball
  drivetrain.strafe(-500, {0.05,0});
  drivetrain.turn(45, {realign, 0}, "c", false); // turn to wall ball

  belt.stop();

  //second goal
    intakes.run(600);

   double spd = -0.45;
   while(Line.get_value() > 1900) {
    if(abs(Inert.get_heading()-45) > 2)
      XDrive->xArcade(spd, 0, -0.05);
    else if(Inert.get_heading()-45 < -2)
      XDrive->xArcade(spd, 0, 0.05);
    else
       XDrive->xArcade(spd, 0, 0);
  }
  drivetrain.turn(45, {realign, 0}, "c", false); // realign

  belt.run("top", 50); // slow down if ball's getting too high
   // //drivetrain.forwards(1300, {0.005,0}); // drive to side goal 1
  drivetrain.bumper(0.7);
   // belt.run("bottom", 600);
   // pros::delay(200);
   // intakes.run(600);
   // belt.run("top", 0);
   // //Inert.reset();
   // belt.run("top", 600); // shoot ball
   // pros::delay(700); // time to run launcher for
   belt.shoot();
   drivetrain.turn(45, {realign, 0}, "c", false); // realign
   belt.run("bottom", 600);
   drivetrain.forwards(-500, {0.01,0}); // back up from second goal
   intakes.run(-600);
   belt.run("back", 600);
   drivetrain.turnCrazy(315, {crazy,0}); //turn 90 degrees
   // drivetrain.turn(0,{3,0});
   // drivetrain.turn(315,{normal,0});

   belt.stop();
   intakes.run(600);

  // third goal
  spd = 1;
  while(Line.get_value() > 1900) {
    if(abs(Inert.get_heading()-315) > 2)
      XDrive->xArcade(0, spd, 0.1);
    else if(Inert.get_heading()-315 < -2)
      XDrive->xArcade(0, spd, -0.1);
    else
       XDrive->xArcade(0, spd, 0);
  }
  drivetrain.turn(315, {realign,0});
  belt.run("indexer", 200);
  drivetrain.forwards(1850,{0.003,0}); // pick up ball next to corner goal 2
  drivetrain.turn(315,{realign,0});
  drivetrain.forwards(-450,{0.01,0});
  belt.stop();
  intakes.run(600);
  drivetrain.turn(359, {normal,0}); // turn to face goal
  //drivetrain.forwards(900, {0.01,0}); // drive to goal
  drivetrain.bumper(0.7, false);
  // belt.run("top", 600); // launch ball
  // pros::delay(800);
  // belt.stop();
  belt.shoot();

  //fourth goal
  belt.run("bottom", 600);
  drivetrain.forwards(-800, {0.01, 0});

  drivetrain.turnCrazy(45, {crazy,0});
  belt.stop();
  intakes.run(600);

  drivetrain.forwards(800, {0.05,0});
  drivetrain.turn(45, {realign,0});
  drivetrain.forwards(-600, {0.05,0});
  drivetrain.turn(45, {realign,0});
  int curDist = Lidar.get();
  while(Lidar.get() > curDist-200) {
    if(Inert.get_heading() - 45 > 3)
      XDrive->xArcade(0, -0.6, -0.1);
    else if(Inert.get_heading() - 45 < 3)
      XDrive->xArcade(0, -0.6, 0.1);
    else
      XDrive->xArcade(0, -0.6, 0);
  }

  drivetrain.turn(0,{3,0});
  drivetrain.turn(315,{normal,0});  //drivetrain.forwards(700, {0.05,0});
  drivetrain.turn(315, {realign,0});
  drivetrain.bumper(1);
  drivetrain.turn(315, {realign,0});
  // belt.run("top", 600);
  // pros::delay(800);
  belt.shoot();
  belt.run("top", 600);
  drivetrain.forwards(-150, {0.05,0});
  belt.run("back", 600);
  drivetrain.turn(225, {2,0});

  //fifth goal
  drivetrain.forwards(2450, {0.05,0});
  belt.stop();
  intakes.run(600);
  drivetrain.forwards(-170, {0.1,0});
  drivetrain.turn(270, {normal,0});
  //drivetrain.forwards(800, {0.05,0});
  drivetrain.bumper(1);
  // belt.run("top", 600);
  belt.shoot();

  //////////////////////
  belt.run("bottom", 600);
  drivetrain.turn(255, {realign, 0});
  drivetrain.forwards( -1050, {0.003 ,0} ); // back up from goal

  //belt.stop();

  //belt.run("indexer", 200); // slow this down if it's pooping
  intakes.stop();

  drivetrain.turn(225, {normal, 0}, "c", false); // turn to wall ball
  belt.run("top", 600);
  drivetrain.strafe(-500, {0.05,0});


   spd = -0.5;
   while(Line.get_value() > 1900) {
    if(abs(Inert.get_heading()-225) > 2)
      XDrive->xArcade(spd, 0, -0.05);
    else if(Inert.get_heading()-225 < -2)
      XDrive->xArcade(spd, 0, 0.05);
    else
      XDrive->xArcade(spd, 0, 0);
  }
  belt.stop();

  drivetrain.turn(225, {realign, 0}, "c", false); // realign

   //drivetrain.strafe(-1100, {0.003,0}); // strafe to face side goal
   belt.run("top", 50); // slow down if ball's getting too high
   intakes.run(600);
   //drivetrain.forwards(1200, {0.01,0}); // drive to side goal 1
   drivetrain.bumper(0.5);
   //intakes.run(-200);
   // belt.run("bottom", 600);
   // pros::delay(200);
   // intakes.run(600);
   // belt.run("top", 0);
   // //Inert.reset();
   // belt.run("top", 600); // shoot ball
   // pros::delay(650); // time to run launcher for
   belt.shoot();
   drivetrain.turn(225, {realign, 0}, "c", false); // realign
   belt.run("back", 600);
   drivetrain.forwards(-550, {0.01,0}); // back up from second goal
   drivetrain.turn(135, {normal,0}); //turn 90 degrees

   belt.stop();
   intakes.run(600);

  // third goal
  spd = 1;
  while(Line.get_value() > 1900) {
    if(abs(Inert.get_heading()-315) > 2)
      XDrive->xArcade(0, spd, 0.1);
    else if(Inert.get_heading()-315 < -2)
      XDrive->xArcade(0, spd, -0.1);
    else
       XDrive->xArcade(0, spd, 0);
  }
  drivetrain.turn(135, {realign,0});
  belt.run("indexer", 70);
  drivetrain.forwards(1950,{0.003,0}); // pick up ball next to corner goal 2
  drivetrain.turn(135,{realign,0});
  drivetrain.forwards(-600,{0.01,0});
  belt.stop();
  intakes.run(600);
  drivetrain.turn(190, {normal,0}); // turn to face goal
  //drivetrain.forwards(1050, {0.01,0}); // drive to goal
  drivetrain.bumper(1);
  // belt.run("top", 600); // launch ball
  //
  // pros::delay(800);
  // belt.stop();
  belt.shoot();

  //fourth goal
  belt.run("bottom", 600);
  drivetrain.forwards(-800, {0.01, 0});

  drivetrain.turnCrazy(225, {normal,0});
  belt.stop();
  intakes.run(600);

  drivetrain.forwards(800, {0.05,0});
  drivetrain.turn(225, {realign,0});
  if( Opt.get_hue() > 100 && Opt.get_hue() < 320 )
    belt.run("bottom",600);
  drivetrain.strafe(-200, {0.1,0});
  drivetrain.turn(235, {realign,0});
  drivetrain.forwards(-1000, {0.05,0});
  int curDist1 = Lidar.get();
  drivetrain.turn(225, {realign,0});
  drivetrain.strafe(-200, {0.1,0});
  drivetrain.turn(225, {realign,0});
  int count = 0;
  while(Lidar.get() > curDist1-200) {
    count++;
    if(Inert.get_heading() - 225 > 3)
      XDrive->xArcade(0, -0.6, -0.07);
    else if(Inert.get_heading() - 225 < 3)
      XDrive->xArcade(0, -0.6, 0.07);
    else
      XDrive->xArcade(0, -0.6, 0);
    pros::delay(10);
    if(count > 140) {
      break;
    }
  }

  drivetrain.turnCrazy(135, {crazy,0});
  //drivetrain.forwards(700, {0.05,0});
  drivetrain.bumper(1);
  //drivetrain.turn(135, {realign,0});
  // belt.run("top", 600);
  // pros::delay(700);
  belt.shoot();
  belt.run("bottom", 600);


  drivetrain.forwards(-150, {0.05,0});
  drivetrain.turnCrazy(315, {normal,0}); //315
  drivetrain.strafe(600, {0.05,0});
  intakes.stop();
  drivetrain.forwards(-700, {0.1,0});
  belt.stop();

  // while(Lidar.get() < 1730 || Lidar.get() > 1770) {
  //   if(Lidar.get() < 1700)
  //     XDrive->xArcade(0.4,0,0);
  //   else
  //     XDrive->xArcade(-0.4,0,0);
  // }
  drivetrain.turn(315, {realign,0}); //315
  while(Line.get_value() > 1900) {
     XDrive->xArcade(0, 0.5, 0);
  }
  drivetrain.move(0);
  drivetrain.forwards(-200, {0.1,0});
  drivetrain.turn(315, {realign,0}); //315
  while(Line.get_value() > 1900) {
     XDrive->xArcade(-0.4, 0, 0);
  }
  drivetrain.move(0);
  drivetrain.turn(315, {realign,0});
  belt.run("indexer", 200);
  intakes.run(600);
  drivetrain.bumper(0.7);
  drivetrain.turn(315, {realign,0}); //315
  intakes.run(-600);

  belt.shoot(false);
  //intakes.run(600);
  drivetrain.forwards(-500, {0.1,0});

  // drivetrain.bumper(0.5);
  // drivetrain.turn(315,{realign,0});
  // drivetrain.bumper(0.5);
  // belt.run("bottom", 600);
  // intakes.run(-600);
  // drivetrain.move(3000);

}
