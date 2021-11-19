#include "include/window.h"

#include <stdio.h>
#include <stdlib.h>

// global window
struct Window window;

// GLFWwindow *handle는 내가 생성한 창을 조정하기 위한 권한이 담김
// ref: https://wonjayk.tistory.com/270
static void _size_callback(GLFWwindow *handle, int width, int height)
{
    // OprnGL의 ViewPort(그려지는 영역 설정)의 크기를 지정하는 함수
    // 여기서는 window의 size도 widh, height로 하였으므로, 윈도우 크기와 ViewPort가 동일하다.
    // ref: https://docs.microsoft.com/ko-kr/windows/win32/opengl/glviewport
    // ref: https://092dc.tistory.com/4
    glViewport(0, 0, width, height);
    window.size = (ivec2s){{width, height}};
}

static void _cursor_callback(GLFWwindow *handle, double xp, double yp)
{
    vec2s p = {{xp, yp}};

    // 마우스 커서가 화면을 넘어가는 것을 방지
    window.mouse.delta = glms_vec2_sub(p, window.mouse.position);
    window.mouse.delta.x = clamp(window.mouse.delta.x, -100.0f, 100.0f);
    window.mouse.delta.y = clamp(window.mouse.delta.y, -100.0f, 100.0f);

    // 마우스 위치 지정
    window.mouse.position = p;
}

static void _key_callback(GLFWwindow *handle, int key, int scancode, int action, int mods)
{
    if (key < 0)
    {
        return;
    }

    // 키가 눌렸는지 체크
    // ref: https://www.glfw.org/docs/3.3/group__input.html
    switch (action)
    {
    case GLFW_PRESS:
        window.keyboard.keys[key].down = true;
        break;
    case GLFW_RELEASE:
        window.keyboard.keys[key].down = false;
        break;
    default:
        break;
    }
}

static void _mouse_callback(GLFWwindow *handle, int button, int action, int mods)
{
    if (button < 0)
    {
        return;
    }

    // 마우스가 눌렸는지 체크
    // ref: https://www.glfw.org/docs/3.3/group__input.html
    switch (action)
    {
    case GLFW_PRESS:
        window.mouse.buttons[button].down = true;
        break;
    case GLFW_RELEASE:
        window.mouse.buttons[button].down = false;
        break;
    default:
        break;
    }
}

// 윈도우 창을 생성하는 함수
void window_create(FWindow init, FWindow destroy, FWindow tick, FWindow update, FWindow render)
{
    window.init = init;
    window.destroy = destroy;
    window.tick = tick;
    window.update = update;
    window.render = render;

    window.last_frame = NOW();
    window.last_second = NOW();

    if (!glfwInit())
    {
        fprintf(stderr, "%s", "error initializing GLFW\n");
        exit(1);
    }

    // glfwWindowHint => GLFW 설정
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    // 버전 설정
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // 프로필 설정 -> CORE_PROFILE = 호환 가능한 프로필 설정
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Mac OS를 위한 설정
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 윈도우 창 크기 설정
    window.size = (ivec2s){{1280, 720}};
    // handle에 창 생성 및 정보 저장
    window.handle = glfwCreateWindow(window.size.x, window.size.y, "Project", NULL, NULL);
    if (window.handle == NULL)
    {
        fprintf(stderr, "%s", "error creating window\n");
        glfwTerminate();
        exit(1);
    }

    // 윈도우 생성 후 띄우기
    glfwMakeContextCurrent(window.handle);

    // callback 함수들 설정
    // ref: https://www.glfw.org/docs/3.3/group__input.html
    glfwSetFramebufferSizeCallback(window.handle, _size_callback);
    glfwSetCursorPosCallback(window.handle, _cursor_callback);
    glfwSetKeyCallback(window.handle, _key_callback);
    glfwSetMouseButtonCallback(window.handle, _mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "%s", "error initializing GLAD\n");
        glfwTerminate();
        exit(1);
    }

    // Vsync를 활성화 해서 fps 제한
    // fps가 너무 치솟는 것을 방지
    glfwSwapInterval(1);
}

// 간격중에 사용자의 입력이 있었는지 저장
static void button_array_tick(size_t n, struct Button *buttons)
{
    // 버튼이 눌려있고, 바로 전에 눌렸지 않았으면 true, 아니면 false
    for (size_t i = 0; i < n; i++)
    {
        buttons[i].pressed_tick = buttons[i].down && !buttons[i].last_tick;
        // 바로 전에 눌렀는지 = 버튼을 눌렀는지
        buttons[i].last_tick = buttons[i].down;
    }
}

static void button_array_update(size_t n, struct Button *buttons)
{
    // 버튼이 눌려있고, 바로 전에 눌렸지 않았으면 true, 아니면 false
    for (size_t i = 0; i < n; i++)
    {
        buttons[i].pressed = buttons[i].down && !buttons[i].last;
        // 바로 전에 눌렀는지 = 버튼을 눌렀는지
        buttons[i].last = buttons[i].down;
    }
}

// 창 초기화
static void _init()
{
    window.init();
}

// 창 파괴
static void _destroy()
{
    window.destroy();
    // 실제 파괴 전에 모든 콜백이 제거되어 창이 남아있을 수도 있으므로
    // glfwTerminate를 호출해 남아있는 모든 창 파괴
    glfwTerminate();
}

// 게임의 간격 조정 -> 너무 빠른 속도로 입력 받거나 게임이 로딩 되지 않도록 방지
static void _tick()
{
    window.ticks++;
    // 마지막에 누른 MOUSE_BUTTON과 KEY을 매개변수로 보내서 pressed_tick과 last_tick 값 변경
    // true or false
    button_array_tick(GLFW_MOUSE_BUTTON_LAST, window.mouse.buttons);
    button_array_tick(GLFW_KEY_LAST, window.keyboard.keys);
    window.tick();
}

// 사용자가 누른 mouse button과 key update
static void _update()
{
    // 마지막에 누른 MOUSE_BUTTON과 KEY을 매개변수로 보내서 pressed와 last 값 변경
    // true or false
    button_array_update(GLFW_MOUSE_BUTTON_LAST, window.mouse.buttons);
    button_array_update(GLFW_KEY_LAST, window.keyboard.keys);
    window.update();

    // delta를 zero vector로 만듦
    window.mouse.delta = GLMS_VEC2_ZERO;
}

static void _render()
{
    // frame 증가
    window.frames++;
    window.render();
}

void window_loop()
{
    _init();

    // GLFW가 청울 종료하도록 지시했는지 확인
    // ref: https://heinleinsgame.tistory.com/6
    while (!glfwWindowShouldClose(window.handle))
    {
        // 현재 시간
        const u64 now = NOW();

        // 일정 시간마다 게임을 rendering 하거나 입력받기 위한 변수
        window.frame_delta = now - window.last_frame;
        window.last_frame = now;

        // 일정 시간마다 fps와 tps를 콘솔창에 표기
        if (now - window.last_second > NS_PER_SECOND)
        {
            window.fps = window.frames;
            window.tps = window.ticks;
            window.frames = 0;
            window.ticks = 0;
            window.last_second = now;

            printf("FPS: %lld | TPS: %lld\n", window.fps, window.tps);
        }

        // tick processing
        const u64 NS_PER_TICK = (NS_PER_SECOND / 60);
        u64 tick_time = window.frame_delta + window.tick_remainder;
        // tick_ime이 NS_PER_TIC보다 감소할 때 까지 반복해 키 입력과 rendering에 간격을 줌
        while (tick_time > NS_PER_TICK)
        {
            _tick();
            tick_time -= NS_PER_TICK;
        }
        // 나머지 값을 0 이상으로 저장
        window.tick_remainder = max(tick_time, 0);

        _update();
        _render();
        // 이미지를 그리고 화면에 출력하는 함수
        // ref: https://heinleinsgame.tistory.com/6
        glfwSwapBuffers(window.handle);
        // 키보드 입력이나 마우스 이동 이벤트가 발생했는지 확인하고
        // 알맞은 콜백 함수(위에서 등록한)을 호출
        glfwPollEvents();
    }

    _destroy();
    exit(0);
}

void mouse_set_grabbed(bool grabbed)
{
    glfwSetInputMode(window.handle, GLFW_CURSOR, grabbed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}