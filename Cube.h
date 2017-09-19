#pragma once
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "CubeType.h"

class Cube: public Model
{
public:

	Cube(vec3 coordonner, std::string const texture);
	Cube(vec3 coordonner, int const texture);
	Cube();
	~Cube();
	void afficher(glm::mat4 &projection, glm::mat4 &modelview);

protected:

	static Shader m_shader;
	static float m_vertices[108];
	static float m_coordTexture[72];

	Texture *m_texture;
};