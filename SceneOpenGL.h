#pragma once
#include "appli.h"
#include "Input.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Cube.h"
#include "Chunk.h"

#define CHUNK_VIEW		3

class SceneOpenGL
{
public:

	SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
	~SceneOpenGL();

	bool initialiserFenetre();
	bool initGL();
	void bouclePrincipale();


private:
	Chunk* m_chunk[CHUNK_VIEW][CHUNK_VIEW];
	std::string m_titreFenetre;
	int m_largeurFenetre;
	int m_hauteurFenetre;
	SDL_Window* m_fenetre;
	SDL_GLContext m_contexteOpenGL;
	Input m_input;
};