#ifndef cglms_ivec2s_h
#define cglms_ivec2s_h

// 기존 cglm의 vec2s(struct).h 를 i(int)vec2s(struct)로 변환한 header file

#include <cglm/common.h>
#include <cglm/types-struct.h>
#include <cglm/util.h>

#include "ivec2.h"

/*
* cglm 구조체 선언법
* ref: https://github.com/recp/cglm/blob/master/include/cglm/types-struct.h
*/
typedef union ivec2s
{
	ivec2 raw;
#if CGLM_USE_ANONYMOUS_STRUCT // 익명 구조체인 경우
	struct
	{
		int x;
		int y;
	};
#endif
} ivec2s;

#define GLMS_IVEC2_ONE_INIT \
	{                       \
		GLM_IVEC2_ONE_INIT  \
	}
#define GLMS_IVEC2_ZERO_INIT \
	{                        \
		GLM_IVEC2_ZERO_INIT  \
	}

#define GLMS_IVEC2_ONE ((ivec2s)GLMS_IVEC2_ONE_INIT)
#define GLMS_IVEC2_ZERO ((ivec2s)GLMS_IVEC2_ZERO_INIT)

/*
* pack an array of ivec2 into an array of ivec2s (vector copy)
* 
* dst	array of ivec2
* src	array of ivec2s
* len	number of elements
*/
CGLM_INLINE
void glms_ivec2_pack(ivec2s dst[], ivec2 src[], size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
	{
		glm_ivec2_copy(src[i], dst[i].raw);
	}
}

/*
* unpack an array of ivec2 into an array of ivec2s (vector copy)
*
* dst	array of ivec2s
* src	array of ivec2
* len	number of elements
*/
CGLM_INLINE
void glms_ivec2_unpack(ivec2 dst[], ivec2s src[], size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
	{
		glm_ivec2_copy(src[i].raw, dst[i]);
	}
}

/*
* make zero vector
* 
* return zero vector
*/
CGLM_INLINE
ivec2s glms_ivec2_zero(void)
{
	ivec2s r;
	glm_ivec2_zero(r.raw);
	return r;
}

/*
* make one vector
* 
* return one vecotr
*/
CGLM_INLINE
ivec2s glms_ivec2_one(void)
{
	ivec2s r;
	glm_ivec2_one(r.raw);
	return r;
}

/*
* ivec2 dot product
* 
* a	vector 1
* b	vector 2
* 
* return dot product
*/
CGLM_INLINE
int glms_ivec2_dot(ivec2s a, ivec2s b)
{
	return glm_ivec2_dot(a.raw, b.raw);
}

/*
* ivec2 cross product
*
* a	vector 1
* b	vector 2
* 
* return corss product
*/
CGLM_INLINE
int glms_ivec2_cross(ivec2s a, ivec2s b)
{
	return glm_ivec2_cross(a.raw, b.raw);
}

/*
* add a vector to bvector
* 
* a			vector 1
* b			vector 2
* 
* return	r = (a[0] + b[0], a[1] + b[1])
*/
CGLM_INLINE
ivec2s glms_ivec2_add(ivec2s a, ivec2s b)
{
	ivec2s r;
	glm_ivec2_add(a.raw, b.raw, r.raw);
	return r;
}

/*
* add scalar to v vector
* 
* v			vector
* s			scalar
* 
* return	r = (a[0] + s, a[1] + s)
*/
CGLM_INLINE
ivec2s glms_ivec2_adds(ivec2s v, int s)
{
	ivec2s r;
	glm_ivec2_adds(v.raw, s, r.raw);
	return r;
}

/*
* subtract b vector from a vector
* 
* a			vector 1
* b			vector 2
* 
* return	r = (a[0] - b[0], a[1] - b[1])
*/
CGLM_INLINE
ivec2s glms_ivec2_sub(ivec2s a, ivec2s b)
{
	ivec2s r;
	glm_ivec2_sub(a.raw, b.raw, r.raw);
	return r;
}

/*
* subtract scalar from v vector
* 
* v			vector
* a			scalar
* 
* return	r = (a[0] - s, a[1] - s)
*/
CGLM_INLINE
ivec2s glms_ivec2_subs(ivec2s v, int s)
{
	ivec2s r;
	glm_ivec2_subs(v.raw, s, r.raw);
	return r;
}

/*
* multiply two vector (아다마르 곱)
* 
* a			vector 1
* b			vector 2
* 
* return	r = (a[0] * b[0], a[1] * b[1])
*/
CGLM_INLINE
ivec2s glms_ivec2_mul(ivec2s a, ivec2s b)
{
	ivec2s r;
	glm_ivec2_mul(a.raw, b.raw, r.raw);
	return r;
}

/*
* scale vector with scalar
* 
* v			vector
* s			scalar
* 
* return	r = (a[0] * s, a[1] * s)
*/
CGLM_INLINE
ivec2s glms_ivec2_scale(ivec2s v, int s)
{
	ivec2s r;
	glm_ivec2_scale(v.raw, s, r.raw);
	return r;
}

/*
* div vector - 각 벡터의 원소끼리 div
*
* a			vector 1
* b			vector 2
* 
* return	r = (a[0] / b[0], a[1] / b[1])
*/
CGLM_INLINE
ivec2s glms_ivec2_div(ivec2s a, ivec2s b)
{
	ivec2s r;
	glm_ivec2_div(a.raw, b.raw, r.raw);
	return r;
}

/*
* div vector with scalar
* 
* v			vector
* s			scalar
* return	r = (a[0] / s, a[1] / s, a[2] / s)
*/
CGLM_INLINE
ivec2s glms_ivec2_divs(ivec2s v, int s)
{
	ivec2s r;
	glm_ivec2_divs(v.raw, s, r.raw);
	return r;
}

#endif