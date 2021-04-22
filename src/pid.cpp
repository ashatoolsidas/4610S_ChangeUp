#include "pid.hpp"

//constructor
PD::PD( double kP, double kD ) :
    kp(kP), kd(kD) {};

void PD::reset( int new_targ ) {
  P = D = 0;
  prevErr = err = new_targ;
}

double PD::getKp() {
  return kp;
}

double PD::getKd() {
  return kd;
}

//calculate speed
double PD::speed( double pos, double target, double maxSpeed ) {
  err = target - pos; // distance to target
  P = err; // proportion
  D = err - prevErr; //derivative
  prevErr = err; // reset prevErr

  //calculate speed
  int spd = P*kp + D*kd;

  //don't let speed go over the maximum
  if( spd > maxSpeed )
    return maxSpeed;
  // if( spd < maxSpeed/5 )
  //   return maxSpeed / 5;

  return spd;
}
