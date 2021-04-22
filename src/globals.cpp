#include "globals.hpp"

pros::Controller  Control ( CONTROLLER_MASTER );

// motors
pros::Motor        FrontLeft   ( 1,  pros::E_MOTOR_GEARSET_18, false ),
                   FrontRight  ( 15, pros::E_MOTOR_GEARSET_18, false ),
                   BackLeft    ( 20, pros::E_MOTOR_GEARSET_18, false ),
                   BackRight   ( 3,  pros::E_MOTOR_GEARSET_18, false ),
                   Indexer     ( 2,  pros::E_MOTOR_GEARSET_06, true  ),
                   Launcher    ( 10, pros::E_MOTOR_GEARSET_06, true  ),
                   IntakeLeft  ( 11, pros::E_MOTOR_GEARSET_18, false ),
                   IntakeRight (  8, pros::E_MOTOR_GEARSET_18, true  );

// odoms
pros::ADIEncoder   RightOdom ( 5, 6, true ),
                   LeftOdom  ( 3, 4, false ),
                   BackOdom  ( 7, 8, false );

// line sensor
pros::ADIAnalogIn  Line (2);

// color sensor
pros::Optical      Opt (18);

// distance sensor
pros::Distance     Lidar (17);

// inertial
pros::Imu          Inert (7);

// bumper
pros::ADIDigitalIn Bumper (1);

// okapi pointers
std::shared_ptr<OdomChassisController> odomController =
  ChassisControllerBuilder()
    // fl, fr, br, bl
    .withMotors( -1, 15, 3, -20 )
    .withDimensions( AbstractMotor::gearset::green, {{6.43_in, 22_in}, imev5GreenTPR} )
    // left, right, back
    .withSensors( ADIEncoder{ 'C', 'D' }, ADIEncoder{ 'E', 'F', true }, ADIEncoder{ 'G', 'H', true } )
    .withOdometry( {{2.75_in, 3.25_in, 7_in, 2.75_in}, quadEncoderTPR}, StateMode::CARTESIAN )
    .buildOdometry();

std::shared_ptr<AsyncMotionProfileController> profileCtrlX =
  AsyncMotionProfileControllerBuilder()
    .withOutput( {odomController} )
    // vel m/s, accel m/s2, jerk m/s3
    .withLimits({0.8,0.5,10})
    .buildMotionProfileController();

std::shared_ptr<AsyncMotionProfileController> profileCtrlY =
  AsyncMotionProfileControllerBuilder()
    .withOutput( odomController )
    // vel m/s, accel m/s2, jerk m/s3
    .withLimits({0.8,0.5,10})
    .buildMotionProfileController();

std::shared_ptr<XDriveModel> XDrive =
  std::dynamic_pointer_cast<XDriveModel>(odomController->getModel());

void printCoords() {
  std::cout << "X: " << XPOS_IN <<
    "\tY: " << YPOS_IN <<
    "\tTH: " << THETA_DEG << std::endl;
}

// math stuff
double toRad( double deg ) {
  return deg * M_PI / 180;
}

double toDeg( double rad ) {
  return rad * 180 / M_PI;
}

PolarPoint toPolar ( CartPoint cartesian ) {
  return {
    std::hypot( cartesian.x, cartesian.y ),
    std::atan( cartesian.y / cartesian.x )
  };
}

CartPoint toCartesian ( PolarPoint polar ) {
  return {
    polar.r * cos( polar.theta ),
    polar.r * sin( polar.theta )
  };
}

int sign( double input ) {
  if( input == 0 )
    return 0;
  else
    return ( input / std::abs(input) );
}

double distance( CartPoint p0, CartPoint p1 ) {
  return std::hypot( p1.x-p0.x, p1.y-p0.y );
}
