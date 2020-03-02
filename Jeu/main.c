#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fonctions.h"
#define tailleNom 50
#define tailleStatut 10
#define tailleInventaire 10
#define tailleForet 3
typedef struct{
    int pv;
    int mana;
    int armure;
    int pv_max;
    int mana_max;
    int degat;
    int coup_critique;
    int inv_or;
    int potion_vie;
    int potion_mana;
    int minerai_fer;
    int minerai_or;
} t_joueur;

typedef struct{
    int pv;
    int mana;
    int armure;
    int pv_max;
    int mana_max;
    int degat;
    int coup_critique;
    int inv_or;
    int potion_vie;
    int potion_mana;
    int minerai_fer;
    int minerai_or;
} t_pnj;

int main () {
char nomJoueur[tailleNom];
int vieManaJoueur[tailleStatut] = {10, 10, 0, 10, 10, 1, 2}; // [0] points de vie // [1] mana // [2] armure // [3] pv max // [4] mana max // [5] degat // [6] Coup Critique

t_joueur joueur1;
int postureCombatJoueur[1] = {0}; // 0 Attaque et 1 Defense
int inventaireJoueur[tailleInventaire] = {10, 0, 0, 0, 0, 0, 0, 0, 0}; // [0] or // [1] potion de vie // [2] potions de mana // [3] fer // [4] minerai d'or
int vieManaBandit[tailleStatut] = {3, 3, 0, 3, 3, 1};
srand(time(NULL));
debutJeu(nomJoueur, vieManaJoueur, inventaireJoueur);
if (voyageForet(inventaireJoueur, vieManaBandit, vieManaJoueur, nomJoueur, postureCombatJoueur)==0){
    return 0;
}
auberge(inventaireJoueur, vieManaJoueur, nomJoueur);

finJeu();
return 0;
}

/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Faire un voyage en for�t :
if (voyageForet(inventaireJoueur, vieManaBandit, vieManaJoueur, nomJoueur, postureCombatJoueur)==0){
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Aller � l'auberge :
auberge(inventaireJoueur, vieManaJoueur, nomJoueur);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
