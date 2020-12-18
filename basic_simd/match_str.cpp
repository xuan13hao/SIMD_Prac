#include <iostream>
#include <time.h>
#include <immintrin.h>
#include "data.h"
using std::cout;
using std::endl;

unsigned popcount_3(uint64_t x)
{
	const uint64_t m1  = 0x5555555555555555; //binary: 0101...
	const uint64_t m2  = 0x3333333333333333; //binary: 00110011..
	const uint64_t m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
	const uint64_t h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...
	//cout << "x = " <<x<<endl;
    x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
	//cout << "x = " <<x<<endl;
	x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits
	//cout << "x = " <<x<<endl;
	x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits
	//cout << "x = " <<x<<endl;
	//cout << "x = " <<((x * h01)>>56)<<endl;
    return (x * h01)>>56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ...
}

unsigned match_block(const char *x, const char *y)
{

	static const __m128i mask = _mm_set1_epi8(0x7F);   //Broadcasts 8-bit integer a to all elements
	__m128i r1 = _mm_loadu_si128 ((__m128i const*)(x));//Loads 128-bits of integer data from memory into a new vector
	__m128i r2 = _mm_loadu_si128 ((__m128i const*)(y));
	r2 = _mm_and_si128(r2, mask);					  //Computes the bitwise AND of 128 bits (representing integer data) in a and b.
    __m128i swap = _mm_cmpeq_epi8(r1, r2);
    //printf("swap  = %4vhhu\n", swap);
    int8_t *i = (int8_t *)&swap;
    for (size_t j = 0; j < 16; j++)
    {
        cout << " " <<i[j] ;
    }
    return _mm_movemask_epi8(swap); //Returns a mask of the most significant bit of each element in a.;Compares packed 8-bit integers in a and b for equality.
}

int main()
{

    int i1 = match_block(s29,s30);
    int j1 = popcount_3(i1);

    int i2 = match_block(s1,s2);
    int j2 = popcount_3(i2);
    //cout << "" <<j<<endl;
    //cout << " " <<i ;

    cout << ", j1 =" <<j1<<endl;
    cout << ", j2 =" <<j2<<endl;
    return 1;
}