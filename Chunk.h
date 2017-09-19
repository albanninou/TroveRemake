#pragma once
#include "Cube.h"
#define CHUNK_SIZE_HAUT		100
#define CHUNK_SIZE_BASE		10
#define CHUNK_SIZE_TOTAL    CHUNK_SIZE_HAUT * CHUNK_SIZE_BASE*CHUNK_SIZE_BASE

class Chunk
{
public:

	Chunk(vec3 coordonner);
	Chunk();
	~Chunk();
	void generateChunk();
	void setAirBlock(int i,int x,int y);
	void afficher(glm::mat4 &projection, glm::mat4 &modelview);
	void removeBlock(vec3 coordonner);
	Cube* getCubeAt(vec3 coordonner);

protected:
	bool containAir(vec3 coordonner);
	Cube *m_cubes[CHUNK_SIZE_HAUT][CHUNK_SIZE_BASE][CHUNK_SIZE_BASE];
	Cube *m_cubesAfficher[CHUNK_SIZE_TOTAL];
	int indexCubesAir;
	glm::vec3 m_coordonner;
};

