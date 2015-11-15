#ifndef GAME
#define GAME
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#endif // GAME

typedef enum {S_DEPART, S_25, S_VORTEX, S_VISION, S_PIEGE, S_MOBILE, S_CONTROLE, S_JUMELLE, S_VIDE, S_MORTELLE, S_PRISON, S_ILLUSION, S_INONDABLE, S_ACIDE, S_FROIDE, S_NOIRE} TypeSalle;
typedef enum {M_SUSPISCION, M_COMPETITION, M_EQUIPE, M_COOPERATION, M_SOLO} Mode;
typedef enum {J_GARDIEN, J_PRISONNIER, J_NORMAL} TypeJoueur;
typedef enum {A_POUSSER, A_CONTROLER, A_DEPLACER, A_REGARDER} Action;
typedef enum {D_BAS, D_HAUT, D_GAUCHE, D_DROITE} Direction;
typedef enum {P_BG, P_BIMBO, P_COLOSSE, P_FILLE, P_GEEK, P_SAVANT} Personnage;
typedef struct {
    TypeJoueur type;
    char nom[255];
    Personnage perso;
    int posx;
    int posy;
    int mort;
    Action action[2];
    Direction dir[2];
    int persopousse;
} Joueur;
typedef struct {
    TypeSalle type;
    int visible;
} Salle;

void ajouter_pioche(int *pioche, int *taille, int elt);
void creer_complexe(Salle complexe[][5], Mode m, int expert);
void role_joueurs(Joueur *joueurs, int nbjoueurs);
void init_joueurs(Joueur *joueurs, int nbjoueurs);
void action(Joueur *joueurs, int nbjoueurs, int debut, Salle complexe[][5]);
void jouer();
