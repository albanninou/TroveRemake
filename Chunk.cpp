#include "Chunk.h"

Chunk::Chunk(vec3 coordonner)
{
	m_coordonner = coordonner;
	generateChunk();
}

Chunk::Chunk()
{
	m_coordonner = vec3(0, 0, 0);
}

Chunk::~Chunk()
{
}

void Chunk::generateChunk()
{
	for (int i = 0; i < CHUNK_SIZE_HAUT; i++) {
		for (int x = 0; x < CHUNK_SIZE_BASE; x++) {
			for (int y = 0; y < CHUNK_SIZE_BASE; y++) {
				m_cubes[i][x][y] = new Cube(vec3(x, i, y), TYPE_GRASS);
			}
		}
	}
}

void Chunk::afficher(glm::mat4 & projection, glm::mat4 & modelview)
{
	for (int i = 0; i < CHUNK_SIZE_HAUT; i++) {
		for (int x = 0; x < CHUNK_SIZE_BASE; x++) {
			for (int y = 0; y < CHUNK_SIZE_BASE; y++) {
				
				m_cubes[i][x][y]->afficher(projection, modelview);
			}
		}
	}
}
