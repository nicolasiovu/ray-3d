#pragma once
#include <algorithm>
#include "engine.h"

float triArea(Vec2 A, Vec2 B, Vec2 C);

float triAreaSigned(Vec2 A, Vec2 B, Vec2 C);

Vec3 barycentric(Vec2 P, Vec2 A, Vec2 B, Vec2 C);
