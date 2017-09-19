#include "CubeType.h"


Texture* getTexture(int type)
{
	static Texture* textures[NUMBER_TEXTURE] = { NULL };
	if (textures[0] != NULL) {
		if (textures[0]->getID() == 0) {
			loadTexture(textures);
		}
	}
	else {
		loadTexture(textures);
	}
	return textures[type];
}

void loadTexture(Texture * *textures)
{
	std::cout << "Load Textures" << std::endl;
	textures[TYPE_GRASS] = new Texture("Textures/Herbe.jpg");
	textures[TYPE_GRASS]->charger();
}

