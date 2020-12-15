#include <stdio.h>
#include <iostream>
#include <emmintrin.h>
#include <time.h>

using std::cout;

int main()
{
    __attribute__((aligned(16))) int32_t x[] = {1,2,3,4};
    __attribute__((aligned(16))) int32_t y[] = {1,3,3,4};
   __m128i mx = _mm_loadu_si128((__m128i const*)x);
   __m128i my = _mm_loadu_si128((__m128i const*)y);
   /**
    * _mm_movemask_epi8
        FOR j := 0 to 15
            i := j*8
            dst[j] := a[i+7]
        ENDFOR
        dst[MAX:16] := 0
 */
   int i = _mm_movemask_epi8(my);
    /**
     * 
        FOR j := 0 to 15
            i := j*8
            dst[i+7:i] := ( a[i+7:i] == b[i+7:i] ) ? 0xFF : 0
        ENDFOR
        Compare packed 8-bit integers in a and b for equality, and store the results in dst
     */
   __m128i rs = _mm_cmpeq_epi32(mx,my);

   int *t = (int *)&rs;
    for (size_t i = 0; i < 4; i++)
    {
        cout << " " << t[i];
    }

   //cout << " " << i;

   return 1;
}