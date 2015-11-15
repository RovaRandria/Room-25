#include "game.h"

void ajouter_pioche(int *pioche, int *taille, int elt) {
    pioche[*taille] = elt;
    (*taille)++;
}

void creer_complexe(Salle complexe[][5], Mode m, int expert) {
    TypeSalle pioche[22];
    int taille = 0;
    int random;
    int i, j, k;
    complexe[2][2].type = S_DEPART;
    complexe[2][2].visible = 1;
    ajouter_pioche(pioche, &taille, S_VIDE);
    ajouter_pioche(pioche, &taille, S_VIDE);
    ajouter_pioche(pioche, &taille, S_VIDE);
    ajouter_pioche(pioche, &taille, S_VIDE);
    ajouter_pioche(pioche, &taille, S_NOIRE);
    ajouter_pioche(pioche, &taille, S_NOIRE);
    ajouter_pioche(pioche, &taille, S_FROIDE);
    ajouter_pioche(pioche, &taille, S_FROIDE);
    ajouter_pioche(pioche, &taille, S_PIEGE);
    ajouter_pioche(pioche, &taille, S_PIEGE);
    ajouter_pioche(pioche, &taille, S_INONDABLE);
    ajouter_pioche(pioche, &taille, S_INONDABLE);
    ajouter_pioche(pioche, &taille, S_ACIDE);
    ajouter_pioche(pioche, &taille, S_ACIDE);
    ajouter_pioche(pioche, &taille, S_VORTEX);
    ajouter_pioche(pioche, &taille, S_MORTELLE);
    ajouter_pioche(pioche, &taille, S_CONTROLE);
    if(expert) {
        ajouter_pioche(pioche, &taille, S_ILLUSION);
        if(m == M_SUSPISCION) {
            ajouter_pioche(pioche, &taille, S_VIDE);
            ajouter_pioche(pioche, &taille, S_VIDE);
            ajouter_pioche(pioche, &taille, S_MORTELLE);
            ajouter_pioche(pioche, &taille, S_MOBILE);
        }
        else {
            ajouter_pioche(pioche, &taille, S_JUMELLE);
            ajouter_pioche(pioche, &taille, S_JUMELLE);
            ajouter_pioche(pioche, &taille, S_PRISON);
            ajouter_pioche(pioche, &taille, S_PRISON);
        }
    }
    else {
        ajouter_pioche(pioche, &taille, S_VIDE);
        ajouter_pioche(pioche, &taille, S_VIDE);
        ajouter_pioche(pioche, &taille, S_VIDE);
        ajouter_pioche(pioche, &taille, S_VIDE);
        ajouter_pioche(pioche, &taille, S_VORTEX);
    }
    srand(time(NULL));
    for(i = 0; i < 5; i++) {
        for(j = abs(i - 2); j <= 4 - abs(i - 2); j++) {
            if(i != 2 || j != 2) {
                random = rand() % taille;
                complexe[i][j].type = pioche[random];
                complexe[i][j].visible = 0;
                taille--;
                for(k = random; k < taille; k++) {
                    pioche[k] = pioche[k+1];
                }
            }
        }
    }
    pioche[taille] = S_25;
    taille++;
    pioche[taille] = S_VISION;
    taille++;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(j < abs(i - 2) || j > 4 - abs(i - 2)) {
                random = rand() % taille;
                complexe[i][j].type = pioche[random];
                complexe[i][j].visible = 0;
                taille--;
                for(k = random; k < taille; k++) {
                    pioche[k] = pioche[k+1];
                }
            }
        }
    }
}

void role_joueurs(Joueur *joueurs, int nbjoueurs) {
    int i, k, random;
    int taille = 0;
    TypeJoueur pioche[6];
    srand(time(NULL));
    ajouter_pioche(pioche, &taille, J_GARDIEN);
    ajouter_pioche(pioche, &taille, J_PRISONNIER);
    ajouter_pioche(pioche, &taille, J_PRISONNIER);
    ajouter_pioche(pioche, &taille, J_PRISONNIER);
    ajouter_pioche(pioche, &taille, J_PRISONNIER);
    if(nbjoueurs >= 5)
        ajouter_pioche(pioche, &taille, J_GARDIEN);
    for(i = 0; i < nbjoueurs; i++) {
        random = rand() % taille;
        joueurs[i].type = pioche[random];
        taille--;
        for(k = random; k < taille; k++) {
            pioche[k] = pioche[k+1];
        }
    }
}

void init_joueurs(Joueur *joueurs, int nbjoueurs) {
    int i;
    for(i = 0; i < nbjoueurs; i++) {
        joueurs[i].mort = 0;
        joueurs[i].posx = 2;
        joueurs[i].posy = 2;
        joueurs[i].type = J_NORMAL;
    }
}

void action(Joueur *joueurs, int nbjoueurs, int debut, Salle complexe[][5]) {
    int i, j, n;
    Salle tmp;
    for(n = 0; n < 2; n++) {
        for(i = 0; i < nbjoueurs; i++) {
            if(joueurs[(i+debut)%nbjoueurs].type == J_GARDIEN) {
                //programmation
            }
            switch(joueurs[(i+debut)%nbjoueurs].action[n]) {
            case A_DEPLACER:
                switch(joueurs[(i+debut)%nbjoueurs].dir[n]) {
                case D_HAUT:
                    joueurs[(i+debut)%nbjoueurs].posy--;
                    break;
                case D_BAS:
                    joueurs[(i+debut)%nbjoueurs].posy++;
                    break;
                case D_GAUCHE:
                    joueurs[(i+debut)%nbjoueurs].posx--;
                    break;
                case D_DROITE:
                    joueurs[(i+debut)%nbjoueurs].posx++;
                    break;
                }
                break;
            case A_POUSSER:
                switch(joueurs[(i+debut)%nbjoueurs].dir[n]) {
                case D_HAUT:
                    joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posy = (joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posy - 1)%5;
                    break;
                case D_BAS:
                    joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posy = (joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posy + 1)%5;
                    break;
                case D_GAUCHE:
                    joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posx = (joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posx - 1)%5;
                    break;
                case D_DROITE:
                    joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posx = (joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posx + 1)%5;
                    break;
                }
                break;
            case A_REGARDER:
                switch(joueurs[(i+debut)%nbjoueurs].dir[n]) {
                case D_HAUT:
                    //Regarder haut
                    break;
                case D_BAS:
                    //Regarder bas
                    break;
                case D_GAUCHE:
                    //Regarder gauche
                    break;
                case D_DROITE:
                    //Regarder droite
                    break;
                }
                break;
            case A_CONTROLER:
                switch(joueurs[(i+debut)%nbjoueurs].dir[n]) {
                case D_HAUT:
                    tmp = complexe[joueurs[(i+debut)%nbjoueurs].posx][0];
                    for(j = 0; j < 4; j++) {
                        complexe[joueurs[(i+debut)%nbjoueurs].posx][j] = complexe[joueurs[(i+debut)%nbjoueurs].posx][j+1];
                    }
                    complexe[joueurs[(i+debut)%nbjoueurs].posx][4] = tmp;
                    for(j = 0; j < nbjoueurs; j++) {
                        if(joueurs[j].posx = joueurs[(i+debut)%nbjoueurs].posx)
                            joueurs[j].posy = (joueurs[j].posy - 1)%5;
                    }
                    break;
                case D_BAS:
                    tmp = complexe[joueurs[(i+debut)%nbjoueurs].posx][4];
                    for(j = 4; j > 0; j--) {
                        complexe[joueurs[(i+debut)%nbjoueurs].posx][j] = complexe[joueurs[(i+debut)%nbjoueurs].posx][j-1];
                    }
                    complexe[joueurs[(i+debut)%nbjoueurs].posx][0] = tmp;
                    for(j = 0; j < nbjoueurs; j++) {
                        if(joueurs[j].posx = joueurs[(i+debut)%nbjoueurs].posx)
                            joueurs[j].posy = (joueurs[j].posy + 1)%5;
                    }
                    break;
                case D_GAUCHE:
                    tmp = complexe[0][joueurs[(i+debut)%nbjoueurs].posy];
                    for(j = 0; j < 4; j++) {
                        complexe[j][joueurs[(i+debut)%nbjoueurs].posy] = complexe[j+1][joueurs[(i+debut)%nbjoueurs].posy];
                    }
                    complexe[4][joueurs[(i+debut)%nbjoueurs].posy] = tmp;
                    for(j = 0; j < nbjoueurs; j++) {
                        if(joueurs[j].posy = joueurs[(i+debut)%nbjoueurs].posy)
                            joueurs[j].posx = (joueurs[j].posx - 1)%5;
                    }
                    break;
                case D_DROITE:
                    tmp = complexe[4][joueurs[(i+debut)%nbjoueurs].posy];
                    for(j = 4; j > 0; j--) {
                        complexe[j][joueurs[(i+debut)%nbjoueurs].posy] = complexe[j-1][joueurs[(i+debut)%nbjoueurs].posy];
                    }
                    complexe[0][joueurs[(i+debut)%nbjoueurs].posy] = tmp;
                    for(j = 0; j < nbjoueurs; j++) {
                        if(joueurs[j].posy = joueurs[(i+debut)%nbjoueurs].posy)
                            joueurs[j].posx = (joueurs[j].posx + 1)%5;
                    }
                    break;
                }
                break;
            }
        }
    }
}

void jouer() {
    Salle complexe[5][5];
    Joueur joueurs[6];
    Mode mode;
    int nbjoueurs, expert, fini, debut;
    fini = 0;
    debut = 0;
    //Choix du mode
    //Choix des joueurs
    init_joueurs(joueurs, nbjoueurs);
    if(mode = M_SUSPISCION)
        role_joueurs(joueurs, nbjoueurs);
    creer_complexe(complexe, mode, expert);
    //Afficher complexe
    //Indice de départ
    while(!fini) {
        //Programmation
        //Action
        action(joueurs, nbjoueurs, debut, complexe);
        //Décompte
        debut = (debut + 1) % nbjoueurs;
    }
}
