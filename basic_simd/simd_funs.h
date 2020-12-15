#ifndef __SIMD_FUNS_H__
#define __SIMD_FUNS_H__

#pragma once
 
#include <immintrin.h>
#include <stdio.h>
 
float MathMulAdd(const float *input1, const float *input2, int size);
float SSEMulAdd(const float *input1, const float *input2, int size);
float SSEFmAdd(const float *input1, const float *input2, int size);
float AVXMulAdd(const float *input1, const float *input2, int size);
float AVXFmAdd(const float *input1, const float *input2, int size);


#endif // __SIMD_FUNS_H__