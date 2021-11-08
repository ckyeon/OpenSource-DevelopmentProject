#ifndef cglm_ivec2_h
#define cglm_ivec2_h

// 기존 cglm의 vec2.h 를 i(int)vec2로 변환한 header file

#include <cglm/include/cglm/common.h>
#include <cglm/include/cglm/util.h>

typedef int ivec2[2];

#define GLM_IVEC2_ONE_INIT {1.0f, 1.0f}
#define GLM_IVEC2_ZERO_INIT {0.0f, 0.0f}

#define GLM_IVEC2_ONE ((ivec2)GLM_IVEC2_ONE_INIT)
#define GLM_IVEC2_ZERO ((ivec2)GLM_IVEC2_ZERO_INIT)



/* 
* init ivec2 using another vector
* 
* v		vector
* dest	destination
*/
// __restrict 포인터 설명 https://dojang.io/mod/page/view.php?id=760
CGLM_INLINE
void glm_ivec2(int* __restrict v, ivec2 dest) {
	dest[0] = v[0];
	dest[1] = v[1];
}

/*
* copy all members of [s] to [dest]
* 
* s	source
* dest	destination
*/
CGLM_INLINE
void glm_ivec2_copy(ivec2 s, ivec2 dest) {
	dest[0] = s[0];
	dest[1] = s[1];
}

/*
* make zero vector
*
* v	vector
*/
CGLM_INLINE
void glm_ivec2_zero(ivec2 v) {
	v[0] = v[1] = 0.0f;
}

/*
* make one vector
*
* v	vector
*/
CGLM_INLINE
void glm_ivec2_one(ivec2 v) {
	v[0] = v[1] = 1.0f;
}

/*
* ivec2 dot product
*
* a	vector 1
* b	vector 2
*/
CGLM_INLINE
int glm_ivec2_dot(ivec2 a, ivec2 b) {
	return (a[0] * b[0]) + (a[1] * b[1]);
}

/*
* ivec2 cross product
* 
* a	vector 1
* b vector 2
*/
// 2차원 외적 http://allenchou.net/2013/07/cross-product-of-2d-vectors/
CGLM_INLINE
int glm_ivec2_cross(ivec2 a, ivec2 b) {
	return a[0] * b[1] - a[1] * b[0];
}

/*
* add a vector to b vector
*
* a		vector 1
* b		vector 2
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec2_add(ivec2 a, ivec2 b, ivec2 dest) {
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
}

/*
* add scalar to v vector
*
* v		vector
* s		scalar
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec2_adds(ivec2 v, int s, ivec2 dest) {
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
}

/*
* subtract b vector from a vector
*
* a		vector 1
* b		vector 2
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec2_sub(ivec2 a, ivec2 b, ivec2 dest) {
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
}

/*
* subtract scalar from v vector
*
* v		vector
* s		scalar
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec2_subs(ivec2 v, int s, ivec2 dest) {
	dest[0] = v[0] - s;
	dest[1] = v[1] - s;
}

/*
* multiply two vector (아다마르 곱)
*
* v		vector
* s		scalar
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec2_mul(ivec2 a, ivec2 b, ivec2 dest) {
	dest[0] = a[0] * b[0];
	dest[1] = a[1] * b[1];
}

/*
* scale vector with scalar
*
* v		vector
* s		scalar
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec2_scale(ivec2 v, int s, ivec2 dest) {
	dest[0] = v[0] * s;
	dest[1] = v[1] * s;
}

/*
* div vector - 각 벡터의 원소끼리 div
*
* a		vector 1
* b		vector 2
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec2_div(ivec2 a, ivec2 b, ivec2 dest) {
	dest[0] = a[0] / b[0];
	dest[1] = a[1] / b[1];
}

/*
* div vector with scalar
*
* a		vector 1
* b		vector 2
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec2_divs(ivec2 v, int s, ivec2 dest) {
	dest[0] = v[0] / s;
	dest[1] = v[1] / s;
}

#endif