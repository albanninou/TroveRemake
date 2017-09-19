#pragma once
#include "appli.h"

class Input
{
public:

	Input();
	~Input();

	void updateEvenements();
	bool terminer() const;
	void afficherPointeur(bool reponse) const;
	void capturerPointeur(bool reponse) const;

	bool getTouche(const SDL_Scancode touche) const;
	bool getBoutonSouris(const Uint8 bouton) const;
	bool getBoutonUpSouris(const Uint8 bouton) const;
	bool mouvementSouris() const;

	int getX() const;
	int getY() const;

	int getXRel() const;
	int getYRel() const;


private:

	SDL_Event m_evenements;
	bool m_touches[SDL_NUM_SCANCODES];
	bool m_boutonsSouris[8];
	bool m_boutonsUpSouris[8];

	int m_x;
	int m_y;
	int m_xRel;
	int m_yRel;

	bool m_terminer;
};