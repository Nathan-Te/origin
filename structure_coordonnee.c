#include <stdlib.h>
#include <stdio.h>

typedef struct coordonnee_s{
	int x;
	int y;
	int w;
	int h;
}coordonnee_t;

int main (){

	coordonnee_t * coordonnee_ptr = malloc(sizeof(coordonnee_t));
	coordonnee_ptr->x = 1;
	coordonnee_ptr->y = 2;
	coordonnee_ptr->w = 3;
	coordonnee_ptr->h = 4;

	coordonnee_t coordonnee_var;
	coordonnee_var.x = 5;
	coordonnee_var.y = 6;
	coordonnee_var.w = 7;
	coordonnee_var.h = 8;

	printf("La variable coordonne_ptr contient : \n");
	printf("x : %d | y : %d | w : %d | h : %d \n\n\n", coordonnee_ptr->x, coordonnee_ptr->y, coordonnee_ptr->w, coordonnee_ptr->h);

	printf("La variable coordonne_var contient : \n");
	printf("x : %d | y : %d | w : %d | h : %d \n\n\n", coordonnee_var.x, coordonnee_var.y, coordonnee_var.w, coordonnee_var.h);

	return 0;

}

// Pour compiler :
// gcc -o structure_coordonnee structure_coordonnee.c
