#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

/*

SDL_Texture *texte_tex_tab[5];
SDL_Rect *txtDestRect_tab = malloc(sizeof(SDL_Rect));

SDL_Texture *texte_tex = initialiser_texte("Ici c est paris", "ChowFun.ttf", 48, 100, 200, pWindow, pRenderer, &txtDestRect, police, texte, texte_tex);
SDL_Texture *texte_tex2 = initialiser_texte("MenFout", "ChowFun.ttf", 48, 300, 400, pWindow, pRenderer, &txtDestRect2, police, texte, texte_tex2);

texte_tex_tab[0] = initialiser_texte("Ici c est paris", "ChowFun.ttf", 48, 100, 200, pWindow, pRenderer, &txtDestRect, texte_tex_tab[0]);
texte_tex_tab[1] = initialiser_texte("MenFout", "ChowFun.ttf", 48, 300, 400, pWindow, pRenderer, &txtDestRect2, texte_tex_tab[1]);

-------------------------------------------------------------------------------------------------------------------------------------------------------------

afficher_texte(pRenderer, texte_tex, txtDestRect);
afficher_texte(pRenderer, texte_tex2, txtDestRect2);

afficher_texte(pRenderer, texte_tex_tab[0], txtDestRect);
afficher_texte(pRenderer, texte_tex_tab[1], txtDestRect2);

*/

 /* Contenu Ajouté */
SDL_Texture *initialiser_texte(char * texte_a_afficher, char * nom_police,  int taille_texte, int position_x, int position_y, SDL_Window* pWindow, SDL_Renderer* pRenderer, SDL_Rect * txtDestRect, SDL_Texture *texte_tex){

	// texte_a_afficher de police nom_police de taile taille_texte en position_x et position_y sera inscrit dans le renvoie de texte_tex

	SDL_Color couleurNoire = {0, 0, 0};
	TTF_Font *police = NULL;
	SDL_Surface *texte=NULL;

	if( (police = TTF_OpenFont(nom_police, taille_texte)) == NULL){
		fprintf(stderr, "erreur chargement font\n");
		exit(EXIT_FAILURE);
	}
	texte = TTF_RenderUTF8_Blended(police, texte_a_afficher, couleurNoire);
	if(!texte){
		fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	texte_tex = SDL_CreateTextureFromSurface(pRenderer, texte);
	if(!texte_tex){
		fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(texte);
	txtDestRect->x = position_x;
	txtDestRect->y = position_y;
	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect->w), &(txtDestRect->h));
	return texte_tex;

}

 /* Contenu Ajouté */
void afficher_texte(SDL_Renderer *pRenderer, SDL_Texture *texte_tex, SDL_Rect txtDestRect){	// Affiche le contenu de texte_tex
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	SDL_RenderCopy(pRenderer, texte_tex, NULL, &txtDestRect);
}

 /* Contenu Ajouté */
SDL_Texture *ecrire_texte(SDL_Window* pWindow, SDL_Renderer* pRenderer, SDL_Rect * txtDestRect, SDL_Texture *texte_tex){ // Pour saisir du texte dans la console ainsi que des paramètres pour l'afficher dans la fenêtre

	char texte_w[30];
	int taille_texte, position_x, position_y;
	printf("Saisir le texte à écrire : ");
	scanf("%s", texte_w);
	printf("Saisir la taille : ");
	scanf("%d", &taille_texte);
	printf("Saisir la position en x : ");
	scanf("%d", &position_x);
	printf("Saisir la position en y : ");
	scanf("%d", &position_y);

	SDL_Color couleurNoire = {0, 0, 0};
	TTF_Font *police = NULL;
	SDL_Surface *texte=NULL;

	if( (police = TTF_OpenFont("Retro_Gaming.ttf", taille_texte)) == NULL){
		fprintf(stderr, "erreur chargement font\n");
		exit(EXIT_FAILURE);
	}
	texte = TTF_RenderUTF8_Blended(police, texte_w, couleurNoire);
	if(!texte){
		fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	texte_tex = SDL_CreateTextureFromSurface(pRenderer, texte);
	if(!texte_tex){
		fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(texte);
	txtDestRect->x = position_x;
	txtDestRect->y = position_y;
	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect->w), &(txtDestRect->h));
	return texte_tex;

}

int main(int argc, char *argv[])
{
		if (SDL_Init(SDL_INIT_VIDEO) < 0){	// Initialisation de la SDL
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
		if (SDL_Init(SDL_INIT_EVENTS) < 0){ // Initialisation des événements
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
		if (TTF_Init() < 0){ // Initialisation de SDL_ttf
    	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
    	return EXIT_FAILURE;
		}

		SDL_Window* pWindow;
		SDL_Renderer* pRenderer;
		SDL_Event events;

		/* Contenu Ajouté */
		SDL_Surface *texte=NULL;
		SDL_Texture *texte_tex_tab[5];
		SDL_Rect txtDestRect_tab[5];
		SDL_Rect txtDestRect;
		SDL_Rect txtDestRect2;
		TTF_Font *police = NULL;
		SDL_Color couleurNoire = {0, 0, 0};

		bool isOpen = true;
		const char* title;

		if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)	// SDL_CreateWindowAndRenderer(taille_x, taille_x, window_settings, ptr_SDL_Window, ptr_SDL_Renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

		SDL_SetWindowTitle(pWindow, "SDL_Program");	// Nom de la fenêtre
		SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);

		/* Contenu Ajouté */
		texte_tex_tab[0] = initialiser_texte("Ici c est paris", "ChowFun.ttf", 48, 100, 200, pWindow, pRenderer, &txtDestRect, texte_tex_tab[0]); // Ecrit "Ici c est paris" en police ChowFun taille 48 en 100,200
		texte_tex_tab[1] = ecrire_texte(pWindow, pRenderer, &txtDestRect, texte_tex_tab[1]);	// Appelle ecrire_texte

		while(isOpen){	// Tant que l'application est active

			while(SDL_PollEvent(&events)){	// Boucle de gestion des événements de la SDL

				switch(events.type){	// Détection des événements de la SDL

					case SDL_WINDOWEVENT: // Fermes l'application si clique de la souris sur la croix rouge de la fenêtre
						if (events.window.event == SDL_WINDOWEVENT_CLOSE){
							isOpen = SDL_FALSE;
							break;
						}

				}

			}

			SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
			SDL_RenderClear(pRenderer);

			 /* Contenu Ajouté */
			afficher_texte(pRenderer, texte_tex_tab[0], txtDestRect);	// Affiche "Ici cest Paris"
			afficher_texte(pRenderer, texte_tex_tab[1], txtDestRect2); // Affiche le résultat de la fonction ecrire_texte

			SDL_RenderPresent(pRenderer); // Met à jour la fenêtre

		}

		SDL_DestroyRenderer(pRenderer);
		SDL_DestroyWindow(pWindow);
		TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

    return 0;
}
