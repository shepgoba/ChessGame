#include "Game.h"

static SDL_Rect SDLRectMake(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	return r;
}

static std::string GetAssetPath(const char *in)
{
	return std::string("assets/") + in;
}

void ChessGame::setup()
{
	setvbuf(stdout, NULL, _IONBF, 0); 

	main_window = SDL_CreateWindow("Chess(tm)",
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		window_width, 
		window_height, 
		0
	);

	if (!main_window)
		throw std::runtime_error("Game window could not be created.");

	main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
	if (!main_renderer)
		throw std::runtime_error("Game renderer could not be created.");

	SDL_SetRenderDrawBlendMode(main_renderer, SDL_BLENDMODE_BLEND);

	load_piece_textures();
}

void ChessGame::load_piece_textures()
{
	const std::array<const char *, 12> urls = {
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

void ChessGame::draw_board()
{
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

void ChessGame::draw_pieces()
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

void ChessGame::draw()
{
	draw_board();
	draw_pieces();
}

void ChessGame::unload_piece_textures()
{
	for (const auto &texture : piece_textures) {
		SDL_DestroyTexture(texture);
	}
}

void ChessGame::cleanup()
{
	unload_piece_textures();
	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyWindow(main_window);
}

ChessGame::ChessGame(int argc, char **argv) {
	for (int i = 0; i < argc; i++) {
		auto str = std::string(argv[i]);
		args.push_back(str);
	}
}

void ChessGame::run() {
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
					printf("mouse released!\n");
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