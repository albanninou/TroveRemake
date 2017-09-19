#include "Chunk.h"

Chunk::Chunk(vec3 coordonner)
{
	m_coordonner = coordonner;
	indexCubesAir = 0;
	generateChunk();
}

Chunk::Chunk()
{
	indexCubesAir = 0;
	m_coordonner = vec3(0, 0, 0);
	generateChunk();
}

Chunk::~Chunk()
{
}

void Chunk::generateChunk()
{
	for (int i = 0; i < CHUNK_SIZE_HAUT; i++) {
		for (int x = 0; x < CHUNK_SIZE_BASE; x++) {
			for (int y = 0; y < CHUNK_SIZE_BASE; y++) {
				if (i>30) {
					m_cubes[i][x][y] = new Cube(vec3(x, i, y), TYPE_AIR);
				}
				else {
					m_cubes[i][x][y] = new Cube(vec3(x, i, y), TYPE_GRASS);
				}
			}
		}
	}
	for (int i = 0; i < CHUNK_SIZE_HAUT; i++) {
		for (int x = 0; x < CHUNK_SIZE_BASE; x++) {
			for (int y = 0; y < CHUNK_SIZE_BASE; y++) {
				if (m_cubes[i][x][y]->getType() == TYPE_AIR) {
					
					setAirBlock(i, x, y);
				}
			}
		}
	}

}

void Chunk::setAirBlock(int i, int x, int y)
{
	
	if (i > 0) {
		if (m_cubes[i - 1][x][y]->getType() != TYPE_AIR) {
			if (!containAir(vec3(x, i-1, y))) {
				m_cubesAfficher[indexCubesAir++] = m_cubes[i - 1][x][y];
			}
		}
	}
	if (i < CHUNK_SIZE_HAUT) {
		if (m_cubes[i + 1][x][y]->getType() != TYPE_AIR) {
			if (!containAir(vec3(x, i + 1, y))) {
				m_cubesAfficher[indexCubesAir++] = m_cubes[i + 1][x][y];
			}
		}
	}
	if (x > 0) {
		if (m_cubes[i][x - 1][y]->getType() != TYPE_AIR) {
			if (!containAir(vec3(x-1, i, y))) {
				m_cubesAfficher[indexCubesAir++] = m_cubes[i][x - 1][y];
			}
		}
	}
	if (x < CHUNK_SIZE_BASE) {
		if (m_cubes[i][x + 1][y]->getType() != TYPE_AIR) {
			if (!containAir(vec3(x + 1, i, y))) {
				m_cubesAfficher[indexCubesAir++] = m_cubes[i][x + 1][y];
			}
		}
	}
	
	if (y > 0) {
		if (m_cubes[i][x][y - 1]->getType() != TYPE_AIR) {
			if (!containAir(vec3(x , i, y-1))) {
				m_cubesAfficher[indexCubesAir++] = m_cubes[i][x][y - 1];
			}
		}
	}
	if (y < CHUNK_SIZE_BASE) {
		if (m_cubes[i][x][y + 1]->getType() != TYPE_AIR) {
			if (!containAir(vec3(x, i, y+1))) {
				m_cubesAfficher[indexCubesAir++] = m_cubes[i][x][y + 1];
			}
		}
	}
}

void Chunk::afficher(glm::mat4 & projection, glm::mat4 & modelview)
{
	for (int i = 0; i < indexCubesAir; i++) {
		m_cubesAfficher[i]->afficher(projection,modelview);
	}
	/*for (int i = 0; i < CHUNK_SIZE_HAUT; i++) {
		for (int x = 0; x < CHUNK_SIZE_BASE; x++) {
			for (int y = 0; y < CHUNK_SIZE_BASE; y++) {	
				m_cubes[i][x][y]->afficher(projection, modelview);
			}
		}
	}*/
}

void Chunk::removeBlock(vec3 coordonner)
{
	m_cubes[(int)coordonner.y][(int)coordonner.x][(int)coordonner.z]->setType(TYPE_AIR);
	setAirBlock((int)coordonner.y,(int)coordonner.x,(int)coordonner.z);
}

Cube* Chunk::getCubeAt(vec3 coordonner)
{
	return m_cubes[(int)coordonner.y][(int)coordonner.x][(int)coordonner.z];
}

bool Chunk::containAir(vec3 coordonner)
{
	int i = 0;
	while (i < indexCubesAir) {
		if (m_cubesAfficher[i]->getCoordonner() == coordonner) {
			
			return true;
		}
		i++;
	}
	return false;
}



