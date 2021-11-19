#ifndef WINDOW_H
#define WINDOW_H

#include "gfx.h"
#include "util.h"

// 버튼 정보
struct Button
{
    bool down, last, last_tick, pressed, pressed_tick;
};

// GLFW_MOUSE_BUTTON_LAST = 마지막에 누른 마우스 값
struct Mouse
{
    struct Button buttons[GLFW_MOUSE_BUTTON_LAST];
    vec2s position, delta;
};

// GLFW_KEY_LAST = 마지막에 누른 키보드 값
struct Keyboard
{
    struct Button keys[GLFW_KEY_LAST];
};

typedef void (*FWindow)();

struct Window
{
    GLFWwindow *handle;
    ivec2s size;
    FWindow init, destroy, tick, update, render;
    struct Mouse mouse;
    struct Keyboard keyboard;

    // timing variables
    // 게임의 프레임이나 시간등을 관리하는 변수들
    u64 last_second;
    u64 frames, fps, last_frame, frame_delta;
    u64 ticks, tps, tick_remainder;
};

// global window
// 전체 창을 뜻함
extern struct Window window;

void window_loop();
void window_create(FWindow init, FWindow destroy, FWindow tick, FWindow update, FWindow render);
void mouse_set_grabbed(bool grabbed);

#endif