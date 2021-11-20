#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "include/texture.h"

// image를 로드하는 함수
void texture_load_pixels(char *path, u8 **pixels_out, size_t *width_out, size_t *height_out)
{
    int width, height, channels;

    // 대부부의 image는 0.0이 y축의 맨 위를 가리키지만
    // OpenGL은 0.0이 맨 아래를 가리켜서 밑의 stbi_set_flip_vertically_on_load()
    // 를 통해 이미지를 뒤집어줘야 한다.
    // ref: https://heinleinsgame.tistory.com/9
    stbi_set_flip_vertically_on_load(true);
    // 이미지를 로드하는 함수
    unsigned char *image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    assert(image != NULL);

    // 각 매개변수에 로드된 image 정보 저장
    *pixels_out = malloc(width * height * 4);
    memcpy(*pixels_out, image, width * height * 4);
    *width_out = width;
    *height_out = height;

    // 이미지의 메모리 반환 (동적할당 해제)
    stbi_image_free(image);
}

// 텍스쳐를 생성하는 함수
struct Texture texture_create_from_pixels(u8 *pixels, size_t width, size_t height)
{
    struct Texture self = {
        .size = (ivec2s){{width, height}}};

    // 텍스쳐를 생성하는 OpenGL 함수
    // glGenTextures(생성하려는 텍스쳐의 갯수, 생성된 텍스쳐의 이름이 저장되는 배열)
    // ref: https://docs.microsoft.com/ko-kr/windows/win32/opengl/glgentextures
    glGenTextures(1, &self.handle);

    // 텍스쳐를 바인딩하는 OPenGL 함수
    // glBindTexture(바인딩 할 텍스쳐 모드, 텍스쳐의 이름)
    // 바인딩 할 텍스쳐 모드 = GL_TEXTURE_1D or GL_TEXTURE_2D
    // ref: https://docs.microsoft.com/ko-kr/windows/win32/opengl/glBindTexture
    glBindTexture(GL_TEXTURE_2D, self.handle);
    // 이미지를 다시 로드하는 것 보다 텍스쳐를 바인딩하는 것이 훨씬 더 빠르다.

    // No interpolation
    // 텍스쳐의 파라미터를 설정한다.
    // glTexParameteri(적용될 텍스쳐 모드, 텍스처 인자, 특정한 텍스터 인자 값)
    // 쉽게 말하자면 내가 가져온 이미지보다 화면에 크게 그려지거나 작게 그려질 때
    // 어떻게 그려야할지 설정하는 것
    // ref: https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=mywjdp&logNo=220801452672

    // ref: https://tech.burt.pe.kr/opengl/opengl-es-tutorial-for-ios/chapter-12
    // GL_TEXTURE_MIN(MAG)_FILTER = 좌표로 추출한 이미지가 폴리곤보다 클/작을 때, GL_NEAREST = 주변 픽셀의 평균값을 가져옴
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // GL_TEXTURE_WRAP_S(T) = 이미지가 범위를 넘었을 경우, GL_CLAMP_TO_EDGE = 테두리의 이미지를 가져옴
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // 텍스쳐를 생성하는 함수
    // glTexImage2D(적용될 텍스쳐 모드, 0, 텍스처 포멧, 너비, 높이, 0, 원본 이미지의 포멧과 데이터 타입, 이미지 데이터(로드된 이미지))
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    return self;
}

struct Texture texture_create_from_path(char *path)
{
    u8 *pixels;
    size_t width, height;
    // image 로드
    texture_load_pixels(path, &pixels, &width, &height);
    // 로드된 image로 텍스쳐 생성
    struct Texture self = texture_create_from_pixels(pixels, width, height);
    free(pixels);
    return self;
}

void texture_destroy(struct Texture self)
{
    // 텍스처를 제거하는 OpenGL 함수
    // glDeleteTextures(제거할 텍스쳐 갯수, 텍스쳐 이름이 저장된 배열(객체))
    glDeleteTextures(1, &self.handle);
}

void texture_bind(struct Texture self)
{
    // 텍스쳐를 바인딩하는 OPenGL 함수
    // glBindTexture(바인딩 할 텍스쳐 모드, 텍스쳐의 이름)
    glBindTexture(GL_TEXTURE_2D, self.handle);
}

struct Atlas atlas_create_from_texture(struct Texture texture, ivec2s sprite_size)
{
    struct Atlas self;
    self.texture = texture;
    self.sprite_size = sprite_size;
    self.sprite_unit = glms_vec2_div(IVEC2S2V(self.sprite_size), IVEC2S2V(self.texture.size));
    self.size = glms_ivec2_div(self.texture.size, self.sprite_size);
    return self;
}

struct Atlas atlas_create(char *path, ivec2s sprite_size)
{
    struct Atlas self;
    self.texture = texture_create_from_path(path);
    self.sprite_size = sprite_size;
    self.sprite_unit = glms_vec2_div(IVEC2S2V(self.sprite_size), IVEC2S2V(self.texture.size));
    self.size = glms_ivec2_div(self.texture.size, self.sprite_size);
    return self;
}

void atlas_destroy(struct Atlas self)
{
    texture_destroy(self.texture);
}

vec2s atlas_offset(struct Atlas self, ivec2s pos)
{
    // Invert Y coordinates so sprite (0, 0) is top-left
    return glms_vec2_mul(IVEC2S2V(((ivec2s){{pos.x, self.sprite_size.y - pos.y - 1}})), self.sprite_unit);
}