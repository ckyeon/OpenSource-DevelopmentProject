#ifndef cglm_ivec3_h
#define cglm_ivec3_h

// 기존 cglm의 vec3.h 를 i(int)vec3로 변환한 header file

#include "cglm/common.h"
#include "cglm/util.h"

#define glm_ivec3_dup(v, dest)         glm_ivec3_copy(v, dest)
#define glm_ivec3_flipsign(v)          glm_ivec3_negate(v)
#define glm_ivec3_flipsign_to(v, dest) glm_ivec3_negate_to(v, dest)
#define glm_ivec3_inv(v)               glm_ivec3_negate(v)
#define glm_ivec3_inv_to(v, dest)      glm_ivec3_negate_to(v, dest)
#define glm_ivec3_mulv(a, b, d)        glm_ivec3_mul(a, b, d)

#define GLM_IVEC3_ONE_INIT   {1, 1, 1}
#define GLM_IVEC3_ZERO_INIT  {0, 0, 0}

#define GLM_IVEC3_ONE  ((ivec3)GLM_IVEC3_ONE_INIT)
#define GLM_IVEC3_ZERO ((ivec3)GLM_IVEC3_ZERO_INIT)

#define GLM_IVEC3_YUP       ((ivec3){0,  1,  0})
#define GLM_IVEC3_ZUP       ((ivec3){0,  0,  1})
#define GLM_IVEC3_XUP       ((ivec3){1,  0,  0})
#define GLM_IVEC3_FORWARD   ((ivec3){0,  0, -1})

#define GLM_IVEC3_XXX GLM_SHUFFLE3(0, 0, 0)
#define GLM_IVEC3_YYY GLM_SHUFFLE3(1, 1, 1)
#define GLM_IVEC3_ZZZ GLM_SHUFFLE3(2, 2, 2)
#define GLM_IVEC3_ZYX GLM_SHUFFLE3(0, 1, 2)

/*
* init ivec3 using vec3
* 
* v4	vector 4
* dest	destination
*/
CGLM_INLINE
void glm_ivec3(vec4 v4, ivec3 dest) {
	dest[0] = v4[0];
	dest[1] = v4[1];
	dest[2] = v4[2];
}

/*
* copy all members of [s] to [dest]
* 
* s		source
* dest	destination
*/
CGLM_INLINE
void glm_ivec3_copy(ivec3 s, ivec3 dest) {
	dest[0] = s[0];
	dest[1] = s[1];
	dest[2] = s[2];
}

/*
* make vector zero
* 
* v	vector
*/
CGLM_INLINE
void glm_ivec3_zero(ivec3 v) {
	v[0] = v[1] = v[2] = 0;
}

/*
* make vector one
* 
* v	vector
*/
CGLM_INLINE
void glm_ivec3_one(ivec3 v) {
	v[0] = v[1] = v[2] = 1;
}

/*
* ivec3 dot product
* 
* a	vector 1
* b	vector 2
*/
CGLM_INLINE
int glm_ivec3_dot(ivec3 a, ivec3 b) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/*
* norm * norm (magnitude)
* 아래의 glm_ivec3_norm 함수에서 vector의 크기를 구하는데 이용되는 함수
* 
* v	vector
*/
CGLM_INLINE
int glm_ivec3_norm2(ivec3 v) {
	return glm_ivec3_dot(v, v);
}

/*
* give magnitude of vector
* 
* v	vector
*/
CGLM_INLINE
int glm_ivec3_norm(ivec3 v) {
	return (int)sqrtf(glm_ivec3_norm2(v));
}

/*
* add a vector to b vector
* 
* a		vector 1
* b		vector 2
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec3_add(ivec3 a, ivec3 b, ivec3 dest) {
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
}

/*
* add scalar to v vector
* 
* v		vector
* s		scalar
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec3_adds(ivec3 v, int s, ivec3 dest) {
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
	dest[2] = v[2] + s;
}

/*
* subtract b vector from a vector
* 
* a		vector 1
* b		vector 2
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec3_sub(ivec3 a, ivec3 b, ivec3 dest) {
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
}

/*
* subtract scalar from v vector
* 
* v		vector
* s		scalar
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec3_subs(ivec3 v, int s, ivec3 dest) {
	dest[0] = v[0] - s;
	dest[1] = v[1] - s;
	dest[2] = v[2] - s;
}

/*
* multiply two vector (아다마르 곱)
* 
* a		vector 1
* b		vector 2
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec3_mul(ivec3 a, ivec3 b, ivec3 dest) {
	dest[0] = a[0] * b[0];
	dest[1] = a[1] * b[1];
	dest[2] = a[2] * b[2];
}

/*
* scale vector with scalar
* 
* v		vector
* s		scalar
* dest	destination	vector
*/
CGLM_INLINE
void glm_ivec3_scale(ivec3 v, int s, ivec3 dest) {
	dest[0] = v[0] * s;
	dest[1] = v[1] * s;
	dest[2] = v[2] * s;
}

/*
* div vector - 각 벡터의 원소끼리 div
* 
* a		vector 1
* b		vector 2
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec3_div(ivec3 a, ivec3 b, ivec3 dest) {
	dest[0] = a[0] / b[0];
	dest[1] = a[1] / b[1];
	dest[2] = a[2] / b[2];
}

/*
* div vector with scalar
* 
* v		vector
* s		scalar
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec3_divs(ivec3 v, int s, ivec3 dest) {
	dest[0] = v[0] / s;
	dest[1] = v[1] / s;
	dest[2] = v[2] / s;
}

/*
* mod vector
* 
* a		vector 1
* b		vector 2
* dest	destination vector
*/
CGLM_INLINE
void glm_ivec3_mod(ivec3 a, ivec3 b, ivec3 dest) {
	dest[0] = a[0] % b[0];
	dest[1] = a[1] % b[1];
	dest[2] = a[2] % b[2];
}

#endif