#include "math.h"

float triArea(Vec2 A, Vec2 B, Vec2 C) {
	Vec2 AB = {B.x - A.x, B.y - A.y};
	Vec2 AC = {C.x - A.x, C.y - A.y};

	float ABxAC = AB.x * AC.y - AB.y * AC.x;
	return 0.5f * std::abs(ABxAC);
}

float triAreaSigned(Vec2 A, Vec2 B, Vec2 C) {
	Vec2 AB = {B.x - A.x, B.y - A.y};
	Vec2 AC = {C.x - A.x, C.y - A.y};

	float ABxAC = AB.x * AC.y - AB.y * AC.x;
	return 0.5f * ABxAC;
}

Vec3 barycentric(Vec2 P, Vec2 A, Vec2 B, Vec2 C) {
	float ABC = triAreaSigned(A, B, C);
	float alpha = triAreaSigned(P, B, C) / ABC;
	float beta = triAreaSigned(P, C, A) / ABC;
	float gamma = triAreaSigned(P, A, B) / ABC;
	
	return Vec3{alpha, beta, gamma};
}
