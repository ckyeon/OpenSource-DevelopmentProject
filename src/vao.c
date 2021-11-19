#include "include/vao.h"

// VAO 생성
struct VAO vao_create()
{
    // 새로운 배열(VAO)를 생성하는 OpenGL 함수
    // glGenVertexArrays(생성하는 배열의 갯수, VAO 객체 주소)
    struct VAO self;
    glGenVertexArrays(1, &self.handle);
    return self;
}

// VAO 제거
void vao_destroy(struct VAO self)
{
    // 배열(VAO)를 제거하는 OpenGL 함수
    // glDeleteVertexArrys(생성하는 배열의 갯수, VAO 객체 주소)
    glDeleteVertexArrays(1, &self.handle);
}

void vao_bind(struct VAO self)
{
    // 생성한 배열(VAO)에 바인딩하는 OpenGL 함수 -> 전달 데이터 명시
    // glBindVertexArray(VAO 객체 주소)
    glBindVertexArray(self.handle);
}

void vao_attr(
    struct VAO self, struct VBO vbo, GLuint index, GLint size, GLenum type,
    GLsizei stride, size_t offset)
{
    // VAO 바인드
    vao_bind(self);
    // VBO 바인드
    vbo_bind(vbo);
    // VAO 속성 포인터 설정
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *)offset);
    // OpenGl에게 vertex 데이터를 어떻게 해석해야 하는지 명시해주는 OpenGL 함수
    // glVertexAttribPointer(vertex 속성, 크기, data type, 데이터 정규화 여부, vetex 사이의 공백, 데이터 시작 위치)
    // ref: https://heinleinsgame.tistory.com/7

    // vertex 속성을 사용할 수 있도록 해주는 함수
    // 기본적으로 vetex 속성은 사용하지 못하도록 설정되어 있으므로 필수
    glEnableVertexAttribArray(index);
}