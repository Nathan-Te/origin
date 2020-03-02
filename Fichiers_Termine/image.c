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

		/* Contenu Ajouté */
		SDL_Texture* pTexture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 300, 300); // création d'un espace pour l'image de taille 300x300

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
		SDL_Surface* image = IMG_Load("mario.png"); // Pointeur sur une SDL_Surface qui contient l'image
		if(!image) {																// Gestion de l'erreur si l'image ne charge pas
    	printf("IMG_Load: %s\n", IMG_GetError());
		}
		SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(pRenderer, image);	// On crée une texture depuis l'image
		SDL_FreeSurface(image);	// On libère le SDL_Surface
		SDL_Rect src1 = {0,0,0,0}; // x,y,largeur,hauteur de l'image de base
		SDL_Rect dst1 = {0,0,150,200}; // x,y,largeur,hauteur où sera affichée l'image
		SDL_QueryTexture(pTextureImage, NULL, NULL, &src1.w, &src1.h);	// on prépare la texture

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

      SDL_RenderClear(pRenderer);	// Rempli la fenêtre

			/* Contenu Ajouté */
			SDL_RenderCopy(pRenderer, pTextureImage, &src1, &dst1); // On copie l'image de la texture au rendu de la fenêtre

			SDL_RenderPresent(pRenderer); // Met à jour la fenêtre

		}

		/* Contenu Ajouté */
		SDL_DestroyTexture(pTexture);

		SDL_DestroyRenderer(pRenderer);
		SDL_DestroyWindow(pWindow);
    TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

    return 0;
}
