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
		
		 /* Contenu Ajouté */
    SDL_Rect positionZozor; // Position de la souris

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


               /*Contenu Ajouté*/
          case SDL_MOUSEBUTTONUP: /* Clic de la souris */
              if (events.button.button == SDL_BUTTON_RIGHT){ /* On arrête le programme si on a fait un clic droit */
                fprintf(stdout,"Appui avec le clic droit\n");
                positionZozor.x = events.button.x;    /*RÉCUPÉRATION DES COORDONNÉES DU CLIC*/
                positionZozor.y = events.button.y;    /*RÉCUPÉRATION DES COORDONNÉES DU CLIC*/
                fprintf(stdout,"x = %d y= %d\n",positionZozor.x, positionZozor.y);
                break;
              }
              if (events.button.button == SDL_BUTTON_LEFT){ /* On arrête le programme si on a fait un clic gauche */
                fprintf(stdout,"Apui avec le clic gauche\n");
                positionZozor.x = events.button.x;    /*RÉCUPÉRATION DES COORDONNÉES DU CLIC*/
                positionZozor.y = events.button.y;    /*RÉCUPÉRATION DES COORDONNÉES DU CLIC*/
                fprintf(stdout,"x = %d y= %d\n",positionZozor.x, positionZozor.y);
                break;
              }

              if (events.button.button == SDL_BUTTON_MIDDLE){ /* On arrête le programme si on a fait un clic molette */
                fprintf(stdout,"Appui avec le clic molette\n");
                positionZozor.x = events.button.x;    /*RÉCUPÉRATION DES COORDONNÉES DU CLIC*/
                positionZozor.y = events.button.y;    /*RÉCUPÉRATION DES COORDONNÉES DU CLIC*/
                fprintf(stdout,"x = %d y= %d\n",positionZozor.x, positionZozor.y);
                break;
              }
          case SDL_MOUSEMOTION:
            positionZozor.x = events.motion.x;    /*RÉCUPÉRATION  DES COORDONNÉES DE CHAQUE ÉVÈNEMENT GÉNÉRÉ*/
            positionZozor.y = events.motion.y;    /*RÉCUPÉRATION  DES COORDONNÉES DE CHAQUE ÉVÈNEMENT GÉNÉRÉ*/
            //fprintf(stdout,"x = %d y= %d\n",positionZozor.x, positionZozor.y);
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
