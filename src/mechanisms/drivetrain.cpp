#include "mechanisms/drivetrain.hpp"

Drivetrain::Drivetrain() {
  FrontLeft.set_brake_mode( pros::E_MOTOR_BRAKE_BRAKE );
  FrontRight.set_brake_mode( pros::E_MOTOR_BRAKE_BRAKE );
  BackLeft.set_brake_mode( pros::E_MOTOR_BRAKE_BRAKE );
  BackRight.set_brake_mode( pros::E_MOTOR_BRAKE_BRAKE );
}

void Drivetrain::move( double fl, double fr, double bl, double br ) {
  FrontLeft.move_velocity(fl);
  FrontRight.move_velocity(fr);
  BackLeft.move_velocity(bl);
  BackRight.move_velocity(br);
}

void Drivetrain::move( double speed ) {
  FrontLeft.move_voltage(-speed);
  FrontRight.move_voltage(speed);
  BackLeft.move_voltage(-speed);
  BackRight.move_voltage(speed);
}

void Drivetrain::forwards(double dist, PD pd ){
  double heading = Inert.get_heading();

  //RightOdom.reset();
  double speed;
  //double current = RightOdom.get_value();
  FrontRight.tare_position();
  FrontLeft.tare_position();

  double current = (std::abs(FrontLeft.get_position())+std::abs(FrontRight.get_position())) / 2 * 0.73;
  double targ = dist;
  int count = 0;
  double turn = 0;
  bool ramp = true;
  double rampSpd = 0.1;

  while( abs(current-dist) > 10 && count < 200) {
    //std::cout << "right: " << RightOdom.get_value() << std:: endl;
    current = (std::abs(FrontLeft.get_position())+std::abs(FrontRight.get_position())) / 2 * 0.73;
    if( pd.getKp() == 0 && pd.getKd() == 0 )
      speed = 0.4; //this is dangerous be careful
    else if(dist > 0) // speed up fwd but not backwards
      speed = pd.speed(current, targ, 1);
    else
      speed = pd.speed(current, targ, 0.2);

    if(dist < 0)
      current *= -1;

    if(count > 130) {
      IntakeLeft.set_brake_mode( pros::E_MOTOR_BRAKE_COAST );
      IntakeRight.set_brake_mode( pros::E_MOTOR_BRAKE_COAST );

      IntakeLeft.move_voltage(0);
      IntakeRight.move_voltage(0);
    }

    // rampSpd += 0.01;
    // if(speed > 1 && ramp)
    //   speed = rampSpd;
    // if(rampSpd > 1)
    //   ramp = false;

    if(Inert.get_heading() - heading > 2 )
      turn = -0.15;
    else if(Inert.get_heading() - heading < -2 )
      turn = 0.15;
    else
      turn = 0;

    XDrive->xArcade(0, speed, turn);

    //if(FrontRight.get_actual_velocity() < 50)
      count++;

    if(count > 150) { // change timeout time
      current = dist;
      break;
    }
    pros::delay(10);
  }
  move(0);
}

void Drivetrain::strafe(double dist, PD pd ){
  double heading = Inert.get_heading();

  //RightOdom.reset();
  double speed;
  //double current = RightOdom.get_value();
  FrontRight.tare_position();
  FrontLeft.tare_position();

  double current = (std::abs(FrontLeft.get_position())+std::abs(FrontRight.get_position())) / 2 * 0.73;
  double targ = dist;
  int count = 0;
  double turn = 0;
  bool ramp = true;
  double rampSpd = 0.1;

  while( abs(current-dist) > 10 && count < 150) {
    //std::cout << "right: " << RightOdom.get_value() << std:: endl;
    current = (std::abs(FrontLeft.get_position())+std::abs(FrontRight.get_position())) / 2 * 0.73;
    if( pd.getKp() == 0 && pd.getKd() == 0 )
      speed = 0.5; //this is dangerous be careful
    else if(dist > 0) // speed up fwd but not backwards
      speed = pd.speed(current, targ, 1);
    else
      speed = pd.speed(current, targ, 0.2);

    if(dist < 0)
      current *= -1;

    // rampSpd += 0.01;
    // if(speed > 1 && ramp)
    //   speed = rampSpd;
    // if(rampSpd > 1)
    //   ramp = false;

    if(Inert.get_heading() - heading > 2 )
      turn = -0.15;
    else if(Inert.get_heading() - heading < -2 )
      turn = 0.15;
    else
      turn = 0;

    XDrive->xArcade(speed, 0, turn);

    //if(FrontRight.get_actual_velocity() < 50)
      count++;

    if(count > 150) { // change timeout time
      current = dist;
      break;
    }
    pros::delay(10);
  }
  move(0);
}

void Drivetrain::bumper(double speed, bool correct ) {
  int count = 0;
  int heading = Inert.get_heading();
  double turn;

  while( Bumper.get_value() == 0 && count < 200 ){
    if(Inert.get_heading() - heading > 2 && correct )
      turn = -0.15;
    else if(Inert.get_heading() - heading < -2 && correct )
      turn = 0.15;
    else
      turn = 0;

    XDrive->xArcade(0, speed, turn);
    count ++;
    pros::delay(10);
  }
  move(0);
}

void Drivetrain::turn( double heading, PD pd, std::string cor, bool rev ) {
  double speed;
  double dist = heading - Inert.get_heading();
  pd.reset( dist );

  while( std::abs(heading - Inert.get_heading()) > 2 ) {
    //std::cout << heading << "," << Inert.get_heading()<< "," << speed << std::endl;

    if( pd.getKp() == 0 && pd.getKd() == 0 )
      speed = 50;
    else
      speed = -pd.speed(Inert.get_heading(), heading, 600);

    if(abs(heading-Inert.get_heading()) > 180 && pd.getKp() > 0)
      speed *= -1;
    if( cor.compare("c") == 0 )
      move(speed, speed, speed, speed);
    else if( cor.compare("fl") == 0 )
      move(0, speed, speed, speed);
    else if( cor.compare("fr") == 0 )
      move(speed, 0, speed, speed);
    else if( cor.compare("bl") == 0 )
      move(speed, speed, 0, speed);
    else if( cor.compare("br") == 0 )
      move(speed, speed, speed, 0);

    if(abs(speed) < 7)
      break;
  }
  move(0);
}

void Drivetrain::turnCrazy( double heading, PD pd, std::string cor, bool rev ) {
  double speed;
  double dist = heading - Inert.get_heading();
  pd.reset( dist );

  std::cout << "starting func" << std::endl;

  if(rev){
    move(-200,-200,-200,-200);
    pros::delay(100);
  }


  while( std::abs(heading - Inert.get_heading()) > 2 ) {
    std::cout << heading << "," << Inert.get_heading()<< "," << speed << std::endl;

    if( pd.getKp() == 0 && pd.getKd() == 0 )
      speed = 30;
    else
      speed = -pd.speed(Inert.get_heading(), heading, 200);

    if( cor.compare("c") == 0 )
      move(speed, speed, speed, speed);
    else if( cor.compare("fl") == 0 )
      move(0, speed, speed, speed);
    else if( cor.compare("fr") == 0 )
      move(speed, 0, speed, speed);
    else if( cor.compare("bl") == 0 )
      move(speed, speed, 0, speed);
    else if( cor.compare("br") == 0 )
      move(speed, speed, speed, 0);

    if(abs(speed) < 7)
      break;
  }
  move(0);
}


std::string Drivetrain::getCtrlType() { return ctrlType; }

void Drivetrain::toggleCtrlType() {
  if( ctrlType.compare("arcade") == 0 )
    ctrlType = "tank";
  else
    ctrlType = "arcade";
}


void Drivetrain::strafeTo( CartPoint dest, PD pd ){
  double speed;
  CartPoint start = {XPOS_FT, YPOS_FT};

  pd.reset( distance(start,dest) );

  while( distance(dest, {XPOS_FT,YPOS_FT}) > 0.1 ) {
    if( pd.getKp() == 0 && pd.getKd() == 0 )
      speed = 1; //change to 1 later
    else
      speed = pd.speed( distance(start, {XPOS_FT,YPOS_FT}), distance(start,dest), 0.3 );
    strafeTo( dest, THETA_DEG, speed );
  }
}

void Drivetrain::strafeTo( CartPoint dest, double heading, double speed ){
  //global coordinate differences between position and destination
  CartPoint coordDiff_glo = {
    dest.x - XPOS_FT,
    dest.y - YPOS_FT
  };

  // local coordinate differences - mapped by theta using polar coordinates
  CartPoint coordDiff_loc =
    toCartesian( {
      toPolar( coordDiff_glo ).r,
      toPolar( coordDiff_glo ).theta - THETA_RAD
  } );

  double headingDiff = toRad(THETA_DEG - heading);

  double fwdSpeed, stfSpeed;

  //determine which set of wheels should be faster
  if( std::abs(coordDiff_loc.y) > std::abs(coordDiff_loc.x) ) {
    fwdSpeed = sign(coordDiff_loc.y);
    stfSpeed = -coordDiff_loc.x/coordDiff_loc.y;
  } else if ( std::abs(coordDiff_loc.y) < std::abs(coordDiff_loc.x) ) {
    fwdSpeed = coordDiff_loc.y/coordDiff_loc.x;
    stfSpeed = -sign(coordDiff_loc.x);
  } else {
    fwdSpeed = sign(coordDiff_loc.y);
    stfSpeed = sign(coordDiff_loc.x);
  }
  std::cout << coordDiff_loc.x << "\t" << coordDiff_loc.y << std::endl;
  std::cout << fwdSpeed << "\t" << stfSpeed << std::endl;
  //while( distance(dest, {XPOS_FT,YPOS_FT}) > 0.1 ) {
    XDrive->xArcade(stfSpeed*speed, fwdSpeed*speed, 0, 0); //headingDiff*speed
    //pros::delay(100);
  //}

  printCoords();
}

void Drivetrain::strafeAlong( Path path, PD pd ) {
  int lookahead = 3;
  CartPoint endPt = path.getPathPoints().back();
  CartPoint target;
  int maxPtIndex;

  pd.reset( path.getPathPoints().size() );
  int speed;

  while( std::hypot( endPt.x - XPOS_IN, endPt.y - YPOS_IN ) > 0.1 ) {
    speed = pd.speed( maxPtIndex, path.getPathPoints().size(), 200 );

    for( int i = maxPtIndex; i < path.getPathPoints().size(); i++ ) {
      if( std::hypot( path.getPathPoints()[i].x - XPOS_IN, path.getPathPoints()[i].y, YPOS_IN ) > lookahead ){
        target = path.getPathPoints()[i];
        maxPtIndex = i;
        break;
      }
    }
    strafeTo( target, THETA_DEG, speed );
    pros::delay(10);
  }
}

void Drivetrain::strafeAlong( Path path, double speed ) {
  int lookahead = 3;
  CartPoint endPt = path.getPathPoints().back();
  CartPoint target;
  int maxPtIndex;


  while( std::hypot( endPt.x - XPOS_IN, endPt.y - YPOS_IN ) > 0.1 ) {
    for( int i = maxPtIndex; i < path.getPathPoints().size(); i++ ) {
      if( std::hypot( path.getPathPoints()[i].x - XPOS_IN, path.getPathPoints()[i].y, YPOS_IN ) > lookahead ){
        target = path.getPathPoints()[i];
        maxPtIndex = i;
        break;
      }
    }
    strafeTo( target, THETA_DEG, speed );
    pros::delay(10);
  }
}

void Drivetrain::teleOp( double speedCtrl, double deadzone ) {
  XDrive->xArcade(
    Control.get_analog(ANALOG_LEFT_X)  * speedCtrl / 100,
    Control.get_analog(ANALOG_LEFT_Y)  * speedCtrl / 100,
    Control.get_analog(ANALOG_RIGHT_X) * speedCtrl / 100,
    deadzone
  );
  std::cout <<"aaaaaa"<<std::endl;
}

void Drivetrain::velocityTest() {
  move(0);
  move(120000);
  for( int t = 0; t < 100; t++) {
    std::cout << YPOS_IN << std::endl;
    pros::delay(10);
  }
  move(0);
}

Drivetrain drivetrain;
