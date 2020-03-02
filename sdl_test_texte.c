#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

/*
void initialiser_texte(char * texte_a_afficher, SDL_Window* pWindow, SDL_Renderer* pRenderer, SDL_RecttxtDestRect, TTF_Font *police, SDL_Color couleurNoire){



}
*/

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
		SDL_Surface *texte=NULL;
		SDL_Event events;
		SDL_Rect txtDestRect;
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

		if( (police = TTF_OpenFont("ChowFun.ttf", 20)) == NULL){
			fprintf(stderr, "erreur chargement font\n");
			exit(EXIT_FAILURE);
		}
		texte = TTF_RenderUTF8_Blended(police, "Vive la programmation !", couleurNoire);
		if(!texte){
			fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
		SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(pRenderer, texte);
		if(!texte_tex){
			fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		SDL_FreeSurface(texte);
		txtDestRect.x = txtDestRect.y = 10;
		SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));

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

			SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
			SDL_RenderCopy(pRenderer, texte_tex, NULL, &txtDestRect);

			SDL_RenderPresent(pRenderer); // Met à jour la fenêtre

		}

		SDL_DestroyRenderer(pRenderer);
		SDL_DestroyWindow(pWindow);
		TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

    return 0;
}
