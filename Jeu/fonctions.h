#define tailleNom 50
#define tailleStatut 10
#define tailleInventaire 10
#define tailleForet 3

void delay(int number_of_seconds);

void afficherInventaireJoueur(int inventaireJoueur[tailleInventaire]);

void afficherLigne();

void afficherStatutBandit(int vieManaBandit[tailleStatut]);

void afficherStatutBandits(int vieManaBandit[tailleStatut], int num);

void afficherStatutJoueur(char nomJoueur[tailleNom], int vieManaJoueur[tailleStatut]);

void arriverAuberge();

void arriverForet();

void auberge(int inventaireJoueur[tailleInventaire], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom]);

void aubergeAllumette(int inventaireJoueur[tailleInventaire]);

int choixChemin(char nomJoueur[tailleNom], int vieManaJoueur[tailleStatut], int inventaireJoueur[tailleInventaire]);

void combatBandit(int vieManaBandit[tailleStatut], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom], int postureCombatJoueur[1]);

void combatJoueur(int vieManaBandit[tailleStatut], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom], int postureCombatJoueur[1], int inventaireJoueur[tailleInventaire]);

int combatJoueurBandit(int vieManaBandit[tailleStatut], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom], int postureCombatJoueur[1], int inventaireJoueur[tailleInventaire]);

int combatJoueur2Bandit(int vieManaBandit[tailleStatut], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom], int postureCombatJoueur[1], int inventaireJoueur[tailleInventaire]);

void debutJeu(char nomJoueur[tailleNom], int vieManaJoueur[tailleStatut], int inventaireJoueur[tailleInventaire]);

void finJeu();

void forge();

int jeuAllumettes(int inventaireJoueur[tailleInventaire], int montant);

void pileFace(int inventaireJoueur[tailleInventaire], char nomJoueur[tailleNom]);

void reposAuberge(int vieManaJoueur[tailleStatut], int inventaireJoueur[tailleInventaire]);

void resetBandit(int vieManaBandit[tailleStatut]);

void saisirNomJoueur(char nomJoueur[tailleNom], int vieManaJoueur[tailleStatut]);

void utiliserObjet(int inventaireJoueur[tailleInventaire], int vieManaJoueur[tailleStatut]);

void venteObjet(char nomJoueur[tailleNom], int inventaireJoueur[tailleInventaire]);

int voyageForet(int inventaireJoueur[tailleInventaire], int vieManaBandit[tailleStatut], int vieManaJoueur[tailleStatut], char nomJoueur[tailleNom], int postureCombatJoueur[1]);

void voyageForetSimple(int inventaireJoueur[tailleInventaire]);

