#pragma once
#include "appli.h"

class Texture
{
public:

	Texture();
	Texture(Texture const &textureACopier);
	Texture(std::string fichierImage);
	~Texture();

	Texture& operator=(Texture const &textureACopier);
	bool charger();
	SDL_Surface* inverserPixels(SDL_Surface *imageSource) const;

	GLuint getID() const;
	void setFichierImage(const std::string &fichierImage);
	

private:

	GLuint m_id;
	std::string m_fichierImage;
};