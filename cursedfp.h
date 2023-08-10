#ifndef CURSED_FP
#define CURSED_FP


#include <unistd.h>


typedef long double f128;


f128 f128_tmp_v;
f128 *f128_tmp = &f128_tmp_v;


// helper stuff
static inline f128 *if128_f(f128 imm) {
  *f128_tmp = imm;
  return f128_tmp;
}
#define if128(i) *if128_f(i)


// floating point stack instructions
#define fs_load(f) asm volatile ("fldt %0" :: "m" (f))
#define fs_store(f) asm volatile ("fstpt %0" : "=m" (f))

#define fs_loadint(i) asm volatile ("fildt %0" :: "m" (i))
#define fs_storeint(i) asm volatile ("fistpt %0" : "=m" (i))

#define fs_imm(i) fs_load(if128(i))

#define finst(n) asm volatile(n)

#define fs_add() finst("faddp")
#define fs_sub() finst("fsubp")
#define fs_abs() finst("fabs")
#define fs_mul() finst("fmulp")
#define fs_div() finst("fdivp")
#define fs_sqrt() finst("fsqrt")
#define fs_tan() finst("fptan")
#define fs_atan() finst("fpatan")
#define fs_round() finst("frndint")
#define fs_sin() finst("fsin")
#define fs_cos() finst("fcos")

#define fs_neg() finst("fchs")
#define fs_swp() finst("fxch")

f128 fs_pop() {
  fs_store(f128_tmp_v);
  f128 *p = (f128 *)sbrk(sizeof(f128));
  for (size_t i = 0; i < sizeof(f128); i++)
    *(p+i) = *(f128_tmp+i);
  return *p;
}


// ==== UNRECOMMENDED ====
// floating point instructions for variables
#define f_add(a, b, res) do { \
    fs_load(b); \
    fs_load(a); \
    fs_add(); \
    fs_store(res); \
  } while (0);

#define f_sub(a, b, res) do { \
    fs_load(b); \
    fs_load(a); \
    fs_sub(); \
    fs_store(res); \
  } while (0);

#define f_neg(a) do { \
    fs_load(a); \
    fs_neg(); \
    fs_store(a); \
  } while (0);

#endif
