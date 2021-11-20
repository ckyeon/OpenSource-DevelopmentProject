#ifndef WORLD_H
#define WORLD_H

#include "util.h"
#include "gfx.h"
#include "chunk.h"
#include "block.h"
#include "player.h"

struct WorldUnloadedData
{
    ivec3s pos;
    u32 data;
};

struct World
{
    struct EntityPlayer player;

    // Size of one dimension of World::chunks
    // chunks의 차원 크기
    size_t chunks_size;

    // 항상 청크 사이즈의 제곱을 갖고,
    // 청크 포인터가 로딩되어야 NULL이 아님.
    struct Chunk **chunks;

    // 청크의 좌측 하단 및 중앙의 오프셋
    ivec3s chunks_origin, center_offset;

    // worldgen에 의해 설정은 되어있지만
    // 실제로 로드되지 않은 데이터
    struct
    {
        struct WorldUnloadedData *list;
        size_t size, capacity;
    } unloaded_data;

    // Per-frame throttles on certain world operations
    struct
    {
        struct
        {
            size_t count, max;
        } load, mesh;
    } throttles;
};

// see worldgen.c
void worldgen_generate(struct Chunk *);

bool world_in_bounds(struct World *self, ivec3s pos);
bool world_contains(struct World *self, ivec3s pos);
struct Chunk *world_get_chunk(struct World *self, ivec3s offset);
ivec3s world_pos_to_block(vec3s pos);
ivec3s world_pos_to_offset(ivec3s pos);
ivec3s world_pos_to_chunk_pos(ivec3s pos);

void world_init(struct World *self);
void world_destroy(struct World *self);

void world_remove_unloaded_data(struct World *self, size_t i);

void world_set_data(struct World *self, ivec3s pos, u32 data);
u32 world_get_data(struct World *self, ivec3s pos);
void world_set_center(struct World *self, ivec3s center_pos);
void world_render(struct World *self);
void world_update(struct World *self);
void world_tick(struct World *self);

#endif