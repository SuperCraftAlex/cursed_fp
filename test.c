#include "cursedfp.h"
#include <stdio.h>

int main() {
  f128 a = 3.3;
  f128 b = 0.4;
  f128 res;

  fs_load(b);
  fs_load(a);
  fs_add();
  fs_imm(1.2);
  fs_swp();
  fs_sub();
  fs_neg();
  res = fs_pop();

  //f_add(a, b, res);
  //f_sub(res, if128(1.2), res);
  //f_neg(res);

  printf("%Lg\n", res);

  return 0;
}
