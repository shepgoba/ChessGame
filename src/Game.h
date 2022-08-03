#ifndef CHESSGAME_INCLUDE_H
#define CHESSGAME_INCLUDE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <cassert>
#include <stdexcept>
#include <array>
#include <vector>
#include <chrono>
#include <iostream>
#include <ctime>
#include "ChessBoard.h"

class ChessGame {
private:
	constexpr static float target_fps = 60.0;

	constexpr static int window_width = 640;
	constexpr static int window_height = 640;

	constexpr static int tile_width = window_width / 8;
	constexpr static int tile_height = window_height / 8;

	bool running = false;

	SDL_Window *main_window = nullptr;
	SDL_Renderer *main_renderer = nullptr;

	ChessBoard board;
	std::array<SDL_Texture *, 12> piece_textures{};
	std::vector<std::string> args;

	// Setup Functions
	void setup_libraries();
	void setup();
	void load_piece_textures(std::array<SDL_Texture *, 12> &texts);

	// Logic Functions
	void poll_events();
	void update(float dt);

	//Drawing functions
	void draw_board();
	void draw_pieces();
	void draw();

	// Cleanup Functions
	void unload_piece_textures();
	void cleanup_libraries();
	void cleanup();
public:
	ChessGame(int argc, char *argv[]);
	void run();
};

#endif