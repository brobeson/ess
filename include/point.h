#ifndef ESS_POINT_H
#define ESS_POINT_H

namespace ess
{
  template <typename T, size_t D>
  struct point
  {
  public:
    using value_type = T;
    using dimensions = D;
    
    T x;
    T y;
    std::enable_if
