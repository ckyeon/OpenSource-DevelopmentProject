#ifndef VAO_H
#define VAO_H

#include "util.h"
#include "gfx.h"
#include "vbo.h"

// Vertext Array Object 선언
// VAO는 하나 혹은 여러개의 VBO를 담을 수 있는 객체다. 또한, 최종적으로 렌더링된 오브젝트들의 정보를 저장한다.
// ex) 정육면체의 꼭짓점의 좌표갑과 각 꼭짓점의 색들을 담는데 사용 -> VBO를 모아놓은 것
// ref: https://whilescape.tistory.com/entry/OpenGL-%EC%98%A4%ED%94%88%EC%A7%80%EC%97%98-%EB%8D%B0%EC%9D%B4%ED%84%B0-%EA%B4%80%EB%A0%A8-%EA%B0%9C%EB%85%90-%EC%A0%95%EB%A6%AC1

// GLint는 OpenGL의 길이가 고정적인 int형으로 항상 32비트이다.
struct VAO
{
    GLuint handle;
};

struct VAO vao_create();

void vao_destroy(struct VAO self);

void vao_bind(struct VAO self);

void vao_attr(
    struct VAO self, struct VBO vbo, GLuint index, GLint size, GLenum type,
    GLsizei stride, size_t offset);

#endif