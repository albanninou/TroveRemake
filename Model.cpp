#include "Model.h"

Model::Model(float taille, vec3 coordonner)
{
	m_taille = taille;
	m_coordonner = coordonner;
}

Model::Model()
{
	m_taille = 1;
	m_coordonner = vec3(0,0,0);
	//std::cout << "Construct Model basic" << std::endl;
}

Model::~Model()
{
}

void Model::afficher(glm::mat4 & projection, glm::mat4 & modelview)
{
}

void Model::setCoordonner(glm::vec3 coordonner)
{
	m_coordonner = coordonner;
}

glm::vec3 Model::getCoordonner() const
{
	return m_coordonner;
}

float Model::getTaille() const
{
	return m_taille;
}
