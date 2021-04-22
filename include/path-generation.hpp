#ifndef PATH_GENERATION_HPP
#define PATH_GENERATION_HPP

#include <vector>
#include <cmath>
#include "globals.hpp"

class Path {
  private:
    std::vector<std::vector<double>> targPoints;
    std::vector<CartPoint> pathPoints;

  public:
    /**
    * Constructor
    * @param targPoints    vector of anchor points in the path
    * @param pointsPerSeg  number of points to include in each segment
    */
    Path( std::vector<std::vector<double>> targPoints_, double pointsPerSeg = 20 );

    /**
    * @return  vector of the points in the path
    */
    std::vector<CartPoint> getPathPoints();

    /**
    * Linear interpolation function
    * @param p1  first anchor point
    * @param p2  second anchor point
    * @param t   time along the path (0-1)
    * @return    point on path at specified time
    */
    CartPoint lerp ( CartPoint p1, CartPoint p2, double t );

    /**
    * Quadratic interpolation function
    * @param p1  first anchor point
    * @param p2  control point
    * @param p3  second anchor point
    * @param t   time along the path (0-1)
    * @return    point on path at specified time
    */
    CartPoint quadCurve ( CartPoint p1, CartPoint p2, CartPoint p3, double t );

    /**
    * Quadratic interpolation function
    * @param p1  first anchor point
    * @param p2  first control point
    * @param p3  second control point
    * @param p4  second anchor point
    * @param t   time along the path (0-1)
    * @return    point on path at specified time
    */
    CartPoint cubicCurve ( CartPoint p1, CartPoint p2, CartPoint p3, CartPoint p4, double t );

    /**
    * Create segment of path between two anchor points
    * @param p0         first anchor point
    * @param th0        heading at p0
    * @param p1         second anchor point
    * @param th1        heading at p1
    * @param numPoints  number of points to generate
    * @return           vector of points along the segment
    */
    std::vector<CartPoint> pathSegment ( CartPoint p0, double th0, CartPoint p1, double th1, double numPoints = 20 );
};

#endif
