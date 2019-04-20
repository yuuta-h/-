#include "Title.h"
#include "textDX.h"
#include "Image.h"
#include"textureLoader.h"
Image back;

void initializeTitle() {
	InitImage(&back, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
};
void updateTitle() {

};
void drawTitle() {
	DrawImage(&back);
};
void printTitle() {
	printTextDX(getDebugFont(), "Title", 0, 0);
};
void unInitializeTitle() {};