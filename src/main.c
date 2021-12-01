#include "include/window.h"
#include "include/gfx.h"

#include "include/vao.h"
#include "include/vbo.h"
#include "include/shader.h"
#include "include/camera.h"
#include "include/state.h"
#include "include/block.h"

// global state
struct State state;

void init()
{
    // 블럭 초기화
    block_init();

    // 윈도우 객체 저장
    state.window = &window;
    // shader 생성
    state.shader = shader_create(
        "res/shaders/basic.vs", "res/shaders/basic.fs",
        1, (struct VertexAttr[]){{.index = 0, .name = "position"}, {.index = 1, .name = "uv"}, {.index = 2, .name = "color"}});
    // 각 블록이 저장된 png 받아오기
    state.block_atlas = blockatlas_create("res/images/blocks.png");
    // 월드 초기화
    world_init(&state.world);
    state.wireframe = false;
    // 마우스 입력 받기 시작
    mouse_set_grabbed(true);

    // OpenGL 설정
    // ref: https://docs.microsoft.com/ko-kr/windows/win32/opengl/glenable
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 플레이어 카메라 위치 세팅
    state.world.player.camera.position = (vec3s){{0, 80, 0}};
}

// 게임 파괴
void destroy()
{
    shader_destroy(state.shader);
    world_destroy(&state.world);
    blockatlas_destroy(&state.block_atlas);
}

void tick()
{
    // 프레임에 맞춰 블럭 로딩
    blockatlas_tick(&state.block_atlas);
    // 프레임에 맞춰 월드 로딩
    world_tick(&state.world);

    // 캐릭터를 중심으로 월드 로딩
    world_set_center(&state.world, world_pos_to_block(state.world.player.camera.position));

    // C를 누르면 
    if (state.window->keyboard.keys[GLFW_KEY_C].pressed_tick)
    {
        for (int x = 0; x < 32; x++)
            for (int y = 64; y < 80; y++)
            {
                world_set_data(&state.world, (ivec3s){{x, y, 4}}, GLASS);
                world_set_data(&state.world, (ivec3s){{x, y, 8}}, LAVA);
            }

        world_set_data(&state.world, (ivec3s){{40, 80, 4}}, ROSE);
    }
}

void update()
{
    // 월드 업데이트
    world_update(&state.world);

    // T를 누르면 wireframe 생성
    if (state.window->keyboard.keys[GLFW_KEY_T].pressed)
    {
        state.wireframe = !state.wireframe;
    }
}

void render()
{
    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, state.wireframe ? GL_LINE : GL_FILL);
    // 게임 렌더링
    world_render(&state.world);
}

int main(int argc, char *argv[])
{
    window_create(init, destroy, tick, update, render);
    window_loop();
}