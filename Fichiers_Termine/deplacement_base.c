#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

 /* Contenu Ajouté */

void deplacement(SDL_Event events, SDL_Rect * rectangle){

	SDL_Log("+key");  // Affiche un message +key (pour dire qu'on appuie sur une touche du clavier)
	if (events.key.keysym.sym == SDLK_s){ // detecte si la touche s est enfoncée
		 SDL_Log("Keycode s"); // Affiche s si la touche est pressée
		 rectangle->y=rectangle->y+10; // fait augmenter les coordonnée x du rectangle passe en parametre
	 }
 if (events.key.keysym.sym == SDLK_z){ //detecte si la touche z est enfoncée
		 SDL_Log("Keycode z"); // Affiche s si la touche est pressée
		 rectangle->y=rectangle->y-10;//fait diminuer les coordonnée y du rectangle passe en parametre
	 }

	if (events.key.keysym.sym == SDLK_q){ //detecte si la touche q est enfoncée
			SDL_Log("Keycode q"); // Affiche q si la touche est pressée
		rectangle->x=rectangle->x-10;//fait diminuer les coordonnée y du rectangle passe en parametre
	}
		}
	if (events.key.keysym.sym == SDLK_d){ // Regarde si on appuyer sur la touche Z (la touche Z sous un azerty)
			SDL_Log("Keycode d"); // Affiche d si la touche est pressée
		rectangle->x=rectangle->x+10; //fait augmanter les coordonnée x du rectangle passe en parametre
	}
		}

}

int main(int argc, char *argv[]){
int xa=20;
int test=0;
 /* Contenu Ajouté */
	SDL_Rect * rectangle = malloc(sizeof(SDL_Rect)); // crée un pointeur sur rectangle
	rectangle->x=100;
	rectangle->y=200;
	rectangle->w=400;
	rectangle->h=75;

	SDL_Rect rectangle2;
	rectangle2.x=200;
	rectangle2.y=100;
	rectangle2.w=75;
	rectangle2.h=400;

	SDL_Rect rectanglec;

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
		SDL_Init(SDL_INIT_EVENTS);
		TTF_Init();

		SDL_Window* pWindow;
		SDL_Renderer* pRenderer;
		SDL_Event events;
		bool isOpen = true;
		const char* title;

		if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }



		while(isOpen){
			SDL_SetWindowTitle(pWindow, "Hello");
			title = SDL_GetWindowTitle(pWindow);
			SDL_Delay(200);
			//SDL_Log("Le titre de la fenêtre est %s\n", title);

			while(SDL_PollEvent(&events)){
				switch(events.type){
					case SDL_QUIT:
						isOpen = false;
						break;

						case SDL_WINDOWEVENT:
				 			 if (events.window.event == SDL_WINDOWEVENT_CLOSE)
				 					 isOpen = SDL_FALSE;
				 					 break;
				 	 case SDL_KEYDOWN: // Un événement de type touche enfoncée est effectué
					 /*partie ajouter*/
					 deplacement(events, rectangle); // appel de la fonction pour deplacer le rectangle avec les touches du clavier
					 /*fin partie ajouter*/
							 break;
				 	 case SDL_KEYUP:// Un événement de type touche relâchée
				 			 SDL_Log("-key");
				 			 break;
				}
			}






							SDL_SetRenderDrawColor(pRenderer, 54, 45, 0, 25); // choisir une couleur
							SDL_RenderClear(pRenderer);
							SDL_RenderPresent(pRenderer); // appliquer la couleur


   						SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
							SDL_RenderDrawPoint(pRenderer, 10, 10);

							/*debut de partie ajouter*/
							SDL_SetRenderDrawColor(pRenderer, 255, 192, 203, 0); // choisir une couleur
							SDL_RenderFillRect(pRenderer,rectangle);//afficher un rectangle rose
							/*fin de partie ajouter */
							//SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
							//SDL_RenderDrawLine(pRenderer, 10, 10, 100, 10);//ecrit une ligne

							SDL_SetRenderDrawColor(pRenderer, 14, 87, 58, 25); // choisir une couleur
							SDL_RenderFillRect(pRenderer,&rectangle2); // afficher le deuxieme ecran


							SDL_IntersectRect(rectangle,&rectangle2,&rectanglec); //faire afficher la hitbox

							SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255); // couleur rouge
							SDL_RenderDrawRect(pRenderer, &rectanglec); // Je dessine le rectangle sans le remplir


						//	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
						//	SDL_RenderClear(pRenderer);
						//	SDL_RenderCopy(pRenderer, pTextureImage, NULL, NULL); // Affiche ma texture sur touts l'écran

						//////////////////////////////////////////////////////////











						///////////////////////////////////////////////////







							SDL_RenderPresent(pRenderer);// fait tout afficher sur l'ecran
		}

		SDL_DestroyRenderer(pRenderer);
		SDL_DestroyWindow(pWindow);

    TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

    return 0;
}
