#include "Texture.h"


// Constructeurs et Destructeur

Texture::Texture() : m_id(0), m_fichierImage("")
{

}


Texture::Texture(Texture const &textureACopier)
{
	// Copie de la texture

	m_fichierImage = textureACopier.m_fichierImage;
	charger();
}


Texture::Texture(std::string fichierImage) : m_id(0), m_fichierImage(fichierImage)
{

}


Texture::~Texture()
{
	// Destruction de la texture

	glDeleteTextures(1, &m_id);
}


// Méthodes

Texture& Texture::operator=(Texture const &textureACopier)
{
	// Copie de la texture

	m_fichierImage = textureACopier.m_fichierImage;
	charger();


	// Retour du pointeur *this

	return *this;
}

extern SDL_Window *fenetre;
bool Texture::charger()
{
	// Chargement de l'image dans une surface SDL
	//std::cout << "texture " << std::endl;
	std::cout << "Chargement texture : "<<m_fichierImage << std::endl;
	SDL_Surface *imageSDL = IMG_Load(m_fichierImage.c_str());
	


	if (imageSDL == 0)
	{
		std::cout << "Erreur : " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_Surface *opt = NULL;
	opt = SDL_ConvertSurfaceFormat(imageSDL, SDL_PIXELFORMAT_RGBA32, 0);
	SDL_FreeSurface(imageSDL);
	imageSDL = opt;
	// Inversion de l'image
	SDL_Surface *imageInversee = imageSDL;
	//SDL_FreeSurface(imageSDL);


	// Destruction d'une éventuelle ancienne texture

	if (glIsTexture(m_id) == GL_TRUE)
		glDeleteTextures(1, &m_id);


	// Génération de l'ID

	glGenTextures(1, &m_id);


	// Verrouillage

	glBindTexture(GL_TEXTURE_2D, m_id);


	// Format de l'image

	// Détermination du format et du format interne pour les images à 3 composantes

	

	// Copie des pixels

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageInversee->w, imageInversee->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageInversee->pixels);


	// Application des filtres

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	// Déverrouillage

	glBindTexture(GL_TEXTURE_2D, 0);


	// Fin de la méthode

	SDL_FreeSurface(imageInversee);
	return true;
}


SDL_Surface* Texture::inverserPixels(SDL_Surface *imageSource) const
{
	// Copie conforme de l'image source sans les pixels

	SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel, imageSource->format->Rmask,
		imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);


	// Tableau intermédiaires permettant de manipuler les pixels

	unsigned char* pixelsSources = (unsigned char*)imageSource->pixels;
	unsigned char* pixelsInverses = (unsigned char*)imageInversee->pixels;


	// Inversion des pixels

	for (int i = 0; i < imageSource->h; i++)
	{
		for (int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
			pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] = pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
	}


	// Retour de l'image inversée

	return imageInversee;
}




GLuint Texture::getID() const
{
	return m_id;
}


void Texture::setFichierImage(const std::string &fichierImage)
{
	m_fichierImage = fichierImage;
}


