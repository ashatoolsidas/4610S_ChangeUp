#include "path-generation.hpp"

Path::Path( std::vector<std::vector<double>> targPoints_, double pointsPerSeg ) {
  targPoints = targPoints_;

  // iterate through each path segment
  for( int p = 0; p < targPoints.size()-1; p++ ) {
    // create points from vector input
    CartPoint p0 = { targPoints[p][0],   targPoints[p][1]  },
              p1 = { targPoints[p+1][0], targPoints[p+1][1] };

    //create path segment
    std::vector<CartPoint> pathSeg =
      pathSegment( p0, toRad(targPoints[p][2]), p1, toRad(targPoints[p+1][2]), pointsPerSeg );

    for( double t = 0; t < pathSeg.size(); t++ ) {
        pathPoints.push_back( pathSeg[t] );
    }
  }
}

// vector of all the points in the path
std::vector<CartPoint> Path::getPathPoints() {
  return pathPoints;
}

// linear interpolation: linear path over time
CartPoint Path::lerp ( CartPoint p1, CartPoint p2, double t ) {
  return {
   p1.x + (p2.x - p1.x) * t,
   p1.y + (p2.y - p1.y) * t
  };
}

// quadratic curve
CartPoint Path::quadCurve ( CartPoint p1, CartPoint p2, CartPoint p3, double t ) {
  return lerp (
    lerp( p1, p2, t ),
    lerp( p2, p3, t ),
    t
  );
}

// cubic curve
CartPoint Path::cubicCurve ( CartPoint p1, CartPoint p2, CartPoint p3, CartPoint p4, double t ) {
  return lerp (
    quadCurve( p1, p2, p3, t ),
    quadCurve( p2, p3, p4, t ),
    t
  );
}

// creates a segment of the path between two anchor points
std::vector<CartPoint> Path::pathSegment ( CartPoint p0, double th0, CartPoint p1, double th1, double numPoints ){
  std::vector<CartPoint> output;

  //distance from control to anchor pt is half the distance between anchor points
  double r = std::hypot( p0.x-p1.x, p0.y-p1.y ) / 2;

  //temporary polar coords for control points
  PolarPoint p0_ctrl_polar = { r, th0 },
             p1_ctrl_polar = { r, th1 - PI };

  //convert polar coords to cartesian
  CartPoint p0_ctrl = {
    p0.x + toCartesian( p0_ctrl_polar ).x,
    p0.y + toCartesian( p0_ctrl_polar ).y
  };

  CartPoint p1_ctrl = {
    p1.x + toCartesian( p1_ctrl_polar ).x,
    p1.y + toCartesian( p1_ctrl_polar ).y
  };

  //add to vector of points
  for( int t = 0; t <= numPoints; t++ ) {
    CartPoint curve =  cubicCurve( p0, p0_ctrl, p1_ctrl, p1, t/numPoints );
    output.push_back ( curve );
  }

  return output;
}
