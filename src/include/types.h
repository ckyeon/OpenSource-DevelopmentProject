#ifndef TYPES_H
#define TYPES_H

// fixed width numeric types
// 변수명을 간소화
#include <stdint.h>
#include <inttypes.h>

// 자료형_t -> 고전적인(primitive) 자료형
// 시스템(운영체제)에서 정의하는 자료형을 뜻함
// ref: https://sean.tistory.com/63
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float f32;
typedef double f64;

#endif