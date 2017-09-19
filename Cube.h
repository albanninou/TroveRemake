#pragma once
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "CubeType.h"

class Cube: public Model
{
public:

	Cube(vec3 coordonner, std::string const texture);
	Cube(vec3 coordonner, int const type);
	Cube();
	~Cube();
	void afficher(glm::mat4 &projection, glm::mat4 &modelview);
	int getType();
	void setType(int type);
	void setCoordonner(glm::vec3 coordonner);
protected:

	static Shader m_shader;
	static float m_vertices[108];
	static float m_coordTexture[72];
	int m_type;
	Texture *m_texture;
};