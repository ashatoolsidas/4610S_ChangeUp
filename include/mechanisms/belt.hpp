#ifndef BELT
#define BELT

#include "main.h"

class Belt {
private:
  static bool index;
  static bool sort;
public:
  Belt();

  /**
  * autoIndex getter
  * @return  index
  */
  bool autoIndex();

  /**
  * autoIndex setter
  * @param i  value to set index to
  */
  void setAutoIndex( bool i );

  /**
  * autoSort getter
  * @return  sort
  */
  bool autoSort();

  /**
  * autoSort setter
  * @param s  value to set sort to
  */
  void setAutoSort( bool s );


  /**
  * Runs indexer and launcher
  * @param loc    where to direct ball:
  *               "top", "back", "bottom", "indexer", or "sort"
  * @param speed  speed in rpm
  */
  void run( std::string loc = "top", int speed = 600 );

  /**
  * Shoot out only one ball
  * @param timeout  whether to stop after a
  *                 certain amount of time
  */
  void shoot( bool timeout = true );

  /**
  * Stops indexer and launcher
  */
  void stop();

  /**
  * Deploy macro
  */
  void deploy();

  /**
  * TeleOp control
  * @param speed  speed in rpm
  */
  void teleOp( int speed = 600 );

};

extern Belt belt;

#endif
