#ifndef FMATH_H
#define FMATH_H

#include <cglm/include/cglm/cglm.h>
#include <cglm/include/cglm/struct.h>

#include "types.h"
#include "direction.h"

// IVEC2S를 VEC2S로 변경
#define IVEC2S2V(_v) ({ ivec2s _u = ( _v ); ((vec2s) {{ _u.x, _u.y }}); })
// VEC2S를 IVEC2S로 변경
#define VEC2S2I(_v) ({ vec2s _u = ( _v ); ((ivec2s) {{ _u.x, _u.y }}); })
// IVEC3S를 VEC3S로 변경
#define IVEC3S2V(_v) ({ ivec3s _u = ( _v ); ((vec3s) {{ _u.x, _u.y, _u.z }}); })
// VEC3S를 IVEC3S로 변경
#define VEC3S2I(_v) ({ vec3s _u = ( _v ); ((ivec3s) {{ _u.x, _u.y, _u.z }}); })

// IVEC2S를 IVEC3S로 변경
#define IVEC2S23(_v) ({ ivec2s _u = ( _v ); ((ivec3s) {{ _u.x, _u.y, 0 }}); })

// 정의된 이름 간략화 및 간단한 연산 정의
#define PI_2 GLM_PI_2
#define PI GLM_PI
#define TAU (2 * PI)
#define F32_EPSILON FLT_EPSILON
#define F64_EPSILON DBL_EPSILON

// 연산 정의
// typeof() 함수를 header파일에서 쓸 경우 __typeof__
#define cosf(_x) ((f32)cos(_x))
#define sinf(_x) ((f32)sin(_x))
#define radians(_x) ((_x) * (__typeof__(_x)) (PI / 180.0f))
#define degrees(_x) ((_x) * (__typeof__(_x)) (180.0f / PI))
// 내림 후 정수로 변경
#define floori(_x) ((int) (floor((double) (_x))))
// _x가 0보다 크면 1, 아니면 -1
#define sign(_x) ({ __typeof__(_x) _xx = (_x);\
    ((__typeof__(_x)) ( (((__typeof__(_x)) 0) < _xx) - (_xx < ((__typeof__(_x)) 0))));})

#define max(a, b) ({\
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

#define max(a, b) ({\
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

// mx와 x 중 더 작은 값을 mn과 비교해 큰 값 반환
#define clamp(x, mn, mx) ({\
    __typeof__ (x) _x = (x); \
    __typeof__ (mn) _mn = (mn); \
    __typeof__ (mx) _mx = (mx); \
    max(_mn, min(_mx, _x)); })

int ivec3scmp(ivec3s a, ivec3s b);
s64 ivec3shash(ivec3s v);

// 레이저
struct Ray {
    vec3s origin, direction;
};

// maybe 레이저가 충돌했는지 확인하는 함수
// ref: https://chameleonstudio.tistory.com/63
extern bool ray_block(struct Ray ray, f32 max_distance, bool (*f)(ivec3s), ivec3s* out, enum Direction* d_out);

#endif