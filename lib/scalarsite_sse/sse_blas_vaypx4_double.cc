// $Id: sse_blas_vaypx4_double.cc,v 1.1 2008-06-23 14:19:43 bjoo Exp $

/*! @file
 *  @brief Generic Scalar VAXPY routine
 *
 */

#include "scalarsite_sse/sse_blas_vaypx4_double.h"

namespace QDP {

#include <xmmintrin.h>

void vaypx4(REAL64 *Out,REAL64 *scalep,REAL64 *InScale, int n_4spin)
{
  __m128d scalar;
  __m128d tmp1;
  __m128d tmp2;
  __m128d tmp3;
   __m128d in1;
  __m128d add1;
  __m128d in2;
  __m128d add2;
  __m128d in3;
  __m128d add3;
  __m128d in4;
  __m128d add4;
  __m128d out1;
  __m128d out2;
  __m128d out3;

  // Load the scalar into low bytes of scalar
  scalar = _mm_load_sd(scalep);
  
  // cross components into tmp 
  // Zero tmp
  tmp1 = _mm_xor_pd(tmp1, tmp1);
  tmp1 = _mm_shuffle_pd(scalar, scalar, 0x1);
  scalar = _mm_add_pd(scalar, tmp1);

  double *in_p=InScale;
  double *out_p=Out;

 
  // We are dealing with n_4 spin 4spinor. 
  // 4 spinors 

  for(int i=0; i < n_4spin; i++) { 
    add1 = _mm_load_pd(out_p);
    in1  = _mm_load_pd(in_p);
    tmp1 = _mm_mul_pd(scalar, add1);
    out1 = _mm_add_pd(tmp1,in1);
    _mm_store_pd(out_p, out1);

    add2 = _mm_load_pd(out_p+2);
    in2  = _mm_load_pd(in_p+2);
    tmp2 = _mm_mul_pd(scalar, add2);
    out2 = _mm_add_pd(tmp2,in2);
    _mm_store_pd(out_p+2, out2);

    add3 = _mm_load_pd(out_p+4);
    in3  = _mm_load_pd(in_p+4);
    tmp3 = _mm_mul_pd(scalar, add3);
    out3 = _mm_add_pd(tmp3,in3);
    _mm_store_pd(out_p+4, out3);



    add1 = _mm_load_pd(out_p+6);
    in1  = _mm_load_pd(in_p+6);
    tmp1 = _mm_mul_pd(scalar, add1);
    out1 = _mm_add_pd(tmp1,in1);
    _mm_store_pd(out_p+6, out1);

    add2 = _mm_load_pd(out_p+8);
    in2  = _mm_load_pd(in_p+8);
    tmp2 = _mm_mul_pd(scalar, add2);
    out2 = _mm_add_pd(tmp2,in2);
    _mm_store_pd(out_p+8, out2);

    add3 = _mm_load_pd(out_p+10);
    in3  = _mm_load_pd(in_p+10);
    tmp3 = _mm_mul_pd(scalar, add3);
    out3 = _mm_add_pd(tmp3,in3);
    _mm_store_pd(out_p+10, out3);



    add1 = _mm_load_pd(out_p+12);
    in1  = _mm_load_pd(in_p+12);
    tmp1 = _mm_mul_pd(scalar, add1);
    out1 = _mm_add_pd(tmp1,in1);
    _mm_store_pd(out_p+12, out1);

    add2 = _mm_load_pd(out_p+14);
    in2  = _mm_load_pd(in_p+14);
    tmp2 = _mm_mul_pd(scalar,  add2);
    out2 = _mm_add_pd(tmp2,in2);
    _mm_store_pd(out_p+14, out2);

    add3 = _mm_load_pd(out_p+16);
    in3  = _mm_load_pd(in_p+16);
    tmp3 = _mm_mul_pd(scalar, add3);
    out3 = _mm_add_pd(tmp3,in3);
    _mm_store_pd(out_p+16, out3);


    add1 = _mm_load_pd(out_p+18);
    in1  = _mm_load_pd(in_p+18);
    tmp1 = _mm_mul_pd(scalar, add1);
    out1 = _mm_add_pd(tmp1,in1);
    _mm_store_pd(out_p+18, out1);

    add2 = _mm_load_pd(out_p+20);
    in2  = _mm_load_pd(in_p+20);
    tmp2 = _mm_mul_pd(scalar,  add2);
    out2 = _mm_add_pd(tmp2,in2);
    _mm_store_pd(out_p+20, out2);

    add3 = _mm_load_pd(out_p+22);
    in3  = _mm_load_pd(in_p+22);
    tmp3 = _mm_mul_pd(scalar, add3);
    out3 = _mm_add_pd(tmp3,in3);
    _mm_store_pd(out_p+22, out3);

    out_p+=24; in_p+=24;

  }
}




} // namespace QDP;

