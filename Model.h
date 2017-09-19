#pragma once
#include "appli.h"

class Model
{
public:

	Model(float taille,vec3 coordonner);
	Model();
	~Model();

	void afficher(glm::mat4 &projection, glm::mat4 &modelview);
	void setCoordonner(glm::vec3 coordonner);
	glm::vec3 getCoordonner()const;
	float getTaille()const;

protected:
	float m_taille;
	glm::vec3 m_coordonner;
};