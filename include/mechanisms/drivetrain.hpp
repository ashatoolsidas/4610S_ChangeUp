#ifndef DRIVE
#define DRIVE

#include <string>
#include <functional>
#include "path-generation.hpp"
#include "pid.hpp"


class Drivetrain {
  private:
    std::string ctrlType;
  public:
    /**
    * Constructor
    */
    Drivetrain();

    void move (double speed);

    void move (double fl, double fr, double bl, double br);


    void forwards(double dist, PD pd );
    void strafe(double dist, PD pd );
    void bumper(double speed, bool correct = true);

    /**
    * Gets control type
    * @return control type string: "arcade" or "tank"
    */
    std::string getCtrlType();

    /**
    * Strafes to a point without turning
    * @ param dest  robot desination point
    * @ param pd    pd controller
    */
    void strafeTo( CartPoint dest, PD pd );
    void strafeTo( CartPoint dest, double heading, double speed );


    void strafeAlong( Path path, PD pd );
    void strafeAlong( Path path, double speed );

    void turn( double heading, PD pd, std::string cor = "c", bool rev = false );
    void turnCrazy( double heading, PD pd, std::string cor = "c", bool rev = false);

    /**
    * Toggles control type between "arcade" and "tank"
    */
    void toggleCtrlType();

    /**
    * TeleOp control
    * @param speedCtrl  multiplier for speed
    * @param deadzone   size of joystick deadzone
    */
    void teleOp(  double speedCtrl = 1, double deadzone = 0.05 );



    double getVelocity( std::string unit );

    void velocityTest();
    /**
    */
    double getMaxAcceleration();

    /**
    */
    double getMaxJerk();
};

extern Drivetrain drivetrain;

#endif
