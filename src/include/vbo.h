#ifndef VBO_H
#define VBO_H

#include "util.h"
#include "gfx.h"

// Vertext Buffer Object 선언
// VBO는 컴퓨터의 GPU의 메모리 공간 상에 있는 메모리 Buffer에 해당한다.
// ex) 정육면체의 위치 정보를 담고 있는 VBO와 색상을 담고 있는 VBO
// ref: https://whilescape.tistory.com/entry/OpenGL-%EC%98%A4%ED%94%88%EC%A7%80%EC%97%98-%EB%8D%B0%EC%9D%B4%ED%84%B0-%EA%B4%80%EB%A0%A8-%EA%B0%9C%EB%85%90-%EC%A0%95%EB%A6%AC1

// GLint는 OpenGL의 길이가 고정적인 int형으로 항상 32비트이다.
struct VBO
{
    GLuint handle;
    GLint type;
    bool dynamic;
};

struct VBO vbo_create(GLint type, bool dynamic);

void vbo_destroy(struct VBO self);

void vbo_bind(struct VBO self);

void vbo_buffer(struct VBO self, void *data, size_t offset, size_t count);

#endif