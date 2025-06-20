#include "engine.h"
#include <iostream>
#include <algorithm>

bool Engine::init(int w, int h) {
	width = w; height = h;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize. SDL Error: " << SDL_GetError() << "\n";
		return false;
	}

	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Window could not be created. SDL_Error: " << SDL_GetError() << "\n";
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cerr << "Renderer could not be created. SDL_Error: " << SDL_GetError() << "\n";
		return false;
	}

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!texture) {
		std::cerr << "Texture could not be created. SDL_Error: " << SDL_GetError() << "\n";
		return false;
	}

	pixels.resize(width * height);
	return true;
}

void Engine::processInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			running = false;
		} else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
			running = false;
		}
	}
}

void Engine::drawPixel(int x, int y, uint32_t color) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		pixels[y * width + x] = color;
	}
}

void Engine::drawLine(Vec2 p1, Vec2 p2, uint32_t color) {
	int x0 = p1.x;
	int y0 = p1.y;
	int x1 = p2.x;
	int y1 = p2.y;

	bool steep = abs(y1 - y0) > abs(x1 - x0); 
	
	if (steep) {
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = abs(y1 - y0);
	int error = dx / 2;
	int ystep = (y0 < y1) ? 1: -1;
	int y = y0;

	for (int x = x0; x <= x1; ++x) {
		if (steep) {
			drawPixel(y, x, color);
		} else {
			drawPixel(x, y, color);
		}

		error -= dy;
		if (error < 0) {
			y += ystep;
			error += dx;
		}
	}
}

void Engine::drawTriangle(Vec2 a, Vec2 b, Vec2 c, uint32_t color) {
	drawLine(a, b, color);
	drawLine(b, c, color);
	drawLine(a, c, color);
}

void Engine::update(float time) {
	// TODO
}

void Engine::render() {
	std::fill(pixels.begin(), pixels.end(), 0xFF000000);
	
	// Test 1: Right-angled triangle (horizontal base)
	Vec2 a = {100, 100};
	Vec2 b = {200, 100};
	Vec2 c = {150, 200};
	drawTriangle(a, b, c, 0xFFFFFFFF);

	// Test 2: Flat-bottom triangle
	Vec2 d = {300, 100};
	Vec2 e = {350, 200};
	Vec2 f = {250, 200};
	drawTriangle(d, e, f, 0xFF00FF00); // Green

	// Test 3: Flat-top triangle
	Vec2 g = {400, 200};
	Vec2 h = {450, 100};
	Vec2 i = {350, 100};
	drawTriangle(g, h, i, 0xFF0000FF); // Blue

	// Test 4: Left-leaning triangle
	Vec2 j = {100, 300};
	Vec2 k = {50, 400};
	Vec2 l = {150, 400};
	drawTriangle(j, k, l, 0xFFFFFF00); // Yellow

	// Test 5: Right-leaning triangle
	Vec2 m = {200, 300};
	Vec2 n = {300, 400};
	Vec2 o = {100, 400};
	drawTriangle(m, n, o, 0xFFFF00FF); // Magenta

	// Test 6: Completely upside down
	Vec2 p = {400, 400};
	Vec2 q = {350, 300};
	Vec2 r = {450, 300};
	drawTriangle(p, q, r, 0xFF00FFFF); // Cyan

	SDL_UpdateTexture(texture, nullptr, pixels.data(), width * sizeof(uint32_t));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void Engine::run() {
	running = true;

	while (running) {
		processInput();
		update(0);
		render();
	}
}

void Engine::shutdown() {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}


