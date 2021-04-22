#ifndef INTAKES
#define INTAKES

class Intakes {
public:
  Intakes();
  /**
  * Runs the intakes
  * @param speed  speed in rpm to run intakes
  */
  void run( int speed = 600 );

  /**
  * Stops and brakes intakes
  */
  void stop();

  /**
  * TeleOp control
  * @param speed  speed in rpm to run intakes
  */
  void teleOp( int speed = 600 );
};

extern Intakes intakes;

#endif
