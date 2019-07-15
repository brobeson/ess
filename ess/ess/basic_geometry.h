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

  template <Number T>
  class basic_2d_vector;
  template <Number T>
  class basic_3d_vector;

  template <Number T>
  struct basic_2d_point final
  {
    using value_type = T;
    value_type x {0};
    value_type y {0};
  };

  template <Number T>
  struct basic_3d_point final
  {
    using value_type = T;
    value_type x {0};
    value_type y {0};
    value_type z {0};
  };

  template <Number T>
  struct basic_2d_vector final
  {
    using value_type = T;
    value_type x {0};
    value_type y {0};
  };

  template <Number T>
  struct basic_3d_vector final
  {
    using value_type = T;
    value_type x {0};
    value_type y {0};
    value_type z {0};
  };

  using ipoint_2d = basic_2d_point<int>;
  using fpoint_2d = basic_2d_point<float>;
  using dpoint_2d = basic_2d_point<double>;
  using ipoint_3d = basic_3d_point<int>;
  using fpoint_3d = basic_3d_point<float>;
  using dpoint_3d = basic_3d_point<double>;
  using ivector_2d = basic_2d_vector<int>;
  using fvector_2d = basic_2d_vector<float>;
  using dvector_2d = basic_2d_vector<double>;
  using ivector_3d = basic_3d_vector<int>;
  using fvector_3d = basic_3d_vector<float>;
  using dvector_3d = basic_3d_vector<double>;

  //---------------------------------------------------------------------------
  //                                                                comparison
  //---------------------------------------------------------------------------

  template <typename T, typename U>
  constexpr bool operator==(const basic_2d_point<T>& a,
                            const basic_2d_point<U>& b) noexcept
  {
    return a.x == b.x && a.y == b.y;
  }

  template <typename T, typename U>
  constexpr bool operator!=(const basic_2d_point<T>& a,
                            const basic_2d_point<U>& b) noexcept
  {
    return !(a == b);
  }

  template <typename T, typename U>
  constexpr bool operator==(const basic_3d_point<T>& a,
                            const basic_3d_point<U>& b) noexcept
  {
    return a.x == b.x && a.y == b.y && a.z == b.z;
  }

  template <typename T, typename U>
  constexpr bool operator!=(const basic_3d_point<T>& a,
                            const basic_3d_point<U>& b) noexcept
  {
    return !(a == b);
  }

  /*
  template <typename T, typename U>
  constexpr bool operator==(const basic_2d_vector<T>& a,
                            const basic_2d_vector<U>& b) noexcept
  {
    return a.x == b.x && a.y == b.y;
  }

  template <typename T, typename U>
  constexpr bool operator!=(const basic_2d_vector<T>& a,
                            const basic_2d_vector<U>& b) noexcept
  {
    return !(a == b);
  }

  template <typename T, typename U>
  constexpr bool operator==(const basic_3d_vector<T>& a,
                            const basic_3d_vector<U>& b) noexcept
  {
    return a.x == b.x && a.y == b.y && a.z == b.y;
  }

  template <typename T, typename U>
  constexpr bool operator!=(const basic_3d_vector<T>& a,
                            const basic_3d_vector<U>& b) noexcept
  {
    return !(a == b);
  }

  //---------------------------------------------------------------------------
  //                                                     arithmetic operations
  //---------------------------------------------------------------------------

  // negation of points and vectors
  template <typename T>
  constexpr basic_2d_point<T> operator-(const basic_2d_point<T>& p)
  {
    return basic_2d_point<T> {-p.x, -p.y};
  }

  template <typename T>
  constexpr basic_3d_point<T> operator-(const basic_3d_point<T>& p)
  {
    return basic_3d_point<T> {-p.x, -p.y};
  }

  template <typename T>
  constexpr basic_2d_vector<T> operator-(const basic_2d_vector<T>& p)
  {
    return basic_2d_vector<T> {-p.x, -p.y};
  }

  template <typename T>
  constexpr basic_3d_vector<T> operator-(const basic_3d_vector<T>& p)
  {
    return basic_3d_vector<T> {-p.x, -p.y};
  }

  // P - Q = V
  // P + V = Q
  template <typename T, typename U>
  constexpr auto operator-(const basic_2d_point<T>& p,
                           const basic_2d_point<U>& q)
  {
    using V = std::common_type_t<T, U>;
    return basic_2d_vector<V> {p.x - q.x, p.y - q.y};
  }

  template <typename T, typename U>
  constexpr auto operator-(const basic_3d_point<T>& p,
                           const basic_3d_point<U>& q)
  {
    using V = std::common_type_t<T, U>;
    return basic_3d_vector<V> {p.x - q.x, p.y - q.y};
  }

  template <typename T, typename U>
  constexpr auto operator+(const basic_2d_point<T>& p,
                           const basic_2d_vector<U>& v)
  {
    using V = std::common_type_t<T, U>;
    return basic_2d_point<V> {p.x + v.x, p.y + v.y};
  }

  template <typename T, typename U>
  constexpr auto operator+(const basic_2d_vector<T>& v,
                           const basic_2d_point<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return basic_2d_point<V> {p.x + v.x, p.y + v.y};
  }

  template <typename T, typename U>
  constexpr auto operator+(const basic_3d_point<T>& p,
                           const basic_3d_vector<U>& v)
  {
    using V = std::common_type_t<T, U>;
    return basic_3d_point<V> {p.x + v.x, p.y + v.y};
  }

  template <typename T, typename U>
  constexpr auto operator+(const basic_3d_vector<T>& v,
                           const basic_3d_point<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return basic_3d_point<V> {p.x + v.x, p.y + v.y};
  }

  // sP, sV, Ps, Vs
  template <typename T, typename U>
  constexpr auto operator*(const basic_2d_point<T>& p, const U s)
  {
    using V = std::common_type_t<T, U>;
    return basic_2d_point<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const T s, const basic_2d_point<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return basic_2d_point<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const basic_3d_point<T>& p, const U s)
  {
    using V = std::common_type_t<T, U>;
    return basic_3d_point<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const T s, const basic_3d_point<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return basic_3d_point<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const basic_2d_vector<T>& p, const U s)
  {
    using V = std::common_type_t<T, U>;
    return basic_2d_vector<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const T s, const basic_2d_vector<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return basic_2d_vector<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const basic_3d_vector<T>& p, const U s)
  {
    using V = std::common_type_t<T, U>;
    return basic_3d_vector<V> {p.x * s, p.y * s};
  }

  template <typename T, typename U>
  constexpr auto operator*(const T s, const basic_3d_vector<U>& p)
  {
    using V = std::common_type_t<T, U>;
    return basic_3d_vector<V> {p.x * s, p.y * s};
  }

  // vector addition & subtraction

  // non-uniform scale

  //---------------------------------------------------------------------------
  //                                                 point & vector operations
  //---------------------------------------------------------------------------

  template <typename T>
  constexpr basic_2d_vector<T> square_length(const basic_2d_vector<T>& v)
  {
    return v.x * v.x + v.y * v.y;
  }

  template <typename T>
  constexpr basic_2d_vector<T> length(const basic_2d_vector<T>& v)
  {
    return std::sqrt(square_length(v));
  }

  template <typename T>
  constexpr basic_3d_vector<T> square_length(const basic_3d_vector<T>& v)
  {
    return v.x * v.x + v.y * v.y + v.z * v.z;
  }

  template <typename T>
  constexpr basic_3d_vector<T> length(const basic_3d_vector<T>& v)
  {
    return std::sqrt(square_length(v));
  }

  template <typename T, typename U>
  constexpr auto dot(const basic_2d_vector<T>& v, const basic_2d_vector<U>& w)
  {
    return v.x * w.x + v.y * w.y;
  }

  template <typename T, typename U>
  constexpr auto dot(const basic_3d_vector<T>& v, const basic_3d_vector<U>& w)
  {
    return v.x * w.x + v.y * w.y + v.z * w.z;
  }

  template <typename T, typename U>
  constexpr auto cross(const basic_3d_vector<T>& v, const basic_3d_vector<U>& w)
  {
    using V = std::common_type_t<T, U>;
    return basic_3d_vector<V> {
      v.y * v.z + v.z * w.y, w.x * v.z + w.z * v.x, v.x * w.y + v.y * w.x};
  }

  //---------------------------------------------------------------------------
  //                                                    point & vector casting
  //---------------------------------------------------------------------------

  template <typename T, typename U>
  constexpr basic_2d_point<T> point_cast(const basic_2d_vector<U>& v)
  {
    return basic_3d_point<T> {static_cast<T>(v.x), static_cast<T>(v.y)};
  }

  template <typename T, typename U>
  constexpr basic_3d_point<T> point_cast(const basic_3d_vector<U>& v)
  {
    return basic_3d_point<T> {
      static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z)};
  }

  template <typename T, typename U>
  constexpr basic_2d_vector<T> vector_cast(const basic_2d_point<U>& p)
  {
    return basic_2d_vector<T> {static_cast<T>(p.x), static_cast<T>(p.y)};
  }

  template <typename T, typename U>
  constexpr basic_3d_vector<T> vector_cast(const basic_3d_point<U>& p)
  {
    return basic_3d_vector<T> {
      static_cast<T>(p.x), static_cast<T>(p.y), static_cast<T>(p.z)};
  }
  */
}  // namespace ess

#endif
