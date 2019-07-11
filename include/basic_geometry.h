#ifndef ESS_POINT_H
#define ESS_POINT_H

#include <cmath>
#include <type_traits>

namespace ess
{
  //---------------------------------------------------------------------------
  //                                                                  concepts
  //---------------------------------------------------------------------------

  // Clang-Format does not support formatting Concepts, yet.
  // clang-format off
  template <typename T>
  concept bool Integer =
    std::is_integral_v<T>
    && !(std::is_same_v<std::decay_t<T>, bool>
      || std::is_same_v<std::decay_t<T>, char>
      || std::is_same_v<std::decay_t<T>, signed char>
      || std::is_same_v<std::decay_t<T>, unsigned char>
      || std::is_same_v<std::decay_t<T>, char16_t>
      || std::is_same_v<std::decay_t<T>, char32_t>
      || std::is_same_v<std::decay_t<T>, wchar_t>);

  template <typename T>
  concept bool Number = std::is_floating_point_v< T> || Integer<T>;
  // clang-format on

  //---------------------------------------------------------------------------
  //                                                    point & vector classes
  //---------------------------------------------------------------------------

  template <typename T>
  class vector2;
  template <typename T>
  class vector3;

  template <Number T>
  struct P final
  {
    T x {0};
    T y {0};
  };

  template <typename T>
  struct point2 final
  {
    using value_type = std::decay_t<T>;
    value_type x {0};
    value_type y {0};

    // template <typename U>
    // explicit point2(const vector2<U>& v): x {v.x}, y {v.y}
    //{
    //}
  };

  template <typename T>
  struct point3 final
  {
    using value_type = std::decay_t<T>;
    value_type x;
    value_type y;
    value_type z;
  };

  template <typename T>
  struct vector2 final
  {
    using value_type = std::decay_t<T>;
    value_type x;
    value_type y;
  };

  template <typename T>
  struct vector3 final
  {
    using value_type = std::decay_t<T>;
    value_type x;
    value_type y;
    value_type z;
  };

  //---------------------------------------------------------------------------
  //                                                                comparison
  //---------------------------------------------------------------------------

  template <typename T, typename U>
  constexpr bool operator==(const point2<T>& a, const point2<U>& b) noexcept
  {
    return a.x == b.x && a.y == b.y;
  }

  template <typename T, typename U>
  constexpr bool operator!=(const point2<T>& a, const point2<U>& b) noexcept
  {
    return !(a == b);
  }

  template <typename T, typename U>
  constexpr bool operator==(const point3<T>& a, const point3<U>& b) noexcept
  {
    return a.x == b.x && a.y == b.y && a.z == b.y;
  }

  template <typename T, typename U>
  constexpr bool operator!=(const point3<T>& a, const point3<U>& b) noexcept
  {
    return !(a == b);
  }

  template <typename T, typename U>
  constexpr bool operator==(const vector2<T>& a, const vector2<U>& b) noexcept
  {
    return a.x == b.x && a.y == b.y;
  }

  template <typename T, typename U>
  constexpr bool operator!=(const vector2<T>& a, const vector2<U>& b) noexcept
  {
    return !(a == b);
  }

  template <typename T, typename U>
  constexpr bool operator==(const vector3<T>& a, const vector3<U>& b) noexcept
  {
    return a.x == b.x && a.y == b.y && a.z == b.y;
  }

  template <typename T, typename U>
  constexpr bool operator!=(const vector3<T>& a, const vector3<U>& b) noexcept
  {
    return !(a == b);
  }

  //---------------------------------------------------------------------------
  //                                                     arithmetic operations
  //---------------------------------------------------------------------------

  // negation of points and vectors
  template <typename T>
  constexpr point2<T> operator-(const point2<T>& p)
  {
    return point2<T> {-p.x, -p.y};
  }

  template <typename T>
  constexpr point3<T> operator-(const point3<T>& p)
  {
    return point3<T> {-p.x, -p.y};
  }

  template <typename T>
  constexpr vector2<T> operator-(const vector2<T>& p)
  {
    return vector2<T> {-p.x, -p.y};
  }

  template <typename T>
  constexpr vector3<T> operator-(const vector3<T>& p)
  {
    return vector3<T> {-p.x, -p.y};
  }

  // P - Q = V
  // P + V = Q
  template <typename T, typename U>
  constexpr auto operator-(const point2<T>& p, const point2<U>& q)
  {
    using V = std::common_type_t<T, U>;
    return vector2<V> {p.x - q.x, p.y - q.y};
  }

  template <typename T, typename U>
  constexpr auto operator-(const point3<T>& p, const point3<U>& q)
  {
    using V = std::common_type_t<T, U>;
    return vector3<V> {p.x - q.x, p.y - q.y};
  }

  template <typename T, typename U>
  constexpr auto operator+(const point2<T>& p, const vector2<U>& v)
  {
    using V = std::common_type_t<T, U>;
    return point2<V> {p.x + v.x, p.y + v.y};
  }

  template <typename T, typename U>
  constexpr auto operator+(const vector2<T>& v, const point2<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return point2<V> {p.x + v.x, p.y + v.y};
  }

  template <typename T, typename U>
  constexpr auto operator+(const point3<T>& p, const vector3<U>& v)
  {
    using V = std::common_type_t<T, U>;
    return point3<V> {p.x + v.x, p.y + v.y};
  }

  template <typename T, typename U>
  constexpr auto operator+(const vector3<T>& v, const point3<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return point3<V> {p.x + v.x, p.y + v.y};
  }

  // sP, sV, Ps, Vs
  template <typename T, typename U>
  constexpr auto operator*(const point2<T>& p, const U s)
  {
    using V = std::common_type_t<T, U>;
    return point2<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const T s, const point2<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return point2<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const point3<T>& p, const U s)
  {
    using V = std::common_type_t<T, U>;
    return point3<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const T s, const point3<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return point3<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const vector2<T>& p, const U s)
  {
    using V = std::common_type_t<T, U>;
    return vector2<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const T s, const vector2<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return vector2<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const vector3<T>& p, const U s)
  {
    using V = std::common_type_t<T, U>;
    return vector3<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const T s, const vector3<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return vector3<V> {p.x * s, p.y * s};
  }

  // vector addition & subtraction

  // non-uniform scale

  //---------------------------------------------------------------------------
  //                                                 point & vector operations
  //---------------------------------------------------------------------------

  template <typename T>
  constexpr vector2<T> square_length(const vector2<T>& v)
  {
    return v.x * v.x + v.y * v.y;
  }

  template <typename T>
  constexpr vector2<T> length(const vector2<T>& v)
  {
    return std::sqrt(square_length(v));
  }

  template <typename T>
  constexpr vector3<T> square_length(const vector3<T>& v)
  {
    return v.x * v.x + v.y * v.y + v.z * v.z;
  }

  template <typename T>
  constexpr vector3<T> length(const vector3<T>& v)
  {
    return std::sqrt(square_length(v));
  }

  template <typename T, typename U>
  constexpr auto dot(const vector2<T>& v, const vector2<U>& w)
  {
    return v.x * w.x + v.y * w.y;
  }

  template <typename T, typename U>
  constexpr auto dot(const vector3<T>& v, const vector3<U>& w)
  {
    return v.x * w.x + v.y * w.y + v.z * w.z;
  }

  template <typename T, typename U>
  constexpr auto cross(const vector3<T>& v, const vector3<U>& w)
  {
    using V = std::common_type_t<T, U>;
    return vector3<V> {
      v.y * v.z + v.z * w.y, w.x * v.z + w.z * v.x, v.x * w.y + v.y * w.x};
  }

  //---------------------------------------------------------------------------
  //                                                    point & vector casting
  //---------------------------------------------------------------------------

  template <typename T, typename U>
  constexpr point2<T> point_cast(const vector2<U>& v)
  {
    return point3<T> {static_cast<T>(v.x), static_cast<T>(v.y)};
  }

  template <typename T, typename U>
  constexpr point3<T> point_cast(const vector3<U>& v)
  {
    return point3<T> {
      static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z)};
  }

  template <typename T, typename U>
  constexpr vector2<T> vector_cast(const point2<U>& p)
  {
    return vector2<T> {static_cast<T>(p.x), static_cast<T>(p.y)};
  }

  template <typename T, typename U>
  constexpr vector3<T> vector_cast(const point3<U>& p)
  {
    return vector3<T> {
      static_cast<T>(p.x), static_cast<T>(p.y), static_cast<T>(p.z)};
  }
}  // namespace ess

#endif
