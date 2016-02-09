#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arm_neon.h>

typedef int16x8_t v16 __attribute__ ((aligned (16)));
typedef int8x16_t v8 __attribute__ ((aligned (16)));
typedef int8x8_t sv8 __attribute__ ((aligned (16)));
typedef int8x8x2_t dsv8 __attribute__ ((aligned (16)));
typedef int32x2_t sv32 __attribute__((aligned (16)));

#define v16_and vandq_s16
#define v16_or  vorrq_s16
#define v16_xor veorq_s16

#define v16_add vaddq_s16
#define v16_sub vsubq_s16
#define v16_mul vmulq_s16
#define v16_neg vnegq_s16

#define v16_shift_r  vshrq_n_s16
#define v16_shift_l  vshlq_n_s16

#define v16_to_v8 vreinterpretq_s8_s16
#define sv8_to_sv32 vreinterpret_s32_s8

#define v8_lside vget_high_s8
#define v8_rside vget_low_s8

#define v8_transpose(x) vtrn_s8(v8_lside(x), v8_rside(x))


#define v16_movemask(x) ({			\
      dsv8 q0 = v8_transpose(v16_to_v8(x));	\
      sv32 q1 = vreinterpret_s32_s8(q0.val[0]);	\
      q1[0]|q1[1];				\
    })


int main(){
  v16 a;
  v8 b;
  dsv8 tr;
  sv32 c;
  int i, mask;

  for(i = 0; i < 8; i++){
    a[i] = 0;
  }

  a[0] = 0xffff;
  a[7] = 0xffff;

  b = v16_to_v8(a);

  /* for(i = 0; i <16 ; i++){ */
  /*   printf("b[%d] = %d\n", i, b[i]); */
  /* } */

  tr = v8_transpose(b);



  /* for(i = 0; i < 8; i++){ */
  /*   printf("tr0[%d] = %d ; tr1[%d] = %d\n", i, tr.val[0][i], i, tr.val[1][i]); */
  /* } */

  c = sv8_to_sv32(tr.val[0]);

  mask = v16_movemask(a);

  printf("mask = %x\n", mask);
  for(i = 0; i < 2; i++){
    printf("c[%d] = %x\n", i, c[i]);
  }

}

