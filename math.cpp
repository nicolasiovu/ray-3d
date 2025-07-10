#include "math.h"

float triArea(Vec2 A, Vec2 B, Vec2 C) {
	Vec2 AB = {B.x - A.x, B.y - A.y};
	Vec2 AC = {C.x - A.x, C.y - A.y};

	float ABxAC = AB.x * AC.y - AB.y * AC.x;
	return (1/2) * std::abs(ABxAC);
}

Vec3 barycentric(Vec2 P, Vec2 A, Vec2 B, Vec2 C) {

}
