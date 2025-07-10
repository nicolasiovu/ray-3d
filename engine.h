#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>

struct Vec2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;
};

class Engine {
public:
	bool init(int width, int height);
	void run();
	void shutdown();

private:
	void processInput();
	void update(float deltaTime);
	void drawPixel(int x, int y, uint32_t color);
	void drawLine(Vec2 p1, Vec2 p2, uint32_t color);
	void drawTriangle(Vec2 a, Vec2 b, Vec2 c, uint32_t color);
	void render();

	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	SDL_Texture *texture = nullptr;
	std::vector<uint32_t> pixels;

	bool running = true;
	int width = 0, height = 0;
};
