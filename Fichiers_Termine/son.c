#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

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
		/* Contenu Ajouté */
		if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) { //Initialisation de l'API Mixer
      	printf("%s", Mix_GetError());
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

	/* Contenu Ajouté */
	/*
	La musique se lance via un pointeur sur Mix_Music
	En revanche, les sons se lancent via pointeur sur Mix_Chunk, pour jouer un son il faut le jouer sur un canal,
	on alloue des canaux avec "Mix_AllocateChannels(nb_canaux);" , on peut jouer un son par canaux en même temps
	On a deux fonctions pour régler le volumes de la musique

	Pour jouer la musique : Mix_PlayMusic(ptr_musique, nb_loop); où nb_loop correspond au nombre de fois que le jeu doit être lancé :
	-1 = boucle infini, 0 = une fois, 1 = 2 fois  etc....

	Pour jouer un son même chose mais avec "Mix_PlayChannel(1, sound_bullet, 0);" , premier paramètre le canal, deuxième un pointeur sur Mix_Chunk,
	troisième sur nb_loop comme pour la fonction de musique

	MIX_MAX_VOLUME = constante du volume maximum
	*/
    Mix_AllocateChannels(10);
    Mix_Volume(1,MIX_MAX_VOLUME/2);
    Mix_Chunk *sound_bullet;
    Mix_Music *musique;
    musique = Mix_LoadMUS("DOOM_music.wav");
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    sound_bullet = Mix_LoadWAV("dspistol.wav");
    Mix_PlayChannel(1, sound_bullet, 0);
    Mix_PlayMusic(musique, -1);



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

			SDL_RenderClear(pRenderer); // Efface l'ecran
			SDL_RenderPresent(pRenderer); // Met à jour la fenêtre

		}

	/* Contenu Ajouté */
	// On libère les sons et musiques
    Mix_FreeChunk(sound_bullet);
    Mix_FreeMusic(musique);
	Mix_CloseAudio(); //Fermeture de l'API
    
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
    TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

    return 0;
}
