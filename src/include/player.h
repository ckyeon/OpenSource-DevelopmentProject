#ifndef PLAYER_H
#define PLAYER_H

#include "util.h"
#include "camera.h"
#include "block.h"

// Forward declaration
struct World;

struct EntityPlayer
{
    struct World *world;
    struct Camera camera;

    // 블럭을 보고 있는지 (왼쪽, 오른쪽 클릭 활성화)
    bool has_look_block;
    ivec3s look_block;
    enum Direction look_face;

    // Player's current chunk offset, block position
    ivec3s offset;
    ivec3s block_pos;

    // true if offset or block position changed since the last update()
    // 마지막 업데이트 이후 위치가 변경된 경우에만 작동
    bool offset_changed, block_pos_changed;

    enum BlockId selected_block;
};

void player_init(struct EntityPlayer *self, struct World *world);
void player_destroy(struct EntityPlayer *self);
void player_render(struct EntityPlayer *self);
void player_update(struct EntityPlayer *self);
void player_tick(struct EntityPlayer *self);

#endif