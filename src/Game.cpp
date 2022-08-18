#include "Game.h"

static inline SDL_Rect SDLRectMake(unsigned x, unsigned y, unsigned w, unsigned h) {
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

ChessGame::ChessGame(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		auto str = std::string(argv[i]);
		args.push_back(str);
	}
}

void ChessGame::setup_libraries()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error("SDL_Init failed");
	}
	if (IMG_Init(IMG_INIT_PNG) < 0) {
		throw std::runtime_error("IMG_Init failed");
	}
}

void ChessGame::setup()
{
	setup_libraries();

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

	load_piece_textures(piece_textures);
}

void ChessGame::load_piece_textures(std::array<SDL_Texture *, 12> &texts)
{
	const std::array<const char *, 12> urls = {
		"PawnW.png", "RookW.png",
		"KnightW.png", "BishopW.png",
		"QueenW.png", "KingW.png",
		"PawnB.png", "RookB.png",
		"KnightB.png", "BishopB.png",
		"QueenB.png", "KingB.png"
	};

	for (std::size_t i = 0; i < urls.size(); i++) {
		const char *url = urls[i];
		auto assetPath = GetAssetPath(url);

		SDL_Texture *texture = IMG_LoadTexture(main_renderer, assetPath.c_str());
		if (!texture)
			throw std::runtime_error("Failed to load texture!");
			
		texts[i] = texture;
	}
}

void ChessGame::draw_board()
{
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			const SDL_Rect tileRect = SDLRectMake(
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
	for (std::size_t y = 0; y < board.GetHeight(); y++) {
		for (std::size_t x = 0; x < board.GetWidth(); x++) {
			const ChessPieceLocation loc = ChessPieceLocation(x, y);
			const ChessPiece &piece = board.GetPiece(loc);

			const SDL_Rect draw_rect = SDLRectMake(x * tile_width, y * tile_height, tile_width, tile_height);
			switch (piece.GetOwner()) {
				case PlayerBlack: {
					// add 6 because of how the pieces are laid out
					std::size_t texture_offset = 6 + piece.GetType();
					assert(texture_offset <= 11);

					SDL_RenderCopy(main_renderer, piece_textures[texture_offset], NULL, &draw_rect);
					break;
				}
				case PlayerWhite: {
					std::size_t texture_offset = piece.GetType();
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

std::vector<ChessPieceLocation> get_valid_pawn_moves(const ChessPiece &piece, const ChessPieceLocation &loc)
{
	std::vector<ChessPieceLocation> valid_moves;

	switch (piece.GetOwner()) {
		case PlayerWhite: {
			valid_moves.push_back(ChessPieceLocation(loc.x, loc.y - 1));
			if (piece.GetMoveCount() == 0) {
				valid_moves.push_back(ChessPieceLocation(loc.x, loc.y - 2));
			}

			break;
		}
		case PlayerBlack: {
			valid_moves.push_back(ChessPieceLocation(loc.x, loc.y + 1));
			if (piece.GetMoveCount() == 0) {
				valid_moves.push_back(ChessPieceLocation(loc.x, loc.y + 2));
			}
			break;
		}
		default: {
			throw std::runtime_error("Unknown player type!");
			break;
		}
	}
	

	return valid_moves;
}

std::vector<ChessPieceLocation> get_valid_rook_moves(const ChessPiece &piece, const ChessPieceLocation &loc)
{
	return {};
}

std::vector<ChessPieceLocation> get_valid_knight_moves(const ChessPiece &piece, const ChessPieceLocation &loc)
{
	return {};
}

std::vector<ChessPieceLocation> get_valid_bishop_moves(const ChessPiece &piece, const ChessPieceLocation &loc)
{
	return {};
}

std::vector<ChessPieceLocation> get_valid_queen_moves(const ChessPiece &piece, const ChessPieceLocation &loc)
{
	return {};
}

std::vector<ChessPieceLocation> get_valid_king_moves(const ChessPiece &piece, const ChessPieceLocation &loc)
{
	return {};
}



std::vector<ChessPieceLocation> ChessGame::get_valid_moves(const ChessPiece &piece, const ChessPieceLocation &loc)
{
	std::vector<ChessPieceLocation> valid_moves{};
	switch (piece.GetType()) {
		case PieceTypePawn: {
			valid_moves = get_valid_pawn_moves(piece, loc);
			break;
		}
		case PieceTypeRook: {
			valid_moves = get_valid_rook_moves(piece, loc);
			break;
		}
		case PieceTypeKnight: {
			valid_moves = get_valid_knight_moves(piece, loc);
			break;
		}
		case PieceTypeBishop: {
			valid_moves = get_valid_bishop_moves(piece, loc);
			break;
		}
		case PieceTypeQueen: {
			valid_moves = get_valid_queen_moves(piece, loc);
			break;
		}
		case PieceTypeKing: {
			valid_moves = get_valid_king_moves(piece, loc);
			break;
		}
		default: {
			throw std::runtime_error("Unknown piece type!");
			break;
		}
	}

	return valid_moves;
}

void ChessGame::handle_click(const SDL_MouseButtonEvent &event)
{
	if (event.button != SDL_BUTTON_LEFT)
		return;

	const int x = event.x;
	const int y = event.y;

	const std::size_t tile_x = x / tile_width;
	const std::size_t tile_y = y / tile_height;

	const ChessPieceLocation loc = ChessPieceLocation(tile_x, tile_y);
	const ChessPiece &piece = board.GetPiece(loc);

	if (!piece.IsValid())
		return;
 
	const std::vector<ChessPieceLocation> moves = get_valid_moves(piece, loc);
	board.MovePiece(loc, moves.back());
}

void ChessGame::poll_events()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT: {
				running = false;
				break;
			}
			case SDL_MOUSEBUTTONUP: {
				handle_click(e.button);
				break;
			}
		}
	}
}

void ChessGame::update(float dt)
{
	poll_events();
}

void ChessGame::draw()
{
	SDL_SetRenderDrawColor(main_renderer, 255, 255, 255, 255);
	SDL_RenderClear(main_renderer);

	draw_board();
	draw_pieces();

	SDL_RenderPresent(main_renderer);
}

void ChessGame::unload_piece_textures()
{
	for (SDL_Texture *&texture : piece_textures) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void ChessGame::cleanup_libraries()
{
	IMG_Quit();
	SDL_Quit();
}

void ChessGame::cleanup()
{
	unload_piece_textures();
	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyWindow(main_window);

	cleanup_libraries();
}

void ChessGame::run() {
	setup();

	running = true;

	float dt = 0.0;
	while (running) {
		update(dt);
		draw();
		SDL_Delay(1000.f / target_fps);
	}
	cleanup();
}