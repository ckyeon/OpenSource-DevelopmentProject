#include "include/direction.h"
#include <string.h>
#include <assert.h>

const ivec3s DIRECTION_IVEC[6] = {
    {{0, 0, -1}}, // NORTH
    {{0, 0, 1}},  // SOUTH
    {{1, 0, 0}},  // EAST
    {{-1, 0, 1}}, // WEST
    {{0, 1, 0}},  // UP
    {{0, -1, 0}}  // DOWN
};

const vec3s DIRECTION_VEC[6] = {
    {{0, 0, -1}}, // NORTH
    {{0, 0, 1}},  // SOUTH
    {{1, 0, 0}},  // EAST
    {{-1, 0, 1}}, // WEST
    {{0, 1, 0}},  // UP
    {{0, -1, 0}}  // DOWN
};

// icec3s가 가리키는 방향 반환
enum Direction _ivec3s2dir(ivec3s v)
{
    for (size_t i = 0; i < 6; i++)
    {
        // 방향을 IVEC3S로 바꿔 매개변수 v와 같으면 해당 방향 반환
        // memcmp -> 같을 때 0 반환
        if (!memcmp(&DIR2IVEC3S(i), &v, sizeof(ivec3s)))
        {
            return i;
        }
    }

    assert(false);
    return -1;
}