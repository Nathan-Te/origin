#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

SDL_Texture* initialiser_image(char * nom_image, int position_x, int position_y, int largeur, int hauteur, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer* pRenderer){

/*
initialiser_image("mario.png",200,200,150,200,&src1,&dst1,pRenderer);
*/


  /* Contenu Ajouté */
		SDL_Surface* image = IMG_Load(nom_image); // Pointeur sur une SDL_Surface qui contient l'image
		if(!image) {																// Gestion de l'erreur si l'image ne charge pas
    	printf("IMG_Load: %s\n", IMG_GetError());
		}
		SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(pRenderer, image);	// On crée une texture depuis l'image
		SDL_FreeSurface(image);	// On libère le SDL_Surface
		src->x = 0; // x,y,largeur,hauteur de l'image de base
    src->y = 0;
    src->w = 0;
    src->h = 0;
    dst->x = position_x;
    dst->y = position_y;
    dst->w = largeur;
    dst->h = hauteur;
		SDL_QueryTexture(pTextureImage, NULL, NULL, &src->w, &src->h);	// on prépare la texture
    return pTextureImage;
}

void afficher_image(SDL_Renderer* pRenderer, SDL_Texture* pTextureImage, SDL_Rect src, SDL_Rect dst){
  SDL_RenderCopy(pRenderer, pTextureImage, &src, &dst);
}


int est_dedans(SDL_Rect objet, SDL_Event events){

  if (events.button.x >= objet.x && events.button.x <= objet.x+objet.w && events.button.y >= objet.y && events.button.y <= objet.y+objet.h){
    printf("est_dedans 1 \n");
    return 1;
  }
  else {
    printf("est_dedans 0 \n");
    return 0;
  }

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
    SDL_Rect positionZozor; // Position de la souris

		bool isOpen = true;
		const char* title;

    int bonjour_mario = 1;

		if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)	// SDL_CreateWindowAndRenderer(taille_x, taille_x, window_settings, ptr_SDL_Window, ptr_SDL_Renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

		SDL_SetWindowTitle(pWindow, "SDL_Program");	// Nom de la fenêtre
		SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);

/*

		SDL_Surface* image = IMG_Load("mario.png");
		if(!image) {																
    	printf("IMG_Load: %s\n", IMG_GetError());
		}
		SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(pRenderer, image);	
		SDL_FreeSurface(image);	
		SDL_Rect src1 = {0,0,0,0}; 
    int x_mario = 200;
    int y_mario = 200;
    int largeur_mario = 150;
    int hauteur_mario = 200;
		SDL_Rect dst1 = {x_mario,y_mario,largeur_mario,hauteur_mario}; 
		SDL_QueryTexture(pTextureImage, NULL, NULL, &src1.w, &src1.h);	

*/
    SDL_Rect src1,dst1;
    SDL_Texture* pTextureImage = initialiser_image("mario.png",200,200,150,200,&src1,&dst1,pRenderer);

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
              if (events.button.button == SDL_BUTTON_RIGHT){
                fprintf(stdout,"Tout de suite le clic droit du joueur Français\n");
                positionZozor.x = events.button.x;    /*RÉCUPÉRATION DES COORDONNÉES DU CLIC*/
                positionZozor.y = events.button.y;    /*RÉCUPÉRATION DES COORDONNÉES DU CLIC*/
                fprintf(stdout,"x = %d y= %d\n",positionZozor.x, positionZozor.y);
                break;
              }
              if (events.button.button == SDL_BUTTON_LEFT && est_dedans(dst1,events)==1 && bonjour_mario == 1){ /* On arrête le programme si on a fait un clic gauche */
                fprintf(stdout,"Mais où est Mario !\n");
                bonjour_mario = 0;
                fprintf(stdout,"Appuie avec le clic gauche\n");
                positionZozor.x = events.button.x;    /*RÉCUPÉRATION DES COORDONNÉES DU CLIC*/
                positionZozor.y = events.button.y;    /*RÉCUPÉRATION DES COORDONNÉES DU CLIC*/
                fprintf(stdout,"x = %d y= %d\n",positionZozor.x, positionZozor.y);
                break;
              }
              if (events.button.button == SDL_BUTTON_LEFT && bonjour_mario == 0){ /* On arrête le programme si on a fait un clic gauche */
                dst1.x = events.button.x - 75;
                dst1.y = events.button.y - 100;
                bonjour_mario = 1;
                fprintf(stdout,"Mais C'est comme Mario !\n");
                fprintf(stdout,"Appuie avec le clic gauche\n");
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

      SDL_RenderClear(pRenderer);	// Rempli la fenêtre

			/* Contenu Ajouté */
      if (bonjour_mario == 1){
        afficher_image(pRenderer, pTextureImage, src1, dst1); // On copie l'image de la texture au rendu de la fenêtre
      }
    
			SDL_RenderPresent(pRenderer); // Met à jour la fenêtre

		}

		SDL_DestroyRenderer(pRenderer);
		SDL_DestroyWindow(pWindow);
    TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

    return 0;
}
