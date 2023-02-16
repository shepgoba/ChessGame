#include "Game.h"

int main(int argc, char *argv[]) {
	ChessGame cg(argc, argv);
	try {
		cg.run();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}