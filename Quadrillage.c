#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct case_s{
  int numero;
  SDL_Rect rectangle;
  SDL_Texture* texture;
}case_t;

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
    //printf("est_dedans 0 \n");
    return 0;
  }

}

void remplir_ecran (SDL_Rect ecran_to_full[196]){
    int add_x = 0;
    int add_y = 0;
    for(int i=0;i<196;i++){
      ecran_to_full[i].x = add_x;
      ecran_to_full[i].y = add_y;
      ecran_to_full[i].w = 60;
      ecran_to_full[i].h = 60;
      add_x = add_x + 60;
      if(add_x == 840){
        add_x = 0;
        add_y = add_y + 60;
      }
  //  fprintf(stdout,"Case nb : %d de x : %d et y : %d \n", i, ecran_to_full[i].x, ecran_to_full[i].y);
    }
}

int find_case (SDL_Rect ecran_to_find[196], SDL_Event events){
  int i;
  for(i=0;i<196;i++){
    if(est_dedans(ecran_to_find[i],events)){
      fprintf(stdout,"Trouvé ! case nb : %d de x : %d et y : %d \n", i, ecran_to_find[i].x, ecran_to_find[i].y);
      return i;
    }
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
    int selection_tile = -1;
    int i = 0;
    int box = 0;
    SDL_Rect rect_NULL = {0,0,0,0};

    SDL_Rect ecran[196];
    remplir_ecran(ecran);

		if (SDL_CreateWindowAndRenderer(840, 840, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)	// SDL_CreateWindowAndRenderer(taille_x, taille_x, window_settings, ptr_SDL_Window, ptr_SDL_Renderer)
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
    SDL_Rect src_tile1,dst_tile11;
    SDL_Texture* pTextureImage_tile1 = initialiser_image("tile1.png",0,0,60,60,&src_tile1,&dst_tile11,pRenderer);
    SDL_Rect src_tile2,dst_tile22;
    SDL_Texture* pTextureImage_tile2 = initialiser_image("tile2.png",0,60,60,60,&src_tile2,&dst_tile22,pRenderer);

    SDL_Texture *pTexture_tile1[500];
    SDL_Rect dst_tile1[500];
    int nb_pTexture_tile1 = 0;

    SDL_Texture *pTexture_tile2[500];
    SDL_Rect dst_tile2[500];
    int nb_pTexture_tile2 = 0;

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

                if (est_dedans(dst_tile11,events)){
                  selection_tile = 0;
                }
                else if (est_dedans(dst_tile22,events)){
                  selection_tile = 1;
                }

                fprintf(stdout,"Selection tile = %d\n", selection_tile);

                break;
              }

              if (events.button.button == SDL_BUTTON_LEFT){

                if (selection_tile == 0){
                  box = find_case(ecran,events);
                  pTexture_tile1[nb_pTexture_tile1] = initialiser_image("tile1.png",ecran[box].x,ecran[box].y,60,60,&rect_NULL,&dst_tile1[nb_pTexture_tile1],pRenderer);
                  //pTexture_tile1[nb_pTexture_tile1] = initialiser_image("tile1.png",events.button.x,events.button.y,60,60,&rect_NULL,&dst_tile1[nb_pTexture_tile1],pRenderer);
                  nb_pTexture_tile1++;
                }
                else if (selection_tile == 1){
                  box = find_case(ecran,events);
                  pTexture_tile1[nb_pTexture_tile1] = initialiser_image("tile2.png",ecran[box].x,ecran[box].y,60,60,&rect_NULL,&dst_tile1[nb_pTexture_tile1],pRenderer);
                  //pTexture_tile2[nb_pTexture_tile2] = initialiser_image("tile2.png",events.button.x,events.button.y,60,60,&rect_NULL,&dst_tile2[nb_pTexture_tile2],pRenderer);
                  nb_pTexture_tile1++;
                }

                break;
              }


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
                fprintf(stdout,"VERIF EN COURS \n");
                for(i=0;i<196;i++){
               //   fprintf(stdout,"Etape : %d \n", i);
                  if(est_dedans(ecran[i],events)){
                    fprintf(stdout,"Case nb : %d de x : %d et y : %d \n", i, ecran[i].x, ecran[i].y);
                  }
                }
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

      afficher_image(pRenderer, pTextureImage_tile1, src_tile1, dst_tile11);
      afficher_image(pRenderer, pTextureImage_tile2, src_tile2, dst_tile22);

      if (nb_pTexture_tile1>0){
        for(i=0;i<nb_pTexture_tile1;i++){
          afficher_image(pRenderer, pTexture_tile1[i], rect_NULL, dst_tile1[i]);
        }
      }
      if (nb_pTexture_tile2>0){
        for(i=0;i<nb_pTexture_tile2;i++){
          afficher_image(pRenderer, pTexture_tile2[i], rect_NULL, dst_tile2[i]);
        }
      }

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
