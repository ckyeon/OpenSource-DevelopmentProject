#include "fmath.h"
#include "util.h"

int ivec3scmp(ivec3s a, ivec3s b)
{
	return memcmp(&a, &b, sizeof(ivec3s));
}

// ivec3s를 hash로 변환하는 함수
// ref: https://minorman.tistory.com/36
//
// 0x9e3779b9 = magin hasing 상수
// ref: https://softwareengineering.stackexchange.com/questions/402542/where-do-magic-hashing-constants-like-0x9e3779b9-and-0x9e3779b1-come-from
s64 ivec3shash(ivec3s v)
{
	s64 seed = 0;
	for (int i = 0; i < 3; i++)
	{
		seed ^= v.raw[i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

// s + t * ds가 정수인 가장 작은 t를 찾는다.
static vec3s intbound(vec3s s, vec3s ds)
{
	vec3s v;

#if defined(__clang__)
#pragma clang loop unroll_count(3)
#elif defined(__GNUC__)
#pragma GCC unroll 3
#endif

	for (size_t i = 0; i < 3; i++)
	{
		v.raw[i] = (ds.raw[i] > 0 ? (ceilf(s.raw[i]) - s.raw[i]) : (s.raw[i] - floorf(s.raw[i]))) / fabsf(ds.raw[i]);
	}
	return v;
}

// 레이저가 블럭과 충돌하는지 확인
// 이 함수를 통해 블럭에 닿는지 아닌지 체크
// ray = 레이저
// max_distance = 최대 사거리
// (*f)(ivec3s) = 블럭이 좌표에 있는지 아닌지 여부
// *out = 블럭을 바라보고 있는지 아닌지

// DDA 알고리즘
// ref: https://365kim.tistory.com/44
bool ray_block(struct Ray ray, f32 max_distance, bool (*f)(ivec3s), ivec3s *out, enum Direction *d_out)
{
	ivec3s p, step;
	vec3s d, tmax, tdelta;
	f32 radius;

	// p(포인트)의 x, y, z를 전부 정수로 만듦
	p = (ivec3s){{floori(ray.origin.x), floori(ray.origin.y), floori(ray.origin.z)}};
	// 레이저의 방향
	d = ray.direction;
	// 각 벡터의 원소가 0보다 큰지 아닌지 저장
	step = (ivec3s){{sign(d.x), sign(d.y), sign(d.z)}};
	// s + t * ds가 정수인 t를 찾는다.
	tmax = intbound(ray.origin, d);
	// IVEC3S 벡터를 방향 벡터로 나눔 -> 해당 방향을 제외하고는 0이 됨
	tdelta = glms_vec3_div(IVEC3S2V(step), d);
	// 최대 거리 / 벡터의 크기
	radius = max_distance / glms_vec3_norm(d);

	while (true)
	{
		if (f(p))
		{
			*out = p;
			return true;
		}

		if (tmax.x < tmax.y)
		{
			if (tmax.x < tmax.z)
			{
				if (tmax.x > radius)
				{
					break;
				}

				p.x += step.x;
				tmax.x += tdelta.x;
				*d_out = IVEC3S2DIR(((ivec3s){{-step.x, 0, 0}}));
			}
			else
			{
				if (tmax.z > radius)
				{
					break;
				}

				p.z += step.z;
				tmax.z += tdelta.z;
				*d_out = IVEC3S2DIR(((ivec3s){{0, 0, -step.z}}));
			}
		}
		else
		{
			if (tmax.y < tmax.z)
			{
				if (tmax.y > radius)
				{
					break;
				}

				p.y += step.y;
				tmax.y += tdelta.y;
				*d_out = IVEC3S2DIR(((ivec3s){{0, -step.y, 0}}));
			}
			else
			{
				if (tmax.z > radius)
				{
					break;
				}

				p.z += step.z;
				tmax.z += tdelta.z;
				*d_out = IVEC3S2DIR(((ivec3s){{0, 0, -step.z}}));
			}
		}
	}

	return false;
}