#include "fmath.h"
#include "util.h"

int ivec3scmp(ivec3s a, ivec3s b) {
	return memcmp(&a, &b, sizeof(ivec3s));
}

// ivec3s를 hash로 변환하는 함수
// ref: https://minorman.tistory.com/36
// 
// 0x9e3779b9 = magin hasing 상수
// ref: https://softwareengineering.stackexchange.com/questions/402542/where-do-magic-hashing-constants-like-0x9e3779b9-and-0x9e3779b1-come-from
s64 ivec3shash(ivec3s v) {
	s64 seed = 0;
	for (int i = 0; i < 3; i++) {
		seed ^= v.raw[i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

// s + t * ds가 정수인 t를 찾는다.
static vec3s intbound(vec3s s, vec3s ds) {
    vec3s v;

    for (size_t i = 0; i < 3; i++) {
        v.raw[i] = (ds.raw[i] > 0 ? (ceilf(s.raw[i]) - s.raw[i]) \
									: (s.raw[i] - floorf(s.raw[i]))) / fabsf(ds.raw[i]);
    }
    return v;
}

bool ray_block(struct Ray ray, f32 max_distance, bool (*f)(ivec3s), ivec3s* out, enum Direction* d_out) {
	ivec3s p;
	vec3s d, tmax, tdelta;
	f32 radius;

	p = (ivec3s){ { floori(ray.origin.x), floori(ray.origin.y), floori(ray.origin.z)} };
	d = ray.direction;
	ivec3s step = (ivec3s){ { sign(d.x), sign(d.y), sign(d.z)} };
	tmax = intbound(ray.origin, d);
	tdelta = glms_vec3_div(IVEC2S2V(step), d);
	radius = max_distance / glms_vec3_norm(d);
}