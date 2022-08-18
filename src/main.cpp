#include "Game.h"

int main(int argc, char *argv[]) {
	ChessGame cg(argc, argv);
	cg.run();
	return 0;
}

static const inline KiB(int amount)
{
	return amount * 1024;
}

static const inline MiB(int amount)
{
	return KiB(amount) * 1024;
}

int main()
{
	int *some_bytes = malloc(MiB(4));
	
	for (int i = 0; i < 4 * 1024 * 1024; i++) {
		some_bytes[i] = i;
	}

	free(some_bytes);
	return 0;
}