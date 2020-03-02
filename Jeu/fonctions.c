#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fonctions.h"
#define tailleNom 50
#define tailleStatut 10
#define tailleInventaire 10
#define tailleForet 3

void delay (int number_of_seconds) {
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
    // Stroing start time
    clock_t start_time = clock();
    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds);
}

void afficherInventaireJoueur (int inventaireJoueur[tailleInventaire]) {
    printf("Votre inventaire : \n");
    printf("Pieces d'or : %d\n", inventaireJoueur[0]);
    printf("Potions de vie : %d\n", inventaireJoueur[1]);
    printf("Potions de mana : %d\n", inventaireJoueur[2]);
    if (inventaireJoueur[3]>0){
        printf("Minerais de fer : %d\n", inventaireJoueur[3]);
    }
    if (inventaireJoueur[4]>0){
        printf("Minerais d'or : %d\n", inventaireJoueur[4]);
    }
}

void afficherLigne () {
    //printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
     printf("\n");
     for (int i=0; i<137; i++){
        printf("-");
        delay(5);
     }
     printf("\n");
     printf("\n");
}

void afficherStatutBandit (int vieManaBandit[tailleStatut]) {
    printf("Bandit : \n");
    printf("Points de vie : %d\n", vieManaBandit[0]);
    printf("Points de mana : %d\n", vieManaBandit[1]);
    printf("\n");
}

void afficherStatutBandits (int vieManaBandit[tailleStatut], int num) {
    printf("Bandit %d : \n", num);
    printf("Points de vie : %d\n", vieManaBandit[0]);
    printf("Points de mana : %d\n", vieManaBandit[1]);
    printf("\n");
}

void afficherStatutJoueur (char nomJoueur[tailleNom], int vieManaJoueur[tailleStatut]) {
    printf("%s : \n", nomJoueur);
    printf("Points de vie : %d\n", vieManaJoueur[0]);
    printf("Points de mana : %d\n", vieManaJoueur[1]);
    printf("\n");
}

void arriverAuberge () {
    printf("Vous arrivez dans une auberge.\n");
    printf("Bienvenue a l'auberge ! Que voulez-vous faire ?\n");
}

void arriverForet () {
    printf("Vous arrivez dans une foret.\n");
}

void auberge (int inventaireJoueur[tailleInventaire], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom]) {
    arriverAuberge();
    int avancement = 0;
    int choix, combien, totalpotionvie, totalpotionmana, prix;
    int montantpotionvie = 3, montantpotionmana = 3;
    char c;
    printf("\n");
    do {
        choix = combien = totalpotionvie = totalpotionmana = prix = 0;
        printf("Jouer a pile ou face [1]\n");
        printf("Jouer au jeu des allumettes [2]\n");
        printf("Acheter quelque chose [3]\n");
        printf("Payer une choppe, un repas et vous reposer [4]\n");
        printf("Voir votre inventaire [5]\n");
        printf("Voir votre statut [6]\n");
        printf("Utiliser un objet de votre inventaire [7]\n");
        printf("Vendre des objets [8]\n");
        printf("Partir de l'auberge [9]\n");
        scanf("%d", &avancement);
        if (avancement!=9) (afficherLigne());
        if (avancement==1){
            pileFace(inventaireJoueur, nomJoueur);
        }
        else if (avancement==2){
            aubergeAllumette(inventaireJoueur);
        }
        else if (avancement==3){
            printf("Hmm je dois avoir quelques babioles a vous vendre.\n");
            printf("Que souhaitez-vous acheter ?\n");
            printf("Potion de vie (3 pieces d'or, restaure 3 points de vie, il m'en reste %d) [1]\n", montantpotionvie);
            printf("Potion de mana (3 pieces d'or, restaure 3 points de mana, il m'en reste %d) [2]\n", montantpotionmana);
            printf("Rien, faire autre chose [3]\n");
            scanf("%d", &choix);
            if (choix==1){
                printf("Combien en voulez-vous ?");
                scanf("%d", &combien);
                totalpotionvie = montantpotionvie - combien;
                prix = combien * 3;
                if (totalpotionvie<0) {
                    printf("Je n'ai pas autant de potions que vous m'en demandez voyons je n'en ai que %d !\n", montantpotionvie);
                }
                else if (prix > inventaireJoueur[0]) {
                    printf("Voyons voyons, vous n'avez pas assez de pieces d'or !\n");
                }
                else {
                    printf("Voici vos %d potions de vie !\n", combien);
                    montantpotionvie = totalpotionvie;
                    inventaireJoueur[1] = inventaireJoueur[1] + combien;
                    inventaireJoueur[0] = inventaireJoueur[0] - prix;
                }

            }
            else if (choix==2){
                printf("Combien en voulez-vous ?");
                scanf("%d", &combien);
                totalpotionmana = montantpotionmana - combien;
                prix = combien * 3;
                if (totalpotionmana<0) {
                    printf("Je n'ai pas autant de potions que vous m'en demandez voyons je n'en ai que %d !\n", montantpotionmana);
                }
                else if (prix > inventaireJoueur[0]) {
                    printf("Voyons voyons, vous n'avez pas assez de pieces d'or !\n");
                }
                else {
                    printf("Voici vos %d potions de mana !\n", combien);
                    montantpotionmana = totalpotionmana;
                    inventaireJoueur[2] = inventaireJoueur[2] + combien;
                    inventaireJoueur[0] = inventaireJoueur[0] - prix;
                }
            }
            else if (choix==3) {
                printf("Rien ? Au moins vous aurez vu ce que j'ai a vous proposer !\n");
            }
        }
        else if (avancement==4){
            reposAuberge(vieManaJoueur, inventaireJoueur);
        }
        else if (avancement==5){
            afficherInventaireJoueur(inventaireJoueur);
        }
        else if (avancement==6){
            afficherStatutJoueur(nomJoueur, vieManaJoueur);
        }
        else if (avancement==7){
            utiliserObjet (inventaireJoueur, vieManaJoueur);
        }
        else if (avancement==8){
            venteObjet(nomJoueur, inventaireJoueur);
        }
        if (avancement!=9) (afficherLigne());
    }while(avancement!=9);
    printf("Vous sortez de l'auberge.\n");
    afficherLigne();
}

void aubergeAllumette (int inventaireJoueur[tailleInventaire]) {
int montant = 0, choix = 0;
printf("Connaissez-vous le principe du jeu ?\n");
printf("Oui [1]\n");
printf("Non [2]\n");
printf("Finalement je ne vais pas jouer [3]\n");
    do{
        scanf("%d", &choix);
    }while(choix<1 || choix>3);
    if (choix==1){
        printf("Combien voulez-vous miser ? ");
        scanf("%d", &montant);
        jeuAllumettes(inventaireJoueur, montant);
    }
    else if (choix==2){
        printf("Il y a 12 allumettes sur la table, chaque tour on retire entre 1 et 3 allumettes.\n");
        printf("Celui qui commence son tour avec 1 allumette sur la table a perdu !\n");
        printf("Bien. Jouons maintenant !\n");
        printf("Combien voulez-vous miser ? ");
        scanf("%d", &montant);
        jeuAllumettes(inventaireJoueur, montant);
    }
    else {
        printf("Revenez me voir quand vous voudrez jouer a mon jeu !\n");
    }
}

void miner (int inventaireJoueur[tailleInventaire]) {
    int i;
    printf("Vous commencez a miner.\n");
    printf("Minage en cours : ");
    for (int i=0; i<119; i++){
        printf("|");
        delay(25);
    }
    printf("\n");
    int hasard = rand()%100;
    if (hasard<60) {
        inventaireJoueur[3]++;
        printf("Vous minez un minerai de fer.\n");
    }
    else if (hasard>=60 && hasard<63){
        inventaireJoueur[4]++;
        printf("Vous minez un minerai d'or.\n");
    }
    else {
        printf("Le rocher que vous venez de miner ne contenait rien d'interessant.\n");
    }
}

void campement (int inventaireJoueur[tailleInventaire]) {
    printf("Vous arrivez dans un campement.\n");
    int chemin = 0;
    int nbRocher[1];
    nbRocher[0]=(rand()%3)+3;
    do {
        printf("Vous apercevez %d rochers aux alentours.\n", nbRocher[0]);
        printf("Miner des roches avoisinantes [1] \n");
        printf("Voir votre inventaire [2]\n");
        printf("Quitter le campement [3]\n");
        scanf("%d", &chemin);
        if (chemin==1 && nbRocher[0]>0) {
            miner(inventaireJoueur);
            nbRocher[0]--;
        }
        else if (chemin==1 && nbRocher[0]==0) {
            printf("Vous avez deja pioche toutes les roches de la zone.\n");
        }
        if (chemin==2) {
            afficherInventaireJoueur(inventaireJoueur);
        }
        afficherLigne();
    }while(chemin == 1 || chemin == 2);
    printf("Vous quittez le campement.\n");
    afficherLigne();
}

int choixChemin (char nomJoueur[tailleNom], int vieManaJoueur[tailleStatut], int inventaireJoueur[tailleInventaire]) {
int choix, vieagagner, manaagagner;
do {
    printf("Prendre le chemin de gauche [1] \n");
    printf("Prendre le chemin de droite [2] \n");
    printf("Voir votre statut [3]\n");
    printf("Voir votre inventaire [4]\n");
    printf("Utiliser un objet de votre inventaire [5]\n");
    scanf("%d", &choix);
    if (choix==1) {
            printf("Vous prenez le chemin de gauche.\n");
            afficherLigne();
    }
    if (choix==2) {
            printf("Vous prenez le chemin de droite.\n");
            afficherLigne();
    }
    if (choix==3) (afficherStatutJoueur(nomJoueur, vieManaJoueur));
    if (choix==4) (afficherInventaireJoueur(inventaireJoueur));
    if (choix==5) (utiliserObjet(inventaireJoueur, vieManaJoueur));
}while(choix == 3 || choix == 4 || choix == 5);

return choix;
}

void combatBandit (int vieManaBandit[tailleStatut], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom], int postureCombatJoueur[1]) {
    int degat;
    afficherStatutBandit(vieManaBandit);
    degat = rand()%100;
    if (degat<50){
        degat = 0;
        printf("Le bandit vous loupe ! Vous ne perdez aucun points de vie !\n");
    }
    else if (degat>=50 && degat <95) {
        degat = 1 - vieManaJoueur[2];
        if(degat >0) {
            vieManaJoueur[0] = vieManaJoueur[0] - degat;
            printf("Le bandit attaque ! Vous perdez %d points de vie !\n", degat);
        }
        else {
            printf("Le bandit vous touche mais avec %d d'armure vous ne perdez aucun points de vie !\n", vieManaJoueur[2]);
        }
    }
    else {
        degat = 2 - vieManaJoueur[2];
        if(degat >0) {
            vieManaJoueur[0] = vieManaJoueur[0] - degat;
            printf("Le bandit effectue un coup critique ! Vous perdez %d points de vie !\n", degat);
        }
        else{
            printf("Le bandit effectue un coup critique mais avec %d d'armure vous ne perdez aucun points de vie !\n", vieManaJoueur[2]);
        }
    }
    //degat = degat - vieManaBandit[2];
    //if(degat >0) (vieManaJoueur[0] = vieManaJoueur[0] - degat);
}

void combatJoueur (int vieManaBandit[tailleStatut], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom], int postureCombatJoueur[1], int inventaireJoueur[tailleInventaire]) {
    int degat, choix, vieagagner, manaagagner;
    afficherStatutJoueur(nomJoueur, vieManaJoueur);
    printf("Voulez vous attaquer ou vous defendre ? \n");
    printf("Attaquer [1]\n");
    printf("Se defendre [2]\n");
    printf("Utiliser un objet de votre inventaire [3]\n");
    printf("Voir votre inventaire [4]\n");
    printf("Voir votre statut [5]\n");
    printf("Attendre [6]\n");
    scanf("%d", &choix);
    if(choix==1){
        degat = rand()%100;
        if (degat<5){
            degat = 0;
            printf("Vous loupez votre coup !\n");
        }
        else if (degat>=5 && degat <95) {
            degat = vieManaJoueur[5] - vieManaBandit[2];
            if (degat>0){
                vieManaBandit[0] = vieManaBandit[0] - degat;
                printf("Vous attaquez ! Le bandit perd %d points de vie !\n", degat);
            }
            else{
                printf("Vous attaquez mais avec %d d'armure le bandit ne perd aucun points de vie !\n", vieManaBandit[2]);
            }
        }
        else {
            degat = vieManaJoueur[6] - vieManaBandit[2];
            if (degat>0){
                vieManaBandit[0] = vieManaBandit[0] - degat;
                printf("Vous effectuez un coup critique ! Le bandit perd %d points de vie !\n", degat);
            }
            else{
                printf("Vous effectuez un coup critique mais avec %d d'armure le bandit ne perd aucun points de vie !\n", vieManaBandit[2]);
            }
        }
    }
    else if(choix==2){
        postureCombatJoueur[0]=1;
        vieManaJoueur[2]++;
    }
    else if(choix==3){
        utiliserObjet (inventaireJoueur, vieManaJoueur);
    }
    else if(choix==4) {
        afficherInventaireJoueur(inventaireJoueur);
        afficherLigne();
        combatJoueur(vieManaBandit, vieManaJoueur, nomJoueur, postureCombatJoueur, inventaireJoueur);
    }
    else if(choix ==5) {
        afficherStatutJoueur(nomJoueur, vieManaJoueur);
        afficherLigne();
        combatJoueur(vieManaBandit, vieManaJoueur, nomJoueur, postureCombatJoueur, inventaireJoueur);
    }
}

int combatJoueurBandit (int vieManaBandit[tailleStatut], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom], int postureCombatJoueur[1], int inventaireJoueur[tailleInventaire]) {
    printf("Oh non ! C'est un bandit !\n");
    printf("Vous engagez le combat avec ce maudit bandit !\n");
    int bandit[tailleStatut] = {3,3,0};
    afficherLigne();
    afficherStatutBandit(bandit);
    do{
    combatJoueur(bandit, vieManaJoueur, nomJoueur, postureCombatJoueur, inventaireJoueur);
    if (bandit[0]<=0){
      printf("Vous avez vaincu le bandit !\n");
      afficherLigne();
      return 1;
    }
    afficherLigne();
    combatBandit(bandit, vieManaJoueur, nomJoueur, postureCombatJoueur);
    if (postureCombatJoueur[0]==1){
      postureCombatJoueur[0]=0;
      vieManaJoueur[2]--;
    }

    if (vieManaJoueur[0]<=0){
            printf("Vous avez perdu !\n");
            afficherLigne();
            return 0;
    }
    afficherLigne();
}while(vieManaBandit[0]>0 && vieManaJoueur[0]>0);
}

int combatJoueur2Bandit (int vieManaBandit[tailleStatut], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom], int postureCombatJoueur[1], int inventaireJoueur[tailleInventaire]) {
    int choix;
    printf("Oh non ! Ce sont deux bandits !\n");
    printf("Vous engagez le combat avec ces maudits bandit !\n");
    int bandit[tailleStatut] = {3,3,0};
    int bandit2[tailleStatut] = {3,3,0};
    afficherLigne();
    do{
    if (bandit[0]>0) (afficherStatutBandits(bandit, 1));
    if (bandit2[0]>0) (afficherStatutBandits(bandit2, 2));
    if (bandit[0]>0 && bandit2[0]>0){
        printf("Quel bandit voulez-vous cibler ?\n");
        printf("Bandit [1]\n");
        printf("Bandit 2 [2]\n");
        scanf("%d", &choix);
        if (choix==1 && bandit[0]>0)(combatJoueur(bandit, vieManaJoueur, nomJoueur, postureCombatJoueur, inventaireJoueur));
        else if (choix==2 && bandit2[0]>0)(combatJoueur(bandit2, vieManaJoueur, nomJoueur, postureCombatJoueur, inventaireJoueur));
    }
    else if (bandit[0]>0 && bandit2[0]<=0) {
        combatJoueur(bandit, vieManaJoueur, nomJoueur, postureCombatJoueur, inventaireJoueur);
    }
    else if (bandit[0]<=0 && bandit2[0]>0) {
        combatJoueur(bandit2, vieManaJoueur, nomJoueur, postureCombatJoueur, inventaireJoueur);
    }
    if (bandit[0]<=0 && bandit2[0]<=0){
      printf("Vous avez vaincu les bandits !\n");
      afficherLigne();
      return 1;
    }
    afficherLigne();
    combatBandit(bandit, vieManaJoueur, nomJoueur, postureCombatJoueur);
    combatBandit(bandit2, vieManaJoueur, nomJoueur, postureCombatJoueur);
    if (postureCombatJoueur[0]==1){
      postureCombatJoueur[0]=0;
      vieManaJoueur[2]--;
    }
    if (vieManaJoueur[0]<=0){
            printf("Vous avez perdu !\n");
            afficherLigne();
            return 0;
    }
    afficherLigne();
}while((bandit[0]>0 || bandit2[0]>0) && vieManaJoueur[0]>0);
}

/*int combatJoueur1Bandit(int vieManaBandit[tailleStatut], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom], int postureCombatJoueur[1], int inventaireJoueur[tailleInventaire]) {
    int degat, choix, vieagagner, manaagagner;
    printf("Oh non ! C'est un bandit !\n");
    printf("Vous engagez le combat avec ce maudit bandit !\n");
    int bandit[tailleStatut] = {3,3,0};
    afficherLigne();
    afficherStatutBandit(bandit);
    do{
    afficherStatutJoueur(nomJoueur, vieManaJoueur);
    printf("Voulez vous attaquer ou vous defendre ? \n");
    printf("Attaquer [1]\n");
    printf("Se defendre [2]\n");
    printf("Utiliser un objet de votre inventaire [3]\n");
    printf("Voir votre inventaire [4]\n");
    printf("Voir votre statut [5]\n");
    printf("Attendre [6]\n");
    scanf("%d", &choix);
    if(choix==1){
        degat = rand()%100;
        if (degat<5){
            degat = 0;
            printf("Vous loupez votre coup !\n");
        }
        else if (degat>=5 && degat <95) {
            degat = 1 - bandit[2];
            if (degat>0){
                bandit[0] = bandit[0] - degat;
                printf("Vous attaquez ! Le bandit perd %d points de vie !\n", degat);
            }
            else{
                printf("Vous attaquez mais avec %d d'armure le bandit ne perd aucun points de vie !\n", bandit[2]);
            }
        }
        else {
            degat = 2 - bandit[2];
            if (degat>0){
                bandit[0] = bandit[0] - degat;
                printf("Vous effectuez un coup critique ! Le bandit perd %d points de vie !\n", degat);
            }
            else{
                printf("Vous effectuez un coup critique mais avec %d d'armure le bandit ne perd aucun points de vie !\n", bandit[2]);
            }
        }
    }
    else if(choix==2){
        postureCombatJoueur[0]=1;
        vieManaJoueur[2]++;
    }
    else if(choix==3){
        utiliserObjet (inventaireJoueur, vieManaJoueur);
    }
    else if(choix==4) {
        afficherInventaireJoueur(inventaireJoueur);
        afficherLigne();
        afficherStatutJoueur(nomJoueur, vieManaJoueur);
        printf("Voulez vous attaquer ou vous defendre ? \n");
        printf("Attaquer [1]\n");
        printf("Se defendre [2]\n");
        printf("Utiliser un objet de votre inventaire [3]\n");
        printf("Voir votre inventaire [4]\n");
        printf("Voir votre statut [5]\n");
        printf("Attendre [6]\n");
        scanf("%d", &choix);
        if(choix==1){
            degat = rand()%100;
            if (degat<5){
                degat = 0;
                printf("Vous loupez votre coup !\n");
            }
            else if (degat>=5 && degat <95) {
                degat = 1 - bandit[2];
                if (degat>0){
                    bandit[0] = bandit[0] - degat;
                    printf("Vous attaquez ! Le bandit perd %d points de vie !\n", degat);
                }
                else{
                    printf("Vous attaquez mais avec %d d'armure le bandit ne perd aucun points de vie !\n", bandit[2]);
                }
            }
            else {
                degat = 2 - bandit[2];
                if (degat>0){
                    bandit[0] = bandit[0] - degat;
                    printf("Vous effectuez un coup critique ! Le bandit perd %d points de vie !\n", degat);
                }
                else{
                    printf("Vous effectuez un coup critique mais avec %d d'armure le bandit ne perd aucun points de vie !\n", bandit[2]);
                }
            }
        }
    }
    else if(choix ==5) {
        afficherStatutJoueur(nomJoueur, vieManaJoueur);
        afficherLigne();
        afficherStatutJoueur(nomJoueur, vieManaJoueur);
        printf("Voulez vous attaquer ou vous defendre ? \n");
        printf("Attaquer [1]\n");
        printf("Se defendre [2]\n");
        printf("Utiliser un objet de votre inventaire [3]\n");
        printf("Voir votre inventaire [4]\n");
        printf("Voir votre statut [5]\n");
        printf("Attendre [6]\n");
        scanf("%d", &choix);
        if(choix==1){
            degat = rand()%100;
            if (degat<5){
                degat = 0;
                printf("Vous loupez votre coup !\n");
            }
            else if (degat>=5 && degat <95) {
                degat = 1 - bandit[2];
                if (degat>0){
                    bandit[0] = bandit[0] - degat;
                    printf("Vous attaquez ! Le bandit perd %d points de vie !\n", degat);
                }
                else{
                    printf("Vous attaquez mais avec %d d'armure le bandit ne perd aucun points de vie !\n", bandit[2]);
                }
            }
            else {
                degat = 2 - bandit[2];
                if (degat>0){
                    bandit[0] = bandit[0] - degat;
                    printf("Vous effectuez un coup critique ! Le bandit perd %d points de vie !\n", degat);
                }
                else{
                    printf("Vous effectuez un coup critique mais avec %d d'armure le bandit ne perd aucun points de vie !\n", bandit[2]);
                }
            }
        }
    }
    if (bandit[0]<=0){
      printf("Vous avez vaincu le bandit !\n");
      afficherLigne();
      return 1;
    }
    afficherLigne();
    afficherStatutBandit(bandit);
    degat = rand()%100;
    if (degat<50){
        degat = 0;
        printf("Le bandit vous loupe ! Vous ne perdez aucun points de vie !\n");
    }
    else if (degat>=50 && degat <95) {
        degat = 1 - vieManaJoueur[2];
        if(degat >0) {
            vieManaJoueur[0] = vieManaJoueur[0] - degat;
            printf("Le bandit attaque ! Vous perdez %d points de vie !\n", degat);
        }
        else {
            printf("Le bandit vous touche mais avec %d d'armure vous ne perdez aucun points de vie !\n", vieManaJoueur[2]);
        }
    }
    else {
        degat = 2 - vieManaJoueur[2];
        if(degat >0) {
            vieManaJoueur[0] = vieManaJoueur[0] - degat;
            printf("Le bandit effectue un coup critique ! Vous perdez %d points de vie !\n", degat);
        }
        else{
            printf("Le bandit effectue un coup critique mais avec %d d'armure vous ne perdez aucun points de vie !\n", vieManaJoueur[2]);
        }
    }


    if (postureCombatJoueur[0]==1){
      postureCombatJoueur[0]=0;
      vieManaJoueur[2]--;
    }

    if (vieManaJoueur[0]<=0){
            printf("Vous avez perdu !\n");
            afficherLigne();
            return 0;
    }
    afficherLigne();
}while(bandit[0]>0 && vieManaJoueur[0]>0);
}*/

void debutJeu (char nomJoueur[tailleNom], int vieManaJoueur[tailleStatut], int inventaireJoueur[tailleInventaire]) {
    saisirNomJoueur(nomJoueur, vieManaJoueur);
    afficherStatutJoueur(nomJoueur, vieManaJoueur);
    afficherInventaireJoueur(inventaireJoueur);
    afficherLigne();
}

void finJeu () {
    afficherLigne();
    printf("\n \n");
    printf("                                                Merci d'avoir joue a la demo de ce petit rpg !\n");
    afficherLigne();
}

int jeuAllumettes (int inventaireJoueur[tailleInventaire], int montant) {
 	int allum, affiche, ordi, texte;
 	int nbAllum = 12;
 	printf("%d :  ", nbAllum);
 	for (affiche = 1 ; affiche <= nbAllum ; affiche++){
 		printf("| ");
 	}
 	printf("\n");
 	do {
		do{
		printf("Combien d'allumettes voulez vous enlever ? ");
		scanf("%d", &allum);
		if (allum > nbAllum) (printf("Vous ne pouvez enlever plus d'allumettes qu'il n'y en a. \n"));
		if (allum > 3) (printf("Vous ne pouvez enlever plus de 3 allumettes. \n"));
		if (allum < 1) (printf("Vous devez enlever au moins une allumette. \n"));
		}while((allum > nbAllum) || (allum > 3) || (allum < 1) || ((nbAllum - allum) == 0));
		nbAllum = nbAllum - allum;
		 printf("%d :  ", nbAllum);
		 for (affiche = 1 ; affiche <= nbAllum ; affiche++) {
			printf("| ");
		}
		printf("\n");
		if (nbAllum == 1) {
                printf("Non ! J'ai perdu. \n");
                inventaireJoueur[0] = inventaireJoueur[0] + montant;
                printf("Vous avez gagne %d pieces d'or !\n", montant);
		}

		if (nbAllum > 1) {

		if (((nbAllum-1)%4)+1==0 || (nbAllum-1==1)){
			ordi = 1;
		}

		else if (((nbAllum-2)%4)+1==0 || (nbAllum-2==1)){
			ordi = 2;
		}
		/*
		else if ((((nbAllum-3)%4)+1==0) || (nbAllum-3==1)){
			ordi = 3;
		}
		*/
		else {
		do{
		ordi = rand()%3+1;
		}while(ordi > nbAllum);
		}
		nbAllum = nbAllum - ordi;
		texte = rand()%100;
        if (texte<33) (printf("Hmm tres bien je retire donc %d allumettes.\n", ordi));
        else if (texte>=33 && texte<66) (printf("Je vais retirer %d allumettes.\n", ordi));
        else {
            printf("Je choisis de retirer %d allumettes.\n", ordi);
        }
		printf("%d :  ", nbAllum);
		for (affiche = 1 ; affiche <= nbAllum ; affiche++){
 			printf("| ");
 		}
 		printf("\n");
		if (nbAllum == 1){
            printf("Vous avez perdu. \n");
            inventaireJoueur[0] = inventaireJoueur[0] - montant;
            printf("Vous perdez donc %d pieces d'or.\n", montant);
        }
		}
 	}while(nbAllum > 1);
}

void pileFace (int inventaireJoueur[tailleInventaire], char nomJoueur[tailleNom]){
    int montant = 0, piece = 0, choix = 0;
    if (inventaireJoueur[0]>0){
        printf("Alors vous voulez jouer a pile ou face ? Vous pouvez gagner le double de votre mise ou tout perdre !\n");
        printf("Combien voulez-vous miser ? ");
        scanf("%d", &montant);
        if (montant>0 && montant<=inventaireJoueur[0]){
            printf("Bien alors jouons ! Je lance une piece.\n");
            piece = rand()%2;
            delay(1000);
            printf("Voyons voir le resultat...\n");
            delay(2000);
            if (piece==0){
                printf("Vous avez perdu ! Je garde l'or pour moi !\n");
                inventaireJoueur[0] = inventaireJoueur[0] - montant;
            }
            else {
                printf("Vous avez gagne ! Felicitations voici le double de votre mise.\n");
                inventaireJoueur[0] = inventaireJoueur[0] + montant;
            }
        }
        else if (montant==0){
            printf("Vous ne voulez pas jouer ? A quoi bon me deranger alors !");
        }
        else if (montant<0){
            printf("Vous ne pouvez pas miser une somme negative de piece d'or %s.\n", nomJoueur);
        }
        else {
            printf("Allons allons vous ne pouvez pas miser plus que ce que vous avez !\n");
        }
    }
    else {
        choix = rand()%100;
        if (choix < 5){
            printf("Allez je suis genereux je vous donne une piece d'or pour jouer !\n");
            delay(1000);
            printf("Bien alors jouons ! Je lance une piece, voyons voir le resultat.\n");
            piece = rand()%2;
            delay(2000);
            if (piece==0){
                printf("Vous avez perdu ! Je garde l'or pour moi !\n");
            }
            else {
                printf("Vous avez gagne ! Felicitations voici donc deux pieces pour vous.\n");
                inventaireJoueur[0] = inventaireJoueur[0] + 2;
            }
        }
        else {
            delay(500);
            printf("Vous n'avez pas un sou, revenez me voir quand vous en aurez au moins un !\n");
        }
    }
}

void reposAuberge (int vieManaJoueur[tailleStatut], int inventaireJoueur[tailleInventaire]) {
    int choix = 0, vieagagner = 0;
    printf("Cela vous coutera 2 pieces d'or !\n");
    printf("Payer [1]\n");
    printf("Ne rien faire [2]\n");
    scanf("%d", &choix);
    if (choix==1 && inventaireJoueur[0]>=2 && vieManaJoueur[0]<vieManaJoueur[3]){
        printf("Vous perdez 2 pieces d'or.\n");
        if (vieManaJoueur[0]+3>vieManaJoueur[3]) {
                vieagagner = vieManaJoueur[3]-vieManaJoueur[0];
                vieManaJoueur[0]=vieManaJoueur[3];
        }
        else {
            vieManaJoueur[0] = vieManaJoueur[0] + 3;
            vieagagner = 3;
        }
        inventaireJoueur[0] = inventaireJoueur[0] - 2;
        printf("Asseyez-vous donc !\n");
        printf("Je vous sers un repas chaud, prenez cette choppe en attendant.\n");
        printf("Vous regagnez %d points de vie.\n", vieagagner);
    }
    else if (choix ==1 && vieManaJoueur[0]>=vieManaJoueur[3]){
        printf("Allons allons vous n'avez pas besoin de vous reposez. Vous m'avez l'air en pleine forme !\n");
    }
    else if (choix ==2) {
        printf("Vous ne voulez pas de repas ? Bien, dites moi si vous souhaitez autre chose.\n");
    }
    else if (inventaireJoueur[0]<2) {
        printf("Vous n'avez pas assez de pieces pour me payer ce repas voyons !\n");
    }
}

void resetBandit (int vieManaBandit[tailleStatut]) {
    vieManaBandit[0] = 3;
    vieManaBandit[1] = 3;
}

void saisirNomJoueur (char nomJoueur[tailleNom], int vieManaJoueur[tailleStatut]) {
    int choix = 0;
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                   Bienvenue dans ce petit RPG !                                                          \n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n");
    do{
        printf("Oye voyageur ! Quel est donc votre nom ? ");
        scanf("%s", nomJoueur);
        printf("\n");
        printf("Vous vous appelez donc %s ?\n", nomJoueur);
        printf("Oui c'est ca ! [1]\n");
        printf("Non attendez je ne suis pas sur [2]\n");
        scanf("%d", &choix);
        if (choix==2) (printf("\n"));
    }while(choix!=1);
    printf("\n");
}

void utiliserObjet (int inventaireJoueur[tailleInventaire], int vieManaJoueur[tailleStatut]) {
    int vieagagner, manaagagner, choix;
    printf("Utiliser une potion de vie [1]\n");
    printf("Utiliser une potion de mana [2]\n");
    printf("Rien [3]\n");
    scanf("%d", &choix);
    if (choix==1 && inventaireJoueur[1]>0){
        inventaireJoueur[1] = inventaireJoueur[1] - 1;
        if (vieManaJoueur[0]+3>vieManaJoueur[3]) {
            vieagagner = vieManaJoueur[3]-vieManaJoueur[0];
            vieManaJoueur[0]=vieManaJoueur[3];
        }
        else {
            vieManaJoueur[0] = vieManaJoueur[0] + 3;
            vieagagner = 3;
        }
        printf("Vous regagnez %d points de vie.\n", vieagagner);
    }
    else if (choix==1 && inventaireJoueur[1]<=0) {
        printf("Vous n'avez pas de potion de vie.\n");
    }
    else if (choix==2 && inventaireJoueur[2]>0){
        inventaireJoueur[2] = inventaireJoueur[2] - 1;
        if (vieManaJoueur[1]+3>vieManaJoueur[4]) {
            manaagagner = vieManaJoueur[4]-vieManaJoueur[1];
            vieManaJoueur[1]=vieManaJoueur[4];
        }
        else {
            vieManaJoueur[1] = vieManaJoueur[1] + 3;
            manaagagner = 3;
        }
        printf("Vous regagnez %d points de mana.\n", manaagagner);
    }
    else if (choix==2 && inventaireJoueur[2]<=0) {
        printf("Vous n'avez pas de potion de mana.\n");
    }
}

void venteObjet(char nomJoueur[tailleNom], int inventaireJoueur[tailleInventaire]) {
    int choix, combien, compte;
    printf("Allons allons que voulez vous me vendre ?\n");
    printf("Je rachete vos potions de vie pour 2 pieces d'or l'unite. Vous en avez %d. [1]\n", inventaireJoueur[1]);
    printf("Des potions de mana ? Je les reprends 2 pieces l'unite, vous en avez actuellement %d. [2]\n", inventaireJoueur[2]);
    printf("Je prends des minerais de fer pour 3 pieces l'unite [3] et l'or pour 5. [4] \nVous avez %d fer et %d or.\n", inventaireJoueur[3], inventaireJoueur[4]);
    printf("Vous ne voulez rien me vendre ? [5]\n");
    printf("Que voulez-vous vendre ?\n");
    scanf("%d", &choix);
    if (choix!=5) {
        printf("Et combien ?\n");
        scanf("%d", &combien);
    }

    compte = inventaireJoueur[choix] - combien;
    if (choix==1 || choix ==2 && compte>0) {
        inventaireJoueur[choix] = inventaireJoueur[choix] - combien;
        inventaireJoueur[0] = inventaireJoueur[0] + 2*combien;
    }
    else if (choix==3 && compte>0) {
        inventaireJoueur[choix] = inventaireJoueur[choix] - combien;
        inventaireJoueur[0] = inventaireJoueur[0] + 3*combien;
    }
    else if (choix==4 && compte>0) {
        inventaireJoueur[choix] = inventaireJoueur[choix] - combien;
        inventaireJoueur[0] = inventaireJoueur[0] + 5*combien;
    }
    else if (compte<0) {
        if (choix==1) (printf("Vous n'avez pas assez de potions de vie a me vendre.\n"));
        if (choix==2) (printf("Vous n'avez pas assez de potions de mana a me vendre.\n"));
        if (choix==3) (printf("Vous n'avez pas assez de minerais de fer a me vendre.\n"));
        if (choix==4) (printf("Vous n'avez pas assez de minerais d'or a me vendre.\n"));
    }
    if (choix==5) (printf("Vous ne voulez donc rien vendre.\n"));
}

int voyageForet(int inventaireJoueur[tailleInventaire], int vieManaBandit[tailleStatut], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom], int postureCombatJoueur[1]) {
    arriverForet();
    int avancement = 0, echec = 1;
    do {
        choixChemin(nomJoueur, vieManaJoueur, inventaireJoueur);
        int event = rand()%100;
        if (event<1) {
            echec = combatJoueurBandit(vieManaBandit, vieManaJoueur, nomJoueur, postureCombatJoueur, inventaireJoueur);
            if (echec == 0) {
                return 0;
            }
        }
        else if (event>=1 && event<2) {
            echec = combatJoueur2Bandit(vieManaBandit, vieManaJoueur, nomJoueur, postureCombatJoueur, inventaireJoueur);
            if (echec == 0) {
                return 0;
            }
        }
        else if (event>=2 && event <99) {
            campement(inventaireJoueur);
        }
        else if (event>=99 && event<100) {
            auberge(inventaireJoueur, vieManaJoueur, nomJoueur);
        }
        else {
            voyageForetSimple(inventaireJoueur);
        }
        avancement++;
    }while(avancement<3);
    printf("Vous etes sortis indemne de la foret !\n");
    afficherLigne();
    return 1;
}

void voyageForetSimple(int inventaireJoueur[tailleInventaire]) {
    int choix, montant;
    choix = rand()%100;
    montant = rand()%5+1;
    printf("Vous avancer dans la foret sans encombre.\n");
    if (choix<25) {
        printf("Vous trouvez quelque chose sur la route !\n");
        printf("Il s'agit de %d pieces d'or !\n", montant);
        inventaireJoueur[0] = inventaireJoueur[0] + montant;
        afficherInventaireJoueur(inventaireJoueur);
    }
    afficherLigne();
}
