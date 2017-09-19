#pragma once
#include "appli.h"
#include "Input.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Cube.h"
#include "Chunk.h"

class SceneOpenGL
{
public:

	SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
	~SceneOpenGL();

	bool initialiserFenetre();
	bool initGL();
	void bouclePrincipale();


private:

	std::string m_titreFenetre;
	int m_largeurFenetre;
	int m_hauteurFenetre;
	SDL_Window* m_fenetre;
	SDL_GLContext m_contexteOpenGL;
	Input m_input;
};