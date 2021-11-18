#ifndef cglms_ivec3s_h
#define cglms_ivec3s_h

// 기존 cglm의 vec3s(struct).h 를 i(int)vec3s(struct)로 변환한 header file

#include <cglm/include/cglm/common.h>
#include <cglm/include/cglm/types-struct.h>
#include <cglm/include/cglm/util.h>

#include "ivec3.h"

#define GLMS_IVEC3_ONE_INIT		{GLM_IVEC3_ONE_INIT}
#define GLMS_IVEC3_ZERO_INIT	{GLM_IVEC3_ZERO_INIT}

#define GLMS_IVEC3_ONE	((ivec3s)GLMS_IVEC3_ONE_INIT)
#define GLMS_IVEC3_ZERO	((ivec3s)GLMS_IVEC3_ZERO_INIT)

#define GLMS_IVEC3_YUP	((ivec3s)({0.0f, 1.0f, 0.0f}))
#define GLMS_IVEC3_ZUP	((ivec3s)({0.0f, 0.0f, 1.0f}))
#define GLMS_IVEC3_XUP	((ivec3s)({1.0f, 0.0f, 0.0f}))

// types-struct.h에 ivec2s와는 다르게 ivec3s는 정의되어 있음

/*
* init ivec3 using vec4
* 
* v4		vector4
* return	destination
*/
CGLM_INLINE
ivec3s glms_ivec3(vec4s v4) {
	ivec3s r;
	glm_ivec3(v4.raw, r.raw);
	return r;
}

/*
* pack an array of ivec3 into an array of ivec3s (vector copy)
* 
* dst	array of ivec3
* src	array of ivec3s
* len	number of elements
*/
CGLM_INLINE
void glms_ivec3_pack(ivec3s dst[], ivec3 src[], size_t len) {
	size_t i;

	for (i = 0; i < len; i++) {
		glm_ivec3_copy(src[i], dst[i].raw);
	}
}

/*
* unpack an array of ivec3s into an array of ivec3
* 
* dst	array of ivec3s
* src	array of ivec3
* len	number of elements
*/
CGLM_INLINE
void glms_ivec3_unpack(ivec3 dst[], ivec3s src[], size_t len) {
	size_t i;

	for (i = 0; i < len; i++) {
		glm_ivec3_copy(src[i].raw, dst[i]);
	}
}


/*
* make	vector zero
* 
* return	zero vector
*/
CGLM_INLINE
ivec3s glms_ivec3_zero(void) {
	ivec3s r;
	glm_ivec3_zero(r.raw);
	return r;
}

/*
* make	vector one
* 
* return	one vector
*/
CGLM_INLINE
ivec3s glms_ivec3_one(void) {
	ivec3s r;
	glm_ivec3_one(r.raw);
	return r;
}


/*
* ivec3 dot product
* 
* a	vector 1
* b	vector 2
* 
* return dot product
*/
CGLM_INLINE
int glms_ivec3_dot(ivec3s a, ivec3s b) {
	return glm_ivec3_dot(a.raw, b.raw);
}

/*
* norm * norm (magnitude)
* 아래의 glms_ivec3_norm 함수에서 vector의 크기를 구하는데 이용되는 함수
*
* v	vector
*/
CGLM_INLINE
int glms_ivec3_norm2(ivec3s v) {
	return glm_ivec3_norm2(v.raw);
}

/*
* norm (magnitude) of vec3
* 
* v	vector
*/
CGLM_INLINE
int glms_ivec3_norm(ivec3s v) {
	return glm_ivec3_norm(v.raw);
}

/*
* add a vecotr to b vector
* 
* a	vector 1
* b	vector 2
* 
* return	r = (a[0] + b[0], a[1] + b[1], a[2] + b[2])
*/
CGLM_INLINE
ivec3s glms_ivec3_add(ivec3s a, ivec3s b) {
	ivec3s r;
	glm_ivec3_add(a.raw, b.raw, r.raw);
	return r;
}

/*
* add scalar to v vector
* 
* v	vector
* s	scalar
* 
* return	r = (v[0] + s, v[1] + s, v[2] + s)
*/
CGLM_INLINE
ivec3s glms_ivec3_adds(ivec3s v, int s) {
	ivec3s r;
	glm_ivec3_adds(v.raw, s, r.raw);
	return r;
}

/*
* subtract b vector from a vector
* 
* a	vector 1
* b	vector 2
* 
* return	r = (a[0] - b[0], a[1] - b[1], a[2] - b[2])
*/
CGLM_INLINE
ivec3s glms_ivec3_sub(ivec3s a, ivec3s b) {
	ivec3s r;
	glm_ivec3_sub(a.raw, b.raw, r.raw);
	return r;
}

/*
* subtract scalar from v vector
*
* v	vector
* s	scalar
*
* return	r = (v[0] - s, v[1] - s, v[2] - s)
*/
CGLM_INLINE
ivec3s glms_ivec3_sub(ivec3s v, int s) {
	ivec3s r;
	glm_ivec3_subs(v.raw, s, r.raw);
	return r;
}

/*
* multiply two vector (아다마르 곱)
* 
* a	vector 1
* b	vector 2
* 
* return	r = (a[0] * b[0], a[1] * b[1], a[2] * b[2])
*/
CGLM_INLINE
ivec3s glms_ivec3_mul(ivec3s a, ivec3s b) {
	ivec3s r;
	glm_ivec3_mul(a.raw, b.raw, r.raw);
	return r;
}

/*
* scale ivec3 vector with scalar
* 
* v	vector
* s	scalar
* 
* return	r = (v[0] * s, v[1] * s, v[2] * s)
*/
CGLM_INLINE
ivec3s glms_ivec3_scale(ivec3s v, int s) {
	ivec3s r;
	glm_ivec3_scale(v.raw, s, r.raw);
	return r;
}

/*
* div vector - 각 벡터의 원소끼리 div
* 
* a	vector 1
* b	vector 2
* 
* return	r = (a[0] / b[0], a[1] / b[1], a[2] / b[2])
*/
CGLM_INLINE
ivec3s glms_ivec3_div(ivec3s a, ivec3s b) {
	ivec3s r;
	glm_ivec3_div(a.raw, b.raw, r.raw);
	return r;
}

/*
* div vector with scalar
* 
* v	vector
* s	scalar
* 
* return	r = (v[0] / s, v[1] / s, v[2] / s)
*/
CGLM_INLINE
ivec3s glms_ivec3_divs(ivec3s v, int s) {
	ivec3s r;
	glm_ivec3_divs(v.raw, s, r.raw);
	return r;
}

/*
* mod vector
*
* a		vector 1
* b		vector 2
* 
* return	r = (a[0] % b[0], a[1] % b[1], a[2] % b[2])
*/
CGLM_INLINE
ivec3s glms_ivec3_mod(ivec3s a, ivec3s b) {
	ivec3s r;
	glm_ivec3_mod(a.raw, b.raw, r.raw);
	return r;
}

#endif