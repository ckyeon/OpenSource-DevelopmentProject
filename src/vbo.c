#include "include/vbo.h"

// ref: https://huiyu.tistory.com/entry/OpenGL-VBO%EB%A1%9C-%ED%81%90%EB%B8%8C-%EA%B7%B8%EB%A6%AC%EA%B8%B0

// VBO 생성
// GLint는 OpenGL의 길이가 고정적인 int형으로 항상 32비트이다.
struct VBO vbo_create(GLint type, bool dynamic)
{
    struct VBO self = {
        .type = type,        // VBO의 타입
        .dynamic = dynamic}; // 동적인지 아닌지
    // 새로운 버퍼(VBO)를 생성하는 OpenGL 함수
    // glGenBuffers(생성하는 버퍼의 갯수, VBO 객체 주소)
    glGenBuffers(1, &self.handle);
    return self;
}

// VBO 파괴
void vbo_destroy(struct VBO self)
{
    // 버퍼(VBO)를 제거하는 OpenGL 함수
    // glDeleteBuffers(삭제하는 버퍼의 갯수, VBO 객체 주소)
    glDeleteBuffers(1, &self.handle);
}

// 생성된 버퍼(VBO)에 type을 바인딩한다.
void vbo_bind(struct VBO self)
{
    // 생성한 버퍼(VBO)에 type을 바인딩하는 OpenGL 함수
    // glBindBuffer(Binding Type, VBO 객체 주소)
    glBindBuffer(self.type, self.handle);
}

// 실제 VBO에 데이터를 넣는 함수
void vbo_buffer(struct VBO self, void *data, size_t offset, size_t count)
{
    // VBO에 타입을 바인딩 한 후
    vbo_bind(self);
    // VBO에 데이터 삽입
    glBufferData(self.type, count - offset, data, self.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    // 실제 VBO에 데이터를 넣는 OpenGL 함수
    // glBufferData(Binding Type, 데이터 크기, 넣을 데이터, 데이터 사용 패턴)
    // 데이터 사용 패턴: ex) GL_STATIC_DRAW의 경우 한번 데이터가 저장되면 변경되지 않음을 의미
}