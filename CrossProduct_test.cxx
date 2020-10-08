#include "CrossProduct.h"
#include <iostream>

int
main()
{
  const double a[3] = { 1, 3, 4 };
  const double b[3] = { 5, 6, 7 };
  double c[3] = {};
  crossVecSSE(c, a, b);
  for (int i = 0; i < 3; ++i) {
    std::cout << c[i] << '\n';
  }
  std::cout << '\n';
  crossScalar(c, a, b);
  for (int i = 0; i < 3; ++i) {
    std::cout << c[i] << '\n';
  }
  std::cout << '\n';
  return 0;
}

