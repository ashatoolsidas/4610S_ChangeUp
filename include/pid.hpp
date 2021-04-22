#ifndef PID_H
#define PID_H

#include "main.h"

class PD {
private:
  double kp, kd;
  double P, D;
  double err, prevErr;

public:
  /**
  * Constructor
  * @param kp_  proportion constant
  * @param kd_  derivative constant
  */
  PD( double kp_ , double kd_ );

  /**
  * Getter for kP
  * @return  kP
  */
  double getKp();

  /**
  * Getter for kD
  * @retrun  kD
  */
  double getKd();

  /**
  * Resets variables
  * @param new_targ  target distance for the next path
  */
  void reset( int new_targ = 0 );

  /**
  * Speed for the robot to move in the next cycle
  * @return          next speed
  * @param pos       current position
  * @param target    goal position
  * @param maxSpeed  speed cap in rpm
  */
  double speed( double pos, double target, double maxSpeed );
};

#endif
