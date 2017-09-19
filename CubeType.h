#pragma once
#include "appli.h"
#include "Cube.h"

#define NUMBER_TEXTURE	1
#define TYPE_AIR		-1
#define TYPE_GRASS		0

Texture* getTexture(int type);

void loadTexture(Texture**textures);