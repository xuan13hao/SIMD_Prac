#include "simd_funs.h"

float MathMulAdd(const float *input1, const float *input2, int size)
{
	float output = 0.0;
	for (int i = 0; i < size; i++)
	{
		output += input1[i] * input2[i];
	}
	return output;
}
 
float SSEMulAdd(const float *input1, const float *input2, int size)
{
	if (input1 == nullptr || input2 == nullptr)
	{
		printf("input data is null\n");
		return -1;
	}
	int nBlockWidth = 4;
	int cntBlock = size / nBlockWidth;
	int cntRem = size % nBlockWidth;
 
	float output = 0;
	__m128 loadData1, loadData2;
	__m128 mulData = _mm_setzero_ps();
	__m128 sumData = _mm_setzero_ps();
	const float *p1 = input1;
	const float *p2 = input2;
	for (int i = 0; i < cntBlock; i++)
	{
		loadData1 = _mm_load_ps(p1);
		loadData2 = _mm_load_ps(p2);
		mulData = _mm_mul_ps(loadData1, loadData2);
		sumData = _mm_add_ps(sumData, mulData);
		p1 += nBlockWidth;
		p2 += nBlockWidth;
	}
	sumData = _mm_hadd_ps(sumData, sumData); // p[0] + p[1] + p[4] + p[5] + ...
	sumData = _mm_hadd_ps(sumData, sumData); // p[2] + p[3] + p[6] + p[7] + ...
	//output += sumData.m128_f32[(0)];         // 前4组
    
	for (int i = 0; i < cntRem; i++)
	{
		output += p1[i] * p2[i];
	}
 
	return output;
}
 
float SSEFmAdd(const float *input1, const float *input2, int size)
{
	if (input1 == nullptr || input2 == nullptr)
	{
		printf("input data is null\n");
		return -1;
	}
	int nBlockWidth = 4;
	int cntBlock = size / nBlockWidth;
	int cntRem = size % nBlockWidth;
 
	float output = 0;
	__m128 loadData1, loadData2;
	//__m128 mulData = _mm_setzero_ps();
	__m128 sumData = _mm_setzero_ps();
	const float *p1 = input1;
	const float *p2 = input2;
	for (int i = 0; i < cntBlock; i++)
	{
		loadData1 = _mm_load_ps(p1);
		loadData2 = _mm_load_ps(p2);
		//mulData = _mm_mul_ps(loadData1, loadData2);
		//sumData = _mm_add_ps(sumData, mulData);
		sumData = _mm_fmadd_ps(loadData1, loadData2, sumData);
		p1 += nBlockWidth;
		p2 += nBlockWidth;
	}
	sumData = _mm_hadd_ps(sumData, sumData); // p[0] + p[1] + p[4] + p[5] + ...
	sumData = _mm_hadd_ps(sumData, sumData); // p[2] + p[3] + p[6] + p[7] + ...
	//output += sumData.m128_f32[(0)];         // 前4组
 
	for (int i = 0; i < cntRem; i++)
	{
		output += p1[i] * p2[i];
	}
 
	return output;
}
 
float AVXMulAdd(const float *input1, const float *input2, int size)
{
	if (input1 == nullptr || input2 == nullptr)
	{
		printf("input data is null\n");
		return -1;
	}
	int nBlockWidth = 8;
	int cntBlock = size / nBlockWidth;
	int cntRem = size % nBlockWidth;
 
	float output = 0;
	__m256 loadData1, loadData2;
	__m256 mulData = _mm256_setzero_ps();
	__m256 sumData = _mm256_setzero_ps();
	const float *p1 = input1;
	const float *p2 = input2;
	for (int i = 0; i < cntBlock; i++)
	{
		loadData1 = _mm256_load_ps(p1);
		loadData2 = _mm256_load_ps(p2);
		mulData = _mm256_mul_ps(loadData1, loadData2);
		sumData = _mm256_add_ps(sumData, mulData);
		p1 += nBlockWidth;
		p2 += nBlockWidth;
	}
	sumData = _mm256_hadd_ps(sumData, sumData); // p[0] + p[1] + p[4] + p[5] + p[8] + p[9] + p[12] + p[13] + ... 
	sumData = _mm256_hadd_ps(sumData, sumData); // p[2] + p[3] + p[6] + p[7] + p[10] + p[11] + p[14] + p[15] + ... 
    
	// output += sumData.m256_f32[(0)];            // 前4组
	// output += sumData.m256_f32[(4)];            // 后4组
 
	for (int i = 0; i < cntRem; i++)
	{
		output += p1[i] * p2[i];
	}
 
	return output;
}
 
float AVXFmAdd(const float *input1, const float *input2, int size)
{
	if (input1 == nullptr || input2 == nullptr)
	{
		printf("input data is null\n");
		return -1;
	}
	int nBlockWidth = 8;
	int cntBlock = size / nBlockWidth;
	int cntRem = size % nBlockWidth;
 
	float output = 0;
	__m256 loadData1, loadData2;
	//__m256 mulData = _mm256_setzero_ps();
	__m256 sumData = _mm256_setzero_ps();
	const float *p1 = input1;
	const float *p2 = input2;
	for (int i = 0; i < cntBlock; i++)
	{
		loadData1 = _mm256_load_ps(p1);
		loadData2 = _mm256_load_ps(p2);
		//mulData = _mm256_mul_ps(loadData1, loadData2);
		//sumData = _mm256_add_ps(sumData, mulData);
		sumData = _mm256_fmadd_ps(loadData1, loadData2, sumData);
		p1 += nBlockWidth;
		p2 += nBlockWidth;
	}
	sumData = _mm256_hadd_ps(sumData, sumData); // p[0] + p[1] + p[4] + p[5] + p[8] + p[9] + p[12] + p[13] + ... 
	sumData = _mm256_hadd_ps(sumData, sumData); // p[2] + p[3] + p[6] + p[7] + p[10] + p[11] + p[14] + p[15] + ... 
	// output += sumData.m256_f32[(0)];            // 前4组
	// output += sumData.m256_f32[(4)];            // 后4组
 
	for (int i = 0; i < cntRem; i++)
	{
		output += p1[i] * p2[i];
	}
 
	return output;
}
