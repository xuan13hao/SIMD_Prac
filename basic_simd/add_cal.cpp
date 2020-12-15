#include <stdio.h>
#include <iostream>
#include <emmintrin.h>
#include <time.h>

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    /**
     * Scalar Calculus
     */
    int a[] = {1,2,3,4};
    int b[] = {1,2,3,4};
    double c[] = {1.01,2.02};
    double d[] = {1.03,2.04};
    for (size_t i = 0; i < 4; i++)
    {
        cout << " " << a[i] + b[i] << endl;
        
    }
    /**
     * SIMD Calculus
     * int
     */
    __m128i r1 = _mm_loadu_si128((__m128i const*)a);
    __m128i r2 = _mm_loadu_si128((__m128i const*)b);
    __m128i result = _mm_add_epi64(r1,r2);
    int *r_1 = (int *)&r1;
    int *r_2 = (int *)&r2;
    int *tmp = (int *)&result;
    for (size_t i = 0; i < 4; i++)
    {
        /* code */
        cout << "r1:" << r_1[i] << "+ r2: " << r_2[i] << "= sum: " << tmp[i] << endl;
        
    }

    /**
     * SIMD Calculus
     * double
     */
    __m128d s1 = _mm_load_pd(c);
    __m128d s2 = _mm_load_pd(d);
    __m128d rt = _mm_add_pd(s1,s2);
    double *s_1 = (double *)&s1;
    double *s_2 = (double *)&s2;
    double *temp = (double *)&rt;
    for (size_t i = 0; i < 2; i++)
    {
        /* code */
        cout << "s1:" << s_1[i] << "+ s2: " << s_2[i] << "= sum: " << temp[i] << endl;
        
    }

    /**
     * Implement a for-loop without/with SIMD
     */
    // __m128i x, y, z,*res;
    int n = 200000;
    // int *mm_x = (int*)_mm_malloc(sizeof(int)*n,16);
    // int *mm_y = (int*)_mm_malloc(sizeof(int)*n,16);
    // int *mm_z = (int*)_mm_malloc(sizeof(int)*n,16);
    __attribute__((aligned(16))) int x[] = {1,2,3,4};
    __attribute__((aligned(16))) int y[] = {0,0,0,0};
    __attribute__((aligned(16))) int z[] = {4,4,4,4};
    __m128i mx = _mm_loadu_si128((__m128i const*)x);
    __m128i my = _mm_loadu_si128((__m128i const*)y);
    __m128i mz = _mm_loadu_si128((__m128i const*)z);
    int s = 0;
    clock_t start = clock();
    for (size_t i = 1; i <= n; i++)
    {
        s += i;
    }
    
    clock_t end = clock();
    cout << "Total 200000000 without SIMD = " <<double(end-start)/CLOCKS_PER_SEC<<","<<s<< endl;

    clock_t start_w = clock();
    for (size_t i = 1; i <= n ; i = i + 4)
    {
       
            my = _mm_add_epi64(my,mx);
            mx = _mm_add_epi64(mx,mz);
       
    }
    int *sum_ = (int*)&my;
    int s_s = sum_[0] + sum_[1] + sum_[2] + sum_[3];
    clock_t end_w = clock();
    cout << "Total 200000000 with SIMD = " <<double(end_w-start_w)/CLOCKS_PER_SEC<<","<<s_s<<endl;

    cout << "SIMD is faster than without SIMD = " <<(double)(end-start)/(end_w-start_w) <<endl;
    // int *rest = (int*)res;
    // for (size_t i = 0; i < sizeof(rest); i++)
    // {
    //     cout << " " <<rest[i];
    // }
    return 0;
}