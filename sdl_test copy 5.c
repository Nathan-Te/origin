#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct case_s{
  int numero;
  SDL_Rect rectangle;
  SDL_Rect dst;
  SDL_Texture* texture;
}case_t;

typedef struct projectile_s{
  int direction;
  SDL_Rect rectangle;
  SDL_Rect dst;
  SDL_Texture* texture;
}projectile_t;

SDL_Texture* initialiser_image(char * nom_image, int position_x, int position_y, int largeur, int hauteur, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer* pRenderer){

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

void remplir_screen (case_t screen_to_full[196]){
    int add_x = 0;
    int add_y = 0;
    for(int i=0;i<196;i++){
      screen_to_full[i].rectangle.x = add_x;
      screen_to_full[i].rectangle.y = add_y;
      screen_to_full[i].rectangle.w = 60;
      screen_to_full[i].rectangle.h = 60;
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

int find_screen (case_t screen_to_find[196], SDL_Event events){
  int i;
  for(i=0;i<196;i++){
    if(est_dedans(screen_to_find[i].rectangle,events)){
      fprintf(stdout,"Trouvé ! case nb : %d de x : %d et y : %d \n", i, screen_to_find[i].rectangle.x, screen_to_find[i].rectangle.y);
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
    bool key_up_pressed = false;
    bool key_down_pressed = false;
    bool key_left_pressed = false;
    bool key_right_pressed = false;
    bool shooting = false;
    bool bullet_shot = false;
    bool idle = true;
		const char* title;

    int bonjour_mario = 1;
    int selection_tile = -1;
    int i = 0;
    int box = 0;
    int look_down = 1;
    int look_up = 0;
    int look_left = 0;
    int look_right = 0;
    int changement_frame = 0;
    SDL_Rect rect_NULL = {0,0,0,0};

    int speed = 0.6;
    int look = 1; // up = 0 , down = 1 , left = 2 , right = 3
    int animation = 0;
    int animation_shoot = 0;
    int old_animation = 0;
    int compteur_animation = 0;
    int compteur_animation_shoot = 0;
    const int limite_compteur_animation = 25;


    SDL_Rect ecran[196];
    case_t screen[196];
    remplir_ecran(ecran);
    remplir_screen(screen);

    for(i=0;i<196;i++){
      screen[i].texture = initialiser_image("white.png",screen[i].rectangle.x,screen[i].rectangle.y,60,60,&rect_NULL,&(screen[i].dst),pRenderer);
    }

		if (SDL_CreateWindowAndRenderer(840, 840, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)	// SDL_CreateWindowAndRenderer(taille_x, taille_x, window_settings, ptr_SDL_Window, ptr_SDL_Renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

		SDL_SetWindowTitle(pWindow, "SDL_Program");	// Nom de la fenêtre
		SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);

    SDL_Rect src1,dst1;
    SDL_Texture* pTextureImage = initialiser_image("doom_down.png",480,480,45,56,&src1,&dst1,pRenderer);
    SDL_Rect src_tile1,dst_tile11;
    SDL_Texture* pTextureImage_tile1 = initialiser_image("tile1.png",0,0,60,60,&src_tile1,&dst_tile11,pRenderer);
    SDL_Rect src_tile2,dst_tile22;
    SDL_Texture* pTextureImage_tile2 = initialiser_image("tile2.png",0,60,60,60,&src_tile2,&dst_tile22,pRenderer);

    SDL_Rect src_bullet1,dst_bullet1;
    SDL_Texture* pTextureImage_bullet;

    SDL_Texture *pTexture_bullet[20];
    SDL_Rect dst_bullet[20];
    int nb_bullet = 0;
    //= initialiser_image("bullet_left.png",dst1.x-15,dst1.y+21,8,5,&src_bullet1,&dst_bullet1,pRenderer);

    SDL_Texture *pTexture_tile1[500];
    SDL_Rect dst_tile1[500];
    int nb_pTexture_tile1 = 0;

    SDL_Texture *pTexture_tile2[500];
    SDL_Rect dst_tile2[500];
    int nb_pTexture_tile2 = 0;

    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);

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
                  //box = find_case(ecran,events);
                  box = find_screen(screen,events);
                  screen[box].texture = initialiser_image("tile1.png",screen[box].rectangle.x,screen[box].rectangle.y,60,60,&rect_NULL,&(screen[box].dst),pRenderer);
                  //pTexture_tile1[nb_pTexture_tile1] = initialiser_image("tile1.png",ecran[box].x,ecran[box].y,60,60,&rect_NULL,&dst_tile1[nb_pTexture_tile1],pRenderer);
                  //pTexture_tile1[nb_pTexture_tile1] = initialiser_image("tile1.png",events.button.x,events.button.y,60,60,&rect_NULL,&dst_tile1[nb_pTexture_tile1],pRenderer);
                  //nb_pTexture_tile1++;
                }
                else if (selection_tile == 1){
                  //box = find_case(ecran,events);
                  box = find_screen(screen,events);
                  screen[box].texture = initialiser_image("tile2.png",screen[box].rectangle.x,screen[box].rectangle.y,60,60,&rect_NULL,&(screen[box].dst),pRenderer);
                  //pTexture_tile1[nb_pTexture_tile1] = initialiser_image("tile2.png",ecran[box].x,ecran[box].y,60,60,&rect_NULL,&dst_tile1[nb_pTexture_tile1],pRenderer);
                  //pTexture_tile2[nb_pTexture_tile2] = initialiser_image("tile2.png",events.button.x,events.button.y,60,60,&rect_NULL,&dst_tile2[nb_pTexture_tile2],pRenderer);
                  //nb_pTexture_tile1++;
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

          case SDL_KEYDOWN:
            if (events.key.keysym.sym == SDLK_z){
              key_up_pressed = true;
            }
            if (events.key.keysym.sym == SDLK_s){
              key_down_pressed = true;
            }
            if (events.key.keysym.sym == SDLK_q){
              key_left_pressed = true;
            }
            if (events.key.keysym.sym == SDLK_d){
              key_right_pressed = true;
            }
            if (events.key.keysym.sym == SDLK_SPACE){
              shooting = true;
              SDL_Log("HELLO SPACE");
            }
            break;

          case SDL_KEYUP:
            if (events.key.keysym.sym == SDLK_z){
              key_up_pressed = false;
              look = 0;
              look_up = 1;
              animation = 0;
            }
            if (events.key.keysym.sym == SDLK_s){
              key_down_pressed = false;
              look = 1;
              look_up = 0;
              animation = 0;
            }
            if (events.key.keysym.sym == SDLK_q){
              key_left_pressed = false;
              look = 2;
              look_left = 1;
              animation = 0;
            }
            if (events.key.keysym.sym == SDLK_d){
              key_right_pressed = false;
              look = 3;
              look_left = 0;
              animation = 0;
            }
            if (events.key.keysym.sym == SDLK_SPACE){
              shooting = false;
              SDL_Log("BUY SPACE");
              //animation = 0;
            }
            break;

				  }

			}

      SDL_RenderClear(pRenderer);	// Rempli la fenêtre

      afficher_image(pRenderer, pTextureImage_tile1, src_tile1, dst_tile11);
      afficher_image(pRenderer, pTextureImage_tile2, src_tile2, dst_tile22);

      
      for(i=0;i<196;i++){
        afficher_image(pRenderer, screen[i].texture, rect_NULL, screen[i].dst);
      }
        
        //SDL_Texture* pTextureImage_bullet = initialiser_image("bullet_left.png",dst1.x-15,dst1.y+21,8,5,&src_bullet1,&dst_bullet1,pRenderer);
        if (bullet_shot == true){
          for (int i = 0; i < nb_bullet ; i++){
            if (dst_bullet[i].x >= -10){
              dst_bullet[i].x -= 1;
            }
          }
          //dst_bullet1.x -= 1;
          /*
          if (dst_bullet1.x == 0){
            bullet_shot == false;
          }
          */
          if (nb_bullet == 19){
            nb_bullet = 0;
          }
        }
        if (shooting == true && look == 2){
          key_down_pressed = key_left_pressed = key_right_pressed = key_up_pressed = false;
          SDL_Log("if shooting");
          SDL_Log("Animation = %d", animation_shoot);
          if (animation_shoot == 0){
            SDL_Log("animation 0");
            if (compteur_animation == 0){
              bullet_shot = true;
              pTexture_bullet[nb_bullet] = initialiser_image("bullet_left.png",dst1.x-10,dst1.y+21,8,5,&rect_NULL,&dst_bullet[nb_bullet],pRenderer);
              //pTextureImage_bullet = initialiser_image("bullet_left.png",dst1.x-15,dst1.y+21,8,5,&src_bullet1,&dst_bullet1,pRenderer);
              nb_bullet++;
            }
            pTextureImage = initialiser_image("doom_left_shooting.png",dst1.x,dst1.y,51,56,&src1,&dst1,pRenderer);
            compteur_animation++;
            if (compteur_animation == 25){
              animation_shoot++;
              compteur_animation = 0;
            }
          }
          else if (animation_shoot == 1){
            SDL_Log("animation 1");
            pTextureImage = initialiser_image("doom_left_idle.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
            compteur_animation++;
            if (compteur_animation == 25){
              animation_shoot--;
              compteur_animation = 0;
            }
          }
        }
        else if(shooting == true && look == 3){
          key_down_pressed = key_left_pressed = key_right_pressed = key_up_pressed = false;
          SDL_Log("if shooting");
          SDL_Log("Animation = %d", animation_shoot);
          if (animation_shoot == 0){
            if (compteur_animation == 0){
              bullet_shot = true;
              pTexture_bullet[nb_bullet] = initialiser_image("bullet_right.png",dst1.x+10,dst1.y+21,8,5,&rect_NULL,&dst_bullet[nb_bullet],pRenderer);
              //pTextureImage_bullet = initialiser_image("bullet_left.png",dst1.x-15,dst1.y+21,8,5,&src_bullet1,&dst_bullet1,pRenderer);
              nb_bullet++;
            }
            SDL_Log("animation 0");
            pTextureImage = initialiser_image("doom_right_shooting.png",dst1.x,dst1.y,51,56,&src1,&dst1,pRenderer);
            compteur_animation++;
            if (compteur_animation == 25){
              animation_shoot++;
              compteur_animation = 0;
            }
          }
          else if (animation_shoot == 1){
            SDL_Log("animation 1");
            pTextureImage = initialiser_image("doom_right_idle.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
            compteur_animation++;
            if (compteur_animation == 25){
              animation_shoot--;
              compteur_animation = 0;
            }
          }
        }
        else {
        if (key_up_pressed == true){
          if (dst1.y >= 0 ){
            dst1.y -= 1;
          }
         if (animation == 0){
              SDL_Log("0");
              pTextureImage = initialiser_image("doom_top_1.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation++;
                compteur_animation = 0;
              }
         }
            else if (animation == 1){
              SDL_Log("1");
              pTextureImage = initialiser_image("doom_top_2.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 2){
              SDL_Log("2");
              pTextureImage = initialiser_image("doom_top_3.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 3){
              SDL_Log("3");
              pTextureImage = initialiser_image("doom_top_4.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation = 0;
                compteur_animation = 0;
              }
            }
         //pTextureImage = initialiser_image("doom_top.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
      }

        if (key_down_pressed == true){
          if (dst1.y <= 840 - 56){
            dst1.y += 1;
          }
          if (animation == 0){
              SDL_Log("0");
              pTextureImage = initialiser_image("doom_down_1.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 1){
              SDL_Log("1");
              pTextureImage = initialiser_image("doom_down_2.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 2){
              SDL_Log("2");
              pTextureImage = initialiser_image("doom_down_3.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 3){
              SDL_Log("3");
              pTextureImage = initialiser_image("doom_down_4.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation = 0;
                compteur_animation = 0;
              }
            }
          //pTextureImage = initialiser_image("doom_down.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
        }

        if (key_left_pressed == true){
          if (dst1.x >= 0 ){
            dst1.x -= 1;
          }
          if (key_up_pressed == true && key_left_pressed == true){
            if (animation == 0){
              SDL_Log("0");
              pTextureImage = initialiser_image("doom_top_left_1.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 1){
              SDL_Log("1");
              pTextureImage = initialiser_image("doom_top_left_2.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 2){
              SDL_Log("2");
              pTextureImage = initialiser_image("doom_top_left_3.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 3){
              SDL_Log("3");
              pTextureImage = initialiser_image("doom_top_left_4.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation = 0;
                compteur_animation = 0;
              }
            }
            //pTextureImage = initialiser_image("doom_top_left.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
          }
          else if (key_down_pressed == true && key_left_pressed == true){
            if (animation == 0){
              SDL_Log("0");
              pTextureImage = initialiser_image("doom_down_left_1.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 1){
              SDL_Log("1");
              pTextureImage = initialiser_image("doom_down_left_2.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 2){
              SDL_Log("2");
              pTextureImage = initialiser_image("doom_down_left_3.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 3){
              SDL_Log("3");
              pTextureImage = initialiser_image("doom_down_left_4.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation = 0;
                compteur_animation = 0;
              }
            }
            //pTextureImage = initialiser_image("doom_down_left.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
          }
          else {
            // Marche vers la gauche
            if (animation == 0){
              SDL_Log("0");
              pTextureImage = initialiser_image("doom_left_1.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 1){
              SDL_Log("1");
              pTextureImage = initialiser_image("doom_left_2.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 2){
              SDL_Log("2");
              pTextureImage = initialiser_image("doom_left_3.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 3){
              SDL_Log("3");
              pTextureImage = initialiser_image("doom_left_4.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation = 0;
                compteur_animation = 0;
              }
            }
            //pTextureImage = initialiser_image("doom_left.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
          }
        }
        if (key_right_pressed == true){
          if (dst1.x <= 840 - 45){
            dst1.x += 1;
          }
          if (key_up_pressed == true && key_right_pressed == true){
            if (animation == 0){
              SDL_Log("0");
              pTextureImage = initialiser_image("doom_top_right_1.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 1){
              SDL_Log("1");
              pTextureImage = initialiser_image("doom_top_right_2.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 2){
              SDL_Log("2");
              pTextureImage = initialiser_image("doom_top_right_3.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 3){
              SDL_Log("3");
              pTextureImage = initialiser_image("doom_top_right_4.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation = 0;
                compteur_animation = 0;
              }
            }
            //pTextureImage = initialiser_image("doom_top_right.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
          }
          else if (key_down_pressed == true && key_right_pressed == true){
            if (animation == 0){
              SDL_Log("0");
              pTextureImage = initialiser_image("doom_down_right_1.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 1){
              SDL_Log("1");
              pTextureImage = initialiser_image("doom_down_right_2.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 2){
              SDL_Log("2");
              pTextureImage = initialiser_image("doom_down_right_3.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 3){
              SDL_Log("3");
              pTextureImage = initialiser_image("doom_down_right_4.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation = 0;
                compteur_animation = 0;
              }
            }
            //pTextureImage = initialiser_image("doom_down_right.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
          }
          else {
            // Marche vers la gauche
            if (animation == 0){
              SDL_Log("0");
              pTextureImage = initialiser_image("doom_right_1.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 1){
              SDL_Log("1");
              pTextureImage = initialiser_image("doom_right_2.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 2){
              SDL_Log("2");
              pTextureImage = initialiser_image("doom_right_3.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                  animation++;
                compteur_animation = 0;
              }
            }
            else if (animation == 3){
              SDL_Log("3");
              pTextureImage = initialiser_image("doom_right_4.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
              compteur_animation++;
              if (compteur_animation == limite_compteur_animation){
                animation = 0;
                compteur_animation = 0;
              }
            }
            //pTextureImage = initialiser_image("doom_right.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
          }
        }

        /*
        if (key_right_pressed == false && key_down_pressed == false && key_left_pressed == false && key_up_pressed == false && look_up == 1 && look_left == 0){
          pTextureImage = initialiser_image("doom_top_right_idle.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
        }
        */

        else if (key_right_pressed == false && key_down_pressed == false && key_left_pressed == false && key_up_pressed == false && look == 0){
          pTextureImage = initialiser_image("doom_top_idle.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
        }
        else if (key_right_pressed == false && key_down_pressed == false && key_left_pressed == false && key_up_pressed == false && look == 1){
          pTextureImage = initialiser_image("doom_down_idle.png",dst1.x,dst1.y,45,56,&src1,&dst1,pRenderer);
        }
        else if (key_right_pressed == false && key_down_pressed == false && key_left_pressed == false && key_up_pressed == false && look == 2){
          pTextureImage = initialiser_image("doom_left_idle.png",dst1.x,dst1.y,51,56,&src1,&dst1,pRenderer);
        }
        else if (key_right_pressed == false && key_down_pressed == false && key_left_pressed == false && key_up_pressed == false && look == 3){
          pTextureImage = initialiser_image("doom_right_idle.png",dst1.x,dst1.y,51,56,&src1,&dst1,pRenderer);
        }

        }

      for(i=0;i<nb_bullet;i++){
        afficher_image(pRenderer, pTexture_bullet[i], rect_NULL, dst_bullet[i]);
      }
      //afficher_image(pRenderer, pTextureImage_bullet, src_bullet1, dst_bullet1);
      afficher_image(pRenderer, pTextureImage, src1, dst1);
    
			SDL_RenderPresent(pRenderer); // Met à jour la fenêtre

      SDL_Delay(5);

		}

		SDL_DestroyRenderer(pRenderer);
		SDL_DestroyWindow(pWindow);
    TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

    return 0;
}
