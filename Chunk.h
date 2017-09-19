#pragma once
#include "Cube.h"
#define CHUNK_SIZE_HAUT		100
#define CHUNK_SIZE_BASE		10

class Chunk
{
public:

	Chunk(vec3 coordonner);
	Chunk();
	~Chunk();
	void generateChunk();
	void afficher(glm::mat4 &projection, glm::mat4 &modelview);

protected:
	Cube *m_cubes[CHUNK_SIZE_HAUT][CHUNK_SIZE_BASE][CHUNK_SIZE_BASE];
	glm::vec3 m_coordonner;
};