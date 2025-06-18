#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char **argv) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize. SDL Error: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Window could not be created. SDL_Error: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cerr << "Renderer could not be created. SDL_Error: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!texture) {
		std::cerr << "Texture could not be created. SDL_Error: " << SDL_GetError() << "\n";
		return 1;
	}

	std::vector<uint32_t> pixels(SCREEN_WIDTH * SCREEN_HEIGHT);

	SDL_Event e;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			} else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
			}
		}

		std::fill(pixels.begin(), pixels.end(), 0xFF000000);

		// placeholder, line
		for (int i = 0; i < std::min(SCREEN_WIDTH, SCREEN_HEIGHT); i++) {
			pixels[i * SCREEN_WIDTH + i] = 0xFFFFFFFF;
		}

		SDL_UpdateTexture(texture, nullptr, pixels.data(), SCREEN_WIDTH * sizeof(uint32_t));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;
}
