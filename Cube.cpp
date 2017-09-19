#include "Cube.h"
float Cube::m_vertices[] = { 0, 0, 0,   1, 0, 0,   1, 1, 0,     // Face 1
0, 0, 0,   0, 1, 0,   1, 1, 0,     // Face 1

1, 0, 1,   1, 0, 0,   1, 1, 0,       // Face 2
1, 0, 1,   1, 1, 1,   1, 1, 0,         // Face 2

0, 0, 1,   1, 0, 1,   1, 0, 0,      // Face 3
0, 0, 1,   0, 0, 0,   1, 0, 0,    // Face 3

0, 0, 1,   1, 0, 1,   1, 1, 1,        // Face 4
0, 0, 1,   0, 1, 1,   1, 1, 1,        // Face 4

0, 0, 0,   0, 0, 1,   0, 1, 1,     // Face 5
0, 0, 0,   0, 1, 0,   0, 1, 1,     // Face 5

0, 1, 1,   1, 1, 1,   1, 1, 0,         // Face 6
0, 1, 1,   0, 1, 0,   1, 1, 0 };      // Face 6

float Cube::m_coordTexture[] = { 0, 0,   1, 0,   1, 1,     // Face 1
0, 0,   0, 1,   1, 1,     // Face 1

0, 0,   1, 0,   1, 1,     // Face 2
0, 0,   0, 1,   1, 1,     // Face 2

0, 0,   1, 0,   1, 1,     // Face 3
0, 0,   0, 1,   1, 1,     // Face 3

0, 0,   1, 0,   1, 1,     // Face 4
0, 0,   0, 1,   1, 1,     // Face 4

0, 0,   1, 0,   1, 1,     // Face 5
0, 0,   0, 1,   1, 1,     // Face 5

0, 0,   1, 0,   1, 1,     // Face 6
0, 0,   0, 1,   1, 1 };    // Face 6


Shader Cube::m_shader = Shader("Shaders/texture.vert", "Shaders/texture.frag");

Cube::Cube(vec3 coordonner, std::string const texture) :Model(1,coordonner)
{
	if (m_shader.getProgramID() == 0) {
		m_shader.charger();
	}
	m_texture = new Texture(texture);
	m_texture->charger();
	
	
}

Cube::Cube(vec3 coordonner, int const type) :Model(1, coordonner)
{
	m_type = type;
	if (m_shader.getProgramID() == 0) {
		m_shader.charger();
	}
	if (type != TYPE_AIR) {
		m_texture = getTexture(type);
	}
	m_coordonner = vec3(round(coordonner.x), round(coordonner.y), round(coordonner.z));
}

Cube::Cube():Model()
{
	if (m_shader.getProgramID() == 0) {
		m_shader.charger();
	}
	m_texture = new Texture("Textures/error.jpg");
	m_texture->charger();
	m_type = -2;
}


Cube::~Cube()
{
}

// Méthodes

void Cube::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
	// Activation du shader
	if (m_type == TYPE_AIR) return;
	glUseProgram(m_shader.getProgramID());


	// Envoi des vertices

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
	glEnableVertexAttribArray(0);


	// Envoi de la couleur

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_coordTexture);
	glEnableVertexAttribArray(2);


	// Envoi des matrices

	mat4 tempo = translate(modelview, m_coordonner);

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(tempo));

	// Verrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, m_texture->getID());
	
	// Rendu

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// Déverrouillage de la texture

	glBindTexture(GL_TEXTURE_2D, 0);
	// Désactivation des tableaux

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(0);


	// Désactivation du shader

	glUseProgram(0);
}

int Cube::getType()
{
	return m_type;
}

void Cube::setType(int type)
{
	m_type = type;
}

void Cube::setCoordonner(glm::vec3 coordonner)
{
	m_coordonner = vec3(round(coordonner.x), round(coordonner.y), round(coordonner.z));
}

