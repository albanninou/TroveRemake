#include "SceneOpenGL.h"


// Permet d'éviter la ré-écriture du namespace glm::

using namespace glm;

SDL_Window *fenetre;
// Constructeur de Destucteur

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0),
m_input()
{

}


SceneOpenGL::~SceneOpenGL()
{
	SDL_GL_DeleteContext(m_contexteOpenGL);
	SDL_DestroyWindow(m_fenetre);
	SDL_Quit();
}


// Méthodes

bool SceneOpenGL::initialiserFenetre()
{
	// Initialisation de la SDL

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}


	// Version d'OpenGL

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


	// Double Buffer

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);


	// Création de la fenêtre

	m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (m_fenetre == 0)
	{
		std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}


	// Création du contexte OpenGL

	m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

	if (m_contexteOpenGL == 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();

		return false;
	}
	fenetre = m_fenetre;
	return true;
}


bool SceneOpenGL::initGL()
{
#ifdef WIN32

	// On initialise GLEW

	GLenum initialisationGLEW(glewInit());


	// Si l'initialisation a échoué :

	if (initialisationGLEW != GLEW_OK)
	{
		// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

		std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;


		// On quitte la SDL

		SDL_GL_DeleteContext(m_contexteOpenGL);
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();

		return false;
	}

#endif


	// Activation du Depth Buffer
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_POLYGON_STIPPLE);

	// Tout s'est bien passé, on retourne true

	return true;
}


void SceneOpenGL::bouclePrincipale()
{
	// Variables

	Uint32 frameRate(1000 / 50);
	Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);


	// Matrice
	mat4 projection;
	mat4 modelview;

	projection = perspective(70.0, (double)m_largeurFenetre / m_hauteurFenetre, 0.01, 100.0);
	modelview = mat4(1.0);


	// Caméra mobile

	Camera camera = Camera(vec3(CHUNK_SIZE_BASE/2, 32, CHUNK_SIZE_BASE/2), vec3(1, 31, 1), vec3(0, 1, 0), 0.2f, 0.1f);
	m_input.afficherPointeur(false);
	m_input.capturerPointeur(true);

	for(int i =0;i < CHUNK_VIEW;i++){
		for (int j = 0; j < CHUNK_VIEW; j++) {
			m_chunk[i][j] = new Chunk(vec3(CHUNK_SIZE_BASE*(i-1), 0, CHUNK_SIZE_BASE*(j - 1)));
		}
	}

	
	//Cube cube =  Cube(vec3(1,0,0), "Textures/Herbe.jpg");
	Cube cube2 = Cube(vec3(0,0,0), "Textures/selected.png");
	cube2.setCoordonner(vec3(0, 0 ,- 1));
	// Boucle principale
	
	while (!m_input.terminer())
	{
		// On définit le temps de début de boucle

		debutBoucle = SDL_GetTicks();


		// Gestion des évènements

		m_input.updateEvenements();

		if (m_input.getTouche(SDL_SCANCODE_ESCAPE))
			break;


		camera.deplacer(m_input);
		camera.lookAt(modelview);
		/*if (chunk.getCubeAt(vec3(camera.getPosition().x, camera.getPosition().y-1, camera.getPosition().z))->getType() != TYPE_AIR) {
			camera.cancelMove();
		}*/
		
		// Nettoyage de l'écran

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vec3 vecteur = normalize(camera.getPointCible() - camera.getPosition());

		if (camera.getPosition().x > m_chunk[CHUNK_VIEW / 2 + 1][CHUNK_VIEW / 2 + 1]->getCoordonner().x + CHUNK_SIZE_BASE) {

		}

		//chunk.afficher(projection, modelview);
		for (int i = 0; i < CHUNK_VIEW; i++) {
			for (int j = 0; j < CHUNK_VIEW; j++) {
				m_chunk[i][j]->afficher(projection, modelview);
			}
		}
		
		vec3 tempo;
		vec3 distance;
		for (float i = 0; i < 5; i= i+0.01f) {
			distance = vec3(i, i, i);
			 tempo = camera.getPosition() + vecteur*distance;
			/*if ((chunk.getCubeAt(tempo)->getType()) != TYPE_AIR && (chunk.getCubeAt(camera.getPosition() + vecteur*vec3(i, i, i))->getType()) != -2) {
				cube2.setCoordonner(tempo);
				cube2.afficher(projection, modelview);
				break;
			}*/
		}

		if (m_input.getBoutonUpSouris(1))
		{
			//chunk.removeBlock(tempo);
		}
		if (m_input.getBoutonUpSouris(3))
		{
			for (float i = distance.x; i > 2; i = i - 0.01f) {
				tempo = camera.getPosition() + vecteur*vec3(i, i, i);
				/*if ((chunk.getCubeAt(tempo)->getType()) == TYPE_AIR) {
					chunk.addBlock(tempo, TYPE_GRASS);
					break;
				}*/
			}
		}



		
		// Désactivation du shader

		glUseProgram(0);


		// Actualisation de la fenêtre

		SDL_GL_SwapWindow(m_fenetre);


		// Calcul du temps écoulé

		finBoucle = SDL_GetTicks();
		tempsEcoule = finBoucle - debutBoucle;
		
		//SDL_SetWindowTitle(m_fenetre, tempsEcoule);

		// Si nécessaire, on met en pause le programme
		if (tempsEcoule < frameRate)
			SDL_Delay(frameRate - tempsEcoule);
	}
}

