#ifndef VISQPROJECT_INCLUDE_VISQ_GEOMETRY_POINT_2_D_H_
#define VISQPROJECT_INCLUDE_VISQ_GEOMETRY_POINT_2_D_H_


namespace visq::geometry {

template<typename T>
struct Point2D {
  Point2D() = default;
  Point2D(T _x, T _y) : x(_x), y(_y) {}
  T x;
  T y;

  bool operator==(const Point2D<T> & other) const{
    return x == other.x && y == other.y;
  }
};

} // geometry
// visq

#endif //VISQPROJECT_INCLUDE_VISQ_GEOMETRY_POINT_2_D_H_
