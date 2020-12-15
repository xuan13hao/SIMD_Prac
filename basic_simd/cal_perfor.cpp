#include <iostream>
#include <time.h>
#include <immintrin.h>
using namespace std;
#define N 20000000
int main()
{
    double *x,*y,*z;
    x=(double*)malloc(sizeof(double)*N);
    y=(double*)malloc(sizeof(double)*N);
    z=(double*)malloc(sizeof(double)*N);
    clock_t start_t,finish_t,simd1,simd2;

    start_t = clock();
    for (int i = 0; i < N; i++)
    {
        z[i]=x[i]+y[i];
    }
    finish_t = clock();
    cout << "Total Time without SIMD = " <<(double)(finish_t - start_t)/CLOCKS_PER_SEC<< endl;

    double *x1,*y2,*z3,*px,*py,*pz;
    x1=(double*)_mm_malloc(sizeof(double)*N,16);
    y2=(double*)_mm_malloc(sizeof(double)*N,16);
    z3=(double*)_mm_malloc(sizeof(double)*N,16);
    px=x1;py=y2;pz=z3;
    __m128d vx,vy,vz;
    simd1 = clock();
    for (int i = 0; i < N / 2; i++)
    {
        vx=_mm_load_pd(px);
        vy=_mm_load_pd(py);
	    vz=vx+vy;
	    _mm_store_pd(pz,vz);
        px+=2;
        py+=2;
        pz+=2;
    }
    simd2 = clock();
    cout << "Total Time with SIMD = " <<(double)(simd2-simd1)/CLOCKS_PER_SEC<< endl;
    _mm_free(x1); 
    _mm_free(y2);
    _mm_free(z3);
    free(x);
    free(y);
    free(z);
    return 1;
}