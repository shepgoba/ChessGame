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

constexpr static unsigned NUM_PIECES = 12;
static std::string GetAssetPath(const char *in)
{
	return std::string("assets/") + in;
}


static SDL_Rect SDLRectMake(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	return r;
}

enum Player : unsigned int{
	PlayerWhite = 0,
	PlayerBlack = 1,
	PlayerNone = 2
};

enum PieceType : unsigned int {
	PieceTypePawn = 0,
	PieceTypeRook = 1,
	PieceTypeKnight = 2,
	PieceTypeBishop = 3,
	PieceTypeQueen = 4,
	PieceTypeKing = 5,
	PieceTypeNone = 6
};

// Described with the top left tile as the origin,
// and the x-axis increasing as it moves to the right,
// and the y-axis increasing as it moves down

struct ChessPieceLocation {
	unsigned int x;
	unsigned int y;

	ChessPieceLocation(unsigned int x, unsigned int y) : x(x), y(y) {
		assert(x >= 0 && x <= 7);
		assert(y >= 0 && y <= 7);
	}
};

class ChessPiece {
private:
	Player owner;
	PieceType type;
public:
	ChessPiece(Player p, PieceType t) : owner(p), type(t) {}

	Player GetOwner() const {
		return owner;
	}

	PieceType GetType() const {
		return type;
	}

	bool IsValid() const {
		return (this->owner != PlayerNone) && (this->type != PieceTypeNone);
	}
};

class ChessBoard {
private:
	static constexpr unsigned int BOARD_WIDTH = 8;
	static constexpr unsigned int BOARD_HEIGHT = 8;

	ChessPiece board[BOARD_WIDTH][BOARD_HEIGHT] = {
		{
			ChessPiece(PlayerBlack, PieceTypeRook),
			ChessPiece(PlayerBlack, PieceTypeKnight),
			ChessPiece(PlayerBlack, PieceTypeBishop),
			ChessPiece(PlayerBlack, PieceTypeQueen),
			ChessPiece(PlayerBlack, PieceTypeKing),
			ChessPiece(PlayerBlack, PieceTypeBishop),
			ChessPiece(PlayerBlack, PieceTypeKnight),
			ChessPiece(PlayerBlack, PieceTypeRook)
		},
		{
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn),
			ChessPiece(PlayerBlack, PieceTypePawn)
		},
		{
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone)
		},
		{
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone)
		},
		{
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone)
		},
		{
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone),
			ChessPiece(PlayerNone, PieceTypeNone)
		},
		{
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn),
			ChessPiece(PlayerWhite, PieceTypePawn)
		},
		{
			ChessPiece(PlayerWhite, PieceTypeRook),
			ChessPiece(PlayerWhite, PieceTypeKnight),
			ChessPiece(PlayerWhite, PieceTypeBishop),
			ChessPiece(PlayerWhite, PieceTypeQueen),
			ChessPiece(PlayerWhite, PieceTypeKing),
			ChessPiece(PlayerWhite, PieceTypeBishop),
			ChessPiece(PlayerWhite, PieceTypeKnight),
			ChessPiece(PlayerWhite, PieceTypeRook)
		}
	};
public:
	bool MovePiece(ChessPieceLocation from, ChessPieceLocation to)
	{
		ChessPiece &pieceFrom = board[from.y][from.x];
		ChessPiece &pieceTo = board[to.y][to.x];

		if (!pieceFrom.IsValid())
			return false;

		board[to.y][to.x] = pieceFrom;
		return true;
	}

	const ChessPiece &GetPiece(ChessPieceLocation loc) const {
		return board[loc.y][loc.x];
	}

	unsigned int GetWidth() const { return BOARD_WIDTH; }
	unsigned int GetHeight() const { return BOARD_HEIGHT; }
};


class ChessGame {
private:
	constexpr static float target_fps = 60.0;

	constexpr static int window_width = 400;
	constexpr static int window_height = 400;

	constexpr static int tile_width = window_width / 8;
	constexpr static int tile_height = window_height / 8;

	bool running = false;

	SDL_Window *main_window = nullptr;
	SDL_Renderer *main_renderer = nullptr;

	ChessBoard board;
	std::array<SDL_Texture *, NUM_PIECES> piece_textures;
	std::vector<std::string> args;

	void setup() {
		setvbuf(stdout, NULL, _IONBF, 0); 

		main_window = SDL_CreateWindow("Chess(tm)",
			SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 
			window_width, 
			window_height, 
			SDL_WINDOW_RESIZABLE);

		if (!main_window)
			throw std::runtime_error("Game window could not be created.");

		main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
		if (!main_renderer)
			throw std::runtime_error("Game renderer could not be created.");

		SDL_SetRenderDrawBlendMode(main_renderer, SDL_BLENDMODE_BLEND);

		
		load_piece_textures();
	}

	
	void load_piece_textures() {
		std::array<const char *, NUM_PIECES> urls = {
			"PawnW.png", "RookW.png",
			"KnightW.png", "BishopW.png",
			"QueenW.png", "KingW.png",
			"PawnB.png", "RookB.png",
			"KnightB.png", "BishopB.png",
			"QueenB.png", "KingB.png"
		};

		for (int i = 0; i < urls.size(); i++) {
			const char *url = urls[i];
			auto assetPath = GetAssetPath(url);

			SDL_Texture *texture = IMG_LoadTexture(main_renderer, assetPath.c_str());
			if (!texture)
				throw std::runtime_error("Failed to load texture!");

			piece_textures[i] = texture;
		}
	}

	void draw_board() {
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				SDL_Rect tileRect = SDLRectMake(
					x * tile_width, y * tile_height, 
					tile_width, tile_height
				);


				// draw checkerboard pattern
				if ((x % 2 == 0) ^ (y % 2 == 0))
					SDL_SetRenderDrawColor(main_renderer, 92, 76, 56, 255);
				else
					SDL_SetRenderDrawColor(main_renderer, 224, 195, 157, 255);

				SDL_RenderFillRect(main_renderer, &tileRect);
			}
		}
	}

	void draw_pieces()
	{
		for (int y = 0; y < board.GetHeight(); y++) {
			for (int x = 0; x < board.GetWidth(); x++) {
				ChessPieceLocation loc = ChessPieceLocation(x, y);
				const ChessPiece &piece = board.GetPiece(loc);

				const SDL_Rect draw_rect = SDLRectMake(x * tile_width, y * tile_height, tile_width, tile_height);
				switch (piece.GetOwner()) {
					case PlayerBlack: {
						// add 6 because of how the pieces are laid out
						unsigned int texture_offset = 6 + piece.GetType();
						assert(texture_offset <= 11);

						SDL_RenderCopy(main_renderer, piece_textures[texture_offset], NULL, &draw_rect);
						break;
					}
					case PlayerWhite: {
						unsigned int texture_offset = piece.GetType();
						assert(texture_offset <= 5);

						SDL_RenderCopy(main_renderer, piece_textures[texture_offset], NULL, &draw_rect);
						break;
					}
					
					case PlayerNone: {
						// draw nothing
						break;
					}
					default: {
						throw std::runtime_error("Unknown player type!");
						break;
					}
				}
			}
		}
	}

	void draw()
	{
		draw_board();
		draw_pieces();
	}

	void unload_piece_textures()
	{
		for (const auto &texture : piece_textures) {
			SDL_DestroyTexture(texture);
		}
	}

	void cleanup()
	{
		unload_piece_textures();
		SDL_DestroyRenderer(main_renderer);
		SDL_DestroyWindow(main_window);
	}

public:
	ChessGame(int argc, char **argv) {
		for (int i = 0; i < argc; i++) {
			auto str = std::string(argv[i]);
			args.push_back(str);
		}
	}

	void run() {
		setup();

		running = true;

		while (running) {
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				switch (e.type) {
					case SDL_QUIT: {
						running = false;
						break;
					}
					case SDL_MOUSEBUTTONUP: {
						printf("mouse up!\n");
						break;
					}
				}
			}
			SDL_SetRenderDrawColor(main_renderer, 255, 255, 255, 255);
			SDL_RenderClear(main_renderer);
			
			draw();

			SDL_RenderPresent(main_renderer);

			SDL_Delay(1000.f / target_fps);
		}
		cleanup();
	}
};

#endif