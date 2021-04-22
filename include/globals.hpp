#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "main.h"

// config
extern pros::Controller   Control;
extern pros::Motor        FrontLeft, FrontRight, BackLeft, BackRight,
                          Indexer, Launcher, IntakeLeft, IntakeRight;
extern pros::ADIEncoder   LeftOdom, RightOdom, BackOdom;
extern pros::ADIAnalogIn  Line;
extern pros::Optical      Opt;
extern pros::Distance     Lidar;
extern pros::Imu          Inert;
extern pros::ADIDigitalIn Bumper;

// okapi pointers
extern std::shared_ptr<OdomChassisController>         odomController;
extern std::shared_ptr<AsyncMotionProfileController>  profileCtrlX;
extern std::shared_ptr<AsyncMotionProfileController>  profileCtrlY;
extern std::shared_ptr<XDriveModel>                   XDrive;

// odom defines
#define XPOS_IN    odomController->getState().x.convert(inch)
#define YPOS_IN    odomController->getState().y.convert(inch)
#define XPOS_FT    odomController->getState().x.convert(foot)
#define YPOS_FT    odomController->getState().y.convert(foot)
#define THETA_DEG  odomController->getState().theta.convert(degree)
#define THETA_RAD  odomController->getState().theta.convert(radian)
void printCoords();

//controls
#define LAUNCH_BTN      Control.get_digital( DIGITAL_R1 )
#define EJECT_BTN       Control.get_digital( DIGITAL_R2 )
#define INTAKE_BTN      Control.get_digital( DIGITAL_L1 )
#define OUTTAKE_BTN     Control.get_digital( DIGITAL_DOWN )
#define INDEXOUT_BTN    Control.get_digital( DIGITAL_L2 )
#define SLOWLAUNCH_BTN  Control.get_digital( DIGITAL_UP );
#define DEPLOY_BTN      Control.get_digital( DIGITAL_Y );

//math stuff
struct PolarPoint {
  double r, theta;
  PolarPoint();
  PolarPoint ( double r_, double theta_ ) : r(r_), theta(theta_) {};
};

struct CartPoint {
  double x, y;
  CartPoint();
  CartPoint ( double x_, double y_ ) : x(x_), y(y_) {};
};

double toRad ( double deg );
double toDeg ( double rad );

PolarPoint toPolar ( CartPoint cartesian );
CartPoint toCartesian ( PolarPoint polar );

int sign( double input );

double distance( CartPoint p0, CartPoint p1 );

#endif
