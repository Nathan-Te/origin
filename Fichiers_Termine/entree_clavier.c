#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

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

		while(isOpen){	// Tant que l'application est active

			while(SDL_PollEvent(&events)){	// Boucle de gestion des événements de la SDL

				switch(events.type){	// Détection des événements de la SDL

					case SDL_WINDOWEVENT: // Fermes l'application si clique de la souris sur la croix rouge de la fenêtre
						if (events.window.event == SDL_WINDOWEVENT_CLOSE){
							isOpen = SDL_FALSE;
							break;
						}

					/* Contenu Ajouté */
					case SDL_KEYDOWN:	// Touche enfoncee
						SDL_Log("Touche enfoncee : ");
						if (events.key.keysym.sym == SDLK_s){
							 SDL_Log("Touche S");
					 	}
			 			if (events.key.keysym.sym == SDLK_z){
							 SDL_Log("Touche Z");
					 	}
						if (events.key.keysym.sym == SDLK_q){
								SDL_Log("Touche Q");
						}
						if (events.key.keysym.sym == SDLK_d){
									SDL_Log("Touche D");
						}
						break;
					case SDL_KEYUP:	// Touche relachee
						if (events.key.keysym.sym == SDLK_s){
						 	SDL_Log("Touche S");
						}
						if (events.key.keysym.sym == SDLK_z){
						 	SDL_Log("Touche Z");
						}
						if (events.key.keysym.sym == SDLK_q){
							SDL_Log("Touche Q");
						}
						if (events.key.keysym.sym == SDLK_d){
							SDL_Log("Touche D");
						}
						SDL_Log("Touche relachee : ");
						break;

				}

			}

			SDL_RenderClear(pRenderer); // Efface l'ecran
			SDL_RenderPresent(pRenderer); // Met à jour la fenêtre

		}

		SDL_DestroyRenderer(pRenderer);
		SDL_DestroyWindow(pWindow);
    TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

    return 0;
}
