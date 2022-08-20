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

	bool m_running = false;
	bool m_show_possible_moves = false;

	SDL_Window *m_main_window = nullptr;
	SDL_Renderer *m_main_renderer = nullptr;

	ChessBoard m_board;
	std::array<SDL_Texture *, 12> m_piece_textures;
	std::vector<std::string> m_args;
	

	int selected_piece_x, selected_piece_y;
	std::vector<ChessPieceLocation> m_possible_moves;

	// Setup Functions
	void setup_libraries();
	void setup();
	void load_piece_textures(std::array<SDL_Texture *, 12> &texts);

	// Logic Functions
	void poll_events();
	void update(float dt);
	void handle_click(const SDL_MouseButtonEvent &event);

	std::vector<ChessPieceLocation> get_valid_moves(const ChessPiece &piece, const ChessPieceLocation &loc);

	void add_valid_pawn_moves(std::vector<ChessPieceLocation> &moves, const ChessPiece &piece, const ChessPieceLocation &loc);
	void add_valid_rook_moves(std::vector<ChessPieceLocation> &moves, const ChessPiece &piece, const ChessPieceLocation &loc);
	void add_valid_knight_moves(std::vector<ChessPieceLocation> &moves, const ChessPiece &piece, const ChessPieceLocation &loc);
	void add_valid_bishop_moves(std::vector<ChessPieceLocation> &moves, const ChessPiece &piece, const ChessPieceLocation &loc);
	void add_valid_queen_moves(std::vector<ChessPieceLocation> &moves, const ChessPiece &piece, const ChessPieceLocation &loc);
	void add_valid_king_moves(std::vector<ChessPieceLocation> &moves, const ChessPiece &piece, const ChessPieceLocation &loc);
	
	//Drawing functions
	void draw_possible_moves();
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