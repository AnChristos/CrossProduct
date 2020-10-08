#ifndef CROSSPRODUCT_H
#define CROSSPRODUCT_H
#include "vec.h"

inline void
crossScalar(double* __restrict__ c,
            const double* __restrict__ a,
            const double* __restrict__ b)
{
  c[0] = a[1] * b[2] - a[2] * b[1];
  c[1] = a[2] * b[0] - a[0] * b[2];
  c[2] = a[0] * b[1] - a[1] * b[0];
}

inline void
crossVecSSE(double* __restrict__ c,
            const double* __restrict__ a,
            const double* __restrict__ b)
{
  //
  using namespace CxxUtils;
  using vec2 = CxxUtils::vec<double, 2>;
  vec2 A_yz;
  vload(A_yz, &a[1]);
  vec2 B_yz;
  vload(B_yz, &b[1]);

  vec2 B_x{ b[0], 0 };
  vec2 B_zx{};
  vblend<1, 2>(B_zx, B_yz, B_x);
  vec2 A_yz_x_B_zx = A_yz * B_zx;

  vec2 A_x{ a[0], 0 };
  vec2 A_zx{};
  vblend<1, 2>(A_zx, A_yz, A_x);
  vec2 A_zx_B_yz = A_zx * B_yz;

  vec2 C_xy = A_yz_x_B_zx - A_zx_B_yz;

  vstore(&c[0], C_xy);
  c[2] = a[0] * b[1] - a[1] * b[0];
}
#endif
