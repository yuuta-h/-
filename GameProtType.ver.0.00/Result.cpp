#include "Result.h"
#include "textDX.h"
#include "game.h"

void initializeResult() {};
void updateResult() { changeScene(); };
void drawResult() {
};
void printResult() {
	printTextDX(getDebugFont(), "Reslut", 0, 0);
};
void unInitializeResult() {};