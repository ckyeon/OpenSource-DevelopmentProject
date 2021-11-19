#ifndef DIRECTION_H
#define DIRECTION_H

#include <cglm/include/cglm/cglm.h>
#include <cglm/include/cglm/struct.h>

enum Direction {
	NORTH = 0,
	SOUTH,
	EAST,
	WEST,
	UP,
	DOWN
};

extern const ivec3s DIRECTION_IVEC[6];
extern const vec3s DIRECTION_VEC[6];

// Direction을 반환하는 함수
enum Direction _ivec3s2dir(ivec3s v);

#define DIR2VEC3S(d) (DIRECTION_VEC[d])
#define DIR2IVEC3S(d) (DIRECTION_IVEC[d])
// IVEC3S를 DIR로 변환
#define IVEC3S2DIR(v) (_ivec3s2dir(v))

#endif