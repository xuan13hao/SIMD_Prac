#include <stdio.h>
#include <iostream>
#include <emmintrin.h>
#include <time.h>

using std::cout;

int main()
{
    // __attribute__((aligned(16))) int32_t x[] = {1,2,3,4};
    // __attribute__((aligned(16))) int32_t y[] = {1,3,3,4};
    // __m128i mx = _mm_loadu_si128((__m128i const*)x);
    // __m128i my = _mm_loadu_si128((__m128i const*)y);
    // __m128i m_str = _mm_loadu_si128((__m128i const*)('A'));

    //char str = 'a';
    __m128i a = _mm_set1_epi8('A');

    char *tmp = (char *)&a;
    for (size_t i = 0; i < 4; i++)
    {
        cout << " " << tmp[i];
    }

    return 1;
}